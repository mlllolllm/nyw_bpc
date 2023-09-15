// const.h
//
/*****************************************************************
	ϵͳ�ĳ�������
			Part 10 �������Ͷ���
			Part 20 �����Ͷ���
			Part 30 �����ַ����ṹ���䳤�ȶ���
			Part 40 ϵͳ���ƶ���
			Part 50 ϵͳ�ض���������
			Part 60 ϵͳ������������----Ԫ���ݲ���
			Part 70 ϵͳ������������----GIS��ϵͳ�����
			Part 80 ����ͨ������ض���
*****************************************************************/
#if defined(_MSC_VER)
#   pragma warning(disable:4267)
#	ifdef _DEBUG
#		pragma warning(disable:4231)
#		pragma warning(disable:4244)
#		pragma warning(disable:4018)
#	endif
#endif /* _MSC_VER */


#if !defined(SgConst_h)
#define SgConst_h

#if ! defined( ACE_Proper_Export_Flag )
#	include "ace/config.h"
#endif

#if defined(_LIB) || defined(_USE_CPP_)
	#define SG_CORE_API  
	#define SG_CORE_TEMPLATE
#else
	#if defined(CORE_BUILD_DLL)
		#define SG_CORE_API ACE_Proper_Export_Flag
		#define SG_CORE_TEMPLATE 
	#else
		#define SG_CORE_API ACE_Proper_Import_Flag
		#define SG_CORE_TEMPLATE extern
	#endif
#endif

//  2006-04-11,����Ԥ�������_USE_CPP_������ֱ�Ӱ���CPP�ļ��Ĺ���
#if defined(_LIB) || defined(_USE_CPP_)
	#define _DATASET_DLL_EXPORT_  
	#define _TEMPLATE_EXPORT_ 
#else
	#if defined(_DATASET_DLL_)
		#define _DATASET_DLL_EXPORT_ ACE_Proper_Export_Flag
		#define _TEMPLATE_EXPORT_ 
	#else
		#define _DATASET_DLL_EXPORT_ ACE_Proper_Import_Flag
		#define _TEMPLATE_EXPORT_
	#endif
#endif

//#include "sys_tabledef.h"

#define		PI			3.1415926535897932384626433832795
#define     EARTH_RADIUS  6378137.0
// --- �������з�ʽ������
#define		NORMAL_RUNSTYLE_MASK_VALUE		0x01
// --- �����豸�����״̬����ֵ
#define		ERROR_BREAK_STATUS				100

// --- ���������ʼ����
#define	ObjMirrorStartID		20000
#define	ObjShadowStartID		40000
#define	ObjShadowLastID			60000

#define DISTANCE_ZERO				6.2e-9	// 1.e-6,�������С��DISTANCE_ZERO������Ϊ�þ���Ϊ0(��λ��)
#define SG_MAX_EDGE_TOLERANCE		0.000001		//���ӱ��ϵĵ�����ݲΧ(��λ��)
#define SG_PRINT_ZERO               10          // ��С�Ĵ�ӡ0.1mm
#define SG_SYMBOL_PART_EXTENT       5.0         // ÿ������״̬���޶���Χ   
#define SG_SYMBOL_MAX_STATUS_NUMS   32
#define SG_DEFAULT_Z_VALUE			-19999.0		//ȱʡ�ĸ߳�ֵ
/******************************************
	Part 10		�������Ͷ���
	����Ӧ�����ֿ������ԣ���ѭ���¶��������͵Ķ���
******************************************/
#define		 SG_SHORT	short
#define		 SG_INT		int
#define		 SG_BOOL	bool
/*
 *  �޸�ԭ��ArcSDE��Oracle�Ľӿڶ�4�ֽ��������ص����Ͳ�һ�£���ǰϵͳ����ʵ�ϵĴ���ʽ����ȫһ����
 *  �޸ķ������̳���ʵ����SG_LONG��SG_INT�Ķ���Ҳ��ȫһ��
 *            8�ֽ���������ΪSG_INT64����ǰϵͳ���ݲ�ʹ��
 */
#define		 SG_LONG	int
#define		 SG_FLOAT	float
#define		 SG_DOUBLE	double

#define		 SG_USHORT	unsigned short
#define		 SG_UINT	unsigned int
#define		 SG_ULONG	unsigned int
#define		 SG_STRING		char*
#define		 SG_PCSTR		const char*
#define		 SG_PSTR		char*
#define		 SG_CHAR		char
#define		 SG_SCHAR		signed char
#define		 SG_UCHAR		unsigned char


