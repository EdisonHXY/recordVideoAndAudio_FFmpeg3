// CombinDemo.cpp : 定义控制台应用程序的入口点。
//

#pragma region 头文件

#include "stdafx.h"
#define __STDC_CONSTANT_MACROS
extern "C"
{
#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include "libavutil/timestamp.h"
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include "libavutil/error.h"


#include "libavdevice/avdevice.h"
#include "libavutil/audio_fifo.h"
#include "libavformat/avio.h"

#include "libavcodec/avcodec.h"

#include "libavutil/avstring.h"
#include "libavutil/frame.h"


#include "libswresample/swresample.h"
	//#include "SDL.h"
}

#include <Windows.h>  
#include <process.h>
#include<iostream>
// a wrapper around a single output AVStream
typedef struct OutputStream {
	AVStream *st;
	AVCodecContext *enc;

	/* pts of the next frame that will be generated */
	int64_t next_pts;
	int samples_count;

	AVFrame *frame;
	AVFrame *tmp_frame;

	float t, tincr, tincr2;

	struct SwsContext *sws_ctx;
	struct SwrContext *swr_ctx;
} OutputStream;

#pragma endregion 

#pragma region 全局变量

bool g_isHaveBuffer = false;
byte * g_srcBuffer = NULL;


bool g_isHaveAudioBuffer = false;
bool g_isStop = false;
CRITICAL_SECTION g_AudioBuffer_SECTION;
CRITICAL_SECTION g_VideoBuffer_SECTION;
CRITICAL_SECTION g_WaitThred_SECTION;

AVAudioFifo     *g_fifo_audio = NULL;

AVFormatContext *g_pFormatCtx_Audio = NULL, *g_pFormatCtx_Out = NULL;  
OutputStream g_video_stream_out = { 0 }, g_audio_stream_out = { 0 };
AVDictionary* g_outPutParam;
AVCodecContext *g_input_codec_context_audio = NULL;
SwrContext *g_resample_context = NULL;

bool g_isSaveAudio = false;

AVPacket *g_audioPack = NULL;

//SDL_Window *g_screen = NULL;
//SDL_Renderer* g_sdlRenderer = NULL;
//SDL_Texture* g_sdlTexture = NULL;

#pragma endregion 


#pragma region 可配置项

long g_deviceIndex = 0;
long g_videoW = 640;
long g_videoH = 480;
long g_subType = 1; //YUV

char g_outPutFileName[MAX_PATH] = "finish.mp4";

wchar_t* g_audioDevName = L"audio=ocean (Realtek High Definition Audio)";
/** The output bit rate in kbit/s */
#define OUTPUT_BIT_RATE 96000
/** The number of output channels */
#define OUTPUT_CHANNELS 2

#define STREAM_DURATION   
#define STREAM_FRAME_RATE 55/* 25 images/s */
#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */
#define SCALE_FLAGS SWS_BICUBIC

long g_SDLWindow_width = 640;
long g_SDLWindow_height = 480;

#pragma endregion 

#pragma region 其他

static char *dup_wchar_to_utf8(wchar_t *w)  
{  
	char *s = NULL;  
	int l = WideCharToMultiByte(CP_UTF8, 0, w, -1, 0, 0, 0, 0);  
	s = (char *) av_malloc(l);  
	if (s)  
		WideCharToMultiByte(CP_UTF8, 0, w, -1, s, l, 0, 0);  
	return s;  
} 

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt)
{
	AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;

	printf("pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
		av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
		av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
		av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
		pkt->stream_index);
}

#pragma endregion

#pragma region 采集视频流

int yuv422toyuv420(unsigned char *out, const unsigned char *in, unsigned int width, unsigned int height)
{
	unsigned char *y = out;
	unsigned char *u = out + width*height;
	unsigned char *v = out + width*height + width*height/4;

	unsigned int i,j;
	unsigned int base_h;
	unsigned int is_y = 1, is_u = 1;
	unsigned int y_index = 0, u_index = 0, v_index = 0;

	unsigned long yuv422_length = 2 * width * height;

	//序列为YU YV YU YV，一个yuv422帧的长度 width * height * 2 个字节
	//丢弃偶数行 u v

	for(i=0; i<yuv422_length; i+=2){
		if (g_isStop)
		{
			return 0;
		}
		*(y+y_index) = *(in+i);
		y_index++;
	}

	for(i=0; i<height; i+=2){
		base_h = i*width*2;
		for(j=base_h+1; j<base_h+width*2; j+=2){
			if (g_isStop)
			{
				return 0;
			}
			if(is_u){
				*(u+u_index) = *(in+j);
				u_index++;
				is_u = 0;
			}
			else{
				*(v+v_index) = *(in+j);
				v_index++;
				is_u = 1;
			}
		}
	}

	return 1;
}

