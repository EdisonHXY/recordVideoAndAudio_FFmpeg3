
#pragma once
#include "../MysherTools/DllParser.h"
#include "../MysherTools/DllXmlParser.h"
#include "../MysherTools/PathManager.h"

//cmcapture.h================
#include <string>
#include <vector>
using namespace std;
//

#include "./include/CmDefine.h"

#define NOT_FIND -99
////设备变换
//enum CAMSDK_DEVCHANGE
//{
//	DEVCHANGE_NONE = 0,			//无变化
//	DEVCHANGE_DEV				//列表变化，调用设备变化
//};

//视频预览回调
typedef bool (CALLBACK * callBackPreviewImage)(byte * src,long width,long height,long size); 

//设备热插拔回调
typedef bool (CALLBACK * callBackDevChange)(CAMSDK_DEVCHANGE deviceChangeType); 

//设备连拍
typedef bool (CALLBACK * callBackAutoCapture)(long state); 

//身份证
//#include "../CmIDCard_RFID/IDCard_RFID.h"
//typedef struct _BASE_MSG
//{
//	//UNI
//	wchar_t sName[20];
//	wchar_t sSex[4];
//	wchar_t sNation[20];
//	wchar_t sBirthdate[10];
//	wchar_t sAddr[50];
//	wchar_t sID[20];
//	wchar_t sOffice[30];
//	wchar_t sBeginDate[10];
//	wchar_t sEndDate[10];
//}BaseMsg;
//获取指纹特征值回调函数
typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData);
//==================================
class CmCaptureHelper
{
public:
	//从当前模块路径加载DL（DLL名称由配置文件决定）
	//bool Load()
	//{
	//	std::string strMysherFile = "CmCapture";
	//	std::string strName = DllXmlParser::GetDllName(strMysherFile);
	//	std::string strPath = PathManager::GetAppPath();
	//	std::string strFullPath = strPath + strName + ".dll";
	//	return this->Load(strFullPath.c_str());
	//}

	//加载DLL
	//参数说明:
	//strDllPath：DLL完整路径，如D:\\MysherImage.dll
	bool Load(const char* strDllPath)
	{
		this->m_bInit =  m_dllParser.Load(strDllPath);
		//if(this->IsAvailable())
		//{
		//	if(!mcvInit())
		//	{
		//		this->m_bInit = false;
		//		m_dllParser.UnLoad();

		//	}
		//}
		return this->m_bInit;
	}

	//判断DLL是否可用
	bool IsAvailable()
	{
		return this->m_bInit;
	}

	//视频函数
	long  camInitCameraLib()
	{
		auto fun = m_dllParser.GetFunction<long()>("camInitCameraLib");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long  camUnInitCameraLib()
	{
		auto fun = m_dllParser.GetFunction<long()>("camUnInitCameraLib");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long camGetDevCount(long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long &)>("camGetDevCount");
		if(fun != 0)
		{
			return fun(count);
		}
		return -99;
	}
	long camGetAudioDevCount(long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long &)>("camGetAudioDevCount");
		if(fun != 0)
		{
			return fun(count);
		}
		return -99;
	}
	long camGetDevType(long devIndex ,long & type)
	{
		auto fun = m_dllParser.GetFunction<long(long,long &)>("camGetDevType");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}
	char * camGetDevName(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetDevName");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}
	char * camGetAudioDevName(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetAudioDevName");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}
	long camGetDevVid(long devIndex ,char * strvid)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("camGetDevVid");
		if(fun != 0)
		{
			return fun(devIndex,strvid);
		}
		return -99;
	}
	long camGetDevPid(long devIndex ,char * strpid)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("camGetDevPid");
		if(fun != 0)
		{
			return fun(devIndex,strpid);
		}
		return -99;
	}
	//打开视频设备
	//返回值:是否打开成功
	//参数:index:设备编号 默认开启最大视频
	//是否打开成功
	//mediaType 默认通过配置文件 默认最大分辨率
	long camOpenDev(long devIndex ,long subtype,long width,long height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long)>("camOpenDev");
		if(fun != 0)
		{
			return fun(devIndex,subtype,width,height);
		}
		return -99;
	}

	long camSetPreviewWindow(long devIndex  ,HWND hPreviewWindow)
	{
		auto fun = m_dllParser.GetFunction<long(long,HWND)>("camSetPreviewWindow");
		if(fun != 0)
		{
			return fun(devIndex,hPreviewWindow);
		}
		return -99;
	}
//关闭视频设备
//返回值:是否关闭成功
	long camCloseDev(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camCloseDev");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}


//获取视频格式个数
//返回值: 视频格式个数
	long camGetMediaTypeCount(long devIndex ,long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long,long &)>("camGetMediaTypeCount");
		if(fun != 0)
		{
			return fun(devIndex,count);
		}
		return -99;
	}
//获取视频格式名称
//参数:index 视频格式
//返回值:分辨率宽
	char * camGetMediaTypeName(long devIndex  ,long index)
	{
		auto fun = m_dllParser.GetFunction<char *(long,long)>("camGetMediaTypeName");
		if(fun != 0)
		{
			return fun(devIndex,index);
		}
		return NULL;
	}


//获取分辨率个数
//返回值:分辨率个数
	long camGetResolutionCount(long devIndex ,long subtype ,long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long &)>("camGetResolutionCount");
		if(fun != 0)
		{
			return fun(devIndex,subtype,count);
		}
		return -99;
	}
