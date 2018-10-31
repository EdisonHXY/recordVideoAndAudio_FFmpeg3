using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Sample_CamDLL_ImageProcesing_WPF.Models;
using System.Collections.ObjectModel;

namespace CamDLLHelper
{
    public class CamDLL
    {
        public delegate bool FrameReceivedHandler(IntPtr src, int width, int height, int size);

        public delegate bool DeviceChangedHandler(IntPtr type);

        public delegate bool AutoCaptureHandler(int state);

        /// <summary>
        /// 异步指纹回调
        /// </summary>
        /// <returns></returns>
        public delegate bool AsynchronousCallback(IntPtr pBmpBuff, IntPtr pFeature, byte[] BmpBuff);


        /// <summary>
        /// 蜂鸣注册按键回调委托
        /// </summary>
        /// <param name="lData">1为按下，2为抬起</param>
        /// <returns></returns>
        public delegate bool callBackKeyRecept(int lData);
        /// <summary>
        /// 初始化
        /// </summary>
        /// <returns>0-,1-</returns>
        [DllImport("CmCapture.dll", EntryPoint = "camInitCameraLib", CallingConvention = CallingConvention.Cdecl)]
        public extern static int InitializeCamera();
        /// <summary>
        /// 反初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camUnInitCameraLib", CallingConvention = CallingConvention.Cdecl)]
        public extern static int DisposeCamera();
        /// <summary>
        /// 打开视频
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="subtype"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camOpenDev", CallingConvention = CallingConvention.Cdecl)]
        public static extern int OpenCamera(int devIndex, int subtype, int width, int height);
        /// <summary>
        /// 关闭视频
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camCloseDev", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CloseCamera(int devIndex);
        /// <summary>
        /// 注册回调
        /// </summary>
        /// <param name="index"></param>
        /// <param name="frameReceived"></param>
        [DllImport("CmCapture.dll", EntryPoint = "camRegOutCallBackGetPreviewImage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterFrameReceived(int index, FrameReceivedHandler frameReceived);
        /// <summary>
        /// 热插拔
        /// </summary>
        /// <param name="deviceChanged"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camRegOutCallBackDeviceChange", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RegisterDeviceChanged(DeviceChangedHandler deviceChanged);
        /// <summary>
        /// 获取设备个数
        /// </summary>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDeviceCount(ref int count);
        /// <summary>
        /// 获取图像设备名
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevName", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetDeviceName(int index);
        /// <summary>
        /// 获取设备类型
        /// </summary>
        /// <param name="index"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevType", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDeviceType(int index, ref int type);
        /// <summary>
        /// 获取视频格式个数
        /// </summary>
        /// <param name="index"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetMediaTypeCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDeviceVideoFormatCount(int index, ref int count);
        /// <summary>
        /// 获取视频格式名称
        /// </summary>
        /// <param name="index"></param>
        /// <param name="formatIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetMediaTypeName", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern string GetDeviceVideoFormatName(int index, int formatIndex);
        /// <summary>
        /// 获取分辨率个数
        /// </summary>
        /// <param name="index"></param>
        /// <param name="formatIndex"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetResolutionCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDeviceResolutionCount(int index, int formatIndex, ref int count);
        /// <summary>
        /// 获取指定分辨率
        /// </summary>
        /// <param name="index"></param>
        /// <param name="formatIndex"></param>
        /// <param name="resolutionIndex"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetResolution", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDeviceResolution(int index, int formatIndex, int resolutionIndex, ref int width, ref int height);
        /// <summary>
        /// 自动裁切
        /// </summary>
        /// <param name="index"></param>
        /// <param name="cropType"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetImageAutoCrop", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AutoCropArea(int index, int cropType);
        /// <summary>
        /// 自动对焦
        /// </summary>
        /// <param name="index"></param>
        /// <param name="focusType"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camAutoFocus", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AutoFocus(int index, int focusType);
        /// <summary>
        /// 拍照
        /// </summary>
        /// <param name="index"></param>
        /// <param name="path"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camCaptureImageFile", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SnapshotCapture(int index, StringBuilder path);
        /// <summary>
        /// 视频格式
        /// </summary>
        /// <param name="index"></param>
        /// <param name="formatIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetMediaType", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetDeviceVideoFormat(int index, int formatIndex);
        /// <summary>
        /// 设置视频分辨率
        /// </summary>
        /// <param name="index"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetResolution", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetDeviceResolution(int index, int width, int height);

        /// <summary>
        /// 设置自定义裁切区域
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="left"></param>
        /// <param name="top"></param>
        /// <param name="right"></param>
        /// <param name="bottom"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetImageCusCropRect", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetCropRectangle(int devIndex, int left, int top, int right, int bottom);

        /// <summary>
        /// 设置图像增强方式
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetImageAdjust", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetAdjust(int devIndex, int type = 1);
        /// <summary>
        /// 获取设备的VID
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="strVid"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevVid", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDevVid(int devIndex, StringBuilder strVid);
        /// <summary>
        /// 获取设备PID
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="strPid"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevPid", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDevPid(int devIndex, StringBuilder strPid);
        /// <summary>
        /// 设置旋转方向
        /// </summary>
        /// <param name="index"></param>
        /// <param name="rotateMode"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetImageRotateMode", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int RotateCapture(int index, int rotateMode);



        //Chad
        /// <summary>
        /// 原始比例
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camOriginalPreview(int devIndex);
        /// <summary>
        /// 最适比例
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camOptimalPreview(int devIndex);
        /// <summary>
        /// 获取麦克风格式名称
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="sEncodeName"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camGetVideoEncodeName(int devIndex, StringBuilder sEncodeName);
        /// <summary>
        /// 获取麦克风格式数量
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camGetVideoEncodeCount(ref int devIndex);
        /// <summary>
        /// 获取麦克风音量
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camGetMicrophoneVolumeLevel(int devIndex);
        /// <summary>
        /// 停止录制
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camStopRecord(int devIndex);
        /// <summary>
        /// 开始录制
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="filePath"></param>
        /// <param name="micphone"></param>
        /// <param name="videoFormat"></param>
        /// <param name="bRecordCam"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camStartRecord(int devIndex, string filePath, int micphone, int videoFormat, bool bRecordCam);
        /// <summary>
        /// 图片彩色格式
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camSetImageColorStyle(int devIndex, int type);
        /// <summary>
        /// 放大
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camZooIn(int devIndex);
        /// <summary>
        /// 缩小
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camZoomOut(int devIndex);
        /// <summary>
        /// 获取音频个数
        /// </summary>
        /// <param name="Count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camGetAudioDevCount(ref int Count);
        /// <summary>
        /// 获取音频设备名称
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr camGetAudioDevName(int devIndex);
        /// <summary>
        /// 弹出“视频属性”设置窗口
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camShowDevSettingWindow(int devIndex);
        /// <summary>
        /// 弹出“视频效果”设置窗口
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camShowImageSettingWindow(int devIndex);
        /// <summary>
        /// 设置JPG压缩率
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="quanlity"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camSetImageJPGQuanlity(int devIndex, int quanlity);
        /// <summary>
        /// 拍摄图像到内存
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="bpp"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr camCaptureImageBuff(int devIndex, ref int width, ref int height, ref int bpp);
        /// <summary>
        /// 内存数据保存为图片
        /// </summary>
        /// <param name="src"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="bpp"></param>
        /// <param name="filePath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camSaveImage(IntPtr src, int width, int height, int bpp, string filePath);
        /// <summary>
        /// 设置是否去噪
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="IsAvailabel"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camSetImageDenoise(int devIndex, bool IsAvailabel);
        /// <summary>
        /// 设置Dpi
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="xDPI"></param>
        /// <param name="yDPI"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camSetImageDPI(int devIndex, int xDPI, int yDPI);
        /// <summary>
        /// 蜂鸣
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="interval">摄像头 0 主头 1 副头</param>
        /// <param name="?">Count 次数 </param>
        /// <param name="Count">duration 鸣响时长，单位ms</param>
        /// <param name="duration">interval 鸣响间隔，单位ms</param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int camEnableBuzzer(int devIndex, int Count, int duration, int interval);
        /// <summary>
        /// 防篡改
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="IsAvailabel"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camSetImageFileSign", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetImageFileSign(int devIndex, bool IsAvailabel);
        /// <summary>
        /// 初始化，连接读卡器
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int idcardrfidInit();
        /// <summary>
        /// 反初始化，断开读卡器
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int idcardrfidUnInit();
        /// <summary>
        /// 获取指纹
        /// </summary>
        /// <param name="buffer"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "idcardrfidGetFingerprintMsg", CallingConvention = CallingConvention.Cdecl)]
        public static extern int IDCardrfidGetFingerprintMsg(IntPtr buffer, ref int count);
        /// <summary>
        /// 身份证信息
        /// </summary>
        /// <param name="Msg"></param>
        /// <param name="headerFilePath"></param>
        /// <returns></returns>
        ///CharSet = CharSet.Unicode
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int idcardrfidReadIDCard(IntPtr Msg, string headerFilePath);
        /// <summary>
        /// 指纹初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintInit();
        /// <summary>
        /// 指纹反初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintUnInit();
        /// <summary>
        /// 采集指纹
        /// </summary>
        /// <param name="pBmpBuff"></param>
        /// <param name="pRawData"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintGetImage(byte[] pBmpBuff, byte[] pRawData);
        /// <summary>
        /// 获取指纹特征值
        /// </summary>
        /// <param name="pRawData"></param>
        /// <param name="pFeatureData"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintGetFeature(byte[] pRawData, IntPtr pFeatureData);
        /// <summary>
        /// 指纹对比
        /// </summary>
        /// <param name="pFeature1"></param>
        /// <param name="pFeature2"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintContrast(IntPtr pFeature1, IntPtr pFeature2);
        /// <summary>
        /// 异步采集指纹
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintStartGetFPDataAsync(AsynchronousCallback callback, byte[] pUserData);
        /// <summary>
        /// 停止异步采集指纹
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fingerprintStopGetFPDataAsync();
        /// <summary>
        /// HTTP上传文件
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="url"></param>
        /// <param name="param"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camUpdataFileHttp", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UpdataFileHttp(string filePath, string url, string param, IntPtr response);
        /// <summary>
        /// FTP上传文件
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="url"></param>
        /// <param name="param"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camUpdataFileFtp", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UpdataFileFtp(string filePath, string ftpPath, string userName, string userPsd, string targetName);
        /// <summary>
        /// 获取SN
        /// </summary>
        /// <param name="devIndex"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetDevSN", CallingConvention = CallingConvention.Cdecl)]
        public static extern string GetDevSN(int devIndex);
        /// <summary>
        /// 写入SN
        /// </summary>
        /// <param name="devIndex"></param>
        /// <param name="sn"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camDevWriteSN", CallingConvention = CallingConvention.Cdecl)]
        public static extern string DevWriteSN(int devIndex, string sn);
        /// <summary>
        /// 多流录制
        /// </summary>
        /// <param name="arrCamID"></param>
        /// <param name="nCamIDCount"></param>
        /// <param name="filePath"></param>
        /// <param name="micphone"></param>
        /// <param name="videoFormat"></param>
        /// <param name="nCompressionRadio"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camStartMultiRecord", CallingConvention = CallingConvention.Cdecl)]
        public static extern int StartMultiRecord(int[] arrCamID, int nCamIDCount, string filePath, int micphone, int videoFormat, int nCompressionRadio = 25);
        //停止多流录制
        [DllImport("CmCapture.dll", EntryPoint = "camStopMultiRecord", CallingConvention = CallingConvention.Cdecl)]
        public static extern int StopMultiRecord();
        /// <summary>
        ///获取录制声音大小
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camGetMultiRecordMicrophoneVolumeLevel", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetMultiRecordMicrophoneVolumeLevel();
        /// <summary>
        /// 获取语言个数
        /// </summary>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrGetLanguageCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetLanguageCount(ref int count);
        /// <summary>
        /// 获取语言名称
        /// </summary>
        /// <param name="index"></param>
        /// <param name="name"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrGetLanguageName", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetLanguageName(int index, StringBuilder name);
        /// <summary>
        /// 将图片加入识别队列
        /// </summary>
        /// <param name="imagePath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrAddImageFileToOCRList", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddImageFileToOCRList(string imagePath);
        /// <summary>
        /// 识别队列中的图片并导出
        /// </summary>
        /// <param name="imagePath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrCombineToFile", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CombineToFile(string filePath, int nlanguage);
        /// <summary>
        /// 识别条码
        /// </summary>
        /// <param name="src"></param>
        /// <param name="codeType"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrRecognizeBarcode", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RecognizeBarcode(string src, int codeType, ref int count);
        /// <summary>
        /// 条码结果
        /// </summary>
        /// <param name="src"></param>
        /// <param name="cText"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "ocrGetBarcodeText", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetBarcodeText(int Index, StringBuilder cText, ref int size);
        /// <summary>
        /// 身份证初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "cardOCRInitIDCardOCR", CallingConvention = CallingConvention.Cdecl)]
        public static extern int OCRInitIDCardOCR();
        /// <summary>
        /// 识别身份证
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "cardOCRRecognizeIDCard_OCR", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr OCRRecognizeIDCard_OCR(string imagePath, string headerFilePath);
        /// <summary>
        /// 身份证反初始化
        /// </summary>
        /// <param name="?"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "cardOCRUnInitIDCardOCR", CallingConvention = CallingConvention.Cdecl)]
        public static extern string OCRUnInitIDCardOCR();
        /// <summary>
        /// 获取模板信息
        /// </summary>
        /// <param name="count"></param>
        /// <param name="chMsg"></param>
        /// <param name="nMsgSize"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrGetTemplateInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetTemplateInfo(int count, StringBuilder chMsg, ref int nMsgSize);
        /// <summary>
        /// 识别
        /// </summary>
        /// <param name="nIndex"></param>
        /// <param name="chPath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrRecog", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Recog(int nIndex, string chPath);
        /// <summary>
        /// 获取识别区域数量
        /// </summary>
        /// <param name="nCount"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrGetResultCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetResultCount(ref int nCount);
        /// <summary>
        /// 获取识别区域数量
        /// </summary>
        /// <param name="nIndex"></param>
        /// <param name="chName"></param>
        /// <param name="chResult"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrGetResultInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetResultInfo(int nIndex, StringBuilder chName, StringBuilder chResult);

        /// <summary>
        /// OTR初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Init();
        /// <summary>
        /// 获取模板数量
        /// </summary>
        /// <param name="nTCount"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrGetTemplateCount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetTemplateCount(ref int nTCount);
        /// <summary>
        /// OTR反初始化
        /// </summary>
        /// <param name="nTCount"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "otrUnInit", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UnInit();
        /// <summary>
        /// 蜂鸟模块初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "KeyOpenDevice", CallingConvention = CallingConvention.Cdecl)]
        public static extern int OpenDevice();
        /// <summary>
        /// 蜂鸟模块反初始化
        /// </summary>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "KeyCloseDevice", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CloseDevice();
        /// <summary>
        /// 注册按键回调
        /// </summary>
        /// <param name="funCB"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "KeyRegCallBackKeyRecept", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RegCallBackKeyRecept(callBackKeyRecept funCB);
        /// <summary>
        /// 设置提示灯工作模式
        /// </summary>
        /// <param name="bAuto"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "KeySetAutoLights", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetAutoLights(bool bAuto);
        /// <summary>
        /// 设置提示灯状态
        /// </summary>
        /// <param name="lState"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "KeySetLedState", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetLedState(int lState);
        /// <summary>
        /// 裁切纠偏
        /// </summary>
        /// <param name="lState"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camRotateImage", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RotateImage(string imageFilePath, int rotateMode);
        /// <summary>
        /// 图片文件加到PDF队列
        /// </summary>
        /// <param name="imageFilePath"></param>
        /// <param name="rotateMode"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camAddFileToPDFList", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddFileToPDFList(string filePath);
        /// <summary>
        /// 导出PDF文件
        /// </summary>
        /// <param name="pdfFilePath"></param>
        /// <param name="nJpegQuality"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camCombinePDF", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CombinePDF(string pdfFilePath, int nJpegQuality);
        /// <summary>
        /// 图片文件加到TIF队列
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camAddFileToTIFList", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddFileToTIFList(string filePath);
        /// <summary>
        /// 导出TIF文件
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        [DllImport("CmCapture.dll", EntryPoint = "camCombineTIF", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CombineTIF(string tifFilePath);
    }
}