//#ifdef _USE_INT64_
#define		 SG_UINT64	unsigned long long
#define		 SG_INT64	long long
//#endif

#define		 SG_COLORREF	long
#define		 SG_PTR         void*

#define		 SG_PBOOL	bool*
#define		 SG_PSHORT	short*

#define		 SG_PINT	int*
#define		 SG_PLONG	int*
#define		 SG_PFLOAT	float*
#define		 SG_PDOUBLE	double*

#define		 SG_PUSHORT	unsigned short*
#define		 SG_PUINT	unsigned int*
#define		 SG_PULONG	unsigned int*
//#define _USE_TOPO_INT64_
#ifdef _USE_TOPO_INT64_
typedef SG_INT64		SG_NODEINT;
#else
typedef SG_LONG		SG_NODEINT;
#endif
//	�������õķ��ش�����
#define		 SG_CODE		SG_UINT
#ifdef _WIN64
typedef SG_INT64		SG_INTPTR;
#else
typedef SG_LONG		SG_INTPTR;
#endif // _WIN64


//��ɫRGBֵ 
#define MYRGB(r,g,b)          ((SG_ULONG)(((SG_UCHAR)(r)|((SG_USHORT)((SG_UCHAR)(g))<<8))|(((SG_ULONG)(SG_UCHAR)(b))<<16)))
#define MYMAX(a,b)				(((a)>(b))?(a):(b))
#define MYMIN(a,b)				(((a)<(b))?(a):(b))

/***********************************************
	Part 20 �����Ͷ���
	����Ӧ���������͵����ݿ⣬��Ӧ�ò������ͬ�������Ͷ���
***********************************************/
#define SG_FIELDTYPE_ILLEGAL		-1
#define SG_FIELDTYPE_CHAR			0
#define SG_FIELDTYPE_BINARY			1
#define SG_FIELDTYPE_LONGCHAR		2
#define SG_FIELDTYPE_LONGBINARY		3
#define SG_FIELDTYPE_TEXT			4
#define SG_FIELDTYPE_IMAGE			5
#define SG_FIELDTYPE_TINYINT		6
#define SG_FIELDTYPE_SMALLINT		7
#define SG_FIELDTYPE_INT			8
#define SG_FIELDTYPE_REAL			9
#define SG_FIELDTYPE_FLOAT			10
#define SG_FIELDTYPE_BIT			11
#define SG_FIELDTYPE_DATETIME		12
#define SG_FIELDTYPE_DATETIME4		13
#define SG_FIELDTYPE_MONEY			14
#define SG_FIELDTYPE_MONEY4			15
#define SG_FIELDTYPE_NUMERIC		16
#define SG_FIELDTYPE_DECIMAL		17
#define SG_FIELDTYPE_VARCHAR		18
#define SG_FIELDTYPE_VARBINARY		19
#define SG_FIELDTYPE_LONG			20
#define SG_FIELDTYPE_SENSITIVITY	21
#define SG_FIELDTYPE_BOUNDARY		22
#define SG_FIELDTYPE_VOID			23
#define SG_FIELDTYPE_USHORT			24
#define SG_FIELDTYPE_GEOMETRY		25			//����SDE�е�SHAPE�ֶ�
#define SG_FIELDTYPE_RAW			26			//
#define SG_FIELDTYPE_INT64			27

// ---- OCI�ĸ�����
#ifndef SQLT_INT
	#define	SQLT_INT		3
#endif
/***********************************************
	Part 30 �����ַ����ṹ���䳤�ȶ���
	����Ӧ���������͵����ݿ⣬��Ӧ�ò������ͬ�������Ͷ���
***********************************************/
//typedef char SG_TABLENAME[32];			//�����洢�ṹ
//typedef char SG_TABLENAMEDES[40];		//������洢�ṹ
typedef char SG_FIELDNAME[32];			//�����洢�ṹ
typedef char SG_FIELDNAMEDES[40];		//������洢�ṹ
typedef char SG_OBJECTNAMEDES[40];		//�������������洢�ṹ
typedef char SG_OBJCODE[24];			//�������洢�ṹ
typedef char SG_MSG[128];		//ϵͳ���������Ϣ
//typedef unsigned long SG_OBJECTIDSTRUCT;//�豸ID
//#define SG_TABLENAME_LEN sizeof(SG_TABLENAME)
//#define SG_TABLENAMEDES_LEN sizeof(SG_TABLENAMEDES)
#define SG_FIELDNAME_LEN sizeof(SG_FIELDNAME)
#define SG_OBJECTNAMEDES_LEN sizeof(SG_OBJECTNAMEDES)
#define SG_OBJCODE_LEN sizeof(SG_OBJCODE)
#define	SG_MSG_LEN	sizeof(SG_MSG)

