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
/** @addtogroup �ص�����
*@{
*/
/**��ƵԤ���ص�
*@param src �ڴ���������Ϊ��ǰ��Ƶͼ��
*@param width ͼ����
*@param height ͼ��߶�
*@param size bpp����λ����24Ϊ���ɫ��
*/
typedef bool (CALLBACK * callBackPreviewImage)(byte * src,long width,long height,long size); 

/**�豸�Ȳ�λص�
*@param deviceChangeType 
*/
typedef bool (CALLBACK * callBackDevChange)(CAMSDK_DEVCHANGE deviceChangeType); 

/**�豸����
*@param state ״ֵ̬�����������ģʽ����ʱģʽ����ֵ��ʾʱ�䵥λ�룻�Զ�ʶ��ģʽ����ֵ��ʾ�ȶ�֡����
*/
typedef bool (CALLBACK * callBackAutoCapture)(long state); 

/**��ȡָ������ֵ�ص�����
*@param pBmpBuff���ڴ洢ָ��BMPͼƬ���ڴ�ռ䣬Ӧ��С�� 512*512�ֽڡ�
*@param pFeatureָ������ֵ���ڴ治С��1024�ֽڡ�
*@param pUserDataԤ����δʹ�á�
*/
typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData);

/**��ȡ��Ӱ����ص�����
*@param lDataֵ������1Ϊ����2Ϊ̧��
*/
typedef bool (CALLBACK * callBackKeyRecept)(long lData); 
/**@}*/ //end of group �ص�����
#endif

#if _CAMDLL_SDK_OPERATION
/** @addtogroup SDK��������
*@{
*/
/**��ʼ��
*����DLL,ͬʱ��¼��ǰ�Ƿ�����Ȩ�豸
*@prarm [��]
*@return
	@ref ERR_NONE ��ʼ���ɹ�
	@ref ERR_NOLICENSE û����Ȩ
*@note ��ʼ���ɹ����˳��뷴��ʼ��
*/
CAMSDK_API long camInitCameraLib();

/**������Ϣ
*�����豸�������Ȩ��
*@prarm [��]
*@return
 @ref ERR_NONE �ɹ�
 @ref ERR_NOLICENSE û����Ȩ
*@note camInitCameraLib�����camUpdateCameraLib����˵���
*/
CAMSDK_API long camUpdateCameraLib();

/**ͳһֹͣ��Ƶģ��Ĺ���������
*��1��ֹͣ��ǰ�Ѿ���ͨ����ͷ
*��2���ͷ���������ͷ
*@prarm [��]
*@return
 @ref ERR_NONE �ɹ�
*/
CAMSDK_API long camStopCameraLib();


/**����ʼ��
*@prarm [��]
*@return
	@ref ERR_NONE ����ʼ���ɹ�
*/
CAMSDK_API long camUnInitCameraLib();
/**@}*/ //end of group SDK��������
#endif

#if _CAMDLL_DEVICE_INFORMATION
/** @addtogroup ��ȡ�豸��Ϣ
*@{
*/
/**@brief ��ȡ����ͷ����
*
*@param [out] count �豸����
*@return
*	- @ref ERR_NONE �ɹ�
*@note �豸����ʽ ���� ������  ��θ�����ͷ  �ٴ� ƾ֤����ͷ �������
*@pre  ��ִ��@ref camInitCameraLib
*/
CAMSDK_API long camGetDevCount(long & count);
CAMSDK_API long camGetDevCountCur(long & count);

/**@brief ��ȡ�豸����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] type �豸���� 0:��ͷ 1:��ͷ  2:ƾ֤����ͷ 99:����
*@return
*	- @ref ERR_NONE �ɹ�
*	- @ref ERR_OUTOFBOUNDS ��ѯ�������豸ID
*	- @ref ERR_NULLPOINT �豸��Ϣ�ǿ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevType(long devIndex ,long & type); 

/**@brief ��ȡ�豸��
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
*	- ����ͷ���豸�������е�����
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char * camGetDevName(long devIndex );

/**@brief ��ȡ�豸VID
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] strvid �豸VID�ַ���
*@return
*	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevVid(long devIndex ,char * strvid);

/**@brief ��ȡ�豸PID
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] strpid �豸PID�ַ���
*@return
*	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDevPid(long devIndex ,char * strpid);


CAMSDK_API long camGetDevDimension(long devIndex ,char * strDimension);
/**@brief ��ȡ�ֱ��ʸ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] subtype ý���ʽID��0�ſ�ʼ
*@param [out] count ���ָ���豸ָ����ʽ֧�ֵķֱ��ʸ���
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetResolutionCount(long devIndex ,long subtype ,long & count);

/**@brief ��ȡָ���ֱ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] subtype ý���ʽID��0�ſ�ʼ
*@param [in] index �ֱ���ID��0�ſ�ʼ
*@param [out] width ���ָ���豸ָ����ʽָ����ŵķֱ��ʵĿ�
*@param [out] height ���ָ���豸ָ����ʽָ����ŵķֱ��ʵĸ�
*@return
*	- @ref ERR_NONE �ɹ�
*	- @ref ERR_OUTOFBOUNDS ��ѯ�������豸ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetResolution(long devIndex ,long subtype,long index,long & width,long & height);

/**@brief ��������Ƶ�л��ֱ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] width ָ���ֱ��ʵĿ�
*@param [in] height ָ���ֱ��ʵĸ�
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetResolution(long devIndex,long width,long height);

/**@brief ��õ�ǰ��Ƶ��ʽ���ֱ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] subtype ���ָ���豸��ǰý���ʽ
*@param [out] width ���ָ���豸��ǰ�ֱ��ʵĿ�
*@param [out] height ���ָ���豸��ǰ�ֱ��ʵĸ�
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS ��ѯ������ͷID������
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetCurResolution(long devIndex,long &subtype,long &width,long &height);

/**@brief ��ȡ��Ƶ��ʽ����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] count ���豸֧�ֵ���Ƶ��ʽ����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetMediaTypeCount(long devIndex ,long & count);

/**@brief ��ȡ��Ƶ��ʽ����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] index ý���ʽID��0�ſ�ʼ
*@return
	ý���ʽ���ƣ����磺MJPEG��YUY2��
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API char * camGetMediaTypeName(long devIndex  ,long index);

CAMSDK_API long camGetMediaTypeNameEx(long devIndex  ,long index,char * subMediaType);

/**@brief ������Ƶ��ʽ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] subtypeIndex ý���ʽID��0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetMediaType(long devIndex  ,long subtypeIndex);

/**@brief �жϵ�ǰ����ͷ�Ƿ�ΪStillPinģʽ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- True����ǰΪStillPinģʽ
    - False����ǰ��ΪStillPinģʽ����������
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API bool camIsStillPin(long devIndex);

/**@brief �Ƿ�����StillPinģʽ(����ͷ��֧������Ч)
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] IsEnable 0ֵ�����ã���0ֵ����
*@return
	- True����ǰΪStillPinģʽ
    - False����ǰ��ΪStillPinģʽ����������
*@note �˽ӿڱ�����camOpenDev֮ǰ���á�
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
//�˽ӿ���������ƫ�ļ�鹤�ߣ�����stillpinģʽ��ͼ��
//��BUG����������ͷ�����Stillpin�ٷ�����
//�˽ӿڱ�����camOpenDev֮ǰ���á�
CAMSDK_API long camEnableStillPin(long devIndex, long IsEnable);

/**@brief StillPinģʽ����Ԥ���ֱ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] width ָ���ֱ��ʵĿ�
*@param [in] height ָ���ֱ��ʵĸ�
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
	- @ref ERR_SETRESOLUTIONFAILD ���÷ֱ���ʧ��
	- @ref ERR_STARTVIDEOFAILD ������Ƶʧ��
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetPreviewResolution(long devIndex,long width,long height);

CAMSDK_API long camGetCurPreviewResolution(long devIndex,long &subtype,long &width,long &height);

/**@brief StillPinģʽ����Ԥ����Ƶ��ʽ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] subtypeIndex ý���ʽID��0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
	- @ref ERR_SETRESOLUTIONFAILD ���÷ֱ���ʧ��
	- @ref ERR_STARTVIDEOFAILD ������Ƶʧ��
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetPreviewMediaType(long devIndex,long subtypeIndex);
/**@}*/ //end of group ��ȡ�豸��Ϣ
#endif

