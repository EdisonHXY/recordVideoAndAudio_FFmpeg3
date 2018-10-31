#pragma once
#ifdef CAMSDK_EXPORTS
#define CAMSDK_API extern "C"  __declspec(dllexport)
#else
#define CAMSDK_API extern "C" __declspec(dllimport)
#endif

#include <string>
using namespace std;

#define _CAMDLL_CALLBACK -1
#define _CAMDLL_SDK_OPERATION 1
#define _CAMDLL_DEVICE_INFORMATION 2
#define _CAMDLL_EQUIPMENT_OPERATION 3
#define _CAMDLL_DEVICE_PREVIEW  4
#define _CAMDLL_EQUIPMENT_ADVANCED_OPERATION 5
#define _CAMDLL_UVC_DRIVE  6
#define _CAMDLL_CAPTURE 7
#define _CAMDLL_RECORD 8
#define _CAMDLL_FILE_OPERATION 9
#define _CAMDLL_BARCODE 10
#define _CAMDLL_IDCARD 11
#define _CAMDLL_IDCARD_DEVICE 12
#define _CAMDLL_FINGERPRINT_DEVICE 13
#define _CAMDLL_OCR 14
#define _CAMDLL_EXTERNAL_BUTTON 15
#define _CAMDLL_OTR 16

#if _CAMDLL_CALLBACK
/** @addtogroup 回调函数
*@{
*/
/**视频预览回调
*@param src 内存数据内容为当前视频图像
*@param width 图像宽度
*@param height 图像高度
*@param size bpp编码位数（24为真彩色）
*/
typedef bool (CALLBACK * callBackPreviewImage)(byte * src,long width,long height,long size); 

/**设备热插拔回调
*@param deviceChangeType 
*/
typedef bool (CALLBACK * callBackDevChange)(CAMSDK_DEVCHANGE deviceChangeType); 

/**设备连拍
*@param state 状态值，意义见连拍模式。定时模式，该值表示时间单位秒；自动识别模式，该值表示稳定帧数。
*/
typedef bool (CALLBACK * callBackAutoCapture)(long state); 

/**获取指纹特征值回调函数
*@param pBmpBuff用于存储指纹BMP图片的内存空间，应不小于 512*512字节。
*@param pFeature指纹特征值，内存不小于1024字节。
*@param pUserData预留，未使用。
*/
typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData);

/**获取外接按键回调函数
*@param lData值的意义1为按下2为抬起
*/
typedef bool (CALLBACK * callBackKeyRecept)(long lData); 
/**@}*/ //end of group 回调函数
#endif

#if _CAMDLL_SDK_OPERATION
/** @addtogroup SDK基本操作
*@{
*/
/**初始化
*加载DLL,同时记录当前是否有授权设备
*@prarm [无]
*@return
	@ref ERR_NONE 初始化成功
	@ref ERR_NOLICENSE 没有授权
*@note 初始化成功后，退出须反初始化
*/
CAMSDK_API long camInitCameraLib();

/**更新信息
*遍历设备，检测授权等
*@prarm [无]
*@return
 @ref ERR_NONE 成功
 @ref ERR_NOLICENSE 没有授权
*@note camInitCameraLib会调用camUpdateCameraLib，因此调用
*/
CAMSDK_API long camUpdateCameraLib();

/**统一停止视频模块的工作，包括
*（1）停止当前已经开通摄像头
*（2）释放所有摄像头
*@prarm [无]
*@return
 @ref ERR_NONE 成功
*/
CAMSDK_API long camStopCameraLib();


/**反初始化
*@prarm [无]
*@return
	@ref ERR_NONE 反初始化成功
*/
CAMSDK_API long camUnInitCameraLib();
/**@}*/ //end of group SDK基本操作
#endif

#if _CAMDLL_DEVICE_INFORMATION
/** @addtogroup 获取设备信息
*@{
*/
/**@brief 获取摄像头个数
*
*@param [out] count 设备个数
*@return
*	- @ref ERR_NONE 成功
*@note 设备排序方式 优先 主摄像  其次副摄像头  再次 凭证摄像头 最后其他
*@pre  先执行@ref camInitCameraLib
*/
CAMSDK_API long camGetDevCount(long & count);
CAMSDK_API long camGetDevCountCur(long & count);