/***********************************************
	Part 40 ϵͳ���ƶ���
***********************************************/
#define		SG_MAX_FIELD_WIDTH			4000		//���ݿ����ֶε���󳤶�
												//������raw�����ֶεĳ��ȿ���
#define		SG_MAX_FIELD_NUMS			200				//ϵͳDoWithCurTable֧�ֵ�����������
#define		SG_MAX_FILEPATH_LEN			512				//�ļ�·����󳤶�
#define		SG_MAX_FILENAME_LEN			64				//�ļ�����󳤶�
#define		SG_MAX_SQLWORD_LEN			3998			//ϵͳ֧�ֵ�����Sql��䳤��
#define		SG_MAX_OBJECT_TYPE			1024			//�������͵����ֵ
#define		SG_MAX_FONTNAME_LEN			28				//��������󳤶�
#define		SG_MAX_ORACLESPATIAL_BUFFER	1			//��OracleSpatial��ȡ���ݵĻ���������
#define		SG_MAX_ATTRIBTABLE_BUFFER   1024			//��һ����ȡ���ݵĻ���������

#define		SG_MAX_DOMAIN_IS_OBJIDTONAME		1000		//DoMainΪ����ID�����Ƶ�ת��ʱ�ṩ������ѡ����ֵ
//ϵͳ������ֵ�ı��� --- ���豸�ĳߴ�������һ��������ֵ�洢��СֵΪ1,�޷����㹤�̵���Ҫ,���Ըñ�����Ϊ����Ĵ�С(����)
extern _DATASET_DLL_EXPORT_ int SG_INTVALUE_SCALE;
//#define					100
#define		SG_FLAG_SCREEN_SCALE		100		//��ʾ��Ǵ�Сռ��Ļ�Ĵ�С
#define     SG_SEGMENT_MAX              101     //���Ķ���
#define		SG_DISP_AS_DEFAULT_SIZE		9000	//��ʾ����������Ϊ��ʾȱʡ��С


/******************************************
	Part 80 ����ͨ������ض���
******************************************/
#define	SG_NET_VERSION_1			1		//�汾1���ݸ�ʽ�汾��
#define	SG_NET_VERSION_2			2		//�汾2���ݸ�ʽ�汾��
#define	SG_NET_VERSION_3			3		//�汾3���ݸ�ʽ�汾��

#define	SG_NET_VERSION_GIS_START	50		//PSP��ʼ�汾��
#define	SG_NET_VERSION_51			51	
#define	SG_NET_VERSION_52			52	
#define	SG_NET_VERSION_53			53	

#define	SG_NET_VERSION				SG_NET_VERSION_53		//��ǰ���ݸ�ʽ�汾��
//#define SG_NET_CHECKVERSION(VERSION) ((VERSION==SG_NET_VERSION_1)||(VERSION==SG_NET_VERSION_2))        
#define SG_NET_CHECKVERSION(VERSION) (VERSION<=SG_NET_VERSION)

#define SgNetVersion SG_NET_VERSION
//#define SG_NET_CHECKVERSION(VERSION) ((VERSION==SG_NET_VERSION_1)||(VERSION==SG_NET_VERSION_2))        
#define	  SG_NET_GETVERSION(VERSION) 	if(VERSION<0) {  VERSION=SgNetVersion; if(VERSION<0) return false; }
#define	  SG_NET_GETHEADVERSION(VERSION) 	if(VERSION<0) { if(CmdVersion>0) VERSION=CmdVersion; else VERSION=SgNetVersion; if(VERSION<0) return false; }

#define DEFAULT_DBNO			1
#define DEFAULT_SYS_DBNO		1000
#define DEFAULT_FILE_DBNO		1001
#define DEFAULT_HDBNO			1002

#define DEFAULT_DATVER_RUN		0  //ȱʡ���������а�

#define SG_DBVERTYPE_NOVER				0 //û�а汾
#define SG_DBVERTYPE_ALLDAT				1 //ȫ���汾
#define SG_DBVERTYPE_INCREMENT			2 //��ʱ������汾
#define SG_DBVERTYPE_ADTBL				3 //����AD��汾

