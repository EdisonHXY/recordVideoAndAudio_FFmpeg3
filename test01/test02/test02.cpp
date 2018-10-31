// test02.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define __STDC_CONSTANT_MACROS
extern "C"
{
	#include "libavdevice/avdevice.h"
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libswscale/swscale.h"
	#include "libavutil/avutil.h"
	#include <libavutil/imgutils.h>
	#include "SDL.h"
};


#pragma comment(lib,"../../ffmpeg3.4.2/lib/avcodec.lib");
#pragma comment(lib,"../../ffmpeg3.4.2/lib/avdevice.lib");
#pragma comment(lib,"../../ffmpeg3.4.2/lib/avformat.lib");
#pragma comment(lib,"../../ffmpeg3.4.2/lib/swscale.lib");
#pragma comment(lib,"../../ffmpeg3.4.2/lib/avutil.lib");
#pragma comment(lib,"../../SDL/lib/SDL2.lib");

void readAllDic(AVDictionary *pDic)
{
	AVDictionaryEntry *t = NULL;
	while((t = av_dict_get(pDic, "", t, AV_DICT_IGNORE_SUFFIX)))
	{
		av_log(NULL, AV_LOG_DEBUG, "%s: %s", t->key, t->value);

	}

}

void show_dshow_device()
{
	AVFormatContext *pFormatCtx = avformat_alloc_context();
	AVDictionary* options = NULL;
	av_dict_set(&options,"list_devices","true",0);
	AVInputFormat *iformat = av_find_input_format("dshow");
	printf("========Device Info=============\n");
	avformat_open_input(&pFormatCtx,"video=dummy",iformat,&options);
	
	printf("================================\n");
	readAllDic(options);

}

void show_dshow_device_option()
{

	AVFormatContext *pFormatCtx = avformat_alloc_context();
	AVDictionary* options = NULL;
	av_dict_set(&options,"list_options","true",0);
	AVInputFormat *iformat = av_find_input_format("dshow");
	AVDeviceInfoList *plist = new AVDeviceInfoList();
	avdevice_list_devices(pFormatCtx,&plist);
	printf("asd");
}