/**@brief 获取设备类型
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] type 设备类型 0:主头 1:副头  2:凭证摄像头 99:其他
*@return
*	- @ref ERR_NONE 成功
*	- @ref ERR_OUTOFBOUNDS 查询不存在设备ID
*	- @ref ERR_NULLPOINT 设备信息是空
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevType(long devIndex ,long & type); 

/**@brief 获取设备名
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
*	- 摄像头在设备管理器中的名称
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char * camGetDevName(long devIndex );

/**@brief 获取设备VID
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] strvid 设备VID字符串
*@return
*	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevVid(long devIndex ,char * strvid);

/**@brief 获取设备PID
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] strpid 设备PID字符串
*@return
*	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevPid(long devIndex ,char * strpid);


CAMSDK_API long camGetDevDimension(long devIndex ,char * strDimension);
/**@brief 获取分辨率个数
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] subtype 媒体格式ID，0号开始
*@param [out] count 获得指定设备指定格式支持的分辨率个数
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetResolutionCount(long devIndex ,long subtype ,long & count);

/**@brief 获取指定分辨率
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] subtype 媒体格式ID，0号开始
*@param [in] index 分辨率ID，0号开始
*@param [out] width 获得指定设备指定格式指定序号的分辨率的宽
*@param [out] height 获得指定设备指定格式指定序号的分辨率的高
*@return
*	- @ref ERR_NONE 成功
*	- @ref ERR_OUTOFBOUNDS 查询不存在设备ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetResolution(long devIndex ,long subtype,long index,long & width,long & height);

/**@brief 播放中视频切换分辨率
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] width 指定分辨率的宽
*@param [in] height 指定分辨率的高
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetResolution(long devIndex,long width,long height);

/**@brief 获得当前视频格式及分辨率
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] subtype 获得指定设备当前媒体格式
*@param [out] width 获得指定设备当前分辨率的宽
*@param [out] height 获得指定设备当前分辨率的高
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 查询的摄像头ID不存在
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetCurResolution(long devIndex,long &subtype,long &width,long &height);

/**@brief 获取视频格式个数
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] count 该设备支持的视频格式个数
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetMediaTypeCount(long devIndex ,long & count);

/**@brief 获取视频格式名称
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] index 媒体格式ID，0号开始
*@return
	媒体格式名称，例如：MJPEG，YUY2。
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API char * camGetMediaTypeName(long devIndex  ,long index);

CAMSDK_API long camGetMediaTypeNameEx(long devIndex  ,long index,char * subMediaType);

/**@brief 设置视频格式
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] subtypeIndex 媒体格式ID，0号开始
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetMediaType(long devIndex  ,long subtypeIndex);

/**@brief 判断当前摄像头是否为StillPin模式
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- True，当前为StillPin模式
    - False，当前不为StillPin模式或其他错误
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API bool camIsStillPin(long devIndex);

/**@brief 是否启用StillPin模式(摄像头不支持则无效)
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] IsEnable 0值不启用，非0值启用
*@return
	- True，当前为StillPin模式
    - False，当前不为StillPin模式或其他错误
*@note 此接口必须在camOpenDev之前设置。
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
//此接口用于梯形偏心检查工具，禁用stillpin模式出图。
//有BUG，开启摄像头后控制Stillpin促发断言
//此接口必须在camOpenDev之前设置。
CAMSDK_API long camEnableStillPin(long devIndex, long IsEnable);

/**@brief StillPin模式设置预览分辨率
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] width 指定分辨率的宽
*@param [in] height 指定分辨率的高
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
	- @ref ERR_SETRESOLUTIONFAILD 设置分辨率失败
	- @ref ERR_STARTVIDEOFAILD 开启视频失败
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetPreviewResolution(long devIndex,long width,long height);

CAMSDK_API long camGetCurPreviewResolution(long devIndex,long &subtype,long &width,long &height);

/**@brief StillPin模式设置预览视频格式
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] subtypeIndex 媒体格式ID，0号开始
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
	- @ref ERR_SETRESOLUTIONFAILD 设置分辨率失败
	- @ref ERR_STARTVIDEOFAILD 开启视频失败
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetPreviewMediaType(long devIndex,long subtypeIndex);
/**@}*/ //end of group 获取设备信息
#endif

#if _CAMDLL_EQUIPMENT_OPERATION
/**@brief 打开视频设备
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] subtype 媒体格式ID，不同设备支持的格式可能不同，
					 常见0：mjpeg，1：yuy2，不支持mjpeg的设备则 0：yuy2。
					 可通过@ref camGetMediaTypeCount ，@ref camGetMediaTypeName 查询
*@param [in] width 指定分辨率宽，可以为0，设备不支持该分辨率时，默认以最大分辨开启视频
*@param [in] height 指定分辨率高，可以为0，设备不支持该分辨率时，默认以最大分辨开启视频
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
	- @ref ERR_OPENDEVFAILD 打开摄像头失败
	- @ref ERR_STARTVIDEOFAILD 播放摄像头失败
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
//mediaType 默认通过配置文件 默认最大分辨率
CAMSDK_API 	long camOpenDev(long devIndex ,long subtype,long width,long height);


CAMSDK_API 	long camPause(long devIndex ,long lstyle);
/**@brief 关闭视频设备
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCloseDev(long devIndex);

/**@brief 注册热插拔消息回调
*
*@param [in] fun 热插拔回调函数 @ref callBackDevChange
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 每次初始化后注册一次即可。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegCallBackDeviceChange(callBackDevChange fun);

/**@brief 注册热插拔消息回调（旧）
*
*@param [in] fun 热插拔回调函数 @ref callBackDevChange
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 每次初始化后注册一次即可。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegOutCallBackDeviceChange(callBackDevChange fun);
#endif

#if _CAMDLL_DEVICE_PREVIEW
/**@brief 注册视频图像回调
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] fun 视频图像回调函数 @ref callBackPreviewImage
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegCallBackPreviewImage(long devIndex,callBackPreviewImage fun);

/**@brief 注册视频图像回调（旧）
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] fun 视频图像回调函数 @ref callBackPreviewImage
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegOutCallBackGetPreviewImage(long devIndex,callBackPreviewImage fun);






/**@brief 设置预览区域
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] lwidth 输出视频宽度
*@param [in] lheight 输出视频高度
*@param [in] lleft ltop lright lbottom 视频需要预览区域
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre @ref camRegOutCallBackGetPreviewImage
*@attention
*/
CAMSDK_API long camSetCallBackImageSize(long devIndex , float fResizeScale);



/**@brief 设置预览窗口
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
@param [in] hPreviewWindow 窗口句柄
*@return
*	- @ref ERR_NONE 成功
*	- @ref ERR_OUTOFBOUNDS 查询不存在设备ID
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetPreviewWindow(long devIndex  ,HWND hPreviewWindow);
CAMSDK_API long camSetPreviewHalfImage(long devIndex  ,bool bHalfImage);
CAMSDK_API long camSetPreviewRectColor(long devIndex , byte r,byte g,byte b);
CAMSDK_API long camSetPreviewText(long devIndex , char * text);
/**@brief 视频放大
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camZooIn(long devIndex); 

/**@brief 视频缩小
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camZoomOut(long devIndex); 

/**@brief 视频以最适比例显示到窗口
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camOptimalPreview(long devIndex); 

/**@brief 视频以原始比例显示到窗口
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camOriginalPreview(long devIndex);
#endif

#pragma region _CAMDLL_EQUIPMENT_ADVANCED_OPERATION 


/**@brief 获取设备序列号
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- 设备序列号 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevSN(long devIndex);

/**@brief 获取设备序列号
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- 设备序列号 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevSNFromDev(long devIndex);

/**@brief 获取设备自定义序列号
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- 自定义设备序列号 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevCusSN(long devIndex);





/**@brief 检测当前设备是否有授权
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] ret是否授权
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camDevCheckLicense(int devIndex,bool & ret);

/**@brief 查询设备是否一键对焦设备
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 是对焦设备
	- @ref ERR_NONSUPPORT 不是对焦设备
	- @ref ERR_OUTOFBOUNDS 无效的devIndex
	- @ref ERR_NULLPOINT 没有设备信息
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camIsAutoFocus(long devIndex);

/**@brief 一键对焦自动对焦 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 0表示一键对焦，1表示自动对焦
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camAutoFocus(long devIndex,long type); 



/**@brief 获取对焦值
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] lvalue 当前对焦值
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camGetFocusValue(long devIndex,long & lvalue); 

/**@brief 设置对焦值
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] lvalue 当前对焦值
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camSetFocusValue(long devIndex,long lvalue); 


/**@brief 设备蜂鸣
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] Count 鸣响次数
*@param [in] Duration 一次鸣响时长，单位ms
*@param [in] Interval 每次鸣响间隔时间，单位ms
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention 
*/
CAMSDK_API long camEnableBuzzer(long devIndex, long Count = 3, long duration = 500, long interval = 500);

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
CAMSDK_API long camGetSnapState(long devIndex);




