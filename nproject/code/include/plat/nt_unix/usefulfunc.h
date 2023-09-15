/*   */

#ifndef USEFULFUNC_INCLUDE
#define USEFULFUNC_INCLUDE

#include "nt_unix/sgdataset.h"
#include "nt_unix/sgnp/sgnp_base.h"
#include "nt_unix/sgnp/FolderManager.h"


class CObjectIndex;

//==================================================================================================
class _DATASET_DLL_EXPORT_ CommonFunc : public FolderManager
{
public:
	/*	��ò�Ʒ��װ·��*/
	static SG_BOOL	GetHome_Root(SG_CHAR *root,int nLength);

	/* ���BMP�ļ���·��*/
	static SG_BOOL GetHome_Bmp(SG_CHAR *bmp,int nLength);

	static SG_BOOL GetHome_Java(SG_CHAR *java,int nLength);

	/* ���etc·�� */	
	static SG_BOOL	GetHome_Etc(SG_CHAR *etc,int nLength);

	/* ���log·�� */
	static SG_BOOL	GetHome_Log(SG_CHAR *log,int nLength);

	/* ���template·�� */
	static SG_BOOL GetHome_Tpl(SG_CHAR *tpl,int nLength);

	/* ���temp·�� */
	static SG_BOOL	GetHome_Temp(SG_CHAR*temp,int nLength);

	/* ���lcf(���ػ����ļ�)·�� */
	static SG_BOOL	GetHome_Lcf(SG_CHAR*lcf,int nLength);

	/* ���symbol�ļ�·�� */
	static SG_BOOL	GetHome_Symbol(SG_CHAR*sym,int nLength);

	/*����ڴ�ӳ���ļ���·��*/
	static SG_BOOL GetHome_Data(SG_CHAR*data,int nLength);

	/*����ڴ�ӳ���ļ����ļ���*/
	static SG_BOOL GetHome_DataFn(SG_CHAR*datafn,int nLength);

	//�㱨ϵͳ���ڴ��CPU��Ϣ
	static void GetLocalSystemInfo(CSgString &msg);

	//���ԡ�,���ŷֿ����ַ����ֽ�Ϊ�ַ�������
	static void StringToArray(SG_PCSTR  SerialStr,CSgStringArray &ArrayString,SG_CHAR ch=',');
	static char *StrIStr(const char * str1, const char * str2);
	//���·�����Ƿ�����ļ�,������ڷ����ļ�����޸�ʱ��
	static SG_BOOL CheckFileExist(SG_STRING Path,SG_STRING FileName,tm *time);

	//���·���£���FileFilterΪ��չ�����ļ���
	static void FindFileInDir(char* rootDir, CSgStringArray&strRet,char*FileFilter);

	//�����ô�ӡ��ǰʱ��
	static SG_CHAR* GetCurTime(char *str=NULL);

	/*��¼GISENGINE������־*/
	static void LogSgGisError(const char*lpszLog);

	//�ж��Ƿ���Ч��Universe��ֵ
	static SG_BOOL	IsValidUniverse(SG_ULONG Universe);

	//�жϻ���FEATURE���͵�����ǵ��໹�Ƿǵ���
	static SG_BOOL	IsPointFeature(SG_UCHAR nBaseFeature);

	//�жϻ���FEATURE���͵��������/�����໹����/������
	static SG_BOOL	IsLineFeature(SG_UCHAR nBaseFeature);

	//�жϻ���FEATURE���͵�����Ƿ�Ϊ�޼�������
	static SG_BOOL	IsGeometryFeature(SG_UCHAR nBaseFeature);

	// �Ƿ�Ϊ�����͵����
	static SG_BOOL	IsGeoPointFeature(SG_UCHAR nBaseFeature);

	// �Ƿ�Ϊ�����͵����
	static SG_BOOL	IsGeoLineFeature(SG_UCHAR nBaseFeature);

	// �Ƿ�Ϊ�����͵����
	static SG_BOOL	IsGeoRegionFeature(SG_UCHAR nBaseFeature);

	// ���߶���ת��Ϊ�ַ�������
	static SG_BOOL	ConvertLineToStr(CSgLine* lpCheckLines,CSgString strLines);

	// �ж�һ���߶����Ƿ�Ϊ�պ�����
	static SG_BOOL	IsLineClosed(CSgLine* lpCheckLines);

	//�Ƿ񳬼����� ���� ѡ��ʱ�������ȼ���
	static SG_BOOL IsAdvancetObj(SG_INT ObjAppType);

	//�Ƿ���������� ���� ѡ��ʱ�������ȼ���
	static SG_BOOL IsTextObj(SG_INT ObjAppType);

	//�Ƿ�һ����� ���� ѡ��ʱ�������ȼ���
	static SG_BOOL IsCommonObj(SG_INT ObjAppType);

	//�жϻ���FEATURE���͵�����Ƿ�����
	static SG_BOOL IsTextFeature(SG_UCHAR nBaseFeature);

	//��SG_OBJECTSת���ɰ��ն���������֯��CSG_OBJECTSArray
	//ע��: ������̽�pObjs�еĳ�Ա����
	static void SgObjectsToAttray(SG_OBJECTS *pObjs,CSG_OBJECTSArray &array);