//获取制定分辨率宽
//参数:index 分辨率编号
//返回值:分辨率宽
	long camGetResolution(long devIndex ,long subtype,long index,long & width,long & height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long &,long &)>("camGetResolution");
		if(fun != 0)
		{
			return fun(devIndex,subtype,index,width,height);
		}
		return -99;
	}

//设置视频格式
//参数: 视频格式
//返回值:是否设置成功
	long camSetMediaType(long devIndex  ,long subtype)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetMediaType");
		if(fun != 0)
		{
			return fun(devIndex,subtype);
		}
		return -99;
	}

	long camSetResolution( long devIndex,long width,long height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long)>("camSetResolution");
		if(fun != 0)
		{
			return fun(devIndex,width,height);
		}
		return -99;
	}

	bool camIsStillPin(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<bool(long)>("camIsStillPin");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return false;
	}
	long camEnableStillPin(long devIndex, long IsEnable)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camEnableStillPin");
		if(fun != 0)
		{
			return fun(devIndex,IsEnable);
		}
		return -99;
	}
	long camSetPreviewResolution(long devIndex,long width,long height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long)>("camSetPreviewResolution");
		if(fun != 0)
		{
			return fun(devIndex,width,height);
		}
		return -99;
	}

	long camSetPreviewMediaType(long devIndex,long subtypeIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetPreviewMediaType");
		if(fun != 0)
		{
			return fun(devIndex,subtypeIndex);
		}
		return -99;
	}

	long camGetCurResolution(long devIndex  ,long & subtype,long & width,long & height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long &,long &,long &)>("camGetCurResolution");
		if(fun != 0)
		{
			return fun(devIndex,subtype,width,height);
		}
		return -99;
	}
//录像
//返回值:是否成功开启录像
	long camStartRecord(long devIndex ,char * filePath,long micphone,long videoFormat)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *,long,long)>("camStartRecord");
		if(fun != 0)
		{
			return fun(devIndex,filePath,micphone,videoFormat);
		}
		return -99;
	}