#pragma endregion _CAMDLL_EQUIPMENT_ADVANCED_OPERATION

#if _CAMDLL_UVC_DRIVE
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
CAMSDK_API long camGetVideoParameter(long devIndex,long para1,long para2,long & min,long & max,long & lvalue,long & ldefault,long & flag); 

/**@brief 设置UVC驱动视频效果 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] para1 0：视频Proc Amp ， 1：摄像头控制CameraContrl
*@param [in] para2
	- Video Proc Amp的属性项：0-亮度，1-对比度，2-色相，3-饱和度，4-清晰度，5-伽玛，6-启用颜色，7-白平衡，8-背光补偿，9-增益。
	- CameraContrl的属性项：0-全景，1-倾斜，2-滚动，3-缩放，4-曝光，5-低照度补偿，6-对焦。
*@param [in] lvalue 设置属性值
*@param [in] flag 标志位，1：自动调节 2：手动设置
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_UNKNOW 失败
	- @ref ERR_OUTOFBOUNDS devIndex无效，查询的设备不存在
*@note 设备不一定支持设置所有属性，支持项和子范围详见 @ref camShowImageSettingWindow 和 @ref camShowDevSettingWindow 窗口中的可配置项。
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetVideoParameter(long devIndex  ,long para1,long para2,long lvalue,long flag);

/**@brief 弹出“视频效果”设置窗口
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camShowImageSettingWindow(long devIndex);

/**@brief 弹出“视频属性”设置窗口
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camShowDevSettingWindow(long devIndex);
#endif

#if _CAMDLL_CAPTURE
/**@brief 设置JPG压缩率 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] quanlity 压缩率值范围：0~100。100不压缩，质量最好尺寸最大
*@return 
	- @ref ERR_NONE 成功
*@note 设置存储图像(拍照)的JPG压缩率，可在开启视频前设置或拍照时设置。SDK初始拍jpg格式照片默认压缩率（质量）为55.
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetImageJPGQuanlity(long devIndex,long quanlity);

/**@brief 拍照 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] filePath 生成的照片的全路径。支持jpg、bmp、png、pdf。
	    [out] filePath 返回实际照片文件全路径，多图裁切时返回以分号为分隔符的多个全路径.		
*@return
	- @ref ERR_NONE 成功
*@note 拍摄图像到文件，开启条码命名，身份证命名，多图裁切等功能时，实际照片文件名与输入的文件名会不同。
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention filePath 是一个可写的变量，且长度应满足应用要求。例如，满足多图裁切，最多裁切n张，则filepath的长度为n*最大路径长度。
*/
CAMSDK_API long camCaptureImageFile(long devIndex ,char * filePath);

/**@brief 内存拍照 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] width  图像的宽度
		[out] height 图像的高度
		[out] bpp 每个像素占用的bit数
*@return
	内存中图像数据
*@note
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention 
*/
CAMSDK_API char *camCaptureImageBuff(long devIndex,long &width,long &height,long &bpp);

/**@brief  保存图片
*
*@param [in] src 图像数据
*@param [in] width  图像的宽
*@param [in] height 图像的高
*@param [in] bpp 每个像素占用的bit数
*@param [in] filePath 保存为此文件（全路径）
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSaveImage(char *src,long width,long height,long bpp,char *filePath);

/**@brief  获得照片与预览的缩放比例。因为插值或stillpin预览与拍照的宽高不一样
*
*@param [in] devIndex 设备编号
*@param [out] fScaleX  照片与预览的X方向缩放比例
*@param [out] fScaleY  照片与预览的Y方向缩放比例
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetCaptureScale(long devIndex,float &fScaleX,float &fScaleY);

/**@brief 自动裁切 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] CropType 0不裁切，1单图裁切，2多图裁切，3单图裁切 & 补边
*@return 
	- @ref ERR_NONE 成功
*@note 设置自动裁切，可以开启视频之前设置，视频会显示绿框，框住裁切内容。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageAutoCrop(long devIndex ,long CropType); 

/**@brief 设置视频旋转方向
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] rotateMode 0: 不旋转 1:90度 2: 180度 3: 270度
*@return 
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageRotateMode(long devIndex,long rotateMode);

/**@brief 设置裁切区域
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] left 裁切区域左顶点的X坐标值
*@param [in] top  裁切区域左顶点的Y坐标值
*@param [in] right 裁切区域右底点的X坐标值
*@param [in] bottom 裁切区域右底点的Y坐标值
*@return 
	- @ref ERR_NONE 成功
*@note 裁切区域全置零即取消裁切
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageCusCropRect(long devIndex,long left,long top,long right,long bottom);

/**@brief 获取裁切区域
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] left 裁切区域左顶点的X坐标值
*@param [out] top  裁切区域左顶点的Y坐标值
*@param [out] right 裁切区域右底点的X坐标值
*@param [out] bottom 裁切区域右底点的Y坐标值
*@return 
	- @ref ERR_NONE 成功
*@pre @ref camInitCameraLib @ref camSetImageCusCropRect
*@attention
*/
CAMSDK_API long camGetImageCusCropRect(long devIndex,long &left,long &top,long &right,long &bottom);