#if _CAMDLL_EQUIPMENT_OPERATION
/**@brief ����Ƶ�豸
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] subtype ý���ʽID����ͬ�豸֧�ֵĸ�ʽ���ܲ�ͬ��
					 ����0��mjpeg��1��yuy2����֧��mjpeg���豸�� 0��yuy2��
					 ��ͨ��@ref camGetMediaTypeCount ��@ref camGetMediaTypeName ��ѯ
*@param [in] width ָ���ֱ��ʿ�����Ϊ0���豸��֧�ָ÷ֱ���ʱ��Ĭ�������ֱ濪����Ƶ
*@param [in] height ָ���ֱ��ʸߣ�����Ϊ0���豸��֧�ָ÷ֱ���ʱ��Ĭ�������ֱ濪����Ƶ
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
	- @ref ERR_OPENDEVFAILD ������ͷʧ��
	- @ref ERR_STARTVIDEOFAILD ��������ͷʧ��
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
//mediaType Ĭ��ͨ�������ļ� Ĭ�����ֱ���
CAMSDK_API 	long camOpenDev(long devIndex ,long subtype,long width,long height);


CAMSDK_API 	long camPause(long devIndex ,long lstyle);
/**@brief �ر���Ƶ�豸
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCloseDev(long devIndex);

/**@brief ע���Ȳ����Ϣ�ص�
*
*@param [in] fun �Ȳ�λص����� @ref callBackDevChange
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note ÿ�γ�ʼ����ע��һ�μ��ɡ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegCallBackDeviceChange(callBackDevChange fun);

/**@brief ע���Ȳ����Ϣ�ص����ɣ�
*
*@param [in] fun �Ȳ�λص����� @ref callBackDevChange
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note ÿ�γ�ʼ����ע��һ�μ��ɡ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegOutCallBackDeviceChange(callBackDevChange fun);
#endif

#if _CAMDLL_DEVICE_PREVIEW
/**@brief ע����Ƶͼ��ص�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] fun ��Ƶͼ��ص����� @ref callBackPreviewImage
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegCallBackPreviewImage(long devIndex,callBackPreviewImage fun);

/**@brief ע����Ƶͼ��ص����ɣ�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] fun ��Ƶͼ��ص����� @ref callBackPreviewImage
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRegOutCallBackGetPreviewImage(long devIndex,callBackPreviewImage fun);






/**@brief ����Ԥ������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] lwidth �����Ƶ���
*@param [in] lheight �����Ƶ�߶�
*@param [in] lleft ltop lright lbottom ��Ƶ��ҪԤ������
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre @ref camRegOutCallBackGetPreviewImage
*@attention
*/
CAMSDK_API long camSetCallBackImageSize(long devIndex , float fResizeScale);



/**@brief ����Ԥ������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
@param [in] hPreviewWindow ���ھ��
*@return
*	- @ref ERR_NONE �ɹ�
*	- @ref ERR_OUTOFBOUNDS ��ѯ�������豸ID
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetPreviewWindow(long devIndex  ,HWND hPreviewWindow);
CAMSDK_API long camSetPreviewHalfImage(long devIndex  ,bool bHalfImage);
CAMSDK_API long camSetPreviewRectColor(long devIndex , byte r,byte g,byte b);
CAMSDK_API long camSetPreviewText(long devIndex , char * text);
/**@brief ��Ƶ�Ŵ�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camZooIn(long devIndex); 

/**@brief ��Ƶ��С
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camZoomOut(long devIndex); 

/**@brief ��Ƶ�����ʱ�����ʾ������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camOptimalPreview(long devIndex); 

/**@brief ��Ƶ��ԭʼ������ʾ������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camOriginalPreview(long devIndex);
#endif

#pragma region _CAMDLL_EQUIPMENT_ADVANCED_OPERATION 


/**@brief ��ȡ�豸���к�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- �豸���к� 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevSN(long devIndex);

/**@brief ��ȡ�豸���к�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- �豸���к� 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevSNFromDev(long devIndex);

/**@brief ��ȡ�豸�Զ������к�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- �Զ����豸���к� 
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetDevCusSN(long devIndex);





/**@brief ��⵱ǰ�豸�Ƿ�����Ȩ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] ret�Ƿ���Ȩ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camDevCheckLicense(int devIndex,bool & ret);

/**@brief ��ѯ�豸�Ƿ�һ���Խ��豸
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ǶԽ��豸
	- @ref ERR_NONSUPPORT ���ǶԽ��豸
	- @ref ERR_OUTOFBOUNDS ��Ч��devIndex
	- @ref ERR_NULLPOINT û���豸��Ϣ
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camIsAutoFocus(long devIndex);

/**@brief һ���Խ��Զ��Խ� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type 0��ʾһ���Խ���1��ʾ�Զ��Խ�
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camAutoFocus(long devIndex,long type); 



/**@brief ��ȡ�Խ�ֵ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] lvalue ��ǰ�Խ�ֵ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camGetFocusValue(long devIndex,long & lvalue); 

/**@brief ���öԽ�ֵ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] lvalue ��ǰ�Խ�ֵ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*/
CAMSDK_API long camSetFocusValue(long devIndex,long lvalue); 