//关闭录像
//返回值:是否成功关闭录像
	long camStopRecord(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camStopRecord");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}

	//录像时获得麦克风音量
	long camGetMicrophoneVolumeLevel(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camGetMicrophoneVolumeLevel");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
#pragma endregion 视频函数


#pragma region 设备控制
/**@brief 获取授权信息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] license授权信息
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
	long camDevGetDevLicense(int devIndex,char * license)
	{
		auto fun = m_dllParser.GetFunction<long(int, char *)>("camDevGetDevLicense");
		if(fun != 0)
		{
			return fun(devIndex,license);
		}
		return NULL;
	}
/**@brief 获取授权信息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] license授权信息
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
	long camDevGetFaceLicense(int devIndex,char* license)
	{
		auto fun = m_dllParser.GetFunction<long(int, char *)>("camDevGetFaceLicense");
		if(fun != 0)
		{
			return fun(devIndex,license);
		}
		return NULL;
	}
/**@brief 写入授权信息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] license授权信息
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
	long camDevWriteFaceLicense(int devIndex,char* license)
	{
		auto fun = m_dllParser.GetFunction<long(int, char *)>("camDevWriteFaceLicense");
		if(fun != 0)
		{
			return fun(devIndex,license);
		}
		return NULL;
	}
/**@brief 获取自定义信息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] customer用户自定义信息
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
	long camDevGetDevCustomer(int devIndex,char * customer)
	{
		auto fun = m_dllParser.GetFunction<long(int, char *)>("camDevGetDevCustomer");
		if(fun != 0)
		{
			return fun(devIndex,customer);
		}
		return NULL;
	}
/**@brief 写入自定义信息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] customer自定义信息
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
	long camDevWriteCustomer(int devIndex,char * customer)
	{
		auto fun = m_dllParser.GetFunction<long(int, char *)>("camDevWriteCustomer");
		if(fun != 0)
		{
			return fun(devIndex,customer);
		}
		return NULL;
	}

//设备控制(5)
//获取设备SN
//返回值:设备SN号
	char *camGetDevSN(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetDevSN");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}

//设备控制(5)
//获取设备SN
//返回值:设备SN号
	char *camGetDevCusSN(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetDevCusSN");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}
/**@brief 写入自定义序列号
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] customersn自定义序列号
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
long camDevWriteCustomerSN(int devIndex,char * customersn)
{
	auto fun = m_dllParser.GetFunction<long(int ,char*)>("camDevWriteCustomerSN");
	if(fun != 0)
	{
		return fun(devIndex,customersn);
	}
	return NULL;
}
//设置UVC驱动视频效果
//参数:para1 0 CameraContrl  1 Video Proc Amp
// para2 :根据参数1变化
//para1 = 0 para2
//	亮度 0
//	对比度 1
//	色相 2
//	饱和度 3
//	清晰度 4
//	Gamma 5
//	启用颜色 6
//	白平衡	7
//	背光补偿	8
//	增益	9
//
//	para1 = 1 para2
//	全景 0
//	倾斜 1
//	滚动 2
//	缩放 3
//	曝光 4
//	低照度补偿 5
//	对焦 6
	//lvalue:需要写入的数据值
	//flag:0 手动 1 自动
	long camSetVideoParameter(long devIndex  ,long para1,long para2,long lvalue,long flag)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long,long)>("camSetVideoParameter");
		if(fun != 0)
		{
			return fun(devIndex,para1,para2,lvalue,flag);
		}
		return -99;
	}
//获取UVC驱动视频效果
/**@brief 获取UVC驱动视频效果 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] para1 0：视频Proc Amp ， 1：摄像头控制CameraContrl
*@param [in] para2
	- Video Proc Amp的属性项：0-亮度，1-对比度，2-色相，3-饱和度，4-清晰度，5-伽玛，6-启用颜色，7-白平衡，8-背光补偿，9-增益。
	- CameraContrl的属性项：0-全景，1-倾斜，2-滚动，3-缩放，4-曝光，5-低照度补偿，6-对焦。
*@param [out] min 属性值范围的最小值
*@param [out] max 属性值范围的最大值
*@param [out] lvalue 当前属性值
*@param [out] ldefault 初始默认值
*@param [out] flag 标志位，1：仅自动调节 2：可手动设置 3：可自动也可手动设置
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_UNKNOW 失败
	- @ref ERR_OUTOFBOUNDS devIndex无效，查询的设备不存在
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
	long camGetVideoParameter(long devIndex,long para1,long para2,long & min,long & max,long & lvalue,long & ldefault,long & flag)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long&,long&,long&,long&,long&)>("camGetVideoParameter");
		if(fun != 0)
		{
			return fun(devIndex,para1,para2,min,max,lvalue,ldefault,flag);
		}
		return -99;
	}

//弹出视频效果设置窗口
//返回值:是否能正确弹出
	long camShowImageSettingWindow(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camShowImageSettingWindow");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
//弹出视频属性设置窗口
//返回值:是否能正确弹出
	long camShowDevSettingWindow(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camShowDevSettingWindow");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
//自动对焦
//参数：0：一键对焦  1：自动对焦
//返回值:是否能正确对焦
	long camAutoFocus(long devIndex  ,long type)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camAutoFocus");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}


	//视频放大 缩小 1:1 最适尺寸
	//放大
	long camZooIn(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camZooIn");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//缩小
	long camZoomOut(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camZoomOut");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//最适比例
	long camOptimalPreview(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camOptimalPreview");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//原始比例 1:1
	long camOriginalPreview(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camOriginalPreview");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}

#pragma endregion 设备控制


#pragma region 图像处理
//设置JPG压缩率
//参数:压缩率 0~100 100压缩率最小 质量最好 尺寸最大
//返回值:是否设置成功
	long camSetImageJPGQuanlity(long devIndex  ,long quanlity)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageJPGQuanlity");
		if(fun != 0)
		{
			return fun(devIndex,quanlity);
		}
		return -99;
	}
//拍照(根据文件后缀自动存储格式)
//参数:图像路径
//返回值:是否拍摄成功
	long camCaptureImageFile(long devIndex ,char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("camCaptureImageFile");
		if(fun != 0)
		{
			return fun(devIndex,filePath);
		}
		return -99;
	}
	char *camCaptureImageBuff(long devIndex ,long &width,long & height,long & bpp)
	{
		auto fun = m_dllParser.GetFunction<char *(long,long &,long &,long &)>("camCaptureImageBuff");
		if(fun != 0)
		{
			return fun(devIndex,width,height,bpp);
		}
		return NULL;
	}
//自动裁切
//参数: 0：不自动 1：单图裁切 2：多图裁切
//返回值：是否设置成功，设置成功后，UI上会显示绿色框
	long camSetImageAutoCrop(long devIndex ,long CropType)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageAutoCrop");
		if(fun != 0)
		{
			return fun(devIndex,CropType);
		}
		return -99;
	}
//设置旋转方向
//参数:0: 不旋转 1:90度 2: 180度 3: 270度
	long camSetImageRotateMode(long devIndex,long rotateMode)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageRotateMode");
		if(fun != 0)
		{
			return fun(devIndex,rotateMode);
		}
		return -99;
	}
//设置自定义裁切区域
//参数:裁切区域  需要用裁切框显示在UI上
//返回值:是否设置成功
	long camSetImageCusCropRect(long devIndex ,long left, long top ,long right,long bottom)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long,long)>("camSetImageCusCropRect");
		if(fun != 0)
		{
			return fun(devIndex,left,top,right,bottom);
		}
		return -99;
	}
//获取自定义裁切区域
//返回值:是否设置成功
	long camGetImageCusCropRect(long devIndex ,long &left, long &top ,long &right,long &bottom)
	{
		auto fun = m_dllParser.GetFunction<long(long,long&,long&,long&,long&)>("camGetImageCusCropRect");
		if(fun != 0)
		{
			return fun(devIndex,left,top,right,bottom);
		}
		return -99;
	}

	long camSetImageEnhancement(long devIndex,bool m_bR , bool m_bG,bool m_bB)
	{
		auto fun = m_dllParser.GetFunction<long(long,bool,bool,bool)>("camSetImageEnhancement");
		if(fun != 0)
		{
			return fun(devIndex,m_bR,m_bG,m_bB);
		}
		return -99;
	}
//设置图像增强方式
//参数：0：	不增强 1：文档增强  2：彩页增强 3.自动处理
//返回值:是否设置成功
	long camSetImageAdjust(long devIndex  ,long type)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageAdjust");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}
	
	long camSetImageFillBorder(long devIndex  ,long type)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageFillBorder");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}
	
//设置是否去噪
//参数:IsAvailaber是否开启去噪  mothod 去噪方法
//返回值:是否设置成功
	long camSetImageDenoise(long devIndex ,bool IsAvailabel)
	{
		auto fun = m_dllParser.GetFunction<long(long,bool)>("camSetImageDenoise");
		if(fun != 0)
		{
			return fun(devIndex,IsAvailabel);
		}
		return -99;
	}
//设置图片格式
//参数: 0:彩色 1:灰度  2: 黑白
//返回值:是否设置成功
	long camSetImageColorStyle(long devIndex ,long type) //0:彩色  1:灰度  2: 黑白
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageColorStyle");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}
	long camSetImageDPI(long devIndex ,long xDPI,long yDPI)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long)>("camSetImageDPI");
		if(fun != 0)
		{
			return fun(devIndex,xDPI,yDPI);
		}
		return -99;
	}
	long camGetImageDPI(long devIndex ,long & xDPI,long & yDPI)
	{
		auto fun = m_dllParser.GetFunction<long(long,long&,long&)>("camGetImageDPI");
		if(fun != 0)
		{
			return fun(devIndex,xDPI,yDPI);
		}
		return -99;
	}
	long camSetImageBinaryMethold(long devIndex  ,long methold,long nthreshold)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long)>("camSetImageBinaryMethold");
		if(fun != 0)
		{
			return fun(devIndex,methold,nthreshold);
		}
		return -99;
	}
//设置水印
//参数:msg 水印内容(支持\n换行) x,y水印位置(像素数)  fontsize 水印字体尺寸 font 字体
// angle 水印旋转角度(0~360)   transparent 透明度 isAvailabel 是否生效
//colorType 水印颜色 0:黑色 1:白色 2:红色 3:天蓝色 4:绿色 5:蓝色 6:黄色
//返回值:是否设置成功
	long camSetImageWaterMark(long devIndex  ,char * msg,long type,long fontSize,char *  font,bool fItalic,bool fUnderline,bool fWeight,
		float angle,float transparent,long colorR,long colorG,long colorB,bool isAvailabel)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *,long,long,char *,bool,bool,bool,
		float,float,long,long,long,bool)>("camSetImageWaterMark");
		if(fun != 0)
		{
			return fun(devIndex,msg,type,fontSize,font,fItalic,fUnderline,fWeight,angle,transparent,colorR,colorG,colorB,isAvailabel);
		}
		return -99;
	}

//图像合并 图像后处理
//参数: imageFilePath1 图片1地址 imageFilePath2 图片2地址  imageFilePath 最终图像
// type 合并位置 0~8 
// long offsetX,long offsetY 偏移量
//返回值:是否设置成功 ?裁切||处理前副头合并？
	long camCombineImage(char * imageFilePath1 , char * imageFilePath2 , char * imageFilePath,long type,long offsetX,long offsetY,long Image2width,long Image2height)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *,char *,long,long,long,long ,long )>("camCombineImage");
		if(fun != 0)
		{
			return fun(imageFilePath1,imageFilePath2,imageFilePath,type,offsetX,offsetY,Image2width,Image2height);
		}
		return -99;
	}
	long camSaveImage(char * src, long width,long  height,long  bpp,char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *,long,long,long,char *)>("camSaveImage");
		if(fun != 0)
		{
			return fun(src,width,height,bpp,filePath);
		}
		return -99;
	}
	long camRotateImage(char * imageFilePath,long rotateMode)
	{
		auto fun = m_dllParser.GetFunction<long(char *,long)>("camRotateImage");
		if(fun != 0)
		{
			return fun(imageFilePath,rotateMode);
		}
		return -99;
	}
#pragma endregion 图像处理

#pragma region 连续拍摄
	long camStartAutoCapture(long devIndex  ,long type,long param, callBackAutoCapture funCB)//0:自动 1:定时
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,callBackAutoCapture)>("camStartAutoCapture");
		if(fun != 0)
		{
			return fun(devIndex,type,param,funCB);
		}
		return -99;
	}
	long camStopAutoCapture(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camStopAutoCapture");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
#pragma endregion 连续拍摄

#pragma region 回调函数
	long camRegCallBackDeviceChange(callBackDevChange funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callBackDevChange)>("camRegCallBackDeviceChange");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return -99;
	}
	//旧的注册回调函数
	long camRegOutCallBackDeviceChange(callBackDevChange funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callBackDevChange)>("camRegOutCallBackDeviceChange");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return -99;
	}
	long camRegCallBackPreviewImage(long devIndex,callBackPreviewImage funCB)
	{
		auto fun = m_dllParser.GetFunction<long(long,callBackPreviewImage)>("camRegCallBackPreviewImage");
		if(fun != 0)
		{
			return fun(devIndex,funCB);
		}
		return -99;
	}
	long camRegOutCallBackGetPreviewImage(long devIndex,callBackPreviewImage funCB)
	{
		auto fun = m_dllParser.GetFunction<long(long,callBackPreviewImage)>("camRegOutCallBackGetPreviewImage");
		if(fun != 0)
		{
			return fun(devIndex,funCB);
		}
		return -99;
	}
#pragma endregion 回调函数

#pragma region 文件操作
//显示图片
//参数:图片路径
//返回值:是否打开成功
	long camShowImage(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camShowImage");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//删除文件
//参数:文件路径
//返回值:是否删除成功
	long camDeleteFile(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camDeleteFile");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//创建文件夹
//参数:文件夹路径
//返回值:是否创建成功
	long camCreateDirectory(char * dirPath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCreateDirectory");
		if(fun != 0)
		{
			return fun(dirPath);
		}
		return -99;
	}
//重命名文件
//参数filePath 原始文件  newFilePath 新文件名
//返回值是否创建成功
	long camRenameFile(char * filePath,char * newFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *)>("camRenameFile");
		if(fun != 0)
		{
			return fun(filePath,newFilePath);
		}
		return -99;
	}
#pragma endregion 文件操作


#pragma region 文件合并
//添加文件到PDF列表
//参数:文件名
//返回值:是否添加成功
	long camAddFileToPDFList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToPDFList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//合并PDF(合并后会清空List)
//参数:合并后的PDF文件名
//返回值:是否合并成功
	long camCombinePDF(char * pdfFilePath,long nJpegQuality)
	{
		auto fun = m_dllParser.GetFunction<long(char *,long)>("camCombinePDF");
		if(fun != 0)
		{
			return fun(pdfFilePath,nJpegQuality);
		}
		return -99;
	}
//添加文件到TIF列表(合并后会清空List)
//参数:文件名
//返回值:是否添加成功
	long camAddFileToTIFList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToTIFList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//合并TIF
//参数:合并后的TIF文件名
//返回值:是否合并成功
	long camCombineTIF(char * tifFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCombineTIF");
		if(fun != 0)
		{
			return fun(tifFilePath);
		}
		return -99;
	}
//添加文件到ZIP列表(合并后会清空List)
//参数:文件名
//返回值:是否添加成功
	long camAddFileToZIPList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToZIPList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//合并ZIP
//参数:合并后的ZIP文件名
//返回值:是否合并成功
	long camCombineZIP(char * zipFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCombineZIP");
		if(fun != 0)
		{
			return fun(zipFilePath);
		}
		return -99;
	}
#pragma endregion 文件合并

#pragma region 文件上传
//Http文件上传(同步模式)
//参数:filePath 文件路径，url  http地址
//返回值:是否上传成功
	long camUpdataFileHttp(char * filePath,char * url,char * param,char * response)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *,char *,char *)>("camUpdataFileHttp");
		if(fun != 0)
		{
			return fun(filePath,url,param,response);
		}
		return -99;
	}
//FTP文件上传(同步模式)
//参数:filePath 文件路径，ftpPath FTP路径，
//UserName ftp用户名 ,UserPsd ftp用户密码,targetName ftp服务器文件存储名
//返回值:是否上传成功0成功 -1上传失败 -2登陆服务器根路径失败
// -3 创建子文件夹失败 -4 断开连接失败 -5 连接失败
	long camUpdataFileFtp(char * filePath, char * ftpPath, char * userName, char * userPsd, char * targetName)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *,char *,char *,char *)>("camUpdataFileFtp");
		if(fun != 0)
		{
			return fun(filePath,ftpPath,userName,userPsd,targetName);
		}
		return -99;
	}
#pragma endregion 文件上传
#pragma region 条码识别
	long coderInitBarcoder ()
	{
		auto fun = m_dllParser.GetFunction<long()>("coderInitBarcoder");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long coderUnInitBarcoder()
	{
		auto fun = m_dllParser.GetFunction<long()>("coderUnInitBarcoder");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long coderNameByBarcode(long devIndex,bool bIsAvailabel,long left,long top ,long right,long bottom)
	{
		auto fun = m_dllParser.GetFunction<long(long,bool,long,long,long,long)>("coderNameByBarcode");
		if(fun != 0)
		{
			return fun(devIndex,bIsAvailabel,left,top,right,bottom);
		}
		return -99;
	}
	char * coderRecognizeBarcode(char * src,long left,long top ,long right,long bottom)
	{
		auto fun = m_dllParser.GetFunction<char *(char *,long,long,long,long)>("coderRecognizeBarcode");
		if(fun != 0)
		{
			return fun(src,left,top,right,bottom);
		}
		return NULL;
	}
#pragma endregion 条码识别

#pragma region 身份证识别
	long cardOCRInitIDCardOCR ()
	{
		auto fun = m_dllParser.GetFunction<long()>("cardOCRInitIDCardOCR");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long cardOCRUnInitIDCardOCR()
	{
		auto fun = m_dllParser.GetFunction<long()>("cardOCRUnInitIDCardOCR");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	char * cardOCRRecognizeIDCard_OCR(char * imagePath,char * headerFilePath)
	{
		auto fun = m_dllParser.GetFunction<char *(char *,char *)>("cardOCRRecognizeIDCard_OCR");
		if(fun != 0)
		{
			return fun(imagePath,headerFilePath);
		}
		return NULL;
	}
	long cardOCRNameByIDCard(long devIndex,long n_NameType)//0 不生效 1 姓名 2 身份证号
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("cardOCRNameByIDCard");
		if(fun != 0)
		{
			return fun(devIndex,n_NameType);
		}
		return -99;
	}
#pragma endregion 身份证识别


#pragma region 指纹采集

	long fingerprintInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("fingerprintInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long fingerprintUnInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("fingerprintUnInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long fingerprintGetFeature(const unsigned char *pRawData, unsigned char * pFeatureData)
	{
		auto fun = m_dllParser.GetFunction<long(const unsigned char *,unsigned char *)>("fingerprintGetFeature");
		if(fun != 0)
		{
			return fun(pRawData,pFeatureData);
		}
		return -99;
	}
	long fingerprintGetImage(unsigned char* pBmpBuff,unsigned char *pRawData)
	{
		auto fun = m_dllParser.GetFunction<long(unsigned char*,unsigned char *)>("fingerprintGetImage");
		if(fun != 0)
		{
			return fun(pBmpBuff,pRawData);
		}
		return -99;
	}
	long fingerprintStartGetFPDataAsync(callBackGetFPDataAsync funCB, void *pUserData)
	{
		auto fun = m_dllParser.GetFunction<long(callBackGetFPDataAsync,void *)>("fingerprintStartGetFPDataAsync");
		if(fun != 0)
		{
			return fun(funCB,pUserData);
		}
		return -99;
	}
	long fingerprintStopGetFPDataAsync()
	{
		auto fun = m_dllParser.GetFunction<long()>("fingerprintStopGetFPDataAsync");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long fingerprintContrast(unsigned char* pFeature1,unsigned char *pFeature2)
	{
		auto fun = m_dllParser.GetFunction<long(unsigned char*,unsigned char *)>("fingerprintContrast");
		if(fun != 0)
		{
			return fun(pFeature1,pFeature2);
		}
		return -99;
	}
	long fingerprintSetPrintQuality(long Score)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("fingerprintSetPrintQuality");
		if(fun != 0)
		{
			return fun(Score);
		}
		return -99;
	}
#pragma endregion 指纹采集

#pragma region 身份证读卡

	long idcardrfidInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("idcardrfidInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long idcardrfidUnInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("idcardrfidUnInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long idcardrfidReadIDCard(BaseMsg &Msg,char* headerFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(BaseMsg &,char*)>("idcardrfidReadIDCard");
		if(fun != 0)
		{
			return fun(Msg,headerFilePath);
		}
		return -99;
	}
	long idcardrfidReadIDCardEx(BaseMsgEx &MsgEx,char* headerFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(BaseMsgEx &,char*)>("idcardrfidReadIDCardEx");
		if(fun != 0)
		{
			return fun(MsgEx,headerFilePath);
		}
		return -99;
	}
	//long idcardrfidGetHeadPicPath(char* picPath)
	//{
	//	auto fun = m_dllParser.GetFunction<long(char *)>("idcardrfidGetHeadPicPath");
	//	if(fun != 0)
	//	{
	//		return fun(picPath);
	//	}
	//	return -99;
	//}
	//long idcardrfidSetHeadPicPath(char* picPath)
	//{
	//	auto fun = m_dllParser.GetFunction<long(char *)>("idcardrfidSetHeadPicPath");
	//	if(fun != 0)
	//	{
	//		return fun(picPath);
	//	}
	//	return -99;
	//}
	long idcardrfidGetFingerprintMsg(unsigned char* pcFPMsg, long &nMsgSize )
	{
		auto fun = m_dllParser.GetFunction<long(unsigned char*,long&)>("idcardrfidGetFingerprintMsg");
		if(fun != 0)
		{
			return fun(pcFPMsg,nMsgSize);
		}
		return -99;
	}
	long idcardrfidGetOneFingerprintMsg(long nIndex,unsigned char* pcFPMsg, long &nFingerType )
	{
		auto fun = m_dllParser.GetFunction<long(int,unsigned char*,long&)>("idcardrfidGetOneFingerprintMsg");
		if(fun != 0)
		{
			return fun(nIndex,pcFPMsg,nFingerType);
		}
		return -99;
	}
	long idcardrfidGetIDCardImage(long nType ,char* pFileFront, char* pFileBack = NULL)
	{
		auto fun = m_dllParser.GetFunction<long(long  ,char* , char* )>("idcardrfidGetIDCardImage");
		if(fun != 0)
		{
			return fun(nType,pFileFront,pFileBack);
		}
		return -99;
	}

#pragma endregion 身份证读卡

#pragma region 防篡改
	long camSetImageFileSign(long devIndex ,bool IsAvailabel)
	{
		auto fun = m_dllParser.GetFunction<long(long,bool)>("camSetImageFileSign");
		if(fun != 0)
		{
			return fun(devIndex,IsAvailabel);
		}
		return -99;
	}
	long camCheckImageFileSign(char * filePath,bool & ret)
	{
		auto fun = m_dllParser.GetFunction<long(char*,bool&)>("camCheckImageFileSign");
		if(fun != 0)
		{
			return fun(filePath,ret);
		}
		return -99;
	}
#pragma endregion 防篡改
	//long FileEncodeBase64(char* filePath,char* buffBase64)
	//{
	//	auto fun = m_dllParser.GetFunction<long(char*,char*)>("FileEncodeBase64");
	//	if(fun != 0)
	//	{
	//		return fun(filePath,buffBase64);
	//	}
	//	return NOT_FIND;
	//}
	char* FileEncodeBase64(char* filePath)
	{
		auto fun = m_dllParser.GetFunction<char*(char*)>("FileEncodeBase64");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return NULL;
	}
	//percentage识别进度,cancel是否取消, pInfo 保留、无用
	typedef long (CALLBACK * callbackProgress) (long percentage, VARIANT_BOOL* cancel, void * pInfo);
	long ocrRegCallBackProgress(callbackProgress funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callbackProgress )>("ocrRegCallBackProgress");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return NOT_FIND;
	}
	//文字识别，一键word，excel
	long ocrGetLanguageCount(long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long & )>("ocrGetLanguageCount");
		if(fun != 0)
		{
			return fun(count);
		}
		return NOT_FIND;
	}
	long ocrGetLanguageName(long index, char * name)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("ocrGetLanguageName");
		if(fun != 0)
		{
			return fun(index,name);
		}
		return NOT_FIND;
	}
	long ocrAddImageFileToOCRList(char* imagePath)
	{
		auto fun = m_dllParser.GetFunction<long(char*)>("ocrAddImageFileToOCRList");
		if(fun != 0)
		{
			return fun(imagePath);
		}
		return NOT_FIND;
	}
	long ocrCombineToFile(char * filePath,long nlanguage)
	{
		auto fun = m_dllParser.GetFunction<long(char*,long)>("ocrCombineToFile");
		if(fun != 0)
		{
			return fun(filePath,nlanguage);
		}
		return NOT_FIND;
	}
	long ocrDetectOrientation(char *filePath,char * language)
	{
		auto fun = m_dllParser.GetFunction<long(char*,char*)>("ocrDetectOrientation");
		if(fun != 0)
		{
			return fun(filePath,language);
		}
		return NOT_FIND;
	}
	//long camEnableBuzzer(long devIndex, long Count = 3, long duration = 500, long interval = 500);
	long camEnableBuzzer(long devIndex, long Count , long duration , long interval)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long)>("camEnableBuzzer");
		if(fun != 0)
		{
			return fun(devIndex,Count,duration,interval);
		}
		return NOT_FIND;
	}

	#pragma region 蜂鸟按键
	//线程控制支持热插拔
	//初始化
	long KeyOpenDevice()
	{
		auto fun = m_dllParser.GetFunction<long()>("KeyOpenDevice");
		if(fun != 0)
		{
			return fun();
		}
		return NOT_FIND;
	}
	//反初始化
	long KeyCloseDevice()
	{
		auto fun = m_dllParser.GetFunction<long()>("KeyCloseDevice");
		if(fun != 0)
		{
			return fun();
		}
		return NOT_FIND;
	}
	//关闭/开启自动亮灯，默认为开启
	long KeySetAutoLights(bool bAuto)
	{
		auto fun = m_dllParser.GetFunction<long(bool)>("KeySetAutoLights");
		if(fun != 0)
		{
			return fun(bAuto);
		}
		return NOT_FIND;
	}
	//设置状态灯
	//0：熄灭，1：绿，2：红，3：两灯同亮（与红色很相近，稍稍偏橙色）
	long KeySetLedState(long lState)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("KeySetLedState");
		if(fun != 0)
		{
			return fun(lState);
		}
		return NOT_FIND;
	}
	//按键消息回调
	//1为按下，2为抬起
	typedef bool (CALLBACK * callBackKeyRecept)(long lData);
	//注册按键回调
	long KeyRegCallBackKeyRecept(callBackKeyRecept funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callBackKeyRecept)>("KeyRegCallBackKeyRecept");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return NOT_FIND;
	}
	#pragma endregion 蜂鸟按键

	//录像格式
	long camGetVideoEncodeCount(long &lCount)
	{
		auto fun = m_dllParser.GetFunction<long(long &)>("camGetVideoEncodeCount");
		if(fun != 0)
		{
			return fun(lCount);
		}
		return NOT_FIND;
	}
	long camGetVideoEncodeName(long Index, char * sEncodeName)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("camGetVideoEncodeName");
		if(fun != 0)
		{
			return fun(Index,sEncodeName);
		}
		return NOT_FIND;
	}

	//获取目录下文件数量和名字
	long camGetDirectoryFileCount(long &lCount,char* cDirectory,long fileType = 0xFFFF)
	{
		auto fun = m_dllParser.GetFunction<long(long&,char *,long)>("camGetDirectoryFileCount");
		if(fun != 0)
		{
			return fun(lCount,cDirectory,fileType);
		}
		return NOT_FIND;
	}
	long camGetFileNameOnDirectory(long nIndex, char * cFileName)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *)>("camGetFileNameOnDirectory");
		if(fun != 0)
		{
			return fun(nIndex,cFileName);
		}
		return NOT_FIND;
	}
	//设置帧率，视频比特率，音频比特率
	long camSetRecordRate(long lFPS, long lVideoBitrate, long lAudioBitrate)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long)>("camSetRecordRate");
		if(fun != 0)
		{
			return fun(lFPS,lVideoBitrate,lAudioBitrate);
		}
		return NOT_FIND;
	}

	long camSetMultiRecordParam(long lWidth,long lHeight,long lLayoutMode = 0,long lRecordMode = 0)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long)>("camSetMultiRecordParam");
		if(fun != 0)
		{
			return fun(lWidth, lHeight,lLayoutMode,lRecordMode);
		}
		return NOT_FIND;
	}
	long camStartMultiRecord(int arrCamID[99],int nCamIDCount,char * filePath,long micphone,long videoFormat,int nCompressionRadio = 25)
	{
		auto fun = m_dllParser.GetFunction<long(int [99],int,char *,long,long,int)>("camStartMultiRecord");
		if(fun != 0)
		{
			return fun(arrCamID, nCamIDCount,filePath,micphone,videoFormat,nCompressionRadio);
		}
		return NOT_FIND;
	}

	long camStopMultiRecord()
	{
		auto fun = m_dllParser.GetFunction<long()>("camStopMultiRecord");
		if(fun != 0)
		{
			return fun();
		}
		return NOT_FIND;
	}

	long camGetMultiRecordMicrophoneVolumeLevel()
	{
		auto fun = m_dllParser.GetFunction<long()>("camGetMultiRecordMicrophoneVolumeLevel");
		if(fun != 0)
		{
			return fun();
		}
		return NULL;
	}
	long camStopCameraLib()
	{
		auto fun = m_dllParser.GetFunction<long()>("camStopCameraLib");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}

	long otrInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("otrInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long otrUnInit()
	{
		auto fun = m_dllParser.GetFunction<long()>("otrUnInit");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
	long otrGetTemplateCount(long &nCount)
	{
		auto fun = m_dllParser.GetFunction<long(long &)>("otrGetTemplateCount");
		if(fun != 0)
		{
			return fun(nCount);
		}
		return -99;
	}
	long otrGetTemplateInfo(long nIndex, char* chMsg, long &nMsgSize)
	{
		auto fun = m_dllParser.GetFunction<long(long,char*,long &)>("otrGetTemplateInfo");
		if(fun != 0)
		{
			return fun(nIndex,chMsg,nMsgSize);
		}
		return -99;
	}
	long otrRecog(long nIndex, char* chPath)
	{
		auto fun = m_dllParser.GetFunction<long(long , char *)>("otrRecog");
		if(fun != 0)
		{
			return fun(nIndex,chPath);
		}
		return -99;
	}
	long otrGetResultCount(long & nCount)
	{
		auto fun = m_dllParser.GetFunction<long(long &)>("otrGetResultCount");
		if(fun != 0)
		{
			return fun(nCount);
		}
		return -99;
	}
	long otrGetResultInfo(long nIndex, char* chName, char* chResult)
	{
		auto fun = m_dllParser.GetFunction<long(long ,char * ,char *)>("otrGetResultInfo");
		if(fun != 0)
		{
			return fun(nIndex,chName,chResult);
		}
		return -99;
	}
	long camUpdateCameraLib()
	{
		auto fun = m_dllParser.GetFunction<long()>("camUpdateCameraLib");
		if(fun != 0)
		{
			return fun();
		}
		return -99;
	}
/**@brief 获得触控按钮状态
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return 
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
	- @ref ERR_OUTOFBOUNDS 无效的devIndex
	- @ref ERR_NONSUPPORT 该设备不支持
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
	long camGetSnapState(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camGetSnapState");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
/**条码/二维码识别
*
*@prarm [in] src 照片路径，可识别图中多个码
*@prarm [in] codeType 编码类型 1条码 2二维码
*@prarm [out] count 识别出结果的个数
*@return
	- NULL 空指针，拍照失败
	- MImage类型指针，拍照成功
*/
	long ocrRecognizeBarcode(char * src,long codeType,long & count)
	{
		auto fun = m_dllParser.GetFunction<long(char * ,long ,long & )>("ocrRecognizeBarcode");
		if(fun != 0)
		{
			return fun(src,codeType,count);
		}
		return -99;
	}


/**获得条码/二维码识别结果
*
*@prarm [in] Index 识别结果ID
*@prarm [out] cText 识别出的文本结果
*@prarm [in/out] size 输入为cText的空间长度，输出为结果的长度。
*@return
	- NULL 空指针，拍照失败
	- MImage类型指针，拍照成功
*/
	long ocrGetBarcodeText(long Index,char* cText,long & size)
	{
		auto fun = m_dllParser.GetFunction<long(long ,char* ,long & )>("ocrGetBarcodeText");
		if(fun != 0)
		{
			return fun(Index,cText,size);
		}
		return -99;
	}
	/* 获得缩放比例
	*
	*@prarm [in] devIndex 设备ID
	*@prarm [out] fScaleX X轴方向缩放比例
	*@prarm [out] fScaleY Y轴方向缩放比例
	*@return
	*/
	long camGetCaptureScale(long devIndex,float& fScaleX,float& fScaleY)
	{
		auto fun = m_dllParser.GetFunction<long(long ,float& ,float& )>("camGetCaptureScale");
		if(fun != 0)
		{
			return fun(devIndex, fScaleX, fScaleY);
		}
		return -99;
	}


	long camGetFocusValue(long devIndex,long & lvalue)
	{
		auto fun = m_dllParser.GetFunction<long(long ,long& )>("camGetFocusValue");
		if(fun != 0)
		{
			return fun(devIndex, lvalue);
		}
		return -99;
	}
	//

	//读取银行卡
	long camGetBankCardInfo(BankBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(BankBaseMsg &)>("camGetBankCardInfo");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//读取信用银行卡
	long camGetBankCardInfoEx(BankBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(BankBaseMsg &)>("camGetBankCardInfoEx");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//读取社保卡
	long camGetSsseInfo(SsseBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(SsseBaseMsg &)>("camGetSsseInfo");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//读取磁条卡
	long camGetMagCard(MagCardMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(MagCardMsg &)>("camGetMagCard");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
public:
	CmCaptureHelper(void)
	{
		this->m_bInit = false;
	};
	~CmCaptureHelper(void)
	{
		m_dllParser.UnLoad();
	};

private:
	DllParser m_dllParser;
	bool m_bInit;
};