/**@brief 设置裁切区域
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] param1 
*@param [in] param2 
*@param [in] param3 
*@param [in] param4 
*@param [in] type 
			- 0 关闭裁切 
			- 1 鼠标裁切 
			- 2 固定裁切 按后四个参数（即万分之一的比例值）设置裁切框 
			- 3 按英寸裁切。param1 param2 是单位为百分之1英寸的裁切区宽高。
*@return 
	- @ref ERR_NONE 成功
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageCusCropRectEx(long devIndex ,long param1, long param2, long param3, long param4, long type = 1 );

//获取自定义裁切框
//type 值类型
// 1 裁切框坐标值 
// 2 比例值。按四个参数（即万分之一的比例值）设置裁切框
// (未完成)3 英寸值。param1为宽,param2高,param3左右偏移,param4上下偏移（单位百分之英寸，默认居中）。
CAMSDK_API long camGetImageCusCropRectEx(long devIndex ,long param1, long param2, long param3, long param4, long type);

/**@brief 设置图像效果
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 效果类型：0-无效果，1-文档增强，2色彩增强，3-灰色(Gray)，4-黑白(Black & White)，
5-油画(Painterly)，6-怀旧(Nostalgic)，7-素描(Sketch)，8-边缘照亮(Glowing Edge)，
9-蓝冷(Cold Blue)，10-马赛克(Mosaic)，11-模糊(Blurry)，12-负片(Negative)。13

*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageAdjust(long devIndex,long type); 


/**@brief 设置印刷偏移矫正
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 效果类型：0-无效果，1-印刷偏移矫正

*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageOffsetCorrection(long devIndex,long type); 


/**@brief 补边
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 效果类型：0-无效果，1-补边

*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageFillBorder(long devIndex,long type); 


/**@brief 去噪
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] IsAvailabel 是否启用去噪功能。0-禁用，1-启用。
*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageDenoise(long devIndex,bool IsAvailabel);

/**@brief 设置图片色彩格式
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 0-彩色(24bpp)，1-灰度，2-黑白。
*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageColorStyle(long devIndex,long type);

/**@brief 设置图片DPI
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] xDPI 
*@param [in] yDPI 
*@return 
	- @ref ERR_NONE 成功
*@note （1）如果设置DPI后（camSetImageDPI），返回设置的DPI
	   （2）如果没有设置DPI，根据当前设置的分辨率返回DPI

*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageDPI(long devIndex,long xDPI,long yDPI);

/**@brief 获取图片DPI
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [out] xDPI，X方向DPI 
*@param [out] yDPI，Y方向DPI 
*@return 
	- @ref ERR_NONE 成功
*@note 设置DPI会修改分辨率
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetImageDPI(long devIndex,long &xDPI,long &yDPI);

/**@brief 设置水印
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] msg 水印内容。
*@param [in] type 水印位置，按九宫格划分左上角开始依次编号0~8九个位置。
*@param [in] fontSize 水印字体尺寸。
*@param [in] fontName 字体。
*@param [in] fItalic 水印字体风格，是否斜体。
*@param [in] fUnderline 水印字体风格，是否下划线。
*@param [in] fWeight 水印字体风格，是否粗体。
*@param [in] angle 水印旋转角度，值范围0~360。
*@param [in] transparent 水印透明度，值范围 0~100。
*@param [in] colorR RGB之红色值，值范围0~255。
*@param [in] colorG RGB之绿色值，值范围0~255。
*@param [in] colorB RGB之蓝色值，值范围0~255。
*@param [in] isAvailabel 水印是否生效。1则生效，0不生效。
*@return 
	- @ref ERR_NONE 成功
*@note 可以开启视频之前设置。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageWaterMark(long devIndex,char * msg,long type,long fontSize,char * font,bool fItalic,bool fUnderline,bool fWeight,
	float angle,float transparent,long colorR,long colorG,long colorB,bool isAvailabel);

/**@brief  拍照启用防篡改标记
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] IsAvailabel 防篡改是否使能，0-禁用，1-启用
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageFileSign(long devIndex,bool IsAvailabel);

/**@brief 检查图片是否有防篡改标记 
*
*@param [in] filePath 要检查的图片的全路径
*@param [out] ret 检查结果，TURE 有标记，FALSE 无标记
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCheckImageFileSign(char *filePath,bool &ret);

/**@brief 开启连拍消息（注册连拍回调）
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] type 0监测模式，1定时模式
*@param [in] param 即callBackAutoCapture回调中数值上限。
*@param [in] fun @ref callBackAutoCapture 回调函数，获得计数或计时得知拍照时机。
*@return 
	- @ref ERR_NONE 成功
*@note 开启连拍并不会拍照，需在回调函数里根据状态值调用拍照接口拍照。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camStartAutoCapture(long devIndex,long type,long param,callBackAutoCapture fun);


CAMSDK_API long camPauseAutoCapture(long devIndex,long lstyle);
/**@brief 停止连拍消息
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return 
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camStartAutoCapture
*@attention
*/
CAMSDK_API long camStopAutoCapture(long devIndex); 