/**@brief �豸����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] Count �������
*@param [in] Duration һ������ʱ������λms
*@param [in] Interval ÿ��������ʱ�䣬��λms
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention 
*/
CAMSDK_API long camEnableBuzzer(long devIndex, long Count = 3, long duration = 500, long interval = 500);

/**@brief ��ô��ذ�ť״̬
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return 
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
	- @ref ERR_OUTOFBOUNDS ��Ч��devIndex
	- @ref ERR_NONSUPPORT ���豸��֧��
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetSnapState(long devIndex);




#pragma endregion _CAMDLL_EQUIPMENT_ADVANCED_OPERATION

#if _CAMDLL_UVC_DRIVE
/**@brief ��ȡUVC������ƵЧ�� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] para1 0����ƵProc Amp �� 1������ͷ����CameraContrl
*@param [in] para2
	- Video Proc Amp�������0-���ȣ�1-�Աȶȣ�2-ɫ�࣬3-���Ͷȣ�4-�����ȣ�5-٤�꣬6-������ɫ��7-��ƽ�⣬8-���ⲹ����9-���档
	- CameraContrl�������0-ȫ����1-��б��2-������3-���ţ�4-�ع⣬5-���նȲ�����6-�Խ���
*@param [out] min ����ֵ��Χ����Сֵ
*@param [out] max ����ֵ��Χ�����ֵ
*@param [out] lvalue ��ǰ����ֵ
*@param [out] ldefault ��ʼĬ��ֵ
*@param [out] flag ��־λ��1�����Զ����� 2�����ֶ����� 3�����Զ�Ҳ���ֶ�����
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_UNKNOW ʧ��
	- @ref ERR_OUTOFBOUNDS devIndex��Ч����ѯ���豸������
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camGetVideoParameter(long devIndex,long para1,long para2,long & min,long & max,long & lvalue,long & ldefault,long & flag); 

/**@brief ����UVC������ƵЧ�� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] para1 0����ƵProc Amp �� 1������ͷ����CameraContrl
*@param [in] para2
	- Video Proc Amp�������0-���ȣ�1-�Աȶȣ�2-ɫ�࣬3-���Ͷȣ�4-�����ȣ�5-٤�꣬6-������ɫ��7-��ƽ�⣬8-���ⲹ����9-���档
	- CameraContrl�������0-ȫ����1-��б��2-������3-���ţ�4-�ع⣬5-���նȲ�����6-�Խ���
*@param [in] lvalue ��������ֵ
*@param [in] flag ��־λ��1���Զ����� 2���ֶ�����
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_UNKNOW ʧ��
	- @ref ERR_OUTOFBOUNDS devIndex��Ч����ѯ���豸������
*@note �豸��һ��֧�������������ԣ�֧������ӷ�Χ��� @ref camShowImageSettingWindow �� @ref camShowDevSettingWindow �����еĿ������
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetVideoParameter(long devIndex  ,long para1,long para2,long lvalue,long flag);

/**@brief ��������ƵЧ�������ô���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camShowImageSettingWindow(long devIndex);

/**@brief ��������Ƶ���ԡ����ô���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camShowDevSettingWindow(long devIndex);
#endif

#if _CAMDLL_CAPTURE
/**@brief ����JPGѹ���� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] quanlity ѹ����ֵ��Χ��0~100��100��ѹ����������óߴ����
*@return 
	- @ref ERR_NONE �ɹ�
*@note ���ô洢ͼ��(����)��JPGѹ���ʣ����ڿ�����Ƶǰ���û�����ʱ���á�SDK��ʼ��jpg��ʽ��ƬĬ��ѹ���ʣ�������Ϊ55.
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetImageJPGQuanlity(long devIndex,long quanlity);

/**@brief ���� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] filePath ���ɵ���Ƭ��ȫ·����֧��jpg��bmp��png��pdf��
	    [out] filePath ����ʵ����Ƭ�ļ�ȫ·������ͼ����ʱ�����Էֺ�Ϊ�ָ����Ķ��ȫ·��.		
*@return
	- @ref ERR_NONE �ɹ�
*@note ����ͼ���ļ��������������������֤��������ͼ���еȹ���ʱ��ʵ����Ƭ�ļ�����������ļ����᲻ͬ��
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention filePath ��һ����д�ı������ҳ���Ӧ����Ӧ��Ҫ�����磬�����ͼ���У�������n�ţ���filepath�ĳ���Ϊn*���·�����ȡ�
*/
CAMSDK_API long camCaptureImageFile(long devIndex ,char * filePath);

/**@brief �ڴ����� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] width  ͼ��Ŀ��
		[out] height ͼ��ĸ߶�
		[out] bpp ÿ������ռ�õ�bit��
*@return
	�ڴ���ͼ������
*@note
*@pre @ref camInitCameraLib @ref camOpenDev
*@attention 
*/
CAMSDK_API char *camCaptureImageBuff(long devIndex,long &width,long &height,long &bpp);

/**@brief  ����ͼƬ
*
*@param [in] src ͼ������
*@param [in] width  ͼ��Ŀ�
*@param [in] height ͼ��ĸ�
*@param [in] bpp ÿ������ռ�õ�bit��
*@param [in] filePath ����Ϊ���ļ���ȫ·����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSaveImage(char *src,long width,long height,long bpp,char *filePath);

/**@brief  �����Ƭ��Ԥ�������ű�������Ϊ��ֵ��stillpinԤ�������յĿ�߲�һ��
*
*@param [in] devIndex �豸���
*@param [out] fScaleX  ��Ƭ��Ԥ����X�������ű���
*@param [out] fScaleY  ��Ƭ��Ԥ����Y�������ű���
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetCaptureScale(long devIndex,float &fScaleX,float &fScaleY);

/**@brief �Զ����� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] CropType 0�����У�1��ͼ���У�2��ͼ���У�3��ͼ���� & ����
*@return 
	- @ref ERR_NONE �ɹ�
*@note �����Զ����У����Կ�����Ƶ֮ǰ���ã���Ƶ����ʾ�̿򣬿�ס�������ݡ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageAutoCrop(long devIndex ,long CropType); 

/**@brief ������Ƶ��ת����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] rotateMode 0: ����ת 1:90�� 2: 180�� 3: 270��
*@return 
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageRotateMode(long devIndex,long rotateMode);

/**@brief ���ò�������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] left ���������󶥵��X����ֵ
*@param [in] top  ���������󶥵��Y����ֵ
*@param [in] right ���������ҵ׵��X����ֵ
*@param [in] bottom ���������ҵ׵��Y����ֵ
*@return 
	- @ref ERR_NONE �ɹ�
*@note ��������ȫ���㼴ȡ������
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageCusCropRect(long devIndex,long left,long top,long right,long bottom);

/**@brief ��ȡ��������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] left ���������󶥵��X����ֵ
*@param [out] top  ���������󶥵��Y����ֵ
*@param [out] right ���������ҵ׵��X����ֵ
*@param [out] bottom ���������ҵ׵��Y����ֵ
*@return 
	- @ref ERR_NONE �ɹ�
*@pre @ref camInitCameraLib @ref camSetImageCusCropRect
*@attention
*/
CAMSDK_API long camGetImageCusCropRect(long devIndex,long &left,long &top,long &right,long &bottom);

