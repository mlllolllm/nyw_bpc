//==================================================================================================
//	Summary:
//		DPS ( Data Process Server ) Share Struct
//
//	---------------------------------------------------------------------------------------------
//	Author: Arctos                    Version: 1.00.000                          Date: 2011-09-01
//==================================================================================================

#ifndef __DPS_SHARE_STRUCT__
#define __DPS_SHARE_STRUCT__
#include "rdp_const.h"
enum SHARE_MEMORY_RECORD_STATUS_
{
	SMRS_LIMIT			= 0x00000007 ,		//	Խ�ޱ��,�μ� SMR_LIMIT_* ����

	SMRS_LOCKED			= 0x00000080 ,		//	����
	SMRS_MANSET			= 0x00000100 ,		//	�˹�����

	SMRS_DEATH			= 0x00001000 ,		//	����

	SMRS_FLASH			= 0x00004000 ,		//	��˸
	SMRS_INVALID		= 0x00008000 ,		//	ֵ��Ч
};

enum SHARE_MEMORY_RECORD_FLAGS_
{
	SMRS_CANYKYT = 0x00000002,		//	ģ������ң����״̬����ң��
	SMRF_EXCEPT			= 0x00000040 ,		//	�¹�
	SMRF_AUTO_RESUM		 = 0x00000080,		//	�Զ�����
	SMRF_INVERT			= 0x00000100 ,		//	�ź���ȡ��

	SMRS_NO_EVENT		= 0x00000200 ,		//	��������
	//SMRF_ALARMDELAY		= 0x00000400 ,		//	�����ӳ�
	SMRS_ALARM_SAVEVAL	= 0x00000800,		//	ģ��������ʱ�洢���ֵ,״̬������ʱ�洢ͬ�豸��yc kwh

	SMRF_LIMIT_1		= 0x00001000 ,		//	��������Ч
	SMRF_LIMIT_2		= 0x00002000 ,		//	���� ��������Ч
	SMRF_RANGE			= 0x00004000 ,		//	��������Ч

	SMRS_DEAD_SAVEVAL	= 0x00008000,		//	ģ�����������洢��ʷ����
	SMRS_SAVE_REALMAXMIN= 0x00010000,		//	ģ�����洢���̼���ڵ�ʵʱ��� ʵʱ��С
	SMRS_SAVE_MAN_RESET= 0x00020000,		//	���˹���λ

	SMRF_INVALID		= 0x00080000 ,		//	ֵ��Ч
};

//==================================================================================================
//ģ������	
typedef struct SMT_DPS_ANA
{
	int		ID;		//ID
	char		Name[80];		//����
	int		Stamp;		//����ʱ���
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	double		Value;		//���ֵ
	int		Status;		//״̬
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	int		Terminal;		//���Ӻ�
	int		Measure;		//��������
	double		Maximum;		//�����ֵ
	double		Minimum;		//����Сֵ
	double		Limit_H;		//����
	double		Limit_L;		//����
	double		Limit_HH;		//������
	double		Limit_LL;		//������
	double		Base;		//�����ֵ
	double		Rate;		//�������
	int		Interval;		//���̼��
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	short		MeasClass;		//�������
	unsigned char		res0[2];
	int		Delay;		//�ӳ�ʱ��
	unsigned char		DatLevel;		//���ݵȼ�
	unsigned char		res1[3];
	int		ProcMode;		//����ģʽ
#if (SG_RDB_VERNO>=2)
	double		BrkChanVal;		//ͻ����ֵ
	int		MaxTime;		//���ֵ����ʱ
	int		MinTime;		//���ֵ����ʱ
	int		DispUnit;		//��ʾ��λ
	int		BakVal1;		//����1
	double	LastSaveVal; //�ϴδ���ֵ
#endif
}SMT_DPS_ANA;
//��������	
typedef struct SMT_DPS_DIG
{
	int		ID;		//ID
	char		Name[80];		//����
	int		Stamp;		//����ʱ���
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	int		Value;		//���ֵ
	int		Status;		//״̬
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	int		Terminal;		//���Ӻ�
	int		Measure;		//��������
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	short		MeasClass;		//�������
	short		MCU_Close;		//MCU��բ���
	short		MCU_Open;		//MCU��բ���
	short		YK_Close;		//ң�غ�բ���
	short		YK_Open;		//ң�ط�բ���
	unsigned char		res0[2];
	int		Delay;		//�ӳ�ʱ��
#if (SG_RDB_VERNO>=2)
	int		BakVal1;		//����1
	int		BakVal2;		//����2
	int		BakVal3;		//����3
	int		BakVal4;		//����4
#endif
}SMT_DPS_DIG;