bool CALLBACK PreviewImage(byte * src,long width,long height,long size)
{
	if (g_isStop)
	{
		return false;
	}
		g_isHaveBuffer = true;


	EnterCriticalSection(&g_VideoBuffer_SECTION); 
	static byte  *destion= new byte[size];

	yuv422toyuv420(destion,src,width,height);
	g_srcBuffer = destion;
	LeaveCriticalSection(&g_VideoBuffer_SECTION);
	
	return true;
}

CmCaptureHelper m_CaptureHelper;
bool LoadSDK()
{
	if (m_CaptureHelper.IsAvailable())
	{
		return true;
	}

	bool isLoad = m_CaptureHelper.Load("./SDK/CmCapture.dll");
	if (!isLoad)
	{
		printf("加载SDK fail");
	}
	return isLoad;
}

int InitVideoSDK()
{

	long re = m_CaptureHelper.camInitCameraLib();
	if (re != 0)
	{
		printf("camInitCameraLib fail");
	}
	return re;
}

int StartVideo()
{
	InitializeCriticalSection(&g_VideoBuffer_SECTION);
	bool re = LoadSDK();
	if (!re)
	{
		return 1;
	}
	int ret = InitVideoSDK();
	
	 ret = m_CaptureHelper.camOpenDev(g_deviceIndex,g_subType,g_videoW,g_videoH);
	if (ret != 0)
	{
		printf("camOpenDev fail");
		return 1;
	}


	m_CaptureHelper.camRegCallBackPreviewImage(g_deviceIndex,PreviewImage);
}
#pragma endregion 

#pragma region 采集音频流

/** Initialize a FIFO buffer for the audio samples to be encoded. */
static int init_fifo(AVAudioFifo **fifo, AVCodecContext *output_codec_context)
{
	/** Create the FIFO buffer based on the specified output sample format. */
	if (!(*fifo = av_audio_fifo_alloc(output_codec_context->sample_fmt,
		output_codec_context->channels, 1))) {
			fprintf(stderr, "Could not allocate FIFO\n");
			return AVERROR(ENOMEM);
	}
	return 0;
}
static int init_input_frame(AVFrame **frame)
{
	if (!(*frame = av_frame_alloc())) {
		fprintf(stderr, "Could not allocate input frame\n");
		return AVERROR(ENOMEM);
	}
	return 0;
}
static void init_packet(AVPacket *packet)
{
	av_init_packet(packet);
	/** Set the packet data and size so that it is recognized as being empty. */
	packet->data = NULL;
	packet->size = 0;
}
/**
 * Initialize a temporary storage for the specified number of audio samples.
 * The conversion requires temporary storage due to the different format.
 * The number of audio samples to be allocated is specified in frame_size.
 */
static int init_converted_samples(uint8_t ***converted_input_samples,
                                  AVCodecContext *output_codec_context,
                                  int frame_size)
{
    int error;

    /**
     * Allocate as many pointers as there are audio channels.
     * Each pointer will later point to the audio samples of the corresponding
     * channels (although it may be NULL for interleaved formats).
     */
    if (!(*converted_input_samples = (uint8_t**)calloc(output_codec_context->channels,
                                            sizeof(**converted_input_samples)))) {
        fprintf(stderr, "Could not allocate converted input sample pointers\n");
        return AVERROR(ENOMEM);
    }

    /**
     * Allocate memory for the samples of all channels in one consecutive
     * block for convenience.
     */
    if ((error = av_samples_alloc(*converted_input_samples, NULL,
                                  output_codec_context->channels,
                                  frame_size,
                                  output_codec_context->sample_fmt, 0)) < 0) {
        fprintf(stderr,
                "Could not allocate converted input samples (error '%s')\n",
                av_err2str(error));
        av_freep(&(*converted_input_samples)[0]);
        free(*converted_input_samples);
        return error;
    }
    return 0;
}

/**
 * Convert the input audio samples into the output sample format.
 * The conversion happens on a per-frame basis, the size of which is specified
 * by frame_size.
 */
static int convert_samples(const uint8_t **input_data,
                           uint8_t **converted_data, const int frame_size,
                           SwrContext *resample_context)
{
    int error;

    /** Convert the samples using the resampler. */
    if ((error = swr_convert(resample_context,
                             converted_data, frame_size,
                             input_data    , frame_size)) < 0) {
        fprintf(stderr, "Could not convert input samples (error '%s')\n",
                av_err2str(error));
        return error;
    }

    return 0;
}

/** Add converted input audio samples to the FIFO buffer for later processing. */
static int add_samples_to_fifo(AVAudioFifo *fifo,
                               uint8_t **converted_input_samples,
                               const int frame_size)
{
    int error;

    /**
     * Make the FIFO as large as it needs to be to hold both,
     * the old and the new samples.
     */
    if ((error = av_audio_fifo_realloc(fifo, av_audio_fifo_size(fifo) + frame_size)) < 0) {
        fprintf(stderr, "Could not reallocate FIFO\n");
        return error;
    }

    /** Store the new samples in the FIFO buffer. */
    if (av_audio_fifo_write(fifo, (void **)converted_input_samples,
                            frame_size) < frame_size) {
        fprintf(stderr, "Could not write data to FIFO\n");
        return AVERROR_EXIT;
    }
    return 0;
}