/**@brief ���ò�������
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] param1 
*@param [in] param2 
*@param [in] param3 
*@param [in] param4 
*@param [in] type 
			- 0 �رղ��� 
			- 1 ������ 
			- 2 �̶����� �����ĸ������������֮һ�ı���ֵ�����ò��п� 
			- 3 ��Ӣ����С�param1 param2 �ǵ�λΪ�ٷ�֮1Ӣ��Ĳ�������ߡ�
*@return 
	- @ref ERR_NONE �ɹ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageCusCropRectEx(long devIndex ,long param1, long param2, long param3, long param4, long type = 1 );

//��ȡ�Զ�����п�
//type ֵ����
// 1 ���п�����ֵ 
// 2 ����ֵ�����ĸ������������֮һ�ı���ֵ�����ò��п�
// (δ���)3 Ӣ��ֵ��param1Ϊ��,param2��,param3����ƫ��,param4����ƫ�ƣ���λ�ٷ�֮Ӣ�磬Ĭ�Ͼ��У���
CAMSDK_API long camGetImageCusCropRectEx(long devIndex ,long param1, long param2, long param3, long param4, long type);

/**@brief ����ͼ��Ч��
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type Ч�����ͣ�0-��Ч����1-�ĵ���ǿ��2ɫ����ǿ��3-��ɫ(Gray)��4-�ڰ�(Black & White)��
5-�ͻ�(Painterly)��6-����(Nostalgic)��7-����(Sketch)��8-��Ե����(Glowing Edge)��
9-����(Cold Blue)��10-������(Mosaic)��11-ģ��(Blurry)��12-��Ƭ(Negative)��13

*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageAdjust(long devIndex,long type); 


/**@brief ����ӡˢƫ�ƽ���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type Ч�����ͣ�0-��Ч����1-ӡˢƫ�ƽ���

*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageOffsetCorrection(long devIndex,long type); 


/**@brief ����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type Ч�����ͣ�0-��Ч����1-����

*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageFillBorder(long devIndex,long type); 


/**@brief ȥ��
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] IsAvailabel �Ƿ�����ȥ�빦�ܡ�0-���ã�1-���á�
*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageDenoise(long devIndex,bool IsAvailabel);

/**@brief ����ͼƬɫ�ʸ�ʽ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type 0-��ɫ(24bpp)��1-�Ҷȣ�2-�ڰס�
*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageColorStyle(long devIndex,long type);

/**@brief ����ͼƬDPI
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] xDPI 
*@param [in] yDPI 
*@return 
	- @ref ERR_NONE �ɹ�
*@note ��1���������DPI��camSetImageDPI�����������õ�DPI
	   ��2�����û������DPI�����ݵ�ǰ���õķֱ��ʷ���DPI

*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageDPI(long devIndex,long xDPI,long yDPI);

/**@brief ��ȡͼƬDPI
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] xDPI��X����DPI 
*@param [out] yDPI��Y����DPI 
*@return 
	- @ref ERR_NONE �ɹ�
*@note ����DPI���޸ķֱ���
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetImageDPI(long devIndex,long &xDPI,long &yDPI);

/**@brief ����ˮӡ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] msg ˮӡ���ݡ�
*@param [in] type ˮӡλ�ã����Ź��񻮷����Ͻǿ�ʼ���α��0~8�Ÿ�λ�á�
*@param [in] fontSize ˮӡ����ߴ硣
*@param [in] fontName ���塣
*@param [in] fItalic ˮӡ�������Ƿ�б�塣
*@param [in] fUnderline ˮӡ�������Ƿ��»��ߡ�
*@param [in] fWeight ˮӡ�������Ƿ���塣
*@param [in] angle ˮӡ��ת�Ƕȣ�ֵ��Χ0~360��
*@param [in] transparent ˮӡ͸���ȣ�ֵ��Χ 0~100��
*@param [in] colorR RGB֮��ɫֵ��ֵ��Χ0~255��
*@param [in] colorG RGB֮��ɫֵ��ֵ��Χ0~255��
*@param [in] colorB RGB֮��ɫֵ��ֵ��Χ0~255��
*@param [in] isAvailabel ˮӡ�Ƿ���Ч��1����Ч��0����Ч��
*@return 
	- @ref ERR_NONE �ɹ�
*@note ���Կ�����Ƶ֮ǰ���á�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageWaterMark(long devIndex,char * msg,long type,long fontSize,char * font,bool fItalic,bool fUnderline,bool fWeight,
	float angle,float transparent,long colorR,long colorG,long colorB,bool isAvailabel);

/**@brief  �������÷��۸ı��
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] IsAvailabel ���۸��Ƿ�ʹ�ܣ�0-���ã�1-����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camSetImageFileSign(long devIndex,bool IsAvailabel);

/**@brief ���ͼƬ�Ƿ��з��۸ı�� 
*
*@param [in] filePath Ҫ����ͼƬ��ȫ·��
*@param [out] ret �������TURE �б�ǣ�FALSE �ޱ��
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCheckImageFileSign(char *filePath,bool &ret);

/**@brief ����������Ϣ��ע�����Ļص���
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] type 0���ģʽ��1��ʱģʽ
*@param [in] param ��callBackAutoCapture�ص�����ֵ���ޡ�
*@param [in] fun @ref callBackAutoCapture �ص���������ü������ʱ��֪����ʱ����
*@return 
	- @ref ERR_NONE �ɹ�
*@note �������Ĳ��������գ����ڻص����������״ֵ̬�������սӿ����ա�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camStartAutoCapture(long devIndex,long type,long param,callBackAutoCapture fun);


CAMSDK_API long camPauseAutoCapture(long devIndex,long lstyle);
/**@brief ֹͣ������Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return 
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camStartAutoCapture
*@attention
*/
CAMSDK_API long camStopAutoCapture(long devIndex); 