#define SG_DB_DATVERNO_BASE			DEFAULT_DATVER_RUN //���汾�汾��
#define SG_FIELD_DAT_VERNO	"DAT_VERNO"

/******************************************
	Part 90 �����豸����Ԫ�豸ID
******************************************/
//
#define META_DEVICE_LOADRANGE			1	//���ز���
#define META_DEVICE_POWERPOINT			2	//��Դ��	
#define META_DEVICE_COMBIN_TEMPLATE		3	//�豸���ģ��
#define META_DEVICE_TEMPLATE			4	//�豸��	
#define META_DEVICE_CIRCUIT				5	//�����Ԫ	
#define META_DEVICE_OFFSET_POINT		6	//ϵͳ��ƫ��	
#define META_DEVICE_OFFSET_LINE			7	//ϵͳ��ƫ��	
#define META_DEVICE_STATION_POS			8	//վַ	
#define META_DEVICE_BAY					9	//��λ	
#define META_DEVICE_CABLE_LINE			10	//վ�����	
#define META_DEVICE_CABLE_LINE_LV		11	//��ѹ����	
#define META_DEVICE_CABLE_STATION		12	//վ�ڵ���	
#define META_DEVICE_COMPANY				13	//��˾
#define META_DEVICE_GRID_LINE			14	//������	
#define META_DEVICE_GRID_POINT			15	//�����	
#define META_DEVICE_YC_BASE				16	//ң���	
#define META_DEVICE_KWH_BASE			17	//��Ȳ�	
#define META_DEVICE_TOPO_POWE			18	//���˵�Ч��Դ	
#define META_DEVICE_TOPO_LINE			19	//������·	
#define META_DEVICE_OBJ_CANVAS			20	//����	
#define META_DEVICE_OBJ_NORMALRANGE		22	//����������������Χ	
#define META_DEVICE_WORK_WELL			23	//����	
#define META_DEVICE_WORK_WELL_COVER		24	//������	
#define META_DEVICE_TEMP_OBJECT			27	//��ʱ����	
#define META_DEVICE_LABEL_ARROW			28	//��ע��ͷ	
#define META_DEVICE_DISTRICT_CHARACTER	29	//������������	
#define META_DEVICE_PIPE_TYPEID			30	//��·Ԫ���������ID	
#define META_DEVICE_DISTRICT_TYPEID		31	//��������Ԫ��������ID	
#define META_DEVICE_TR_LINE				32	//�����·
#define META_DEVICE_LINE				33  //�����·
#define META_DEVICE_LV_LINE			    34  //��ѹ��·
#define META_DEVICE_OBJLABEL			35	//�豸��ע
#define META_DEVICE_SUBSTATION			36	//���վ
#define META_DEVICE_SWITCHSTATION		37	//����վ
#define META_DEVICE_TRANSSET			38	//��̨
#define META_DEVICE_RMU					39	//������
#define META_DEVICE_POLE				40	//����
#define META_DEVICE_LVLINKFUSE			41	//��ѹ��˿��
#define META_DEVICE_USERSTATION			44	//�û���վ(38��44֮����������ϸ������ĵ�վ)
#define META_DEVICE_LINEPOINT			45	//�����ߵ�
#define META_DEVICE_DYNAMOTOR			47	//�����

#define META_DEVICE_DISTRIBUTE_SUBSTAION 50 //�����
#define META_DEVICE_TRUNK_SUBSTATION	51	//��ʽ��
#define META_DEVICE_BRANCH_BOX			52	//���·�֧��
#define META_DEVICE_LV_CIRCUIT			53	//��ѹ���
#define META_DEVICE_LV_LINEPOINT		54	//��ѹ�����ߵ�
#define META_DEVICE_LV_SUPPLY_POINT		55	//��ѹ�ӵ��
#define META_DEVICE_LV_TRANS_REGION		56	//��ѹ̨��
#define META_DEVICE_HYPER_LINE			57	//��ѹ��������
#define META_DEVICE_LV_HYPER_LINE		58	//��ѹ��������
#define META_DEVICE_LV_POWER_LINE		59	//�˱�������
#define META_DEVICE_WORLD_TYPE			60	//world����
#define META_DEVICE_MAIN_TRANS			61  //����
#define META_DEVICE_DISTR_TRANS			62  //���
#define META_DEVICE_USER_SUBSTAION		63	//�û�վ


#define META_DEVICE_LINE_SEGMENT		70	//����
#define META_DEVICE_CABLE_SEGMENT		71	//���¶�

#define META_DEVICE_METER				80	//���
#define META_DEVICE_LAYOUT_LINE			85	//��������ͼ�߶���
#define META_DEVICE_LAYOUT_POINT		86	//��������ͼ�����
#define META_DEVICE_SCHEME_RANGE		87	//�滮������Χ
#define META_DEVICE_RDP_ANA				101	//ң����
#define META_DEVICE_RDP_DIG				102	//״̬��
#define META_DEVICE_RDP_ACC				103	//�����
#define META_DEVICE_RDP_EVENT			104	//����

#define DEVICE_RDP_ANA				500	//ң����
#define DEVICE_RDP_DIG				501	//״̬��
#define DEVICE_RDP_ACC				502	//�����
#define DEVICE_RDP_EVENT			503	//����
#define DEVICE_RDP_CPSEVT			504	//ƽ̨����
#define DEVICE_RDP_POSITION			505	//λ����

#define DEVICE_PHYNODE              1000 //����ڵ�
#define DEVICE_RDP_RTU				1001 //�ն�
#define DEVICE_SUBSTATION			1		//��վ���豸����
#define DEVICE_COMPANY				600		//��˾���豸����
#define DEVICE_TEAM					601		//�Ŷӵ��豸����
#define DEVICE_INVERTER				29		//�����
#define DEVICE_COMBINING			30		//������
#define DEVICE_PVARRAY				31		//������鴮
#define DEVICE_CIRCUIT				20		//��·
#define DEVICE_CONTAINER			4		//����
#define DEVICE_POWERPOINT           22		//��Դ��
#define DEVICE_AREA					602		//����
#define DEVICE_CUSTOMER				800		//�õ��û�
#define DEVICE_BATTERIES			34		//�����
#define DEVICE_BATTERY				35		//���
#define DEVICE_MCU				24   //����豸

#define SG_RDP_MAX_TERMAINL				1000000

/**************************************************************************************
	Part 100 ϵͳ�ض��������Ͷ��壬��ͨ��Ԫ�����ݽ�����ע��Ҫ�����ݿ�����һ��
**************************************************************************************/
#define DEVICE_SYMBOL_ELEMENT		31		//ͨ�����Ŷ��������ҽ�ϵͳ����
//�Ҽ���DEVICE_SYMBOL_ELEMENT�ϵķ�����Ϊϵͳ��������
enum SYS_SYMBOL
{
	FLOW_SYMBOL					=0,		//�����������
	STATICTOP_SYMBOL			=1,		//��̬���˷������
	TOPBARRIER_SYMBOL			=2,		//�����ϰ������
	WORK_WELL_SYMBOL			=3		//����ģ�����
};

//��ˢ����
/* Brush Styles */
#define HS_HORIZONTAL       0       /* ----- */
#define	HS_VERTICAL         1       /* ||||| */
#define	HS_FDIAGONAL        2       /* \\\\\ */
#define	HS_BDIAGONAL        3       /* ///// */
#define	HS_CROSS            4       /* +++++ */
#define	HS_DIAGCROSS        5       /* xxxxx */
//
#ifndef WIN32
#define BS_SOLID            0
#define BS_NULL             1
#define BS_PATTERN          3
#define PS_SOLID            0
#define PS_DOT              2 
#define TRANSPARENT         1
#define OPAQUE              2
#endif
#define HS_BASE				6
#define	HS_SOLID			BS_SOLID+HS_BASE	//6
#define	HS_NULL				BS_NULL+HS_BASE		//7
#define	HS_BITMAP			BS_PATTERN+HS_BASE	//9
//
#define stop_dev_status 59	//�豸��ֹ״ֵ̬