/** Decode one audio frame from the input file. */
static int decode_audio_frame(AVFrame *frame,
                              AVFormatContext *input_format_context,
                              AVCodecContext *input_codec_context,
                              int *data_present, int *finished)
{
    /** Packet used for temporary storage. */
    AVPacket input_packet;
    int error;
    init_packet(&input_packet);

    /** Read one audio frame from the input file into a temporary packet. */
    if ((error = av_read_frame(input_format_context, &input_packet)) < 0) {
        /** If we are at the end of the file, flush the decoder below. */
        if (error == AVERROR_EOF)
            *finished = 1;
        else {
            fprintf(stderr, "Could not read frame (error '%s')\n",
                    av_err2str(error));
            return error;
        }
    }

    /**
     * Decode the audio frame stored in the temporary packet.
     * The input audio stream decoder is used to do this.
     * If we are at the end of the file, pass an empty packet to the decoder
     * to flush it.
     */
    if ((error = avcodec_decode_audio4(input_codec_context, frame,
                                       data_present, &input_packet)) < 0) {
        fprintf(stderr, "Could not decode frame (error '%s')\n",
                av_err2str(error));
        av_packet_unref(&input_packet);
        return error;
    }

    /**
     * If the decoder has not been flushed completely, we are not finished,
     * so that this function has to be called again.
     */
    if (*finished && *data_present)
        *finished = 0;
    av_packet_unref(&input_packet);
    return 0;
}

/**
 * Read one audio frame from the input file, decodes, converts and stores
 * it in the FIFO buffer.
 */
static int read_decode_convert_and_store(AVAudioFifo *fifo,
                                         AVFormatContext *input_format_context,
                                         AVCodecContext *input_codec_context,
                                         AVCodecContext *output_codec_context,
                                         SwrContext *resampler_context,
                                         int *finished)
{
    /** Temporary storage of the input samples of the frame read from the file. */
    AVFrame *input_frame = NULL;
    /** Temporary storage for the converted input samples. */
    uint8_t **converted_input_samples = NULL;
    int data_present;
    int ret = AVERROR_EXIT;
	
    /** Initialize temporary storage for one input frame. */
    if (init_input_frame(&input_frame))
        goto cleanup;

    /** Decode one frame worth of audio samples. */
    if (decode_audio_frame(input_frame, input_format_context,
                           input_codec_context, &data_present, finished))
        goto cleanup;
    /**
     * If we are at the end of the file and there are no more samples
     * in the decoder which are delayed, we are actually finished.
     * This must not be treated as an error.
     */
    if (*finished && !data_present) {
        ret = 0;
        goto cleanup;
    }
    /** If there is decoded data, convert and store it */
    if (data_present) {
        /** Initialize the temporary storage for the converted input samples. */
        if (init_converted_samples(&converted_input_samples, output_codec_context,
                                   input_frame->nb_samples))
            goto cleanup;

        /**
         * Convert the input samples to the desired output sample format.
         * This requires a temporary storage provided by converted_input_samples.
         */
        if (convert_samples((const uint8_t**)input_frame->extended_data, converted_input_samples,
                            input_frame->nb_samples, resampler_context))
            goto cleanup;

        /** Add the converted input samples to the FIFO buffer for later processing. */
        if (add_samples_to_fifo(fifo, converted_input_samples,
                                input_frame->nb_samples))
            goto cleanup;
        ret = 0;
    }
    ret = 0;

cleanup:
    if (converted_input_samples) {
        av_freep(&converted_input_samples[0]);
        free(converted_input_samples);
    }
    av_frame_free(&input_frame);

    return ret;
}

static int init_output_frame(AVFrame **frame,
                             AVCodecContext *output_codec_context,
                             int frame_size)
{
    int error;

    /** Create a new frame to store the audio samples. */
    if (!(*frame = av_frame_alloc())) {
        fprintf(stderr, "Could not allocate output frame\n");
        return AVERROR_EXIT;
    }

    /**
     * Set the frame's parameters, especially its size and format.
     * av_frame_get_buffer needs this to allocate memory for the
     * audio samples of the frame.
     * Default channel layouts based on the number of channels
     * are assumed for simplicity.
     */
    (*frame)->nb_samples     = frame_size;
    (*frame)->channel_layout = output_codec_context->channel_layout;
    (*frame)->format         = output_codec_context->sample_fmt;
    (*frame)->sample_rate    = output_codec_context->sample_rate;

    /**
     * Allocate the samples of the created frame. This call will make
     * sure that the audio frame can hold as many samples as specified.
     */
    if ((error = av_frame_get_buffer(*frame, 0)) < 0) {
        fprintf(stderr, "Could not allocate output frame samples (error '%s')\n",
                av_err2str(error));
        av_frame_free(frame);
        return error;
    }

    return 0;
}