/**@brief ͼƬ�ϲ�
*
*@param [in] imageFilePath1 Ҫ�ϲ�ͼ���ļ�ȫ·����
*@param [in] imageFilePath2 Ҫ�ϲ�ͼ���ļ�ȫ·����
*@param [in] imageFilePath ����Ҫ���ɵ�ͼ���ļ�ȫ·����
*@param [in] type ͼ1��ͼ2�ϲ�Ϊһ��ͼ��λ�ù�ϵ��ֵΪ0~9��	
	type�����壺
	- 0-ͼ��2������ͼ��1
	- 1-ͼ��2��ͼ��1����Ϸ���������
	- 2-ͼ��2��ͼ��1�Ϸ���࣬������
	- 3-ͼ��2��ͼ��1�Ϸ��Ҳ࣬������
	- 4-ͼ��2��ͼ��1�Ҳ��Ϸ���������
	- 5-ͼ��2��ͼ��1�Ҳ��·���������
	- 6-ͼ��2��ͼ��1�·��Ҳ࣬������
	- 7-ͼ��2��ͼ��1�·���࣬������
	- 8-ͼ��2��ͼ��1����·���������
	- 9-ͼ��1��2�������У������м���һ�����루���֤�����п��ã�
*@param [in] offsetX �ص�ģʽtype = 0ʱʹ�ã�ͼ2��ͼ1��X��λ��ƫ����
*@param [in] offsetY �ص�ģʽtype = 0ʱʹ�ã�ͼ2��ͼ1��Y��λ��ƫ����
*@param [in] Image2width �ص�ģʽtype = 0ʱʹ�ã�����ͼ2�Ŀ�
*@param [in] Image2height �ص�ģʽtype = 0ʱʹ�ã�����ͼ2�ĸ�
*@return 
	- @ref ERR_NONE �ɹ�
	- @ref ERR_SAVEIMAGEFAILD ����ͼƬʧ��
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombineImage(char *imageFilePath1,char *imageFilePath2,char *imageFilePath,long type,long offsetX = 0,long offsetY = 0,long Image2width = 0,long Image2height = 0); 

/**@brief ������Ƭ��ת����
*
*@param [in] imageFilePath ��Ƭ��ȫ·����
*@param [in] rotateMode 0: ����ת 1:90�� 2: 180�� 3: 270�� 4: �Զ����о�ƫ
*@return 
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camRotateImage(char *imageFilePath,long rotateMode);
#endif

#pragma region _CAMDLL_RECORD
/**@brief ��ȡϵͳ��˷����
*
*@param [out] count ��˷����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetAudioDevCount(long &count);

/**@brief ��ȡ��˷�����
*
*@param [in] devIndex ��˷����,0�ſ�ʼ
*@return
	- ��˷�����
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *camGetAudioDevName(long devIndex);

CAMSDK_API long camGetAudioDevNameEx(long devIndex,char * devName);

/**@brief ���֧�ֵ�¼���ʽ���� 
*
*@param [out] lCount ¼���ʽ����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  
*/
CAMSDK_API long camGetVideoEncodeCount(long &lCount);

/**@brief ���¼���ʽ���� 
*
*@param [in] Index ¼���ʽID
*@param [out] sEncodeName ���ָ��ID��¼���ʽ����
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre
*/
CAMSDK_API long camGetVideoEncodeName(long Index,char * sEncodeName);

/**@brief ¼�� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] filePath Ҫ���ɵ�¼���ļ�
*@param [in] micphone ѡ�õ���˷�ID
*@param [in] videoFormat �����¼���ļ���ʽID
*@return
	- @ref ERR_NONE �ɹ�
*	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camStartRecord(long devIndex,char * filePath,long micphone,long videoFormat,bool bRecordCam = true);

/**@brief �ر�¼�� 
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartRecord
*@attention
*/
CAMSDK_API long camStopRecord(long devIndex);

/**@brief ¼��ʱ�����˷�����
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@return ��˷�����
*/
CAMSDK_API long camGetMicrophoneVolumeLevel();

//����֡�ʣ���Ƶ�����ʣ���Ƶ������
/**@brief ����¼��֡�ʡ���Ƶ�����ʡ�Ƶ������
*
*@param [in] lFPS ֡��,ֵС�ڵ���0ʱ����Ĭ��ֵ��
*@param [in] lVideoBitrate ��Ƶ�����ʣ�ֵС�ڵ���0ʱ����Ĭ��ֵ��
*@param [in] lAudioBitrate ��Ƶ�����ʣ�ֵС�ڵ���0ʱ����Ĭ��ֵ��
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetRecordRate(long lFPS, long lVideoBitrate, long lAudioBitrate);

/**@brief ���ö�·¼��
*
*@param [in] lWidth ¼����Ƶ�Ŀ�
*@param [in] lHeight ¼����Ƶ�ĸ�
*@param [in] lLayoutMode ��Ƶ���֣�������ͷ���з�ʽ�� 0���򶥶��룬1����׶��룬2��������룬3�����Ҷ��롣
*@param [in] lRecordMode ¼��ѡ�һ������Ϊ0���ɡ�0ʹ�õ�ǰ����¼��-1ʹ��ԭ��·¼������ֵԤ�������ڶ��ƻ�¼���ȡ�
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camSetMultiRecordParam(long lLayoutMode,long offsetX[10],long offsetY[10],long ImageWidth[10],long ImageHeight[10]);

/**@brief ��ʼ��·¼�� 
*
*@param [in] arrCamID[99] ���������ͷ���,���˴���������Ƶ¼������ÿ������Ƶ��Ӵ���ʱ��ˮӡ��
*@param [in] nCamIDCount ��Ч������ͷ������
*@param [in] filePath Ҫ���ɵ�¼���ļ�
*@param [in] micphone ѡ�õ���˷�ID
*@param [in] videoFormat �����¼���ļ���ʽID
*@param [in] nCompressionRadio ѹ����ֵ��Χ0~55��ֵԽ��������Խ���ļ�Խ��
*@return
	- @ref ERR_NONE �ɹ�
*	- @ref ERR_OUTOFBOUNDS �����ڵ��豸ID
*@note 
*@pre  @ref camInitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long camStartMultiRecord(long arrCamID[10],long nCamIDCount,char * filePath,long micphone,long videoFormat,int nCompressionRadio = 25);

/**@brief �رն�·¼�� 
*
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartMultiRecord
*@attention
*/
CAMSDK_API long camStopMultiRecord();

/**@brief ��ö�·¼����˷�����
*
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib @ref camOpenDev @ref camStartMultiRecord
*@attention
*/
#pragma endregion _CAMDLL_RECORD