//��ȱ�
typedef struct SMT_DPS_ACC
{
	int		ID;		//ID
	char		Name[80];		//����
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	int		Status;		//״̬
	double		Value;		//����ֵ
	double		MarkValue;		//����ֵ
	double		LastMarkValue;		//�ϴα���ֵ
	int		Stamp;		//����ʱ���
	int		MarkStamp;		//����ʱ���
	int		DayEvtCnt;		//���յ����������
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	short		Terminal;		//���Ӻ�
	unsigned char		res0[2];
	int		Measure;		//��������
	double		ConvFact;		//���㱶��
	double		FullCode;		//����
	int		Interval;		//���̼��
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	short		MeasClass;		//�������
	unsigned char		res1[2];
	int		ProcMode;		//����ģʽ
	int		Delay;		//�ӳ�ʱ��
#if (SG_RDB_VERNO>=2)
	int		DispUnit;		//��ʾ��λ
	double	InitMarkValue;		//��ʼ����
	int		BakVal4;		//ÿ���������ֵ
#endif
	unsigned char		res2[4];
}SMT_DPS_ACC;

typedef struct  SMT_DPS_ANA S_YCINFO;
typedef struct  SMT_DPS_DIG S_YXINFO;
typedef struct  SMT_DPS_ACC S_KWHINFO;
//ģ����������	
typedef struct S_ANA_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	int		Terminal;		//���Ӻ�
	int		Measure;		//��������
	double		Limit_H;		//����
	double		Limit_L;		//����
	double		Limit_HH;		//������
	double		Limit_LL;		//������
	double		Base;		//�����ֵ
	double		Rate;		//�������
	int		Interval;		//���̼��
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	int		Delay;		//�ӳ�ʱ��
	int		ProcMode;		//����ģʽ
	double		BrkChanVal;		//ͻ����ֵ
}S_ANA_BASEINFO;
//������������	
typedef struct S_DIG_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	int		Terminal;		//���Ӻ�
	int		Measure;		//��������
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	short		MCU_Close;		//MCU��բ���
	short		MCU_Open;		//MCU��բ���
	short		YK_Close;		//ң�غ�բ���
	short		YK_Open;		//ң�ط�բ���
	int		Delay;		//�ӳ�ʱ��
}S_DIG_BASEINFO;

//�����������	
typedef struct S_ACC_BASEINFO
{
	int		ID;		//ID
	int		Remote;		//�ն˱��
	int		Serial;		//���������
	int		SFlag;		//��̬״̬��Ϣ
	int		ObjType;		//�豸����
	int		ObjID;		//�豸ID
	int		Terminal;		//���Ӻ�
	int		Measure;		//��������
	double		ConvFact;		//���㱶��
	double		FullCode;		//����
	int		Interval;		//���̼��
	int		WorkSpace;		//�����ռ�
	int		SrcType;		//�����־
	int		SubStation;		//վID
	int		ProcMode;		//����ģʽ
	int		Delay;		//�ӳ�ʱ��
	int		BakVal4;		//ÿ�����仯ֵ
	unsigned char		res1[4];
}S_ACC_BASEINFO;



//ͨ���豸���ͱ�	
typedef struct S_CHANDEVTYPEINFO
{
	short		Type;		//ͨ���豸����
	char		Desc[40];		//ͨ���豸����
	char		DllName[40];		//ͨ���豸��̬��
}S_CHANDEVTYPEINFO;

//��������	
typedef struct SMT_DPS_CALC
{ 
int		ObjType;		//�豸����
int		ObjID;		//�豸ID
char	RtField[32];		//�����ֶ�
int		WorkSpace;		//�����ռ�
char		Formula[1024];		//���㹫ʽ
int		StartItemNo;		//��ʼ�����
int		ItemNum;		//�������
short		CalcState;		//����״̬
unsigned char		CalcHisFlag;		//������ʷ����
unsigned char		res0[1];
short		DelayHours;		//��ʷ�ͺ�Сʱ
short		FieldNo;		//ʵʱ�����
}SMT_DPS_CALC;
//��������	
typedef struct SMT_DPS_CALCITEM
{ 
int		CalcNo;		//�����
short		ItemNo;		//��������
short		ItemType;		//Ԫ������
short		DatType;		//ʵʱ��ı�No/����/��������
short		FieldNo;		//ʵʱ�����
int		KeyID;		//ʵʱ��ļ�ֵ
char		FieldName[32];		//ʵʱ����
double		ItemVal;		//Ԫ��ֵ
}SMT_DPS_CALCITEM;

