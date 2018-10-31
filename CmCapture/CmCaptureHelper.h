
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
////�豸�任
//enum CAMSDK_DEVCHANGE
//{
//	DEVCHANGE_NONE = 0,			//�ޱ仯
//	DEVCHANGE_DEV				//�б�仯�������豸�仯
//};

//��ƵԤ���ص�
typedef bool (CALLBACK * callBackPreviewImage)(byte * src,long width,long height,long size); 

//�豸�Ȳ�λص�
typedef bool (CALLBACK * callBackDevChange)(CAMSDK_DEVCHANGE deviceChangeType); 

//�豸����
typedef bool (CALLBACK * callBackAutoCapture)(long state); 

//���֤
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
//��ȡָ������ֵ�ص�����
typedef bool (__stdcall * callBackGetFPDataAsync)(unsigned char* pBmpBuff,unsigned char * pFeature, void *pUserData);
//==================================
class CmCaptureHelper
{
public:
	//�ӵ�ǰģ��·������DL��DLL�����������ļ�������
	//bool Load()
	//{
	//	std::string strMysherFile = "CmCapture";
	//	std::string strName = DllXmlParser::GetDllName(strMysherFile);
	//	std::string strPath = PathManager::GetAppPath();
	//	std::string strFullPath = strPath + strName + ".dll";
	//	return this->Load(strFullPath.c_str());
	//}

	//����DLL
	//����˵��:
	//strDllPath��DLL����·������D:\\MysherImage.dll
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

	//�ж�DLL�Ƿ����
	bool IsAvailable()
	{
		return this->m_bInit;
	}

	//��Ƶ����
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
	//����Ƶ�豸
	//����ֵ:�Ƿ�򿪳ɹ�
	//����:index:�豸��� Ĭ�Ͽ��������Ƶ
	//�Ƿ�򿪳ɹ�
	//mediaType Ĭ��ͨ�������ļ� Ĭ�����ֱ���
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
//�ر���Ƶ�豸
//����ֵ:�Ƿ�رճɹ�
	long camCloseDev(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camCloseDev");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}


//��ȡ��Ƶ��ʽ����
//����ֵ: ��Ƶ��ʽ����
	long camGetMediaTypeCount(long devIndex ,long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long,long &)>("camGetMediaTypeCount");
		if(fun != 0)
		{
			return fun(devIndex,count);
		}
		return -99;
	}
//��ȡ��Ƶ��ʽ����
//����:index ��Ƶ��ʽ
//����ֵ:�ֱ��ʿ�
	char * camGetMediaTypeName(long devIndex  ,long index)
	{
		auto fun = m_dllParser.GetFunction<char *(long,long)>("camGetMediaTypeName");
		if(fun != 0)
		{
			return fun(devIndex,index);
		}
		return NULL;
	}


//��ȡ�ֱ��ʸ���
//����ֵ:�ֱ��ʸ���
	long camGetResolutionCount(long devIndex ,long subtype ,long & count)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long &)>("camGetResolutionCount");
		if(fun != 0)
		{
			return fun(devIndex,subtype,count);
		}
		return -99;
	}
//��ȡ�ƶ��ֱ��ʿ�
//����:index �ֱ��ʱ��
//����ֵ:�ֱ��ʿ�
	long camGetResolution(long devIndex ,long subtype,long index,long & width,long & height)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long &,long &)>("camGetResolution");
		if(fun != 0)
		{
			return fun(devIndex,subtype,index,width,height);
		}
		return -99;
	}

//������Ƶ��ʽ
//����: ��Ƶ��ʽ
//����ֵ:�Ƿ����óɹ�
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
//¼��
//����ֵ:�Ƿ�ɹ�����¼��
	long camStartRecord(long devIndex ,char * filePath,long micphone,long videoFormat)
	{
		auto fun = m_dllParser.GetFunction<long(long,char *,long,long)>("camStartRecord");
		if(fun != 0)
		{
			return fun(devIndex,filePath,micphone,videoFormat);
		}
		return -99;
	}