#if _CAMDLL_FILE_OPERATION
/**@brief ��ʾͼƬ 
*
*@param [in] filePath ҪԤ����ͼƬ��ȫ·��
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camShowImage(char *filePath);

/**@brief ɾ���ļ� 
*
*@param [in] filePath Ҫɾ�����ļ���ȫ·��
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camDeleteFile(char *filePath);

/**@brief ����Ŀ¼ 
*
*@param [in] dirPath Ҫ������Ŀ¼
*@return
	- @ref ERR_NONE �ɹ�
*@note ��֧�ּ���������
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camCreateDirectory(char *dirPath);

/**@brief �������ļ����� 
*
*@param [in] filePath �ļ�����
*@param [in] newFilePath �޸�����
*@return
	- @ref ERR_NONE �ɹ�
*@pre @ref camInitCameraLib
*/
CAMSDK_API long camRenameFile(char *filePath,char *newFilePath);

/**@brief ��ȡĿ¼���ļ�����
*
*@param [out] lCount ���������ļ�����
*@param [in] cDirectory Ŀ¼·��,��������Ŀ¼
*@param [in] fileType �ļ����ͣ���ָ���������ļ����͡����ö�� CAMSDK_SEARCH_FILE
*@return 
	- @ref ERR_NONE �ɹ�
	- @ref ERR_INVALIDPATH ��Ч��Ŀ¼·��
*@note fileTypeʾ��������bmp��jpg ��fileType = FILE_BMP|FILE_JPG;��fileType = FILE_BMP+FILE_JPG;
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camGetDirectoryFileCount(long &lCount,char* cDirectory,long fileType = 0xFFFF);

/**@brief ��ȡ���������ļ���
*
*@param [in] nIndex �ļ���ţ�0�ſ�ʼ����������lCount-1
*@param [out] cFileName �ļ����ơ��������㹻���ڴ汣���ļ�����
*@return 
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NULLPOINT cFileName��ַΪNULL������д���ļ�����
	- @ref ERR_OUTOFBOUNDS ��Ч��nIndex
*@note 
	����ʾ����
	//��ʼ��
	camInitCameraLib();
	//������Ŀ¼���ļ�����������Ŀ¼���ļ���
	long n = 0;
	long lRet = camGetDirectoryFileCount(n��L"d:\\", FILE_ALL); //ö��FILE_ALL = 0XFFFF = 65535�������ͼ�ö��CAMSDK_SEARCH_FILE
	//����ļ�����
	for(int i = 0; i < n; ++i)
	{
		char cFileName[MAX_PATH] = {0};
		long lRet = camGetFileNameOnDirectory(n-1,cFileName);
	}
*@pre @ref camInitCameraLib @ref camGetDirectoryFileCount
*@attention
*/
CAMSDK_API long camGetFileNameOnDirectory(long nIndex,char *cFileName);

/**@brief �ļ�Base64���� 
*
*@param [in] filePath ��תBase64��ͼƬ�ļ�ȫ·��
*@return
	- Base64�����ͼƬ���ݡ�
*@note 
*@pre @ref camInitCameraLib
*@attention 
*/
CAMSDK_API char* FileEncodeBase64(char* filePath);

/**@brief ͼƬ�ļ��ӵ�PDF����
*
*@param [in] filePath �赼��PDF��ͼƬ�ļ�ȫ·��
*@return
	- @ref ERR_NONE �ɹ�
*@note ��ͽӿ�@ref CombinePDF ʵ�ֵ��Ż����ͼƬתΪһ��PDF�ļ�������ӵ����е�ͼƬ��ִ�кϲ�@ref CombinePDF ����Զ���ա�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camAddFileToPDFList(char *filePath);

/**@brief ����PDF�ļ�
*
*@param [in] pdfFilePath ������PDF�ļ���ȫ·����
*@param [in] lJpegQuality ѹ���ʣ�ֵ��Χ1~100����ѹ���ٲ����PDFǰ
*@return
	- @ref ERR_NONE �ɹ�
*@note �����PDF����@ref AddFileToPDFList �����ͼƬ�������ɵġ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombinePDF(char *pdfFilePath,long nJpegQuality);

/**@brief ͼƬ�ļ��ӵ�TIF����
*
*@param [in] filePath �赼��PDF��ͼƬ�ļ�ȫ·��
*@return
	- @ref ERR_NONE �ɹ�
*@note ��ͽӿ�@ref CombineTIF ʵ�ֵ��Ż����ͼƬתΪһ��TIF�ļ�������ӵ����е�ͼƬ��ִ�кϲ�@ref CombineTIF ����Զ���ա�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camAddFileToTIFList(char *filePath);

/**@brief ����TIF�ļ�
*
*@param [in] tifFilePath ������TIF�ļ���ȫ·����
*@return
	- @ref ERR_NONE �ɹ�
*@note �����TIF����@ref AddFileToTIFList �����ͼƬ�������ɵġ�
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camCombineTIF(char *tifFilePath);

/**@brief HTTP�ϴ��ļ�
*
*@param [in] filePath ������TIF�ļ�ȫ·����
*@param [in] url �����HTTP���ӡ�
*@param [in] param �Զ�����Ϣ����Ϊ�ա�
*@param [out] response ������Ӧ�����ݣ������ǿ�
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camUpdataFileHttp(char *filePath,char *url,char *param,char *response);

/**@brief FTP�ϴ��ļ�
*
*@param [in] filePath ���ϴ����ļ���ȫ·����
*@param [in] ftpPath FTP�����ַ��
*@param [in] userName ftp�û�����
*@param [in] userPsd ftp�û����롣
*@param [in] targetName ��ftp�����������ɵ��ļ��洢����
*@return
	- @ref ERR_NONE �ɹ�,
	-1�ϴ�ʧ�� 
	-2��½��������·��ʧ��
	-3 �������ļ���ʧ�� 
	-4 �Ͽ�����ʧ�� 
	-5 ����ʧ��
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long camUpdataFileFtp(char *filePath,char *ftpPath,char *userName,char *userPsd,char *targetName);
#endif

#if _CAMDLL_BARCODE
/**@brief ����ģ���ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long coderInitBarcoder();

/**@brief ����ģ�鷴��ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long coderUnInitBarcoder();

/**@brief ����������������
*
*������������ָ��������������ʱ�����սӿ��ڲ����������ʶ����ʶ������������Ƭ�ļ���
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] bIsAvailabel �Ƿ���������������0-���ã�1-���á�
*@param [in] left ���������󶥵��X����ֵ
*@param [in] top  ���������󶥵��Y����ֵ
*@param [in] right ���������ҵ׵��X����ֵ
*@param [in] bottom ���������ҵ׵��Y����ֵ
*@return
	- @ref ERR_NONE �ɹ�
*@note ��������ָ��ͼƬ������λ������ߴ�ͼ�������ʶ���ʡ��������У�������������ȫ����Ϊ�㣺0��
*@pre @ref InitCameraLib @ref camOpenDev
*@attention
*/
CAMSDK_API long coderNameByBarcode(long devIndex,bool bIsAvailabel,long left,long top ,long right,long bottom);