/** Global timestamp for the audio frames */
static int64_t pts = 0;

/** Encode one frame worth of audio to the output file. */
static int encode_audio_frame(AVFrame *frame,
                              AVFormatContext *output_format_context,
                              AVCodecContext *output_codec_context,
                              int *data_present)
{
    /** Packet used for temporary storage. */
    AVPacket output_packet;
    int error;
    init_packet(&output_packet);

    /** Set a timestamp based on the sample rate for the container. */
    if (frame) {
        frame->pts = pts;
        pts += frame->nb_samples;
    }

    /**
     * Encode the audio frame and store it in the temporary packet.
     * The output audio stream encoder is used to do this.
     */
    if ((error = avcodec_encode_audio2(output_codec_context, &output_packet,
                                       frame, data_present)) < 0) {
        fprintf(stderr, "Could not encode frame (error '%s')\n",
                av_err2str(error));
        av_packet_unref(&output_packet);
        return error;
    }
	
    /** Write one audio frame from the temporary packet to the output file. */
    if (*data_present) {

		output_packet.stream_index = g_audio_stream_out.st->index;


		g_audioPack = &output_packet;
		log_packet(output_format_context,&output_packet);
		if ((error = av_write_frame(output_format_context, &output_packet)) < 0) {
			fprintf(stderr, "Could not write frame (error '%s')\n",
				av_err2str(error));
			av_packet_unref(&output_packet);

			
			return error;
		}

        av_packet_unref(&output_packet);
    }

    return 0;
}

static AVFrame *alloc_audio_frame(enum AVSampleFormat sample_fmt,
	uint64_t channel_layout,
	int sample_rate, int nb_samples)
{
	AVFrame *frame = av_frame_alloc();
	int ret;

	if (!frame) {
		fprintf(stderr, "Error allocating an audio frame\n");
		exit(1);
	}

	frame->format = sample_fmt;
	frame->channel_layout = channel_layout;
	frame->sample_rate = sample_rate;
	frame->nb_samples = nb_samples;

	if (nb_samples) {
		ret = av_frame_get_buffer(frame, 0);
		if (ret < 0) {
			fprintf(stderr, "Error allocating an audio buffer\n");
			exit(1);
		}
	}

	return frame;
}

static int load_encode_and_write(AVAudioFifo *fifo,
                                 AVFormatContext *output_format_context,
                                 AVCodecContext *output_codec_context)
{
	int nb_samples = 0;
    /** Temporary storage of the output samples of the frame written to the file. */
	if (output_codec_context->codec->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE)
		nb_samples = 10000;
	else
		nb_samples = output_codec_context->frame_size;

	AVFrame *output_frame = alloc_audio_frame(output_codec_context->sample_fmt, output_codec_context->channel_layout,
		output_codec_context->sample_rate, nb_samples);;
    /**
     * Use the maximum number of possible samples per frame.
     * If there is less than the maximum possible frame size in the FIFO
     * buffer use this number. Otherwise, use the maximum possible frame size
     */
    const int frame_size = FFMIN(av_audio_fifo_size(fifo),
                                 output_codec_context->frame_size);
    int data_written;

    /** Initialize temporary storage for one output frame. */
  /*  if (init_output_frame(&output_frame, output_codec_context, frame_size))
        return AVERROR_EXIT;*/

    /**
     * Read as many samples from the FIFO buffer as required to fill the frame.
     * The samples are stored in the frame temporarily.
     */
	//AVRational r = {1,1 };
	//if (av_compare_ts(g_audio_stream_out.next_pts, g_audio_stream_out.enc->time_base,
	//	STREAM_DURATION, r) >= 0)
	//{

	//	return 1;
	//}



    if (av_audio_fifo_read(fifo, (void **)output_frame->data, frame_size) < frame_size) {
        fprintf(stderr, "Could not read data from FIFO\n");
        av_frame_free(&output_frame);
        return AVERROR_EXIT;
    }

	for (int j = 0; j <output_frame->nb_samples; j++) {

		g_audio_stream_out.t     += g_audio_stream_out.tincr;
		g_audio_stream_out.tincr += g_audio_stream_out.tincr2;
	}

	output_frame->pts = g_audio_stream_out.next_pts;
	g_audio_stream_out.next_pts  += output_frame->nb_samples;


    /** Encode one frame worth of audio samples. */
   if (encode_audio_frame(output_frame, output_format_context,
                           output_codec_context, &data_written)) {
        av_frame_free(&output_frame);
        return AVERROR_EXIT;
    }

    av_frame_free(&output_frame);
    return 0;
}


