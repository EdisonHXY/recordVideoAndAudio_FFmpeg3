#pragma once
//CmCapture ö��,���ͣ��ṹ�壬�궨��

//������
enum CAMSDK_ERR
{
	ERR_NONE = 0x0000,		//�޴���
	ERR_UNKNOW,			//δ֪����
	ERR_PROPERTY,		//�������ô���
	ERR_INIT,			//��ʼ������
	ERR_OUTOFBOUNDS,	//����Խ��
	ERR_NULLPOINT,		//��ָ��
	ERR_PARAM,			//��������
	ERR_INVALIDPATH,	//��Ч��·��
	ERR_NONSUPPORT,		//��֧��
	ERR_INUSE,			//ʹ���У�æ
	ERR_NOCAMERA,			//û���ҵ��κ�����ͷ
	ERR_UNOPENED,		//�豸δ����
			
	ERR_OPENDEVFAILD = 0x0101,	//�����豸ʧ��
	ERR_STARTVIDEOFAILD,	//������Ƶʧ��
	ERR_SETRESOLUTIONFAILD,	//���÷ֱ���ʧ��
	ERR_AUTOFOCUSFAILD,		//�Զ��Խ�ʧ��
	ERR_CAPTURENULLBUF,		//���տ�ָ��
	ERR_SAVEIMAGEFAILD,		//����ͼ��ʧ��
	ERR_NOLICENSE,		   //û����Ȩ
	ERR_WRITEDEVFAILED,	   //д�豸����ʧ��
	ERR_DISABLE,		   //����Ȩ�ѷ���ʼ��SDK

	ERR_FTPCONNECTFAILED = 0x0401,	//FTP����ʧ��
	ERR_FTPDISCONNECTFAILED,	//FTP�Ͽ�ʧ��
	ERR_FTPADDRESSERROR,		//FTP·������
	ERR_FTPPUTFILEFAILED,	//FTP�ϴ�ʧ��
	ERR_HTTPPUTFILEFAILED,	//HTTP����ʧ��
	
	ERR_LOADIDCARDOCRFAILED = 0x0501,	//����֤��ʶ��ʧ��
	
	ERR_LOADBARCODEFAILED = 0x0511,		//��������ʶ��ʧ��
};

//���֤��Ϣ���ṹ��
typedef struct _BASE_MSG
{
	//UNICODE
	wchar_t sName[20];
	wchar_t sSex[4];
	wchar_t sNation[20];
	wchar_t sBirthdate[10];
	wchar_t sAddr[50];
	wchar_t sID[20];
	wchar_t sOffice[30];
	wchar_t sBeginDate[10];
	wchar_t sEndDate[10];
	wchar_t sFingerData[4096];
	int nFingerDataLen ; 
}BaseMsg;
//���֤��Ϣ��չ���ṹ��
 typedef struct _BASE_MSG_EX
{
	//UNI
	wchar_t sName[20];
	wchar_t sSex[4];
	wchar_t sNation[20];
	wchar_t sBirthdate[10];
	wchar_t sAddr[50];
	wchar_t sID[20];
	wchar_t sOffice[30];
	wchar_t sBeginDate[10];
	wchar_t sEndDate[10];
	//���֤����ӵ�
	wchar_t sEName[120];
	wchar_t sVersion[4];
	wchar_t sCategory[2];
	wchar_t sOther[6];//Ԥ����
}BaseMsgEx;
 //���п���Ϣ
 typedef struct _BANK_BASE_MSG
{
	//UNICODE
	wchar_t sNumber[50];
}BankBaseMsg;
 //�籣��
typedef struct _SSSE_BASE_MSG
{
	//UNI
	wchar_t sID[20];
	wchar_t sName[20];
	wchar_t sSex[20];
	wchar_t sNation[20];
	wchar_t sAddr[50];
	wchar_t sBirthdate[20];
}SsseBaseMsg;
 //��������Ϣ
 typedef struct _MAGCARD_BASE_MSG
{
	//UNICODE
	wchar_t sPassOne[200];
	wchar_t sPassTwo[200];
	wchar_t sPassThree[200];
}MagCardMsg;
//#if SEARCH_FILE
//�ļ�����
typedef enum
{	
	//FILE_
	FILE_BMP	=	0x0001,
	FILE_JPG	=	0x0002,
	FILE_PNG	=	0x0004,
	FILE_TIF	=	0x0008,
	FILE_PDF	=	0x0010,
	FILE_TXT	=	0x0020,
	FILE_DOC	=	0x0040,
	FILE_DOCX	=	0x0080,
	FILE_XLS	=	0x0100,
	FILE_XLSX	=	0x0200,
	FILE_ALL = 0xFFFF

}CAMSDK_SEARCH_FILE;
//#endif

//�豸�任
enum CAMSDK_DEVCHANGE
{
	DEVCHANGE_NONE = 0,			//�ޱ仯
	DEVCHANGE_DEV,				//�б�仯�������豸�仯
	DEVCHANGE_DEVLOST			//�豸��ʧ
};