	//��SG_OBJECTS�е��к�ת����CSgObjects�ṹ
	//ע��: SG_OBJECTS�еĶ��������ͬһ���еĶ���
	static void SgObjectsToSgObjects(SG_OBJECTS *pObjs,CSgObjects &objs,SG_BOOL AddNoCheck=false);

	//��SG_OBJECTS�е��к�ת����CSgObjectsArray�ṹ(��Layer����)
	static void SgObjectsToSgObjects(SG_OBJECTS *pObjs,CSgObjectsArray &objsArray,SG_BOOL AddNoCheck=false);

	//��SG_OBJECTS�е��к�ת����CSgObjectsArray�ṹ(��ObjType����)
	static void SgObjectsToSgObjectsEx(SG_OBJECTS *pObjs,CSgObjectsArray &objsArray,SG_BOOL AddNoCheck=false);

	//�ֲ�SQL��䵽SG_SQLINFO�ṹ
	static SG_BOOL SplitSqlClause(char *pSql,SG_SQLINFO &sqlInfo);

	// --- �����ַ���
	static SG_CHAR *FormatString(const char *format,...);

	// --- ��ö���ľ����������
	
	static SG_SHORT GetMirrorObjType(SG_SHORT ObjType);
	// --- ��þ������ĺ��Ķ�������
	
	static SG_SHORT GetKernelObjType(SG_SHORT ObjType);

	// --- ��SG_Date�ṹ�е����ݸ���tm�ṹ
	
	static void SG_DateTotm(SG_Date*pDate,tm*ptm);
	// --- ��tm�ṹ�е����ݸ���SG_Date�ṹ
	
	static void tmToSG_Date(SG_Date*pDate,tm*ptm);


	//�Ӵ����ݿ������ַ���ȡ������ָ��
	
	static SG_STRING SplitTableName(SG_STRING pSurceStr,SG_STRING pTable);
	//����ѡ������IN,char����
	
	static SG_BOOL	MakeCharCondition(SG_STRING sqlworld,SG_STRING fieldname,CSgStringArray &IndexArray,SG_LONG &ptr);
	//����ѡ������IN,Math����
	
	static SG_BOOL	MakeMathCondition(SG_STRING sqlworld,SG_STRING fieldname,CSgStringArray &IndexArray,SG_LONG &ptr);
	//����ѡ������IN,char����
	
	static SG_BOOL   MakeSqlConditionOnCode(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_OBJCODE *pCode,SG_INT &ptr);
	
	static SG_BOOL   MakeSqlConditionOnID(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_LONG *pID,SG_INT &ptr);
	static SG_BOOL   MakeSqlConditionOnID(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_INT64 *pID,SG_INT &ptr);

	// --- ����Ч�����⣬��Ӧ�ô���objs���п����ڴ����������ߴ���Ч��
	
	static void	CObjectIndexToCSgObjects(SG_INT UpBound,CObjectIndex&index,CSgObjects&objs,SG_INT KeyValue);

	//---�����淶�ĵ��½�ͷ���ƣ������ JointNums Ϊ���¾��еĽ�ͷ����
	
	static void CreateCableJointName(SG_INT JointNums,CSgStringArray &JointNames);
	//---�����淶�ĵ��¶����ƣ������ ptr Ϊbase 0 �ĵ��¶����
	
	static void CreateCableSectName(SG_INT ptr,CSgStringArray &JointNames,CSgString &SectName);
	/************************************************************************/
	/*                        ���÷���                                      */
	/************************************************************************/
	//ȥ���ַ�������İ��������
	//�������lenΪ�ַ�������
	//ע�⣺���������У���֤���ڵ�len-1���ַ������ַ���������
	static void GetRidErrChineseCode(char*str,SG_INT len);
	//
	/************************************************************************/
	/*��¼������־��Ϣ������־����10Mʱ��ɾ�����ļ���������־���ļ�				*/
	/************************************************************************/
	//LogFileΪ��־�ļ�����LogInfoΪ��¼����־��Ϣ
	static void WriteLog(char*LogFile,char*LogInfo);
};

// --- ͬwindows SYSTEMTIME�ṹ

struct SG_SYSTEMTIME
{
	
    SG_USHORT wYear;
	
    SG_USHORT wMonth;
	
    SG_USHORT wDayOfWeek;
	
    SG_USHORT wDay;
	
    SG_USHORT wHour;
	
    SG_USHORT wMinute;
	
    SG_USHORT wSecond;
	
    SG_USHORT wMilliseconds;
};


class _DATASET_DLL_EXPORT_ CSysEfficCheck
{
public:
	
	CSysEfficCheck();
	
	~CSysEfficCheck();

	// --- ȡ��ǰ��ʱ��Ϊ��ʼʱ��
	
	void SetStartTime();
	// --- ָ����ʼʱ��
	
	void SetStartTime(SG_SYSTEMTIME *st);
	// -- �����ʼʱ��
	
	SG_SYSTEMTIME *GetStartTime();
	
	SG_CHAR *GetSubTime(SG_BOOL *pGTZero=NULL);
	
	static void GetNow(SG_SYSTEMTIME *systime);
	static void GetNow(CSgString&NowTime);
protected:
	
	SG_SYSTEMTIME systime_start;
	
	SG_CHAR str[32];
};

_DATASET_DLL_EXPORT_ char * ToUpperString( char * string );

#endif