/**@brief �����ά��ʶ��
*
*@param [in] src ��ʶ�������\��ά��ͼƬȫ·����
*@param [in] left ���������󶥵��X����ֵ
*@param [in] top  ���������󶥵��Y����ֵ
*@param [in] right ���������ҵ׵��X����ֵ
*@param [in] bottom ���������ҵ׵��Y����ֵ
*@return 
	- ʶ����
*@note ��������ָ��ͼƬ������λ����ߴ�ͼ�������ʶ���ʡ��������У�������������ȫ����Ϊ�㣺0��
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *coderRecognizeBarcode(char *src,long left,long top,long right,long bottom);
CAMSDK_API long coderRecognizeBarcode2(char *src,long left,long top,long right,long bottom,char * ret);

CAMSDK_API long coderRecognizeBarcode3(char *src,long left,long top,long right,long bottom,long & lcount);

CAMSDK_API long coderGetCodeText(long index,char * ret,long & lsize);
/**@brief �����ά��ʶ���ڴ棩
*
*@param [in] src ͼ�����ݣ�����Ƶ�ص��ṩ��ͼ��������Ϣ
*@param [in] width ͼ�������Ƶ�ص��ṩ��ͼ��������Ϣ
*@param [in] height ͼ��ߣ�����Ƶ�ص��ṩ��ͼ��������Ϣ
*@param [in] size bpp����λ����24Ϊ���ɫ������Ƶ�ص��ṩ��ͼ��������Ϣ
*@param [in] left ���������󶥵��X����ֵ
*@param [in] top  ���������󶥵��Y����ֵ
*@param [in] right ���������ҵ׵��X����ֵ
*@param [in] bottom ���������ҵ׵��Y����ֵ
*@return 
	- ʶ����
*@note ��������ָ��ͼƬ������λ����ߴ�ͼ�������ʶ���ʡ��������У�������������ȫ����Ϊ�㣺0��
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API char *coderRecognizeBarcodeByBuffer(byte *src,long width,long height,long size,long left,long top,long right,long bottom);
#endif

#if _CAMDLL_IDCARD 
/**@brief ���֤ʶ����ʼ��
*@prarm [��]
*@return
 @ref ERR_NONE �ɹ�
*@note ��ʼ���ɹ����˳��뷴��ʼ��
*/
CAMSDK_API long cardOCRInitIDCardOCR();

/**@brief ���֤ʶ��ⷴ��ʼ��
*@prarm [��]
*@return
 @ref ERR_NONE �ɹ�
*/
CAMSDK_API long cardOCRUnInitIDCardOCR();

/**@brief ʶ�����֤
*@param [in] imagePathʶ��ͼ��·��
*@param [in] headerFilePathʶ��ͷ��·��
*@return
	-ʶ���������������߷ֿ�
*/
CAMSDK_API char *cardOCRRecognizeIDCard_OCR(char *imagePath,char *headerFilePath);

/**@brief ����ʱ��ʶ��֤��������Ƭ
*@prarm [in] devIndex���豸ID��������ͷ���,0�ſ�ʼ
*@prarm [in] NameType��0-����Ч 1-���� 2-���֤��
*@return
 @ref ERR_NONE �ɹ�
*/
CAMSDK_API long cardOCRNameByIDCard(long devIndex,long n_NameType);
#endif

#if _CAMDLL_IDCARD_DEVICE 
/**@brief ���֤��������ʼ��
*@prarm [��]
*@return
 @ref ERR_NONE �ɹ�
*@note ��ʼ���ɹ����˳��뷴��ʼ��
*/
CAMSDK_API long idcardrfidInit();

/**@brief ���֤����������ʼ�����Ͽ�������
*@prarm [��]
*@return
 @ref ERR_NONE ����ʼ���ɹ�
*/
CAMSDK_API long idcardrfidUnInit();