//�ر�¼��
//����ֵ:�Ƿ�ɹ��ر�¼��
	long camStopRecord(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camStopRecord");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}

	//¼��ʱ�����˷�����
	long camGetMicrophoneVolumeLevel(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camGetMicrophoneVolumeLevel");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
#pragma endregion ��Ƶ����


#pragma region �豸����
/**@brief ��ȡ��Ȩ��Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] license��Ȩ��Ϣ
*@return
	- @ref ERR_NONE �ɹ�
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
/**@brief ��ȡ��Ȩ��Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] license��Ȩ��Ϣ
*@return
	- @ref ERR_NONE �ɹ�
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
/**@brief д����Ȩ��Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] license��Ȩ��Ϣ
*@return
	- @ref ERR_NONE �ɹ�
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
/**@brief ��ȡ�Զ�����Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [out] customer�û��Զ�����Ϣ
*@return
	- @ref ERR_NONE �ɹ�
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
/**@brief д���Զ�����Ϣ
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] customer�Զ�����Ϣ
*@return
	- @ref ERR_NONE �ɹ�
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

//�豸����(5)
//��ȡ�豸SN
//����ֵ:�豸SN��
	char *camGetDevSN(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetDevSN");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}

//�豸����(5)
//��ȡ�豸SN
//����ֵ:�豸SN��
	char *camGetDevCusSN(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<char *(long)>("camGetDevCusSN");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return NULL;
	}
/**@brief д���Զ������к�
*
*@param [in] devIndex �豸ID��������ͷ���,0�ſ�ʼ
*@param [in] customersn�Զ������к�
*@return
	- @ref ERR_NONE �ɹ�
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
//����UVC������ƵЧ��
//����:para1 0 CameraContrl  1 Video Proc Amp
// para2 :���ݲ���1�仯
//para1 = 0 para2
//	���� 0
//	�Աȶ� 1
//	ɫ�� 2
//	���Ͷ� 3
//	������ 4
//	Gamma 5
//	������ɫ 6
//	��ƽ��	7
//	���ⲹ��	8
//	����	9
//
//	para1 = 1 para2
//	ȫ�� 0
//	��б 1
//	���� 2
//	���� 3
//	�ع� 4
//	���նȲ��� 5
//	�Խ� 6
	//lvalue:��Ҫд�������ֵ
	//flag:0 �ֶ� 1 �Զ�
	long camSetVideoParameter(long devIndex  ,long para1,long para2,long lvalue,long flag)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long,long)>("camSetVideoParameter");
		if(fun != 0)
		{
			return fun(devIndex,para1,para2,lvalue,flag);
		}
		return -99;
	}
//��ȡUVC������ƵЧ��
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
	long camGetVideoParameter(long devIndex,long para1,long para2,long & min,long & max,long & lvalue,long & ldefault,long & flag)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long&,long&,long&,long&,long&)>("camGetVideoParameter");
		if(fun != 0)
		{
			return fun(devIndex,para1,para2,min,max,lvalue,ldefault,flag);
		}
		return -99;
	}

//������ƵЧ�����ô���
//����ֵ:�Ƿ�����ȷ����
	long camShowImageSettingWindow(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camShowImageSettingWindow");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
//������Ƶ�������ô���
//����ֵ:�Ƿ�����ȷ����
	long camShowDevSettingWindow(long devIndex )
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camShowDevSettingWindow");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
//�Զ��Խ�
//������0��һ���Խ�  1���Զ��Խ�
//����ֵ:�Ƿ�����ȷ�Խ�
	long camAutoFocus(long devIndex  ,long type)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camAutoFocus");
		if(fun != 0)
		{
			return fun(devIndex,type);
		}
		return -99;
	}


	//��Ƶ�Ŵ� ��С 1:1 ���ʳߴ�
	//�Ŵ�
	long camZooIn(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camZooIn");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//��С
	long camZoomOut(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camZoomOut");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//���ʱ���
	long camOptimalPreview(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camOptimalPreview");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
	//ԭʼ���� 1:1
	long camOriginalPreview(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camOriginalPreview");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}

#pragma endregion �豸����


#pragma region ͼ����
//����JPGѹ����
//����:ѹ���� 0~100 100ѹ������С ������� �ߴ����
//����ֵ:�Ƿ����óɹ�
	long camSetImageJPGQuanlity(long devIndex  ,long quanlity)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageJPGQuanlity");
		if(fun != 0)
		{
			return fun(devIndex,quanlity);
		}
		return -99;
	}
//����(�����ļ���׺�Զ��洢��ʽ)
//����:ͼ��·��
//����ֵ:�Ƿ�����ɹ�
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
//�Զ�����
//����: 0�����Զ� 1����ͼ���� 2����ͼ����
//����ֵ���Ƿ����óɹ������óɹ���UI�ϻ���ʾ��ɫ��
	long camSetImageAutoCrop(long devIndex ,long CropType)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageAutoCrop");
		if(fun != 0)
		{
			return fun(devIndex,CropType);
		}
		return -99;
	}
//������ת����
//����:0: ����ת 1:90�� 2: 180�� 3: 270��
	long camSetImageRotateMode(long devIndex,long rotateMode)
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("camSetImageRotateMode");
		if(fun != 0)
		{
			return fun(devIndex,rotateMode);
		}
		return -99;
	}
//�����Զ����������
//����:��������  ��Ҫ�ò��п���ʾ��UI��
//����ֵ:�Ƿ����óɹ�
	long camSetImageCusCropRect(long devIndex ,long left, long top ,long right,long bottom)
	{
		auto fun = m_dllParser.GetFunction<long(long,long,long,long,long)>("camSetImageCusCropRect");
		if(fun != 0)
		{
			return fun(devIndex,left,top,right,bottom);
		}
		return -99;
	}
//��ȡ�Զ����������
//����ֵ:�Ƿ����óɹ�
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
//����ͼ����ǿ��ʽ
//������0��	����ǿ 1���ĵ���ǿ  2����ҳ��ǿ 3.�Զ�����
//����ֵ:�Ƿ����óɹ�
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
	
//�����Ƿ�ȥ��
//����:IsAvailaber�Ƿ���ȥ��  mothod ȥ�뷽��
//����ֵ:�Ƿ����óɹ�
	long camSetImageDenoise(long devIndex ,bool IsAvailabel)
	{
		auto fun = m_dllParser.GetFunction<long(long,bool)>("camSetImageDenoise");
		if(fun != 0)
		{
			return fun(devIndex,IsAvailabel);
		}
		return -99;
	}
//����ͼƬ��ʽ
//����: 0:��ɫ 1:�Ҷ�  2: �ڰ�
//����ֵ:�Ƿ����óɹ�
	long camSetImageColorStyle(long devIndex ,long type) //0:��ɫ  1:�Ҷ�  2: �ڰ�
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
//����ˮӡ
//����:msg ˮӡ����(֧��\n����) x,yˮӡλ��(������)  fontsize ˮӡ����ߴ� font ����
// angle ˮӡ��ת�Ƕ�(0~360)   transparent ͸���� isAvailabel �Ƿ���Ч
//colorType ˮӡ��ɫ 0:��ɫ 1:��ɫ 2:��ɫ 3:����ɫ 4:��ɫ 5:��ɫ 6:��ɫ
//����ֵ:�Ƿ����óɹ�
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

//ͼ��ϲ� ͼ�����
//����: imageFilePath1 ͼƬ1��ַ imageFilePath2 ͼƬ2��ַ  imageFilePath ����ͼ��
// type �ϲ�λ�� 0~8 
// long offsetX,long offsetY ƫ����
//����ֵ:�Ƿ����óɹ� ?����||����ǰ��ͷ�ϲ���
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
#pragma endregion ͼ����

#pragma region ��������
	long camStartAutoCapture(long devIndex  ,long type,long param, callBackAutoCapture funCB)//0:�Զ� 1:��ʱ
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
#pragma endregion ��������

#pragma region �ص�����
	long camRegCallBackDeviceChange(callBackDevChange funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callBackDevChange)>("camRegCallBackDeviceChange");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return -99;
	}
	//�ɵ�ע��ص�����
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
#pragma endregion �ص�����

#pragma region �ļ�����
//��ʾͼƬ
//����:ͼƬ·��
//����ֵ:�Ƿ�򿪳ɹ�
	long camShowImage(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camShowImage");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//ɾ���ļ�
//����:�ļ�·��
//����ֵ:�Ƿ�ɾ���ɹ�
	long camDeleteFile(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camDeleteFile");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//�����ļ���
//����:�ļ���·��
//����ֵ:�Ƿ񴴽��ɹ�
	long camCreateDirectory(char * dirPath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCreateDirectory");
		if(fun != 0)
		{
			return fun(dirPath);
		}
		return -99;
	}
//�������ļ�
//����filePath ԭʼ�ļ�  newFilePath ���ļ���
//����ֵ�Ƿ񴴽��ɹ�
	long camRenameFile(char * filePath,char * newFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *)>("camRenameFile");
		if(fun != 0)
		{
			return fun(filePath,newFilePath);
		}
		return -99;
	}
#pragma endregion �ļ�����


#pragma region �ļ��ϲ�
//����ļ���PDF�б�
//����:�ļ���
//����ֵ:�Ƿ���ӳɹ�
	long camAddFileToPDFList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToPDFList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//�ϲ�PDF(�ϲ�������List)
//����:�ϲ����PDF�ļ���
//����ֵ:�Ƿ�ϲ��ɹ�
	long camCombinePDF(char * pdfFilePath,long nJpegQuality)
	{
		auto fun = m_dllParser.GetFunction<long(char *,long)>("camCombinePDF");
		if(fun != 0)
		{
			return fun(pdfFilePath,nJpegQuality);
		}
		return -99;
	}
//����ļ���TIF�б�(�ϲ�������List)
//����:�ļ���
//����ֵ:�Ƿ���ӳɹ�
	long camAddFileToTIFList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToTIFList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//�ϲ�TIF
//����:�ϲ����TIF�ļ���
//����ֵ:�Ƿ�ϲ��ɹ�
	long camCombineTIF(char * tifFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCombineTIF");
		if(fun != 0)
		{
			return fun(tifFilePath);
		}
		return -99;
	}
//����ļ���ZIP�б�(�ϲ�������List)
//����:�ļ���
//����ֵ:�Ƿ���ӳɹ�
	long camAddFileToZIPList(char * filePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camAddFileToZIPList");
		if(fun != 0)
		{
			return fun(filePath);
		}
		return -99;
	}
//�ϲ�ZIP
//����:�ϲ����ZIP�ļ���
//����ֵ:�Ƿ�ϲ��ɹ�
	long camCombineZIP(char * zipFilePath)
	{
		auto fun = m_dllParser.GetFunction<long(char *)>("camCombineZIP");
		if(fun != 0)
		{
			return fun(zipFilePath);
		}
		return -99;
	}
#pragma endregion �ļ��ϲ�

#pragma region �ļ��ϴ�
//Http�ļ��ϴ�(ͬ��ģʽ)
//����:filePath �ļ�·����url  http��ַ
//����ֵ:�Ƿ��ϴ��ɹ�
	long camUpdataFileHttp(char * filePath,char * url,char * param,char * response)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *,char *,char *)>("camUpdataFileHttp");
		if(fun != 0)
		{
			return fun(filePath,url,param,response);
		}
		return -99;
	}
//FTP�ļ��ϴ�(ͬ��ģʽ)
//����:filePath �ļ�·����ftpPath FTP·����
//UserName ftp�û��� ,UserPsd ftp�û�����,targetName ftp�������ļ��洢��
//����ֵ:�Ƿ��ϴ��ɹ�0�ɹ� -1�ϴ�ʧ�� -2��½��������·��ʧ��
// -3 �������ļ���ʧ�� -4 �Ͽ�����ʧ�� -5 ����ʧ��
	long camUpdataFileFtp(char * filePath, char * ftpPath, char * userName, char * userPsd, char * targetName)
	{
		auto fun = m_dllParser.GetFunction<long(char *,char *,char *,char *,char *)>("camUpdataFileFtp");
		if(fun != 0)
		{
			return fun(filePath,ftpPath,userName,userPsd,targetName);
		}
		return -99;
	}
#pragma endregion �ļ��ϴ�
#pragma region ����ʶ��
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
#pragma endregion ����ʶ��

#pragma region ���֤ʶ��
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
	long cardOCRNameByIDCard(long devIndex,long n_NameType)//0 ����Ч 1 ���� 2 ���֤��
	{
		auto fun = m_dllParser.GetFunction<long(long,long)>("cardOCRNameByIDCard");
		if(fun != 0)
		{
			return fun(devIndex,n_NameType);
		}
		return -99;
	}
#pragma endregion ���֤ʶ��


#pragma region ָ�Ʋɼ�

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
#pragma endregion ָ�Ʋɼ�

#pragma region ���֤����

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

#pragma endregion ���֤����

#pragma region ���۸�
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
#pragma endregion ���۸�
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
	//percentageʶ�����,cancel�Ƿ�ȡ��, pInfo ����������
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
	//����ʶ��һ��word��excel
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

	#pragma region ���񰴼�
	//�߳̿���֧���Ȳ��
	//��ʼ��
	long KeyOpenDevice()
	{
		auto fun = m_dllParser.GetFunction<long()>("KeyOpenDevice");
		if(fun != 0)
		{
			return fun();
		}
		return NOT_FIND;
	}
	//����ʼ��
	long KeyCloseDevice()
	{
		auto fun = m_dllParser.GetFunction<long()>("KeyCloseDevice");
		if(fun != 0)
		{
			return fun();
		}
		return NOT_FIND;
	}
	//�ر�/�����Զ����ƣ�Ĭ��Ϊ����
	long KeySetAutoLights(bool bAuto)
	{
		auto fun = m_dllParser.GetFunction<long(bool)>("KeySetAutoLights");
		if(fun != 0)
		{
			return fun(bAuto);
		}
		return NOT_FIND;
	}
	//����״̬��
	//0��Ϩ��1���̣�2���죬3������ͬ�������ɫ�����������ƫ��ɫ��
	long KeySetLedState(long lState)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("KeySetLedState");
		if(fun != 0)
		{
			return fun(lState);
		}
		return NOT_FIND;
	}
	//������Ϣ�ص�
	//1Ϊ���£�2Ϊ̧��
	typedef bool (CALLBACK * callBackKeyRecept)(long lData);
	//ע�ᰴ���ص�
	long KeyRegCallBackKeyRecept(callBackKeyRecept funCB)
	{
		auto fun = m_dllParser.GetFunction<long(callBackKeyRecept)>("KeyRegCallBackKeyRecept");
		if(fun != 0)
		{
			return fun(funCB);
		}
		return NOT_FIND;
	}
	#pragma endregion ���񰴼�

	//¼���ʽ
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

	//��ȡĿ¼���ļ�����������
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
	//����֡�ʣ���Ƶ�����ʣ���Ƶ������
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
	long camGetSnapState(long devIndex)
	{
		auto fun = m_dllParser.GetFunction<long(long)>("camGetSnapState");
		if(fun != 0)
		{
			return fun(devIndex);
		}
		return -99;
	}
/**����/��ά��ʶ��
*
*@prarm [in] src ��Ƭ·������ʶ��ͼ�ж����
*@prarm [in] codeType �������� 1���� 2��ά��
*@prarm [out] count ʶ�������ĸ���
*@return
	- NULL ��ָ�룬����ʧ��
	- MImage����ָ�룬���ճɹ�
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


/**�������/��ά��ʶ����
*
*@prarm [in] Index ʶ����ID
*@prarm [out] cText ʶ������ı����
*@prarm [in/out] size ����ΪcText�Ŀռ䳤�ȣ����Ϊ����ĳ��ȡ�
*@return
	- NULL ��ָ�룬����ʧ��
	- MImage����ָ�룬���ճɹ�
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
	/* ������ű���
	*
	*@prarm [in] devIndex �豸ID
	*@prarm [out] fScaleX X�᷽�����ű���
	*@prarm [out] fScaleY Y�᷽�����ű���
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

	//��ȡ���п�
	long camGetBankCardInfo(BankBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(BankBaseMsg &)>("camGetBankCardInfo");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//��ȡ�������п�
	long camGetBankCardInfoEx(BankBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(BankBaseMsg &)>("camGetBankCardInfoEx");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//��ȡ�籣��
	long camGetSsseInfo(SsseBaseMsg &Msg)
	{
		auto fun = m_dllParser.GetFunction<long(SsseBaseMsg &)>("camGetSsseInfo");
		if(fun != 0)
		{
			return fun(Msg);
		}
		return -99;
	}
	//��ȡ������
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