/**@brief 图片合并
*
*@param [in] imageFilePath1 要合并图像文件全路径。
*@param [in] imageFilePath2 要合并图像文件全路径。
*@param [in] imageFilePath 最终要生成的图像文件全路径。
*@param [in] type 图1与图2合并为一张图的位置关系。值为0~9。	
	type的意义：
	- 0-图像2叠加在图像1
	- 1-图像2在图像1左侧上方，不叠加
	- 2-图像2在图像1上方左侧，不叠加
	- 3-图像2在图像1上方右侧，不叠加
	- 4-图像2在图像1右侧上方，不叠加
	- 5-图像2在图像1右侧下方，不叠加
	- 6-图像2在图像1下方右侧，不叠加
	- 7-图像2在图像1下方左侧，不叠加
	- 8-图像2在图像1左侧下方，不叠加
	- 9-图像1和2上下排列，并且中间间隔一倍距离（身份证或银行卡用）
*@param [in] offsetX 重叠模式type = 0时使用，图2在图1上X轴位置偏移量
*@param [in] offsetY 重叠模式type = 0时使用，图2在图1上Y轴位置偏移量
*@param [in] Image2width 重叠模式type = 0时使用，缩放图2的宽
*@param [in] Image2height 重叠模式type = 0时使用，缩放图2的高
*@return 
	- @ref ERR_NONE 成功
	- @ref ERR_SAVEIMAGEFAILD 保存图片失败
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombineImage(char *imageFilePath1,char *imageFilePath2,char *imageFilePath,long type,long offsetX = 0,long offsetY = 0,long Image2width = 0,long Image2height = 0); 

/**@brief 设置照片旋转方向
*
*@param [in] imageFilePath 照片（全路径）
*@param [in] rotateMode 0: 不旋转 1:90度 2: 180度 3: 270度 4: 自动裁切纠偏
*@return 
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRotateImage(char *imageFilePath,long rotateMode);
#endif

#pragma region _CAMDLL_RECORD
/**@brief 获取系统麦克风个数
*
*@param [out] count 麦克风个数
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetAudioDevCount(long &count);

/**@brief 获取麦克风名称
*
*@param [in] devIndex 麦克风序号,0号开始
*@return
	- 麦克风名称
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetAudioDevName(long devIndex);

CAMSDK_API long camGetAudioDevNameEx(long devIndex,char * devName);

/**@brief 获得支持的录像格式个数 
*
*@param [out] lCount 录像格式个数
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  
*/
CAMSDK_API long camGetVideoEncodeCount(long &lCount);

/**@brief 获得录像格式名称 
*
*@param [in] Index 录像格式ID
*@param [out] sEncodeName 获得指定ID的录像格式名称
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre
*/
CAMSDK_API long camGetVideoEncodeName(long Index,char * sEncodeName);

/**@brief 录像 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] filePath 要生成的录像文件
*@param [in] micphone 选用的麦克风ID
*@param [in] videoFormat 输出的录像文件格式ID
*@return
	- @ref ERR_NONE 成功
*	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camStartRecord(long devIndex,char * filePath,long micphone,long videoFormat,bool bRecordCam = true);

/**@brief 关闭录像 
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartRecord
*@attention
*/
CAMSDK_API long camStopRecord(long devIndex);

/**@brief 录像时获得麦克风音量
*
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@return 麦克风音量
*/
CAMSDK_API long camGetMicrophoneVolumeLevel();

//设置帧率，视频比特率，音频比特率
/**@brief 设置录像帧率、视频比特率、频比特率
*
*@param [in] lFPS 帧率,值小于等于0时启用默认值。
*@param [in] lVideoBitrate 视频比特率，值小于等于0时启用默认值。
*@param [in] lAudioBitrate 音频比特率，值小于等于0时启用默认值。
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetRecordRate(long lFPS, long lVideoBitrate, long lAudioBitrate);

/**@brief 设置多路录像
*
*@param [in] lWidth 录像视频的宽
*@param [in] lHeight 录像视频的高
*@param [in] lLayoutMode 视频布局，即摄像头排列方式： 0横向顶对齐，1横向底对齐，2竖向左对齐，3竖向右对齐。
*@param [in] lRecordMode 录制选项，一般设置为0即可。0使用当前设置录像，-1使用原多路录像，其它值预留可用于定制或录屏等。
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetMultiRecordParam(long lLayoutMode,long offsetX[10],long offsetY[10],long ImageWidth[10],long ImageHeight[10]);

/**@brief 开始多路录像 
*
*@param [in] arrCamID[99] 有序的摄像头序号,依此次序排列视频录像，且在每两个视频相接处有时间水印。
*@param [in] nCamIDCount 有效的摄像头个数。
*@param [in] filePath 要生成的录像文件
*@param [in] micphone 选用的麦克风ID
*@param [in] videoFormat 输出的录像文件格式ID
*@param [in] nCompressionRadio 压缩率值范围0~55，值越大画面质量越好文件越大。
*@return
	- @ref ERR_NONE 成功
*	- @ref ERR_OUTOFBOUNDS 不存在的设备ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camStartMultiRecord(long arrCamID[10],long nCamIDCount,char * filePath,long micphone,long videoFormat,int nCompressionRadio = 25);

/**@brief 关闭多路录像 
*
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartMultiRecord
*@attention
*/
CAMSDK_API long camStopMultiRecord();

/**@brief 获得多路录像麦克风音量
*
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartMultiRecord
*@attention
*/
#pragma endregion _CAMDLL_RECORD

#if _CAMDLL_FILE_OPERATION
/**@brief 显示图片 
*
*@param [in] filePath 要预览的图片的全路径
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camShowImage(char *filePath);

/**@brief 删除文件 
*
*@param [in] filePath 要删除的文件的全路径
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camDeleteFile(char *filePath);

/**@brief 创建目录 
*
*@param [in] dirPath 要创建的目录
*@return
	- @ref ERR_NONE 成功
*@note 不支持级联创建。
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camCreateDirectory(char *dirPath);

/**@brief 重命名文件名称 
*
*@param [in] filePath 文件名称
*@param [in] newFilePath 修改名称
*@return
	- @ref ERR_NONE 成功
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camRenameFile(char *filePath,char *newFilePath);

/**@brief 获取目录下文件数量
*
*@param [out] lCount 搜索到的文件数量
*@param [in] cDirectory 目录路径,不搜索子目录
*@param [in] fileType 文件类型，可指定搜索的文件类型。详见枚举 CAMSDK_SEARCH_FILE
*@return 
	- @ref ERR_NONE 成功
	- @ref ERR_INVALIDPATH 无效的目录路径
*@note fileType示例：搜索bmp和jpg 则fileType = FILE_BMP|FILE_JPG;或fileType = FILE_BMP+FILE_JPG;
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDirectoryFileCount(long &lCount,char* cDirectory,long fileType = 0xFFFF);

/**@brief 获取搜索到的文件名
*
*@param [in] nIndex 文件序号，0号开始到搜索到的lCount-1
*@param [out] cFileName 文件名称。请申请足够的内存保存文件名。
*@return 
	- @ref ERR_NONE 成功
	- @ref ERR_NULLPOINT cFileName地址为NULL，不可写入文件名。
	- @ref ERR_OUTOFBOUNDS 无效的nIndex
*@note 
	调用示例：
	//初始化
	camInitCameraLib();
	//搜索该目录中文件（不包含子目录中文件）
	long n = 0;
	long lRet = camGetDirectoryFileCount(n，L"d:\\", FILE_ALL); //枚举FILE_ALL = 0XFFFF = 65535所有类型见枚举CAMSDK_SEARCH_FILE
	//获得文件名称
	for(int i = 0; i < n; ++i)
	{
		char cFileName[MAX_PATH] = {0};
		long lRet = camGetFileNameOnDirectory(n-1,cFileName);
	}
*@pre @ref camInitCameraLib @ref camGetDirectoryFileCount
*@attention
*/
CAMSDK_API long camGetFileNameOnDirectory(long nIndex,char *cFileName);