//ǰ�������	
typedef struct S_FERT_CMDINFO
{ 
unsigned char		Valid;		//��Ч��־
unsigned char		CmdType;		//��������
unsigned char		SubCmdType;		//����������
unsigned char		Status;		//ִ��״̬
int		ExSysID;		//SCDϵͳID
int		SendCmdTime;		//�����´�ʱ��
int		MaxProcTime;		//�ִ��ʱ��
char	CmdDat[128];		//����������
}S_FERT_CMDINFO;

//�ⲿϵͳ	
typedef struct S_EXSYSINFO
{ 
char		Code[32];		//�ⲿϵͳ����
short		ID;		//�ⲿϵͳID
unsigned char		res0[2];
int		WorkSpace;		//�����ռ�
int		SysAddr;		//�ⲿϵͳ��ַ
short		Type;		//�ⲿϵͳ����
short		ProtocolID;		//��Լ��
unsigned char		UseFlag;		//ʹ�ñ�־
unsigned char		res1[3];
int		SavePeriod;		//���̼��(��)
int		KWHSavePeriod;		//KWH���̼��(��)
char		User[64];		//�û���
char		Passwd[64];		//����
char		SysPara[128];		//ϵͳ����
int		DeadPeriod;		//�����б�ʱ��(��)
short		HisYCDelayHours;		//��ʷYC��ʱСʱ
unsigned char		res2[2];
int		HisYCCallTime;		//��ʷYC�ٻ�����Է�
short		HisKWHDelayHours;		//��ʷKWH��ʱСʱ
unsigned char		res3[2];
int		HisKWHCallTime;		//��ʷKWH�ٻ�����Է�
int		CallAllTime;		//�ٻ�ȫ����ʱ��
int		HisDatBaseYMD;		//���ջ�׼������
short		Warn_LackPercent;		//ȱ�������ٷֱ�
short		Warn_YXChanNum;		//��λ��������
int		ProcMode;		//����ģʽ
unsigned char		RealLinkStatus;		//ʵʱ����״̬
unsigned char		HisLinkStatus;		//��ʷ����״̬
unsigned char		res4[2];
int		ErrCnt;		//���ߴ���
int		ErrYMD;		//������������
int		ErrHMS;		//������ʱ����
int		ProcTime_HisYC;		//��ʷң���ٻ�����ʱ��
int		ProcTime_HisKWH;		//��ʷ����ٻ�����ʱ��
int		ProcTime_HisKWH_Mark;		//��ʷ��ȱ����ٻ�����ʱ��
}S_EXSYSINFO;
//�ն˱�	
typedef struct S_RTUINFO
{
	char		Code[32];		//�ն�����
	int		ID;		//�ն�ID
	int		RtuAddr;		//�ն˵�ַ
	short		Type;		//�ն�����
	unsigned char		UseFlag;		//ʹ�ñ�־
	unsigned char		res0[1];
	int		SavePeriod;		//���̼��(��)
	int		KWHSavePeriod;		//KWH���̼��(��)
	char		User[64];		//�û���
	char		Passwd[64];		//����
	char		RtuPara[128];		//�ն˲���
	int		DeadPeriod;		//�����б�ʱ��(��)
	int		ProcMode;		//����ģʽ
	int		ZFGrpNo;		//ת�����
	int		WorkSpace;		//�����ռ�
	int		NodeID;		//ǰ�û�ID
	int		MainLinkPathID;		//����·ID
	int		ProcTime;		//������ʱ��
	unsigned char		LinkStatus;		//����״̬
	unsigned char		Status;		//�ն�״̬
	unsigned char		res1[2];
	int		ErrCnt;		//���ߴ���
	int		ErrYMD;		//������������
	int		ErrHMS;		//������ʱ����
}S_RTUINFO;//ģ������	
//��������Ϣ��	
typedef struct S_METERINFO
{
	int		ID;		//���ID
	char		Code[32];		//����
	int		WorkSpace;		//�����ռ�
	int		ReaderID;		//�ɼ���ID
	int		RtuID;		//�ն�ID
	int		MeterNo;		//�ɼ���
	short		Phase;		//��λ
	unsigned char		res0[2];
	int		BaudRate;		//������
	short		PortNo;		//�˿ں�
	short		ProtocolType;		//ͨѶЭ��
	char		TXPasswd[16];		//ͨѶ����
	short		RateNum;		//���ʸ���
	short		UseClass1;		//�û������
	short		UseClass2;		//�û�С���
	short		MarkIntegerNum;		//�����������λ����
	short		MarkDecimalNum;		//�������С��λ����
	unsigned char		res1[2];
	int		ReaderID_CJ;		//ʵ�ʲɼ���ID
	int		RtuID_CJ;		//ʵ���ն�ID
	int		MeterNo_CJ;		//ʵ�ʲɼ���
	short		Phase_CJ;		//ʵ����λ
	unsigned char		res2[2];
	int		ProcTime;		//����ʱ��
	int		PtID_11;		//�������ID
	int		PtID_12;		//A��������ID
	int		PtID_13;		//B��������ID
	int		PtID_14;		//C��������ID
	int		PtID_1;		//��ѹ���ID
	int		PtID_7;		//A���ѹ���ID
	int		PtID_8;		//B���ѹ���ID
	int		PtID_9;		//C���ѹ���ID
	int		PtID_201;		//�й��������ID
}S_METERINFO;
//�ɼ�����Ϣ��	
typedef struct S_READERINFO
{
	int		ID;		//�ɼ���ID
	char		Code[32];		//����
	int		WorkSpace;		//�����ռ�
	short		Phase;		//��λ
	unsigned char		res0[2];
	int		RtuID;		//�ն�ID
	short		Phase_CJ;		//ʵ����λ
	unsigned char		res1[2];
	int		RtuID_CJ;		//ʵ�ʲɼ����ն�
	int		ProcTime;		//����ʱ��
}S_READERINFO;
//ת��ģ������	
typedef struct S_ZFINFO_ANA
{
	int		GroupID;		//ת�����
	int		ZFPointNo;		//ת�����
	char	Name[24];		// ����
	int		PtID;		//���ID
	int		WorkSpace;		//�����ռ�
	float		ConvFace;		//ת��ϵ��
	int		ProcMode;		//����ģʽ
	unsigned char		NewFlag;		//������־
	unsigned char		res0[3];
	float		Val;		//ֵ
	int		Status;		//������־
}S_ZFINFO_ANA;
//ת����������	
typedef struct S_ZFINFO_DIG
{
	int		GroupID;		//ת�����
	int		ZFPointNo;		//ת�����
	char	Name[24];		// ����
	int		PtID;		//���ID
	int		WorkSpace;		//�����ռ�
	int		ProcMode;		//����ģʽ
	unsigned char		NewFlag;		//������־
	unsigned char		res0[3];
	int		Val;		//ֵ
	int		Status;		//������־
}S_ZFINFO_DIG;
//ת���������	
typedef struct S_ZFINFO_ACC
{
	int		GroupID;		//ת�����
	int		ZFPointNo;		//ת�����
	char	Name[24];		// ����
	int		PtID;		//���ID
	int		WorkSpace;		//�����ռ�
	float		ConvFace;		//ת��ϵ��
	int		ProcMode;		//����ģʽ
	unsigned char		NewFlag;		//������־
	unsigned char		res0[3];
	int		Status;		//������־
	double		Val;		//ֵ
	double		MarkVal;		//����ֵ
}S_ZFINFO_ACC;
typedef struct S_CHANNELINFO
{
	int		ID;		//ID
	char		Name[40];		//����
	unsigned char		UseFlag;		//ʹ�ñ�־
	unsigned char		res0[1];
	short		ChanType;		//ͨ������
	int		ProcMode;		//����ģʽ
	char		IPAddr[20];		//��ַIP
	int		BaudRate;		//������
	short		CheckBit;		//У�鷽ʽ
	short		DatBit;		//����λ
	short		StopBit;		//ֹͣλ
	short		FCtrlBit;		//������λ
	short		DevType;		//�豸����
	char		DevAddr[40];		//�豸��ַ
	unsigned char		res1[2];
	int		StopLimitTime;		//ͨ��ֹͣʱ����
	int		ErrCodeRateLimit;		//��������ֵ
	int		ErrTimeLimit;		//�����ʳ���ʱ��
	int		ChanGroup;		//ͨ����
	int		WorkSpace;		//�����ռ�
	int		ChanStatus;		//ͨ��״̬
	int		DevStatus;		//�豸״̬
}S_CHANNELINFO;
//��·��	
typedef struct S_LINKPATHINFO
{
	int		ID;		//ID
	char		Name[40];		//����
	short		RtuType;		//�ն�����
	unsigned char		res0[2];
	int		RtuID;		//�ն�ID
	int		ChanID;		//ͨ��ID
	int		WorkSpace;		//�����ռ�
	unsigned char		MainFlag;		//��ͨ����־
	unsigned char		res1[1];
	short		ProtocolID;		//��Լ��
	int		RealRtuID;		//ʵ���ն�ID
	int		ProcTime;		//������ʱ��
}S_LINKPATHINFO;
//ģ���������ݱ�	
typedef struct S_YCINFO_RAW
{
	int		ID;		//��ID
	int		WorkSpace;		//�����ռ�
	float		Val;		//ֵ
	int		Status;		//������־
	int		ProcTime;		//����ʱ��
	unsigned char		NewFlag;		//������־
	unsigned char		res0[3];
}S_YCINFO_RAW;
//״̬�������ݱ�	
typedef struct S_YXINFO_RAW
{
	int		ID;		//��ID
	int		WorkSpace;		//�����ռ�
	short		Val;		//ֵ
	unsigned char		res0[2];
	int		Status;		//������־
	int		ProcTime;		//����ʱ��
	short		Ms;		//����
	unsigned char		NewFlag;		//������־
	unsigned char		res1[1];
}S_YXINFO_RAW;
//����������ݱ�	
typedef struct S_KWHINFO_RAW
{
	int		ID;		//��ID
	int		WorkSpace;		//�����ռ�
	double		Val;		//ֵ
	double		MarkVal;		//����ֵ
	int		Status;		//������־
	int		ProcTime;		//����ʱ��
	int		MarkProcTime;		//���봦��ʱ��
	unsigned char		NewFlag;		//������־
	unsigned char		res0[3];
}S_KWHINFO_RAW;
//����λ�ñ�	
typedef struct S_POSITIONINFO
{
	char	Code[32];		//λ������
	int		ID;		//λ��ID
	int		WorkSpace;		//�����ռ�
	double		X;		//X����
	double		Y;		//Y����
	double		Z;		//Z����
	double		Distance;		//λ�Ʊ仯
#if (SG_RDB_VERNO>=2)
	double		Speed;		//�ٶ�
	double		Angle;		//�Ƕ�
	int		ProcTime;		//ʱ��
	unsigned char		res0[4];
#endif
}S_POSITIONINFO;