void FuncAudio(void* parm)
{
	  AVAudioFifo *fifo = NULL;
	  if (init_fifo(&fifo, g_audio_stream_out.enc))
	  {

		  return;
	  }

	  while(!g_isStop)
	  {
		  if(::GetAsyncKeyState(VK_LSHIFT)) /* */
		  {

			  g_isStop = true;
			  break;
		  }
	
		  int finished                = 0;
		   const int output_frame_size = g_audio_stream_out.enc->frame_size;
		    while (av_audio_fifo_size(fifo) < output_frame_size  &&  !g_isStop) {
				if (read_decode_convert_and_store(fifo, g_pFormatCtx_Audio,
					g_input_codec_context_audio,
					g_audio_stream_out.enc,
					g_resample_context, &finished))
				{
					continue;
				}
			
			}
			g_isHaveAudioBuffer = true;

			while (av_audio_fifo_size(fifo) >= output_frame_size ||
				(av_audio_fifo_size(fifo) > 0))
			{
				if (g_isStop)
				{
					break;
				}

				/*	EnterCriticalSection(&g_AudioBuffer_SECTION);

				g_fifo_audio = fifo;
				LeaveCriticalSection(&g_AudioBuffer_SECTION);
				*/
				if (load_encode_and_write(fifo,g_pFormatCtx_Out,g_audio_stream_out.enc))
				{
					
					break;
				}
			
			}

	  }


}


/** Open an input file and the required decoder. */
static int open_dshowDevice(const char *filename,
	AVFormatContext **input_format_context,
	AVCodecContext **input_codec_context)
{
	AVCodecContext *avctx;
	AVCodec *input_codec;
	int error;
	AVInputFormat *ifmt = av_find_input_format("dshow");
	/** Open the input file to read from it. */
	if ((error = avformat_open_input(input_format_context, filename, ifmt,
		NULL)) < 0) {
			fprintf(stderr, "Could not open input file '%s' (error '%s')\n",
				filename, av_err2str(error));
			*input_format_context = NULL;
			return error;
	}

	/** Get information on the input file (number of streams etc.). */
	if ((error = avformat_find_stream_info(*input_format_context, NULL)) < 0) {
		fprintf(stderr, "Could not open find stream info (error '%s')\n",
			av_err2str(error));
		avformat_close_input(input_format_context);
		return error;
	}

	/** Make sure that there is only one stream in the input file. */
	if ((*input_format_context)->nb_streams != 1) {
		fprintf(stderr, "Expected one audio input stream, but found %d\n",
			(*input_format_context)->nb_streams);
		avformat_close_input(input_format_context);
		return AVERROR_EXIT;
	}

	/** Find a decoder for the audio stream. */
	if (!(input_codec = avcodec_find_decoder((*input_format_context)->streams[0]->codecpar->codec_id))) {
		fprintf(stderr, "Could not find input codec\n");
		avformat_close_input(input_format_context);
		return AVERROR_EXIT;
	}

	/** allocate a new decoding context */
	avctx = avcodec_alloc_context3(input_codec);
	if (!avctx) {
		fprintf(stderr, "Could not allocate a decoding context\n");
		avformat_close_input(input_format_context);
		return AVERROR(ENOMEM);
	}

	/** initialize the stream parameters with demuxer information */
	error = avcodec_parameters_to_context(avctx, (*input_format_context)->streams[0]->codecpar);
	if (error < 0) {
		avformat_close_input(input_format_context);
		avcodec_free_context(&avctx);
		return error;
	}

	/** Open the decoder for the audio stream to use it later. */
	if ((error = avcodec_open2(avctx, input_codec, NULL)) < 0) {
		fprintf(stderr, "Could not open input codec (error '%s')\n",
			av_err2str(error));
		avcodec_free_context(&avctx);
		avformat_close_input(input_format_context);
		return error;
	}

	/** Save the decoder context for easier access later. */
	*input_codec_context = avctx;

	return 0;
}



int StartAudio()
{
	InitializeCriticalSection(&g_AudioBuffer_SECTION);	
	int re = open_dshowDevice(dup_wchar_to_utf8(g_audioDevName),&g_pFormatCtx_Audio,&g_input_codec_context_audio);
	if (re )
	{
		return re;
	}
	
	return 0;
}

int CloseAudio()
{
	avformat_close_input(&g_pFormatCtx_Audio);
	if (g_pFormatCtx_Audio)
	{
		avformat_free_context(g_pFormatCtx_Audio);
	}

	if (g_input_codec_context_audio)
	{
		avcodec_free_context(&g_input_codec_context_audio);

	}

	return 0;
}


#pragma endregion 

#pragma region 操作流