/**@brief 文件Base64编码 
*
*@param [in] filePath 需转Base64的图片文件全路径
*@return
	- Base64编码的图片数据。
*@note 
*@pre @ref camInitCameraLib
*@attention 
*/
CAMSDK_API char* FileEncodeBase64(char* filePath);

/**@brief 图片文件加到PDF队列
*
*@param [in] filePath 需导出PDF的图片文件全路径
*@return
	- @ref ERR_NONE 成功
*@note 配和接口@ref CombinePDF 实现单张或多张图片转为一个PDF文件输出。加到队列的图片在执行合并@ref CombinePDF 后会自动清空。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camAddFileToPDFList(char *filePath);

/**@brief 导出PDF文件
*
*@param [in] pdfFilePath 导出的PDF文件（全路径）
*@param [in] lJpegQuality 压缩率，值范围1~100。先压缩再并输出PDF前
*@return
	- @ref ERR_NONE 成功
*@note 输出的PDF是由@ref AddFileToPDFList 导入的图片队列生成的。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombinePDF(char *pdfFilePath,long nJpegQuality);

/**@brief 图片文件加到TIF队列
*
*@param [in] filePath 需导出PDF的图片文件全路径
*@return
	- @ref ERR_NONE 成功
*@note 配和接口@ref CombineTIF 实现单张或多张图片转为一个TIF文件输出。加到队列的图片在执行合并@ref CombineTIF 后会自动清空。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camAddFileToTIFList(char *filePath);

/**@brief 导出TIF文件
*
*@param [in] tifFilePath 导出的TIF文件（全路径）
*@return
	- @ref ERR_NONE 成功
*@note 输出的TIF是由@ref AddFileToTIFList 导入的图片队列生成的。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombineTIF(char *tifFilePath);

/**@brief HTTP上传文件
*
*@param [in] filePath 导出的TIF文件全路径。
*@param [in] url 服务端HTTP连接。
*@param [in] param 自定义信息，可为空。
*@param [out] response 服务器应答内容，可能是空
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camUpdataFileHttp(char *filePath,char *url,char *param,char *response);

/**@brief FTP上传文件
*
*@param [in] filePath 需上传的文件的全路径。
*@param [in] ftpPath FTP服务地址。
*@param [in] userName ftp用户名。
*@param [in] userPsd ftp用户密码。
*@param [in] targetName 在ftp服务器端生成的文件存储名。
*@return
	- @ref ERR_NONE 成功,
	-1上传失败 
	-2登陆服务器根路径失败
	-3 创建子文件夹失败 
	-4 断开连接失败 
	-5 连接失败
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camUpdataFileFtp(char *filePath,char *ftpPath,char *userName,char *userPsd,char *targetName);
#endif

#if _CAMDLL_BARCODE
/**@brief 条码模块初始化
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long coderInitBarcoder();

/**@brief 条码模块反初始化
*
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long coderUnInitBarcoder();

/**@brief 启用条码命名功能
*
*条码命名功能指高拍仪拍摄条码时，拍照接口内部会调用条码识别，以识别结果重命名照片文件。
*@param [in] devIndex 设备ID，即摄像头序号,0号开始
*@param [in] bIsAvailabel 是否启用条码命名，0-禁用，1-启用。
*@param [in] left 裁切区域左顶点的X坐标值
*@param [in] top  裁切区域左顶点的Y坐标值
*@param [in] right 裁切区域右底点的X坐标值
*@param [in] bottom 裁切区域右底点的Y坐标值
*@return
	- @ref ERR_NONE 成功
*@note 裁切用于指定图片中条码位置能提高大图中条码的识别率。若不裁切，裁切区域坐标全设置为零：0。
*@pre @ref InitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long coderNameByBarcode(long devIndex,bool bIsAvailabel,long left,long top ,long right,long bottom);

/**@brief 条码二维码识别
*
*@param [in] src 需识别的条码\二维码图片全路径。
*@param [in] left 裁切区域左顶点的X坐标值
*@param [in] top  裁切区域左顶点的Y坐标值
*@param [in] right 裁切区域右底点的X坐标值
*@param [in] bottom 裁切区域右底点的Y坐标值
*@return 
	- 识别结果
*@note 裁切用于指定图片中条码位置提高大图中条码的识别率。若不裁切，裁切区域坐标全设置为零：0。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *coderRecognizeBarcode(char *src,long left,long top,long right,long bottom);
CAMSDK_API long coderRecognizeBarcode2(char *src,long left,long top,long right,long bottom,char * ret);

CAMSDK_API long coderRecognizeBarcode3(char *src,long left,long top,long right,long bottom,long & lcount);

CAMSDK_API long coderGetCodeText(long index,char * ret,long & lsize);
/**@brief 条码二维码识别（内存）
*
*@param [in] src 图像数据，即视频回调提供的图像数据信息
*@param [in] width 图像宽，即视频回调提供的图像数据信息
*@param [in] height 图像高，即视频回调提供的图像数据信息
*@param [in] size bpp编码位数（24为真彩色）即视频回调提供的图像数据信息
*@param [in] left 裁切区域左顶点的X坐标值
*@param [in] top  裁切区域左顶点的Y坐标值
*@param [in] right 裁切区域右底点的X坐标值
*@param [in] bottom 裁切区域右底点的Y坐标值
*@return 
	- 识别结果
*@note 裁切用于指定图片中条码位置提高大图中条码的识别率。若不裁切，裁切区域坐标全设置为零：0。
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *coderRecognizeBarcodeByBuffer(byte *src,long width,long height,long size,long left,long top,long right,long bottom);
#endif

#if _CAMDLL_IDCARD 
/**@brief 身份证识别库初始化
*@prarm [无]
*@return
 @ref ERR_NONE 成功
*@note 初始化成功后，退出须反初始化
*/
CAMSDK_API long cardOCRInitIDCardOCR();