//��ѹ�ȼ�������Domain����һ��
enum STANDARD_VOLTAGE
{
	STANDARD_220V_VOLTAGE			=	7,	//0.4ǧ��/380������ֵ
	STANDARD_380V_VOLTAGE			=	8,	//0.4ǧ��/380������ֵ
	STANDARD_2_5KV_VOLTAGE			=	15, //2.5kV
	STANDARD_3KV_VOLTAGE			=	20,	//3ǧ������ֵ
	STANDARD_6KV_VOLTAGE			=	21,	//6ǧ������ֵ
	STANDARD_10KV_VOLTAGE			=	22,  //10kV��ѹ�ȼ�����ֵ
	STANDARD_15_75KV_VOLTAGE		=	23,	//15.75kV��ѹ�ȼ�����ֵ
	STANDARD_20KV_VOLTAGE			=	24,	//20kV��ѹ�ȼ�����ֵ
	STANDARD_35KV_VOLTAGE			=	25,  //35kV��ѹ�ȼ�����ֵ
	STANDARD_50KV_VOLTAGE			=	5,  //50kV��ѹ�ȼ�����ֵ
	STANDARD_66KV_VOLTAGE			=	30,  //66kV��ѹ�ȼ�����ֵ
	STANDARD_110KV_VOLTAGE			=	32,  //110kV��ѹ�ȼ�����ֵ
	STANDARD_220KV_VOLTAGE			=	33,  //220kV��ѹ�ȼ�����ֵ
	STANDARD_330KV_VOLTAGE			=	34,  //330kV��ѹ�ȼ�����ֵ
	STANDARD_500KV_VOLTAGE			=	35,  //500kV��ѹ�ȼ�����ֵ
	STANDARD_750KV_VOLTAGE			=	36,  //750kV��ѹ�ȼ�����ֵ
	STANDARD_1000KV_VOLTAGE			=	37  //1000kV��ѹ�ȼ�����ֵ
};

enum
{
	STANDARD_110V_DC_VOLT			=	56,	//ֱ��110V5
	STANDARD_220V_DC_VOLT			=	60,	//ֱ��220V
	STANDARD_120kV_DC_VOLT			=	80,	//ֱ��120kV
	STANDARD_125kV_DC_VOLT			=	81,	//ֱ��125kV
	STANDARD_500kV_DC_VOLT			=	83,	//ֱ��500kV
	STANDARD_800kV_DC_VOLT			=	85,	//ֱ��800kV
	STANDARD_1000kV_DC_VOLT			=	86	//ֱ��1000kV	
};

enum
{
	STANDARD_220V_VOLT_VAL			=	220,		//220���ļ���ֵ
	STANDARD_380V_VOLT_VAL			=	400,		//0.4ǧ��/380���ļ���ֵ
	STANDARD_2_5KV_VOLT_VAL			=	2500,		//2.5ǧ���ļ���ֵ
	STANDARD_3KV_VOLT_VAL			=	3000,		//3ǧ���ļ���ֵ
	STANDARD_6KV_VOLT_VAL			=	6000,		//6ǧ���ļ���ֵ
	STANDARD_10KV_VOLT_VAL			=	10000,		//10kV��ѹ�ȼ��ļ���ֵ
	STANDARD_15_75KV_VOLT_VAL		=	15750,		//15.75kV��ѹ�ȼ��ļ���ֵ
	STANDARD_20KV_VOLT_VAL			=	20000,		//20kV��ѹ�ȼ��ļ���ֵ
	STANDARD_35KV_VOLT_VAL			=	35000,		//35kV��ѹ�ȼ��ļ���ֵ
	STANDARD_50KV_VOLT_VAL			=	50000,		//50kV��ѹ�ȼ��ļ���ֵ
	STANDARD_66KV_VOLT_VAL			=	66000,		//50kV��ѹ�ȼ��ļ���ֵ
	STANDARD_110KV_VOLT_VAL			=	110000,		//110kV��ѹ�ȼ��ļ���ֵ
	STANDARD_220KV_VOLT_VAL			=	220000,		//220kV��ѹ�ȼ��ļ���ֵ
	STANDARD_330KV_VOLT_VAL			=	330000,		//330kV��ѹ�ȼ��ļ���ֵ
	STANDARD_500KV_VOLT_VAL			=	500000,		//500kV��ѹ�ȼ��ļ���ֵ		
	STANDARD_750KV_VOLT_VAL			=	750000,		//500kV��ѹ�ȼ��ļ���ֵ	
	STANDARD_1000KV_VOLT_VAL		=	1000000		//500kV��ѹ�ȼ��ļ���ֵ	
};

enum
{
	STANDARD_110V_DC_VOLT_VAL			=	110,	//ֱ��110V5
	STANDARD_220V_DC_VOLT_VAL			=	220,	//ֱ��220V
	STANDARD_120kV_DC_VOLT_VAL			=	120000,	//ֱ��120kV
	STANDARD_125kV_DC_VOLT_VAL			=	125000,	//ֱ��125kV
	STANDARD_500kV_DC_VOLT_VAL			=	500000,	//ֱ��500kV
	STANDARD_800kV_DC_VOLT_VAL			=	800000,	//ֱ��800kV
	STANDARD_1000kV_DC_VOLT_VAL			=	1000000	//ֱ��1000kV	
};
#endif