static void add_stream(OutputStream *ost, AVFormatContext *oc,
                       AVCodec **codec,
                       enum AVCodecID codec_id)
{
    AVCodecContext *c;
    int i;

    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        exit(1);
    }

    ost->st = avformat_new_stream(oc, NULL);
    if (!ost->st) {
        fprintf(stderr, "Could not allocate stream\n");
        exit(1);
    }
    ost->st->id = oc->nb_streams-1;
    c = avcodec_alloc_context3(*codec);
    if (!c) {
        fprintf(stderr, "Could not alloc an encoding context\n");
        exit(1);
    }
    ost->enc = c;

    switch ((*codec)->type) {
    case AVMEDIA_TYPE_AUDIO:
		{

				c->channels       = OUTPUT_CHANNELS;
				c->channel_layout = av_get_default_channel_layout(OUTPUT_CHANNELS);
				c->sample_rate    = g_input_codec_context_audio->sample_rate;
				c->sample_fmt     = (*codec)->sample_fmts[0];
				c->bit_rate       = OUTPUT_BIT_RATE;

				/** Allow the use of the experimental AAC encoder */
				c->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

				/** Set the sample rate for the container. */
				ost->st->time_base.den = g_input_codec_context_audio->sample_rate;
				ost->st->time_base.num = 1;
				int error;
				if ((error = avcodec_open2(c, (*codec), NULL)) < 0) {
					fprintf(stderr, "Could not open output codec (error '%s')\n",
						av_err2str(error));
					break;
				}

				error = avcodec_parameters_from_context(ost->st->codecpar, c);
				if (error < 0) {
					fprintf(stderr, "Could not initialize stream parameters\n");
					break;
				}

			

		}

        break;

    case AVMEDIA_TYPE_VIDEO:
        c->codec_id = codec_id;

        c->bit_rate = 400000;
        /* Resolution must be a multiple of two. */
        c->width    = g_videoW;
        c->height   = g_videoH;


		ost->st->time_base.num = 1;
        ost->st->time_base.den = STREAM_FRAME_RATE;


        c->time_base       = ost->st->time_base;

        c->gop_size      = 12; /* emit one intra frame every twelve frames at most */
        c->pix_fmt       = STREAM_PIX_FMT;
        if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
            /* just for testing, we also add B-frames */
            c->max_b_frames = 2;
        }
        if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            /* Needed to avoid using macroblocks in which some coeffs overflow.
             * This does not happen with normal video, it just happens here as
             * the motion of the chroma plane does not match the luma plane. */
            c->mb_decision = 2;
        }
    break;

    default:
        break;
    }

    /* Some formats want stream headers to be separate. */
    if (oc->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
}


static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height)
{
	AVFrame *picture;
	int ret;

	picture = av_frame_alloc();
	if (!picture)
		return NULL;

	picture->format = pix_fmt;
	picture->width  = width;
	picture->height = height;

	/* allocate the buffers for the frame data */
	ret = av_frame_get_buffer(picture, 32);
	if (ret < 0) {
		fprintf(stderr, "Could not allocate frame data.\n");
		exit(1);
	}

	return picture;
}

static void open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost, AVDictionary *opt_arg)
{
    int ret;
    AVCodecContext *c = ost->enc;
    AVDictionary *opt = NULL;

    av_dict_copy(&opt, opt_arg, 0);

    /* open the codec */
    ret = avcodec_open2(c, codec, &opt);
    av_dict_free(&opt);
    if (ret < 0) {
        fprintf(stderr, "Could not open video codec: %s\n", av_err2str(ret));
        exit(1);
    }

    /* allocate and init a re-usable frame */
    ost->frame = alloc_picture(c->pix_fmt, c->width, c->height);
    if (!ost->frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    /* If the output format is not YUV420P, then a temporary YUV420P
     * picture is needed too. It is then converted to the required
     * output format. */
    ost->tmp_frame = NULL;
    if (c->pix_fmt != AV_PIX_FMT_YUV420P) {
        ost->tmp_frame = alloc_picture(AV_PIX_FMT_YUV420P, c->width, c->height);
        if (!ost->tmp_frame) {
            fprintf(stderr, "Could not allocate temporary picture\n");
            exit(1);
        }
    }

    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, c);
    if (ret < 0) {
        fprintf(stderr, "Could not copy the stream parameters\n");
        exit(1);
    }
}

void addAudioParamToOutFormat()
{
	 AVCodec *audio_codec;
	 add_stream(&g_audio_stream_out, g_pFormatCtx_Out, &audio_codec, g_pFormatCtx_Out->oformat->audio_codec);

}

void addVideoParamToOutFormat()
{
	AVCodec *video_codec;
	add_stream(&g_video_stream_out, g_pFormatCtx_Out, &video_codec, g_pFormatCtx_Out->oformat->video_codec);
	open_video(g_pFormatCtx_Out, video_codec, &g_video_stream_out, g_outPutParam);
}

static void close_stream(AVFormatContext *oc, OutputStream *ost)
{
	if (ost->enc)
	{
		avcodec_free_context(&ost->enc);
	}
	
	if (ost->frame)
	{
		av_frame_free(&ost->frame);

	}
	if (ost->tmp_frame)
	{
		av_frame_free(&ost->tmp_frame);

	}
	if (ost->sws_ctx)
	{
		sws_freeContext(ost->sws_ctx);

	}
	if (ost->swr_ctx)
	{
		swr_free(&ost->swr_ctx);

	}
}
#pragma endregion 