/**@brief 身份证识别库反初始化
*@prarm [无]
*@return
 @ref ERR_NONE 成功
*/
CAMSDK_API long cardOCRUnInitIDCardOCR();

/**@brief 识别身份证
*@param [in] imagePath识别图像路径
*@param [in] headerFilePath识别头像路径
*@return
	-识别结果，各项以竖线分开
*/
CAMSDK_API char *cardOCRRecognizeIDCard_OCR(char *imagePath,char *headerFilePath);

/**@brief 拍照时，识别证件命名照片
*@prarm [in] devIndex，设备ID，即摄像头序号,0号开始
*@prarm [in] NameType，0-不生效 1-姓名 2-身份证号
*@return
 @ref ERR_NONE 成功
*/
CAMSDK_API long cardOCRNameByIDCard(long devIndex,long n_NameType);
#endif

#if _CAMDLL_IDCARD_DEVICE 
/**@brief 身份证读卡器初始化
*@prarm [无]
*@return
 @ref ERR_NONE 成功
*@note 初始化成功后，退出须反初始化
*/
CAMSDK_API long idcardrfidInit();

/**@brief 身份证读卡器反初始化，断开读卡器
*@prarm [无]
*@return
 @ref ERR_NONE 反初始化成功
*/
CAMSDK_API long idcardrfidUnInit();

/**@brief 身份证读卡器读卡
*@prarm [in] Msg,身份证信息
*@prarm [in] headerFilePath,识别生成头像
*@return
 @ref ERR_NONE 成功
*/
CAMSDK_API long idcardrfidReadIDCard(BaseMsg &Msg,char* headerFilePath);
/**@brief 身份证读卡器读卡扩展
*@prarm [in] Msg,身份证信息，可读外国中文身份证
*@prarm [in] headerFilePath,识别生成头像
*@return
 @ref ERR_NONE 成功
*/
CAMSDK_API long idcardrfidReadIDCardEx(BaseMsgEx &MsgEx,char* headerFilePath);
/**@brief 身份证读卡器获取指纹
*@prarm [in] pcFPMsg，指纹数据（特征值）
*@prarm [in] nMsgSize，指纹数据长度
*@return
	- 值为-1时，表示没有指纹信息。
	- @ref ERR_NONE 成功
*/
CAMSDK_API long idcardrfidGetFingerprintMsg(unsigned char* pcFPMsg,long &nMsgSize);

/**@brief 身份证读卡器获取一个指纹
*@prarm [in] nIndex，指纹序号，由零开始的。
*@prarm [in] pcFPMsg，指纹数据（特征值）长度都是512
*@prarm [in] nFingerType，拇指类型,11 右手拇指，12 右手食指，13 右手中指 ，14 右手环指 ，15 右手小指 
16 左手拇指 ，17 左手食指 ，18 左手中指 ，19 左手环指 ，20 左手小指 ，97 右手不确定指位 ，98 左手不确定指位，99 其他不确定指位
*@return
	- 值为-1时，表示没有指纹信息。
	- @ref ERR_NONE 成功
*/
CAMSDK_API long idcardrfidGetOneFingerprintMsg(long nIndex,unsigned char* pcFPMsg, long &nFingerType );


//Young
CAMSDK_API long idcardrfidGetIDCardImage(long nType ,char* pFileFront, char* pFileBack = NULL);


#endif

#if _CAMDLL_FINGERPRINT_DEVICE 
/**@brief 指纹模块初始化
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintInit();

/**@brief 指纹模块反初始化
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintUnInit();

/**@brief 采集指纹
*
*@param [out] Bmp指纹图片。用于存储指纹BMP图片的内存空间，应不小于 512*512字节。
*@param [out] 指纹原始数据文件。用于存储指纹原始数据的内存空间，应不512*512 字节。
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintGetImage(unsigned char* pBmpBuff,unsigned char *pRawData);

/**@brief 获取指纹特征值
*
*@param [in] 已有的指纹原始数据。
*@param [out] 生成的指纹特征值。内存不小于1024字节。
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintGetFeature(const unsigned char *pRawData,unsigned char *pFeatureData);

/**@brief 异步采集指纹
*
*@param [in] funCB 函数原型typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData); pBmpBuff用于存储指纹BMP图片的内存空间，应不小于 512*512字节。pFeature指纹特征值，内存不小于1024字节。pUserData预留，未使用。
*@param [in] 预留，未使用。
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintStartGetFPDataAsync(callBackGetFPDataAsync funCB,void *pUserData);

/**@brief 停止异步采集指纹
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintStopGetFPDataAsync(); 

/**@brief 指纹对比
*
*@param [in] pFeature1 指纹特征值1。
*@param [in] pFeature2 指纹特征值2。
*@return
	-  
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintContrast(unsigned char* pFeature1,unsigned char *pFeature2);

/**@brief 设置指纹质量采集标准
*
*@param [in] Score 值范围0~100，值越大质量越高。
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintSetPrintQuality(long Score);
#endif

#if _CAMDLL_OCR 
/**@brief 获取OCR支持的语言个数
*
*@param [out] count 语言个数
*@return
*	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrGetLanguageCount(long &count);

/**@brief 获取OCR语言名称
*@param [in] index编号，从0开始
*@param [out] name语言名称
*@return
*	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrGetLanguageName(long index,char *name);

/**@brief 向OCR识别队列中添加图像
*@param [in] imagePath需要识别的图像路径
*@return
*	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrAddImageFileToOCRList(char *imagePath);

/**@brief 识别OCR队列中的图像并导出
*@param [in] filePath导出路径
*@param [in] nlanguage语言序号
*@return
*	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrCombineToFile(char *filePath,long nlanguage);

/**@brief OCR条码/二维码识别
*
*@prarm [in] src 照片路径，可识别图中多个码
*@prarm [in] codeType 编码类型 1条码 2二维码
*@prarm [out] count 识别出结果的个数
*@return
	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrRecognizeBarcode(char *src,long codeType,long &count);

/**@brief自动文字方向
*
*@prarm [in/out]filePath,输入为输入图片的路径，输出为输出图片的路径
*@param [in] nlanguage语言序号
*@return
	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrDetectOrientation(char *filePath,char * language);

/**@brief OCR获得条码/二维码识别结果
*
*@prarm [in] Index 识别结果ID
*@prarm [out] cText 识别出的文本结果
*@prarm [in/out] size 输入为cText的空间长度，输出为结果的长度。
*@return
	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrGetBarcodeText(long Index,char* cText,long &size);

//percentage识别进度,cancel是否取消, pInfo 保留、无用
typedef bool (CALLBACK * callBackProgress)(long nPos); 
/**@brief OCR获得进度与取消识别
*
*@prarm [in] callbackProgress 回调函数

*@return
	- @ref ERR_NONE 成功
*/
CAMSDK_API long ocrRegCallBackProgress(callBackProgress funCB);