//��Լ���ͱ�	
typedef struct S_PROTOCOLINFO
{ 
short		Type;		//��Լ����
char		Desc[40];		//��Լ����
char		DllName[40];		//��Լ��̬��
char		HisDllName[40];		//��ʷ��Լ��̬��
}S_PROTOCOLINFO;

//�ⲿϵͳ��Լ���ͱ�	
typedef struct S_EXSYS_PROTINFO
{ 
short		ID;		//��Լ����
char		Desc[40];		//��Լ����
char		DllName[40];		//��Լ��̬��
char		HisDllName[40];		//��ʷ��Լ��̬��
unsigned char		IsClock24;		//0��Ϊ24��
char		ExSysDllName[40];		//�ⲿϵͳ��̬��
char		ProcName_ANA[40];		//ģ�����洢����
char		ProcName_DIG[40];		//״̬���洢����
char		ProcName_ACC[40];		//������洢����
unsigned char		res0[1];
}S_EXSYS_PROTINFO;
//�������ͱ�	
typedef struct S_MEASTYPEINFO
{ 
short		ID;		//��������
short		B_MeasType;		//������������
char		Code[32];		//����
char		Desc[40];		//����
short		ClassID;		//������
short		Phase;		//��λ
int		ProcMode;		//����ģʽ
unsigned char		AbNormalVal;		//�쳣״̬
unsigned char		res0[1];
short		DigStatID;		//״̬����ID
}S_MEASTYPEINFO;
//״̬������	
typedef struct S_STATDESCINFO
{ 
short		DigStatID;		//״̬����ID
unsigned char		DigVal;		//״ֵ̬
char		DigDesc[32];		//״̬����
unsigned char		res0[1];
}S_STATDESCINFO;

#endif /* __DPS_SERVICE_ADAPTER__ */