#pragma region 重采集
static int init_resampler(AVCodecContext *input_codec_context,
                          AVCodecContext *output_codec_context,
                          SwrContext **resample_context)
{
        int error;

        /**
         * Create a resampler context for the conversion.
         * Set the conversion parameters.
         * Default channel layouts based on the number of channels
         * are assumed for simplicity (they are sometimes not detected
         * properly by the demuxer and/or decoder).
         */
        *resample_context = swr_alloc_set_opts(NULL,
                                              av_get_default_channel_layout(output_codec_context->channels),
                                              output_codec_context->sample_fmt,
                                              output_codec_context->sample_rate,
                                              av_get_default_channel_layout(input_codec_context->channels),
                                              input_codec_context->sample_fmt,
                                              input_codec_context->sample_rate,
                                              0, NULL);
        if (!*resample_context) {
            fprintf(stderr, "Could not allocate resample context\n");
            return AVERROR(ENOMEM);
        }
        /**
        * Perform a sanity check so that the number of converted samples is
        * not greater than the number of samples to be converted.
        * If the sample rates differ, this case has to be handled differently
        */
        av_assert0(output_codec_context->sample_rate == input_codec_context->sample_rate);

        /** Open the resampler with the specified parameters. */
        if ((error = swr_init(*resample_context)) < 0) {
            fprintf(stderr, "Could not open resample context\n");
            swr_free(resample_context);
            return error;
        }
    return 0;
}
#pragma endregion 


#pragma region 合成流

int OpenOutPut()
{
	
	int ret = -1;
	avformat_alloc_output_context2(&g_pFormatCtx_Out, NULL, NULL, g_outPutFileName);
	if (!g_pFormatCtx_Out) {
		printf("Could not deduce output format from file extension: using MPEG.\n");
		avformat_alloc_output_context2(&g_pFormatCtx_Out, NULL, "mpeg", g_outPutFileName);
	}
	if (!g_pFormatCtx_Out)
		return 1;


	if (g_pFormatCtx_Out->oformat->video_codec != AV_CODEC_ID_NONE) {
		
		//配置视频的设置
		addVideoParamToOutFormat();
	}

	if (g_pFormatCtx_Out->oformat->audio_codec != AV_CODEC_ID_NONE) {
		//音频的设置
		addAudioParamToOutFormat();
		
	}
	
	/** Initialize the resampler to be able to convert audio sample formats. */
	if (init_resampler(g_input_codec_context_audio, g_audio_stream_out.enc,
		&g_resample_context))
	{
		return -1;

	}


	  av_dump_format(g_pFormatCtx_Out, 0, g_outPutFileName, 1);

	  if (!(g_pFormatCtx_Out->oformat->flags & AVFMT_NOFILE)) {
		  ret = avio_open(&g_pFormatCtx_Out->pb, g_outPutFileName, AVIO_FLAG_WRITE);
		  if (ret < 0) {
			  fprintf(stderr, "Could not open '%s': %s\n", g_outPutFileName,
				  av_err2str(ret));
			  return 1;
		  }
	  }

	  ret = avformat_write_header(g_pFormatCtx_Out, &g_outPutParam);

	  return ret;
}
/* Prepare a dummy image. */
static void fill_yuv_image(AVFrame *pict, int frame_index,
                           int width, int height)
{
	

	 EnterCriticalSection(&g_VideoBuffer_SECTION);

	if (g_srcBuffer !=NULL)
	{
	
		memccpy(pict->data[0],g_srcBuffer,sizeof(byte),width*height);
		memccpy(pict->data[1],g_srcBuffer+width*height,sizeof(byte),width*height/4);
		memccpy(pict->data[2],g_srcBuffer+width*height+width*height/4,sizeof(byte),width*height/4);
	}
	
	 LeaveCriticalSection(&g_VideoBuffer_SECTION);
}

static AVFrame *get_video_frame(OutputStream *ost)
{
    AVCodecContext *c = ost->enc;

    /* check if we want to generate more frames */
	//AVRational r = {1,1 };
 //   if (av_compare_ts(ost->next_pts, c->time_base,
 //                     STREAM_DURATION, r) >= 0)
 //       return NULL;

    /* when we pass a frame to the encoder, it may keep a reference to it
     * internally; make sure we do not overwrite it here */
    if (av_frame_make_writable(ost->frame) < 0)
        exit(1);

    if (c->pix_fmt != AV_PIX_FMT_YUV420P) {
        /* as we only generate a YUV420P picture, we must convert it
         * to the codec pixel format if needed */
        if (!ost->sws_ctx) {
            ost->sws_ctx = sws_getContext(c->width, c->height,
                                          AV_PIX_FMT_YUV420P,
                                          c->width, c->height,
                                          c->pix_fmt,
                                          SCALE_FLAGS, NULL, NULL, NULL);
            if (!ost->sws_ctx) {
                fprintf(stderr,
                        "Could not initialize the conversion context\n");
                exit(1);
            }
        }
        fill_yuv_image(ost->tmp_frame, ost->next_pts, c->width, c->height);
        sws_scale(ost->sws_ctx,
                  (const uint8_t * const *)ost->tmp_frame->data, ost->tmp_frame->linesize,
                  0, c->height, ost->frame->data, ost->frame->linesize);
    } else {
        fill_yuv_image(ost->frame, ost->next_pts, c->width, c->height);
    }

    ost->frame->pts = ost->next_pts++;

    return ost->frame;
}