/**@brief ���֤����������
*@prarm [in] Msg,���֤��Ϣ
*@prarm [in] headerFilePath,ʶ������ͷ��
*@return
 @ref ERR_NONE �ɹ�
*/
CAMSDK_API long idcardrfidReadIDCard(BaseMsg &Msg,char* headerFilePath);
/**@brief ���֤������������չ
*@prarm [in] Msg,���֤��Ϣ���ɶ�����������֤
*@prarm [in] headerFilePath,ʶ������ͷ��
*@return
 @ref ERR_NONE �ɹ�
*/
CAMSDK_API long idcardrfidReadIDCardEx(BaseMsgEx &MsgEx,char* headerFilePath);
/**@brief ���֤��������ȡָ��
*@prarm [in] pcFPMsg��ָ�����ݣ�����ֵ��
*@prarm [in] nMsgSize��ָ�����ݳ���
*@return
	- ֵΪ-1ʱ����ʾû��ָ����Ϣ��
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long idcardrfidGetFingerprintMsg(unsigned char* pcFPMsg,long &nMsgSize);

/**@brief ���֤��������ȡһ��ָ��
*@prarm [in] nIndex��ָ����ţ����㿪ʼ�ġ�
*@prarm [in] pcFPMsg��ָ�����ݣ�����ֵ�����ȶ���512
*@prarm [in] nFingerType��Ĵָ����,11 ����Ĵָ��12 ����ʳָ��13 ������ָ ��14 ���ֻ�ָ ��15 ����Сָ 
16 ����Ĵָ ��17 ����ʳָ ��18 ������ָ ��19 ���ֻ�ָ ��20 ����Сָ ��97 ���ֲ�ȷ��ָλ ��98 ���ֲ�ȷ��ָλ��99 ������ȷ��ָλ
*@return
	- ֵΪ-1ʱ����ʾû��ָ����Ϣ��
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long idcardrfidGetOneFingerprintMsg(long nIndex,unsigned char* pcFPMsg, long &nFingerType );


//Young
CAMSDK_API long idcardrfidGetIDCardImage(long nType ,char* pFileFront, char* pFileBack = NULL);


#endif

#if _CAMDLL_FINGERPRINT_DEVICE 
/**@brief ָ��ģ���ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintInit();

/**@brief ָ��ģ�鷴��ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintUnInit();

/**@brief �ɼ�ָ��
*
*@param [out] Bmpָ��ͼƬ�����ڴ洢ָ��BMPͼƬ���ڴ�ռ䣬Ӧ��С�� 512*512�ֽڡ�
*@param [out] ָ��ԭʼ�����ļ������ڴ洢ָ��ԭʼ���ݵ��ڴ�ռ䣬Ӧ��512*512 �ֽڡ�
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintGetImage(unsigned char* pBmpBuff,unsigned char *pRawData);

/**@brief ��ȡָ������ֵ
*
*@param [in] ���е�ָ��ԭʼ���ݡ�
*@param [out] ���ɵ�ָ������ֵ���ڴ治С��1024�ֽڡ�
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintGetFeature(const unsigned char *pRawData,unsigned char *pFeatureData);

/**@brief �첽�ɼ�ָ��
*
*@param [in] funCB ����ԭ��typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData); pBmpBuff���ڴ洢ָ��BMPͼƬ���ڴ�ռ䣬Ӧ��С�� 512*512�ֽڡ�pFeatureָ������ֵ���ڴ治С��1024�ֽڡ�pUserDataԤ����δʹ�á�
*@param [in] Ԥ����δʹ�á�
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintStartGetFPDataAsync(callBackGetFPDataAsync funCB,void *pUserData);

/**@brief ֹͣ�첽�ɼ�ָ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintStopGetFPDataAsync(); 

/**@brief ָ�ƶԱ�
*
*@param [in] pFeature1 ָ������ֵ1��
*@param [in] pFeature2 ָ������ֵ2��
*@return
	-  
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintContrast(unsigned char* pFeature1,unsigned char *pFeature2);

/**@brief ����ָ�������ɼ���׼
*
*@param [in] Score ֵ��Χ0~100��ֵԽ������Խ�ߡ�
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long fingerprintSetPrintQuality(long Score);
#endif

#if _CAMDLL_OCR 
/**@brief ��ȡOCR֧�ֵ����Ը���
*
*@param [out] count ���Ը���
*@return
*	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrGetLanguageCount(long &count);

/**@brief ��ȡOCR��������
*@param [in] index��ţ���0��ʼ
*@param [out] name��������
*@return
*	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrGetLanguageName(long index,char *name);

/**@brief ��OCRʶ����������ͼ��
*@param [in] imagePath��Ҫʶ���ͼ��·��
*@return
*	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrAddImageFileToOCRList(char *imagePath);

/**@brief ʶ��OCR�����е�ͼ�񲢵���
*@param [in] filePath����·��
*@param [in] nlanguage�������
*@return
*	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrCombineToFile(char *filePath,long nlanguage);

/**@brief OCR����/��ά��ʶ��
*
*@prarm [in] src ��Ƭ·������ʶ��ͼ�ж����
*@prarm [in] codeType �������� 1���� 2��ά��
*@prarm [out] count ʶ�������ĸ���
*@return
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrRecognizeBarcode(char *src,long codeType,long &count);

/**@brief�Զ����ַ���
*
*@prarm [in/out]filePath,����Ϊ����ͼƬ��·�������Ϊ���ͼƬ��·��
*@param [in] nlanguage�������
*@return
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrDetectOrientation(char *filePath,char * language);

/**@brief OCR�������/��ά��ʶ����
*
*@prarm [in] Index ʶ����ID
*@prarm [out] cText ʶ������ı����
*@prarm [in/out] size ����ΪcText�Ŀռ䳤�ȣ����Ϊ����ĳ��ȡ�
*@return
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrGetBarcodeText(long Index,char* cText,long &size);

//percentageʶ�����,cancel�Ƿ�ȡ��, pInfo ����������
typedef bool (CALLBACK * callBackProgress)(long nPos); 
/**@brief OCR��ý�����ȡ��ʶ��
*
*@prarm [in] callbackProgress �ص�����

*@return
	- @ref ERR_NONE �ɹ�
*/
CAMSDK_API long ocrRegCallBackProgress(callBackProgress funCB);

CAMSDK_API long ocrCancelProcess();
#endif

#pragma region _CAMDLL_EXTERNAL_BUTTON 
/**@brief ��Ӱ���ģ���ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyOpenDevice();

/**@brief ��Ӱ���ģ�鷴��ʼ��
*
*@return
	- @ref ERR_NONE �ɹ�
*@note
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyCloseDevice();

/**@brief ��Ӱ���������ʾ�ƹ���ģʽ
*@param [in] bAuto  True��ʾ�Զ�ģʽ��False��ʾ�ֶ�ģʽ���ɽӿ�KeySetLedState������ʾ�Ƶ�״̬
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeySetAutoLights(bool bAuto);

/**@brief ��Ӱ���������ʾ��״̬
*@param [in] lState ֵ���壺0-Ϩ��1-��ɫ��2-��ɫ��3-��ɫ�����ɫ�������
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeySetLedState(long lState);

/**@brief ��Ӱ�����ȡ״̬����ע��ص�������
*@param [in] funCB  ����ָ�룬����ԭ��Ϊtypedef bool (CALLBACK * callBackKeyRecept)(long lData);����lDataֵ������1Ϊ����2Ϊ̧��
*@return
	- @ref ERR_NONE �ɹ�
*@note 
*@pre @ref camInitCameraLib
*@attention
*/
CAMSDK_API long KeyRegCallBackKeyRecept(callBackKeyRecept funCB);
#pragma endregion _CAMDLL_EXTERNAL_BUTTON 

#if _CAMDLL_OTR 
/**@brief OTRģ���ʼ��
*
*@prarm [��]
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
	- @ref ERR_UNKNOW ʧ��
*/
CAMSDK_API long otrInit();

/**@brief OTRģ�鷴��ʼ��
*
*@prarm [��]
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*/
CAMSDK_API long otrUnInit();

/**@brief OTRģ���ȡģ��֧������
*
*@prarm [out] nCount ģ������
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*/
CAMSDK_API long otrGetTemplateCount(long &nCount);

/**@brief OTRģ���ȡģ����Ϣ
*
*@prarm [in] nIndex ģ����
*@prarm [out] chMsg ģ������
*@prarm [in] nMsgSize ģ�����Ƴ���
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*@note chMsg����Ҫ������Ϊ1024 
*/
CAMSDK_API long otrGetTemplateInfo(long nIndex, char* chMsg, long &nMsgSize);

/**@brief OTRģ��ʶ��
*
*@prarm [in] nIndex ģ����
*@prarm [in] chPath ��Ҫʶ���ͼƬ

*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*@note chMsg����Ҫ������Ϊ10000 
*/
CAMSDK_API long otrRecog(long nIndex, char* chPath);

/**@brief OTRģ���ȡʶ����������
*
*@prarm [out] nCount ʶ����������
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
*/
CAMSDK_API long otrGetResultCount(long &nCount);

/**@brief OTRģ���ȡʶ��������
*
*@prarm [in] nIndex ʶ������
*@prarm [out] chName ��������
*@prarm [out] chResult ������
*@return
	- @ref ERR_NONE �ɹ�
	- @ref ERR_NOLICENSE û����Ȩ
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