int _tmain(int argc, _TCHAR* argv[])
{
	//FFmpeg
	AVFormatContext *pFormatCtx;
	int i,videoindex;
	AVCodec *pCodec;
	AVCodecContext	*pCodecCtx;
	AVPacket *packet;
	AVFrame *pFrame,*pFrameYUV;
	struct SwsContext *img_convert_ctx;
	unsigned char *out_buffer;
	//SDL
	int screen_w,screen_h;
	SDL_Window *screen; 
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
	SDL_Rect sdlRect;

	FILE *fp_yuv;
	int ret, got_picture;
	//char filepath[]="F:\\FFmpegDemo\\test01\\Debug\\test.mp4";
	
	av_register_all();
	avdevice_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	show_dshow_device();
	//show_dshow_device_option();
	AVInputFormat *ifmt=av_find_input_format("dshow");

	char *pVideoName = "video=Q1080";//"video=WebCam SC-10HDD12636N";//"video=Document Scanner";////

	 AVDictionary* options = NULL;
	 /*
	 av_dict_set(&options, "fflags", "nobuffer", 0);
	 av_dict_set(&options, "max_delay", "100000", 0);*/
	 av_dict_set(&options, "framerate", "15", 0);
	 //av_dict_set(&options, "input_format", "mjpeg", 0);
	 
	
	if(avformat_open_input(&pFormatCtx,pVideoName,ifmt,&options) < 0){
		printf("Couldn't open input stream.\n");
		system("pause");
		return -1;
	}
	if(avformat_find_stream_info(pFormatCtx,NULL)<0){
		printf("Couldn't find stream information.\n");
		system("pause");

		return -1;
	}
	for(i=0; i<pFormatCtx->nb_streams; i++) 
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
			videoindex=i;
			break;
		}
	if(videoindex==-1){
		

		printf("Didn't find a video stream.\n");
		system("pause");
		return -1;
	}

	pCodecCtx=pFormatCtx->streams[videoindex]->codec;
	pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec==NULL){

		printf("Codec not found.\n");
		system("pause");

		return -1;
	}

	if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
		printf("Could not open codec.\n");
		return -1;
	}
	pFrame=av_frame_alloc();
	pFrameYUV=av_frame_alloc();
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		
		printf( "Could not initialize SDL - %s\n", SDL_GetError()); 
		system("pause");
		return -1;
	
	}
	
	out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  pCodecCtx->width, pCodecCtx->height,1));
	av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,
	AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height,1);
	packet=(AVPacket *)av_malloc(sizeof(AVPacket));
	printf("--------------- File Information ----------------\n");	
	//av_dump_format(pFormatCtx,0,filepath,0);	
	printf("-------------------------------------------------\n");
	
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	fp_yuv=fopen("output.yuv","wb+"); 

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) 
	{ 
		printf( "Could not initialize SDL - %s\n", SDL_GetError());
		system("pause");
		return -1;	
	} 
	screen_w = pCodecCtx->width;
	screen_h = pCodecCtx->height;

	screen = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,		screen_w, screen_h,		SDL_WINDOW_OPENGL);
	
	sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,pCodecCtx->width,pCodecCtx->height);
	sdlRect.x=0;
	sdlRect.y=0;
	sdlRect.w=screen_w;
	sdlRect.h=screen_h;
	//SDL End----------------------
	while(av_read_frame(pFormatCtx, packet)>=0){
		if(packet->stream_index==videoindex){
						
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if(ret < 0){
				printf("Decode Error.\n");
				return -1;
			}
			if(got_picture){
				sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,pFrameYUV->data, pFrameYUV->linesize);	
				int y_size=pCodecCtx->width*pCodecCtx->height;  				
				//fwrite(pFrameYUV->data[0],1,y_size,fp_yuv);    //Y 				
				//fwrite(pFrameYUV->data[1],1,y_size/4,fp_yuv);  //U				
				//fwrite(pFrameYUV->data[2],1,y_size/4,fp_yuv);  //V
				SDL_UpdateYUVTexture(sdlTexture, &sdlRect,pFrameYUV->data[0], pFrameYUV->linesize[0],pFrameYUV->data[1], pFrameYUV->linesize[1],pFrameYUV->data[2], pFrameYUV->linesize[2]);
				SDL_RenderClear( sdlRenderer );  
				SDL_RenderCopy( sdlRenderer, sdlTexture,  NULL, &sdlRect);  
				SDL_RenderPresent( sdlRenderer ); 
				SDL_Delay(40);
			}

		}
			av_free_packet(packet);
	}

		while (1) {
				
					int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
					if (ret < 0)
						break;
					if (!got_picture)
						break;
					sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,pFrameYUV->data, pFrameYUV->linesize);

					int y_size=pCodecCtx->width*pCodecCtx->height;  				
					fwrite(pFrameYUV->data[0],1,y_size,fp_yuv);    //Y 				
					fwrite(pFrameYUV->data[1],1,y_size/4,fp_yuv);  //U				
					fwrite(pFrameYUV->data[2],1,y_size/4,fp_yuv);  //V
					SDL_UpdateYUVTexture(sdlTexture, &sdlRect,pFrameYUV->data[0], pFrameYUV->linesize[0],pFrameYUV->data[1], pFrameYUV->linesize[1],pFrameYUV->data[2], pFrameYUV->linesize[2]);
					SDL_RenderClear( sdlRenderer );  
					SDL_RenderCopy( sdlRenderer, sdlTexture,  NULL, &sdlRect);  
					SDL_RenderPresent( sdlRenderer ); 
					SDL_Delay(40);
		}
			sws_freeContext(img_convert_ctx);
			fclose(fp_yuv);
				SDL_Quit();
				av_frame_free(&pFrameYUV);
				av_frame_free(&pFrame);
				avcodec_close(pCodecCtx);
				avformat_close_input(&pFormatCtx);
	return 0;
}