static int write_frame(AVFormatContext *fmt_ctx, const AVRational *time_base, AVStream *st, AVPacket *pkt)
{
	/* rescale output packet timestamp values from codec to stream timebase */
	av_packet_rescale_ts(pkt, *time_base, st->time_base);
	pkt->stream_index = st->index;

	/* Write the compressed frame to the media file. */
	log_packet(fmt_ctx, pkt);
	return av_interleaved_write_frame(fmt_ctx, pkt);
}
static int write_video_frame(AVFormatContext *oc, OutputStream *ost)
{
	int ret;
	AVCodecContext *c;
	AVFrame *frame;
	int got_packet = 0;
	AVPacket pkt = { 0 };

	c = ost->enc;

	frame = get_video_frame(ost);

	av_init_packet(&pkt);
	
	/* encode the image */
	ret = avcodec_encode_video2(c, &pkt, frame, &got_packet);
	if (ret < 0) {
		fprintf(stderr, "Error encoding video frame: %s\n", av_err2str(ret));
		exit(1);
	}

	if (got_packet) {
		ret = write_frame(oc, &c->time_base, ost->st, &pkt);
	} else {
		ret = 0;
	}

	if (ret < 0) {
		fprintf(stderr, "Error while writing video frame: %s\n", av_err2str(ret));
	//	exit(1);
	}

	return (frame || got_packet) ? 0 : 1;
}
int GenerateOutFile(bool encode_video,bool encode_audio)
{
	while (encode_video || encode_audio) {

		if(::GetAsyncKeyState(VK_LSHIFT)) /* */
		{
			g_isStop = true;
			break;
		}

	if (g_video_stream_out.enc == NULL)
	{
		break;
	}
		if (encode_video &&
		(!encode_audio || av_compare_ts(g_video_stream_out.next_pts, g_video_stream_out.enc->time_base,
		g_audio_stream_out.next_pts, g_audio_stream_out.enc->time_base) <= 0))
		{

			encode_video = !write_video_frame(g_pFormatCtx_Out, &g_video_stream_out);

		}else
		{
			/*EnterCriticalSection(&g_AudioBuffer_SECTION);
			if (load_encode_and_write(g_fifo_audio,g_pFormatCtx_Out,g_audio_stream_out.enc))
			{

				continue;
			}
			LeaveCriticalSection(&g_AudioBuffer_SECTION);*/


		}
	}


	return 0;

}


#pragma endregion 


void FuncVideo(void* parm)
{
	EnterCriticalSection(&g_WaitThred_SECTION);

	int re = GenerateOutFile(true,true);

	g_isStop = true;

	if (!(g_pFormatCtx_Out->oformat->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_flush(g_pFormatCtx_Out->pb);


	av_write_trailer(g_pFormatCtx_Out);
	printf("write_trailer finish\n");


	if (!(g_pFormatCtx_Out->oformat->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_closep(&g_pFormatCtx_Out->pb);


	CloseAudio();

	m_CaptureHelper.camCloseDev(g_deviceIndex);
	m_CaptureHelper.camUnInitCameraLib();
	LeaveCriticalSection(&g_WaitThred_SECTION);
}


int main(int argc, char **argv)
{

	//printf("请输入最终生成的文件名：");
	//std::cin.get(g_outPutFileName,MAX_PATH);
	//printf(g_outPutFileName);

	av_register_all();
	avdevice_register_all();
	avformat_network_init();
	
	int re = StartVideo();

	re = StartAudio();
	re = OpenOutPut();
	InitializeCriticalSection(&g_WaitThred_SECTION);	

	_beginthread(FuncAudio,0,NULL);
	//_beginthread(FuncVideo,0,NULL);
	 re = GenerateOutFile(true,true);

	g_isStop = true;

	if (!(g_pFormatCtx_Out->oformat->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_flush(g_pFormatCtx_Out->pb);


	av_write_trailer(g_pFormatCtx_Out);
	printf("write_trailer finish\n");


	if (!(g_pFormatCtx_Out->oformat->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_closep(&g_pFormatCtx_Out->pb);


	CloseAudio();

	m_CaptureHelper.camCloseDev(g_deviceIndex);
	m_CaptureHelper.camUnInitCameraLib();
	//EnterCriticalSection(&g_WaitThred_SECTION);
	//LeaveCriticalSection(&g_WaitThred_SECTION);

	system("pause");

	return 0;
}

