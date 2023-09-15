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
	/*	获得产品安装路径*/
	static SG_BOOL	GetHome_Root(SG_CHAR *root,int nLength);

	/* 获得BMP文件的路径*/
	static SG_BOOL GetHome_Bmp(SG_CHAR *bmp,int nLength);

	static SG_BOOL GetHome_Java(SG_CHAR *java,int nLength);

	/* 获得etc路径 */	
	static SG_BOOL	GetHome_Etc(SG_CHAR *etc,int nLength);

	/* 获得log路径 */
	static SG_BOOL	GetHome_Log(SG_CHAR *log,int nLength);

	/* 获得template路径 */
	static SG_BOOL GetHome_Tpl(SG_CHAR *tpl,int nLength);

	/* 获得temp路径 */
	static SG_BOOL	GetHome_Temp(SG_CHAR*temp,int nLength);

	/* 获得lcf(本地缓存文件)路径 */
	static SG_BOOL	GetHome_Lcf(SG_CHAR*lcf,int nLength);

	/* 获得symbol文件路径 */
	static SG_BOOL	GetHome_Symbol(SG_CHAR*sym,int nLength);

	/*获得内存映象文件的路径*/
	static SG_BOOL GetHome_Data(SG_CHAR*data,int nLength);

	/*获得内存映象文件的文件名*/
	static SG_BOOL GetHome_DataFn(SG_CHAR*datafn,int nLength);

	//汇报系统的内存和CPU信息
	static void GetLocalSystemInfo(CSgString &msg);

	//将以“,”号分开的字符串分解为字符串队列
	static void StringToArray(SG_PCSTR  SerialStr,CSgStringArray &ArrayString,SG_CHAR ch=',');
	static char *StrIStr(const char * str1, const char * str2);
	//检测路径下是否具有文件,如果存在返回文件最后修改时间
	static SG_BOOL CheckFileExist(SG_STRING Path,SG_STRING FileName,tm *time);

	//获得路径下，以FileFilter为扩展名的文件名
	static void FindFileInDir(char* rootDir, CSgStringArray&strRet,char*FileFilter);

	//调试用打印当前时间
	static SG_CHAR* GetCurTime(char *str=NULL);

	/*记录GISENGINE错误日志*/
	static void LogSgGisError(const char*lpszLog);

	//判断是否有效的Universe内值
	static SG_BOOL	IsValidUniverse(SG_ULONG Universe);

	//判断基本FEATURE类型的类别，是点类还是非点类
	static SG_BOOL	IsPointFeature(SG_UCHAR nBaseFeature);

	//判断基本FEATURE类型的类别，是线/区域类还是线/区域类
	static SG_BOOL	IsLineFeature(SG_UCHAR nBaseFeature);

	//判断基本FEATURE类型的类别，是否为无几何特征
	static SG_BOOL	IsGeometryFeature(SG_UCHAR nBaseFeature);

	// 是否为点类型的类别
	static SG_BOOL	IsGeoPointFeature(SG_UCHAR nBaseFeature);

	// 是否为线类型的类别
	static SG_BOOL	IsGeoLineFeature(SG_UCHAR nBaseFeature);

	// 是否为面类型的类别
	static SG_BOOL	IsGeoRegionFeature(SG_UCHAR nBaseFeature);

	// 将线对象转换为字符串描述
	static SG_BOOL	ConvertLineToStr(CSgLine* lpCheckLines,CSgString strLines);

	// 判断一个线对象是否为闭合曲线
	static SG_BOOL	IsLineClosed(CSgLine* lpCheckLines);

	//是否超级对象 －－ 选择时控制优先级用
	static SG_BOOL IsAdvancetObj(SG_INT ObjAppType);

	//是否文字类对象 －－ 选择时控制优先级用
	static SG_BOOL IsTextObj(SG_INT ObjAppType);

	//是否一般对象 －－ 选择时控制优先级用
	static SG_BOOL IsCommonObj(SG_INT ObjAppType);

	//判断基本FEATURE类型的类别，是否文字
	static SG_BOOL IsTextFeature(SG_UCHAR nBaseFeature);

	//将SG_OBJECTS转换成按照对象类型组织的CSG_OBJECTSArray
	//注意: 处理过程将pObjs中的成员销毁
	static void SgObjectsToAttray(SG_OBJECTS *pObjs,CSG_OBJECTSArray &array);

	//将SG_OBJECTS中的行号转换成CSgObjects结构
	//注意: SG_OBJECTS中的对象必须是同一层中的对象
	static void SgObjectsToSgObjects(SG_OBJECTS *pObjs,CSgObjects &objs,SG_BOOL AddNoCheck=false);

	//将SG_OBJECTS中的行号转换成CSgObjectsArray结构(以Layer分组)
	static void SgObjectsToSgObjects(SG_OBJECTS *pObjs,CSgObjectsArray &objsArray,SG_BOOL AddNoCheck=false);

	//将SG_OBJECTS中的行号转换成CSgObjectsArray结构(以ObjType分组)
	static void SgObjectsToSgObjectsEx(SG_OBJECTS *pObjs,CSgObjectsArray &objsArray,SG_BOOL AddNoCheck=false);

	//分拆SQL语句到SG_SQLINFO结构
	static SG_BOOL SplitSqlClause(char *pSql,SG_SQLINFO &sqlInfo);

	// --- 复制字符串
	static SG_CHAR *FormatString(const char *format,...);

	// --- 获得对象的镜像对象类型
	
	static SG_SHORT GetMirrorObjType(SG_SHORT ObjType);
	// --- 获得镜像对象的核心对象类型
	
	static SG_SHORT GetKernelObjType(SG_SHORT ObjType);

	// --- 将SG_Date结构中的内容赋给tm结构
	
	static void SG_DateTotm(SG_Date*pDate,tm*ptm);
	// --- 将tm结构中的内容赋给SG_Date结构
	
	static void tmToSG_Date(SG_Date*pDate,tm*ptm);


	//从带数据库名的字符串取出表名指针
	
	static SG_STRING SplitTableName(SG_STRING pSurceStr,SG_STRING pTable);
	//创建选择条件IN,char类型
	
	static SG_BOOL	MakeCharCondition(SG_STRING sqlworld,SG_STRING fieldname,CSgStringArray &IndexArray,SG_LONG &ptr);
	//创建选择条件IN,Math类型
	
	static SG_BOOL	MakeMathCondition(SG_STRING sqlworld,SG_STRING fieldname,CSgStringArray &IndexArray,SG_LONG &ptr);
	//创建选择条件IN,char类型
	
	static SG_BOOL   MakeSqlConditionOnCode(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_OBJCODE *pCode,SG_INT &ptr);
	
	static SG_BOOL   MakeSqlConditionOnID(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_LONG *pID,SG_INT &ptr);
	static SG_BOOL   MakeSqlConditionOnID(SG_LONG SqlMaxLen,SG_STRING sqlworld,SG_STRING fieldname,SG_INT ElementNums,SG_INT64 *pID,SG_INT &ptr);

	// --- 存在效率问题，在应用处对objs进行开辟内存操作可以提高处理效率
	
	static void	CObjectIndexToCSgObjects(SG_INT UpBound,CObjectIndex&index,CSgObjects&objs,SG_INT KeyValue);

	//---产生规范的电缆接头名称，入参数 JointNums 为电缆具有的接头数量
	
	static void CreateCableJointName(SG_INT JointNums,CSgStringArray &JointNames);
	//---产生规范的电缆段名称，入参数 ptr 为base 0 的电缆段序号
	
	static void CreateCableSectName(SG_INT ptr,CSgStringArray &JointNames,CSgString &SectName);
	/************************************************************************/
	/*                        共用方法                                      */
	/************************************************************************/
	//去除字符串后面的半个汉字码
	//入参数：len为字符串长度
	//注意：本处理方法中，保证会在第len-1个字符处加字符串结束符
	static void GetRidErrChineseCode(char*str,SG_INT len);
	//
	/************************************************************************/
	/*记录本地日志信息。当日志大于10M时，删除旧文件，开启日志新文件				*/
	/************************************************************************/
	//LogFile为日志文件名，LogInfo为记录的日志信息
	static void WriteLog(char*LogFile,char*LogInfo);
};

// --- 同windows SYSTEMTIME结构

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

	// --- 取当前的时间为起始时间
	
	void SetStartTime();
	// --- 指定起始时间
	
	void SetStartTime(SG_SYSTEMTIME *st);
	// -- 获得起始时间
	
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
