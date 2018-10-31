#pragma once
//CmCapture 枚举,类型，结构体，宏定义

//错误码
enum CAMSDK_ERR
{
	ERR_NONE = 0x0000,		//无错误
	ERR_UNKNOW,			//未知错误
	ERR_PROPERTY,		//属性设置错误
	ERR_INIT,			//初始化错误
	ERR_OUTOFBOUNDS,	//数组越界
	ERR_NULLPOINT,		//空指针
	ERR_PARAM,			//参数错误
	ERR_INVALIDPATH,	//无效的路径
	ERR_NONSUPPORT,		//不支持
	ERR_INUSE,			//使用中，忙
	ERR_NOCAMERA,			//没有找到任何摄像头
	ERR_UNOPENED,		//设备未开启
			
	ERR_OPENDEVFAILD = 0x0101,	//开启设备失败
	ERR_STARTVIDEOFAILD,	//开启视频失败
	ERR_SETRESOLUTIONFAILD,	//设置分辨率失败
	ERR_AUTOFOCUSFAILD,		//自动对焦失败
	ERR_CAPTURENULLBUF,		//拍照空指针
	ERR_SAVEIMAGEFAILD,		//保存图像失败
	ERR_NOLICENSE,		   //没有授权
	ERR_WRITEDEVFAILED,	   //写设备数据失败
	ERR_DISABLE,		   //无授权已反初始化SDK

	ERR_FTPCONNECTFAILED = 0x0401,	//FTP连接失败
	ERR_FTPDISCONNECTFAILED,	//FTP断开失败
	ERR_FTPADDRESSERROR,		//FTP路径有误
	ERR_FTPPUTFILEFAILED,	//FTP上传失败
	ERR_HTTPPUTFILEFAILED,	//HTTP连接失败
	
	ERR_LOADIDCARDOCRFAILED = 0x0501,	//加载证件识别失败
	
	ERR_LOADBARCODEFAILED = 0x0511,		//加载条码识别失败
};

//身份证信息，结构体
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
//身份证信息扩展，结构体
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
	//外国证件添加的
	wchar_t sEName[120];
	wchar_t sVersion[4];
	wchar_t sCategory[2];
	wchar_t sOther[6];//预留项
}BaseMsgEx;
 //银行卡信息
 typedef struct _BANK_BASE_MSG
{
	//UNICODE
	wchar_t sNumber[50];
}BankBaseMsg;
 //社保卡
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
 //磁条卡信息
 typedef struct _MAGCARD_BASE_MSG
{
	//UNICODE
	wchar_t sPassOne[200];
	wchar_t sPassTwo[200];
	wchar_t sPassThree[200];
}MagCardMsg;
//#if SEARCH_FILE
//文件类型
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

//设备变换
enum CAMSDK_DEVCHANGE
{
	DEVCHANGE_NONE = 0,			//无变化
	DEVCHANGE_DEV,				//列表变化，调用设备变化
	DEVCHANGE_DEVLOST			//设备丢失
};