CAMSDK_API long ocrCancelProcess();
#endif

#pragma region _CAMDLL_EXTERNAL_BUTTON 
/**@brief 外接按键模块初始化
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyOpenDevice();

/**@brief 外接按键模块反初始化
*
*@return
	- @ref ERR_NONE 成功
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyCloseDevice();

/**@brief 外接按键设置提示灯工作模式
*@param [in] bAuto  True表示自动模式。False表示手动模式，由接口KeySetLedState控制提示灯的状态
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeySetAutoLights(bool bAuto);

/**@brief 外接按键设置提示灯状态
*@param [in] lState 值意义：0-熄灭，1-绿色，2-红色，3-橙色（与红色很相近）
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeySetLedState(long lState);

/**@brief 外接按键获取状态，（注册回调函数）
*@param [in] funCB  函数指针，函数原型为typedef bool (CALLBACK * callBackKeyRecept)(long lData);其中lData值的意义1为按下2为抬起。
*@return
	- @ref ERR_NONE 成功
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyRegCallBackKeyRecept(callBackKeyRecept funCB);
#pragma endregion _CAMDLL_EXTERNAL_BUTTON 

#if _CAMDLL_OTR 
/**@brief OTR模块初始化
*
*@prarm [无]
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
	- @ref ERR_UNKNOW 失败
*/
CAMSDK_API long otrInit();

/**@brief OTR模块反初始化
*
*@prarm [无]
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*/
CAMSDK_API long otrUnInit();

/**@brief OTR模块获取模板支持数量
*
*@prarm [out] nCount 模板数量
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*/
CAMSDK_API long otrGetTemplateCount(long &nCount);

/**@brief OTR模块获取模板信息
*
*@prarm [in] nIndex 模板编号
*@prarm [out] chMsg 模板名称
*@prarm [in] nMsgSize 模板名称长度
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*@note chMsg长度要求至少为1024 
*/
CAMSDK_API long otrGetTemplateInfo(long nIndex, char* chMsg, long &nMsgSize);

/**@brief OTR模块识别
*
*@prarm [in] nIndex 模板编号
*@prarm [in] chPath 需要识别的图片

*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*@note chMsg长度要求至少为10000 
*/
CAMSDK_API long otrRecog(long nIndex, char* chPath);

/**@brief OTR模块获取识别区域数量
*
*@prarm [out] nCount 识别区域数量
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*/
CAMSDK_API long otrGetResultCount(long &nCount);

/**@brief OTR模块获取识别区域结果
*
*@prarm [in] nIndex 识别区域
*@prarm [out] chName 区域名称
*@prarm [out] chResult 区域结果
*@return
	- @ref ERR_NONE 成功
	- @ref ERR_NOLICENSE 没有授权
*/
CAMSDK_API long otrGetResultInfo(long nIndex,char* chName,char* chResult);
#endif


//#if CAPTUREANDCOMBINE
CAMSDK_API long camCaptureAndCombine(char * filePath,long devIndex1,long devIndex2,long lType = 0,long offsetX = 0,long offsetY = 0,long Image2width = 0,long Image2height = 0);
//#endif


//CAMSDK_API long camGetRectPos(int devIndex,MRectRArray* ptMRectRArray);


CAMSDK_API long camGetFwVersion(int devIndex,char * cVersion);

//HQC


CAMSDK_API long camInitHqc();

CAMSDK_API long camImageListToHqc(long count, const char* fileList[], const char* outPath,long type = 0 );

CAMSDK_API long camImageListToPdf(long count, const char* fileList[], const char* outPath,long type = 0);

CAMSDK_API long camRecImageListToHqc(long count, const char* fileList[], const char* outPath,long type = 0);

CAMSDK_API long camRecImageListToPdf(long count,const char* fileList[], const char* outPath,long type = 0);
//
CAMSDK_API long camImageToHqc(const char* filePath, const char* outPath,long type = 0);

CAMSDK_API long camImageToPdf(const char* filePath,const char* outPath,long type = 0);

CAMSDK_API long camRecImageToHqc(const char* filePath, const char* outPath,long type = 0);

CAMSDK_API long camRecImageToPdf(const char* filePath,const char* outPath,long type = 0);

CAMSDK_API long camSetFrequency(long devIndex ,long lFreq);

CAMSDK_API long camInitRfidEx();

CAMSDK_API long camGetBankCardInfo(BankBaseMsg &Msg);

CAMSDK_API long camGetSsseInfo(SsseBaseMsg &Msg);

CAMSDK_API long camGetCertIDcard(BaseMsg &Msg,char* headerFilePath);

CAMSDK_API long camGetBankCardInfoEx(BankBaseMsg &Msg);

CAMSDK_API long camGetMagCard(MagCardMsg &Msg);

CAMSDK_API long camSetPreviewImageFormat(long nType);