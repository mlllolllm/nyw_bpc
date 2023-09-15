// sgdef.h
//
/*****************************************************************
	ϵͳ�Ľṹ���壬ͬʱ������ϵͳ����ͷ�ļ��ĵ���

	part 0	����ļ�¼�����ṹ
			��һ�����¼�ṹ
			���󼯺ϵļ�¼�����ṹ
			���󼯺ϵļ�¼�����ṹ
			��������˶��Ӽ�¼�ṹ
			��������˶��Ӽ�ֵ�ṹ
			�����ȱʡ�ߴ�ṹ
			����ķ������Խṹ --- ���ļ� CSgSymbol.h SG_OBJ_SYMBOL

 
	Part 10 ����ͼ�����ԣ�
		Part 10 ������ȱʡ��ʾ���� ����ļ������Ե���ʾ���Խṹ
		Part 12 ϵͳ�ض��ֶ��ڵ�ǰ���е��ֶ�ƫ�����ṹ
		Part 14 "��������"���е��ڿ�����������Ϣ�ڴ�洢�ṹ
		Part 15 ��ȡ�����кţ�ͨ����������type�ͻ�������id���ýṹ
	Part 20 ����ʵ�������Խṹ
	Part 30 �������Ա�����Ϣ�ṹ
	Part 40 ���������ϰ������Խṹ
	Part 50	ƽ�漸��������ؽṹ

	Part 60	ϵͳö�����Ͷ���
			��������Ϊ��������
			��Ӧ�����Ͷ���
			�����������Ͷ���
			�ռ�����Դ����
			��������Դ����
			����ʵ������
			����ģ�ͱ任��ʽ
			�������
			��������
			��������
			World������ʾ����
			��ϵ����
			��������
			��ʩ�豸����
			��ͼ����
			�߷�������
			��ѡ������󣩵ķ���
			��ѡ����������󣩵ķ���
			"��������"���е��ڿ���������
			���˼��㷽ʽ
			�����ԣ����뷽ʽ
			���紫���ö���
			�������Ƽ�����

	Part 80	ϵͳָ�������
	Part 90	��SCADA�ӿڽṹ����

	Part 100 ��ͼ��Ӧ�ýṹ����

	Part 110 ��ͼ���ö�����Ͷ���
			���紦�ڵ�״̬
			ϵͳ��ʾ����

	Part 120 ����༭���ƽṹ

	part 130 ϵͳ�ض���ṹ

	part 140 ϵͳ����ʱ����

	part 150 �ڴ�ռ�ü��
*****************************************************************/

#if !defined(SG_Def_h)
#define SG_Def_h

#include "sgconst.h"
#include <memory.h>
#include <string>
#include <math.h>
//#include "sggeodef_template.h"
#include "sgdataset.h"
//#ifndef WIN32
//#define SG_CORE_API 
//#endif
/************************************************
	part -1	�������Ϊ��¼�����ṹ
 SG GIS ��������Ϊ��������
	ͨ��Ԫ���ݵ�SYS_OBJECT_RELATION���BEHAVIOUR���Լ�¼
	��ϵ����Ϊ����: ��ʽ����/��ʽ����/���/����ɾ��/������ϵ/�����ӹ�ϵ/��ʾ�����ϵ
************************************************/
#define	SG_BEHAVIOUR_CONTAIN	0x07	//���������ϵ����ֵ
enum SG_Obj_BehaviourType
{
	/*
		��ʽ���� ���豸�����豸 �豸�����豸�� �豸����֧�� ֧�����豸 ̨�����豸
		��ϵ���ݴ����Ԫ���ݱ�SYS_OBJECT_RELATION��
		���¼��ʽΪ�򵥵����ݿ��ϵ,���ܻ����һ���Ƚϸ��ӵĶ�Ӧ��ϵ
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_HIDE		= 0x01,
	/*
		��ʽ���� ��վ�����������а�װ���豸
		���¼��ʽ����ڶ�������Ա���
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_VISIBLE	= 0x02,
	/*
		���ʽ���� ������������ ������ܿ���/ͨ���ߵȶ���
		��ϵ���ݴ����Ԫ���ݱ�SYS_OBJECT_RELATION��
		���¼��ʽΪ�򵥵����ݿ��ϵ
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_COMBIN	= 0x04,
	/*
		����ɾ��
	*/
	SG_OBJ_BEHAVIOUR_CASCADEDELETE = 0x08,
	/*
		������ϵ --- �ù�ϵGIS�ڲ���
	*/
	SG_OBJ_BEHAVIOUR_TRIGGER = 0x10,
	/*
		�����ӹ�ϵ --- �ù�ϵGIS�ڲ���
	*/
	SG_OBJ_BEHAVIOUR_CONNECT = 0x20,
	/*
		��ʾ�����ϵ --- �ù�ϵGIS�ڲ���
	*/
	SG_OBJ_BEHAVIOUR_DISPMUTEX = 0x40,
	/*
		������ϵ --- �ù�ϵGIS�ڲ���
	*/
	SG_OBJ_BEHAVIOUR_ADHERE  = 0x80,
	/*
		ֱ������
		����ģ�͵�������һ�Ӷุ��Ϊ�������ӵĹ�ϵ�����Ӹñ��λ
		�����ϲ�����ֱ�������ĸ��ӹ�ϵ�ɳ�ν����ֶ��ϵ
	*/
	SG_OBJ_BEHAVIOUR_CONTAIN_FATHER = 0x100,
	/*
	 ɾ�����ƹ�ϵ������������豸�����豸���ܱ�ɾ��
	 */
	SG_OBJ_BEHAVIOUR_DELETE_RESTRICT=0x200,
	/*
	 �硰�߼��⡱���ù�ϵ���磺�滮��վ��������վ֮��
	 */
	 SG_OBJ_BEHAVIOUR_REFRENCE=0x400
};

//����֮��Ĺ�ϵ��¼�ṹ

struct SG_CORE_API OBJECT_RELATION
{
	
	SG_LONG			Objtype;	//��������
	
	SG_ULONG		Behaviour;	//������Ϊ
	
	SG_UCHAR		nRelation;	//��ϵ��ά��
private:
	
	SG_FIELDNAME	fieldName;	//�����ֶ��� --- ������Ϊһ�����豸����ʱ��Ч�������븸����ID�������õ��ֶ���
	
	SG_FIELDNAME    fieldName0;
public:
	
	OBJECT_RELATION();
	//�Ƿ�Ϊ����������ϵ
	
	SG_BOOL IsVisibleContain();
	//�Ƿ�Ϊ������ϵ
	
	SG_BOOL IsContain();
	//���� ���ϸ������ ��ϵ --- �ض�Ӧ��
	
	SG_BOOL IsOnPoleRelation();
	//�Ƿ�Ϊ�����ӹ�ϵ
	
	SG_BOOL IsConnectRelation();
	//�Ƿ����ʽ����
	
	SG_BOOL IsCombin();
	//�Ƿ���ʾ����
	
	SG_BOOL IsDispMetex();
	//�Ƿ���������ϵ
	
	SG_BOOL IsAdhereRelation();
	//���ù�ϵ�ֶ���
	
	void SetRelaFieldName(SG_CHAR *p);
	
	void SetRelaFieldName_class(SG_CHAR *p);
	//ȡ��ϵ�ֶ���
	
	SG_CHAR *GetRelaFieldName();
	
	SG_CHAR *GetRelaFieldName_class();
	//�Ƿ���й�ϵ�ֶ�
	
	SG_BOOL HasRelaFieldName();
	//��չ�ϵ�ֶα�
	
	void ClearRelaFieldName();
	
	void ClearRelaFieldName_class();
};
//�����ϵ��¼�ṹ

struct SG_CORE_API OBJECT_RELATIONS
{
	
	SG_LONG			RelationNums;	//��ϵ����
	
	OBJECT_RELATION *pRelation;		//��ϵ����
	
	OBJECT_RELATIONS();
	
	~OBJECT_RELATIONS(){Clear();}
	//���ӹ���
	
	void Add(OBJECT_RELATION *pRelation);
	//���ӹ�ϵ
	
	void Add(SG_LONG Objtype,SG_LONG Behaviour,SG_UCHAR nRelation,SG_CHAR *f=0,SG_CHAR*pclass=0);
	//��ptr����ϵ�Ƿ���"���ϸ�����"���ʵĹ�ϵ --- �������Ӷ���
	
	SG_BOOL IsOnPoleRelation(SG_INT ptr);
	//��ö�ObjType�Ĺ�ϵ
	
	OBJECT_RELATION*GetRelation(SG_INT ObjType);
	//��ն���
	
	void	Clear();
};



struct SG_CORE_API ObjTypeAndSubTypeStruct
{
	
	SG_SHORT ObjType;
	
	SG_SHORT SubType;
};

// --- ��������Խṹ

struct SG_CORE_API SG_REAL_OBJECT:public SG_OBJECT
{
	
	SG_LONG Value;
};

//��������˶��Ӽ�¼�ṹ

struct SG_CORE_API SG_TOPNODE{
	
	SG_LONG MemNums;
	
	SG_LONG NodeNums;
	
	SG_NODEINT *pNode;
	
	SG_TOPNODE(){MemNums=0;NodeNums=0;pNode=0;}
	
	~SG_TOPNODE(){if(pNode)free(pNode);pNode=0;}
	
	inline SG_BOOL IsNull() const
	{
		if(NodeNums<1)return true;
		if(!pNode)return true;
		return false;
	}
	
	inline void Add(SG_NODEINT node)
	{
		if(node<1)return;
		if(IsNodeIn(node))return;
		SetSize(NodeNums+1);
		pNode[NodeNums] = node;
		NodeNums++;
	}
	
	inline SG_BOOL IsNodeIn(SG_NODEINT node)
	{
		SG_INT i;	
		for(i=0;i<NodeNums;i++)
			if(pNode[i]==node)break;
		return i<NodeNums;
	}
	
	inline void SetSize(SG_INT nums){
		if(nums<=MemNums)return;
		if(pNode==NULL)
			pNode = (SG_NODEINT*)malloc(sizeof(SG_NODEINT)*nums);
		else
			pNode = (SG_NODEINT*)realloc(pNode,sizeof(SG_NODEINT)*nums);
		MemNums=nums;
	}
	
	inline void operator = (const SG_TOPNODE&p)
	{
		SetSize(p.NodeNums);
		NodeNums = p.NodeNums;
		if(!p.IsNull()&&!IsNull())
			memcpy(pNode,p.pNode,sizeof(SG_NODEINT)*NodeNums);
	}
	
	SG_LONG GetAllMemLen(){
		SG_LONG len = sizeof(SG_TOPNODE);
		if(pNode)
			len += sizeof(SG_NODEINT)*MemNums;
		return len;
	}
};

//��������˶��Ӽ�ֵ�ṹ
//ע�⣺�ýṹ��λ��λ�ò��������ģ�����Ӱ��ϵͳ����
//#define SG_MASK_BREAKOPEN_VALUE		0x00000100		//�������� IsBreakOpen ��ֵ
//#define SG_MASK_POWERPOINT_VALUE	0x00000200		//
//#define SG_MASK_LINESTART_VALUE		0x00000400		//
//#define SG_MASK_LINEEND_VALUE		0x00000800		//
//#define SG_MASK_VOLTLEVEL_VALUE		0x000f0000		//�������� VoltLevel ��ֵ
//#define SG_MASK_POWERON_VALUE		0x00100000		//�������� ����״̬ ��ֵ
//#define SG_MASK_DIS_TRANS_VALUE		0x00200000		//�������� ���� ��ֵ

struct SG_CORE_API TopNodeKeyValue{
	union{
		SG_ULONG Value;
		struct{
#if defined(__sun)||defined(_AIX)
			SG_UCHAR res1;
			SG_UCHAR IsDisTrans:1;	//��ʱ�������Ƿ�����
			SG_UCHAR PowerOn:1;	//��ǰ����״̬�´���
			SG_UCHAR Volt:6;	//������ѹ�ȼ�
			SG_UCHAR res:3;
			SG_UCHAR IsKGStationBus:1;	//��ʾ�ڵ�Ϊ����վ�ڵ�ĸ��
			SG_UCHAR IsLineEnd:1;		//��ʶ�ڵ�Ϊ��·��ֹ��
			SG_UCHAR IsLineStart:1;		//��ʶ�ڵ�Ϊ��·���
			SG_UCHAR IsPowerPoint:1;	//��ʶ�ڵ�Ϊ��Դ��
			SG_UCHAR IsBreakOpen:1;

			SG_UCHAR rev3:1;
			SG_UCHAR rev2:1;
			SG_UCHAR rev1:1;
			SG_UCHAR hasLargeResistor:1;
			SG_UCHAR hasUser:1;
			SG_UCHAR hasBus:1;
			SG_UCHAR hasTrans:1;
			SG_UCHAR hasBreaker:1;
#else
			SG_UCHAR hasBreaker:1;
			SG_UCHAR hasTrans:1;
			SG_UCHAR hasBus:1;
			SG_UCHAR hasUser:1;
			SG_UCHAR hasLargeResistor:1;
			SG_UCHAR rev1:1;
			SG_UCHAR rev2:1;
			SG_UCHAR rev3:1;
			// --- 2005-05-15�������˽ڵ㿪�ϱ��
			SG_UCHAR IsBreakOpen:1;
			SG_UCHAR IsPowerPoint:1;	//��ʶ�ڵ�Ϊ��Դ��
			SG_UCHAR IsLineStart:1;		//��ʶ�ڵ�Ϊ��·���
			SG_UCHAR IsLineEnd:1;		//��ʶ�ڵ�Ϊ��·��ֹ��
			SG_UCHAR IsKGStationBus:1;	//��ʾ�ڵ�Ϊ����վ�ڵ�ĸ��
			SG_UCHAR res:3;
			//
			SG_UCHAR Volt:6;		//������ѹ�ȼ�
			SG_UCHAR PowerOn:1;		//��ǰ����״̬�´���
			SG_UCHAR IsDisTrans:1;	//��ʱ�������Ƿ�����
			SG_UCHAR res1;
#endif
		}BitVal;
	};
	TopNodeKeyValue();
	void Clear();
	/*
	 *	��ֵ���
	 */
	void operator += (TopNodeKeyValue&AddV);
	/*
	 *	�Ƿ���йؼ��豸(�����ࡢ��ѹ���ࡢĸ����)
	 *  �㷨��ȡǰ�ĸ�λ��Value&0x0f����������������迹�豸
	 */
	SG_BOOL HasKeyEquip();
	/*
	 *	��ô������ǰ����Ҫ�ļ�ֵ����ֵ
	 *  �㷨��SG_MASK_BREAKOPEN_VALUE|SG_MASK_POWERPOINT_VALUE|SG_MASK_LINESTART_VALUE|
	 *		SG_MASK_VOLTLEVEL_VALUE|SG_MASK_POWERON_VALUE|SG_MASK_DIS_TRANS_VALUE
	 */
	SG_ULONG ElecCalMaskValue();
};

//�����ȱʡ�ߴ�ṹ

struct SG_CORE_API SG_OBJ_DEFAULT_SIZE
{
	
	SG_ULONG Universe;
	
	SG_INT InContainer;
	
	SG_INT ContainerType;
	
	SG_FLOAT DefWidth;
	
	SG_FLOAT DefHeight;
	
	SG_OBJ_DEFAULT_SIZE()
	{
		memset(this,0,sizeof(SG_OBJ_DEFAULT_SIZE));
	}
	
	SG_OBJ_DEFAULT_SIZE &operator = (const SG_OBJ_DEFAULT_SIZE& equipsize)
	{
		if(this==&equipsize)
			return *this;
		Universe=equipsize.Universe;
		InContainer=equipsize.InContainer;
		ContainerType=equipsize.ContainerType;
		DefWidth=equipsize.DefWidth;
		DefHeight=equipsize.DefHeight;
		return *this;
	}
};


/***********************************************
	Part 10 ������ȱʡ��ʾ���� ����ļ������Ե���ʾ���Խṹ
***********************************************/
//����FeatureΪ�����ʾ���Խṹ

struct SG_CORE_API SG_POINT_ATTRIB
{
	
	SG_USHORT	sym;		
	
	SG_USHORT	size;		//0-65535
	
	SG_SHORT	angle;		//0-511,Բ��360��ʾ��
};

//����FeatureΪ�ߵ���ʾ���Խṹ
///* Pen Styles */
//#define PS_SOLID            0
//#define PS_DASH             1       /* -------  */
//#define PS_DOT              2       /* .......  */
//#define PS_DASHDOT          3       /* _._._._  */
//#define PS_DASHDOTDOT       4       /* _.._.._  */
//#define PS_NULL             5

struct SG_CORE_API LINE_COLOR_STYLE
{
	
	SG_ULONG style:4;		/*0-8*/
	
	SG_ULONG color:(32-4);
	
	void SetValue(SG_ULONG StorageValue)
	{
		memcpy(this,&StorageValue,sizeof(SG_ULONG));
	}
	
	SG_ULONG GetValue()
	{
		SG_ULONG StorageValue;
		memcpy(&StorageValue,this,sizeof(SG_ULONG));
		return StorageValue;
	}
};
//���Ͷ�������������

struct SG_CORE_API SG_LINE_ATTRIB:LINE_COLOR_STYLE
{
	
	SG_USHORT width;		/*�߿�*/
	
	SG_USHORT sym;			//�߷���
};
//����FeatureΪ�������ʾ���Խṹ
/* Brush Styles */
// CBrushStyleCmb window
//	HS_HORIZONTAL       0       /* ----- */
//	HS_VERTICAL         1       /* ||||| */
//	HS_FDIAGONAL        2       /* \\\\\ */
//	HS_BDIAGONAL        3       /* ///// */
//	HS_CROSS            4       /* +++++ */
//	HS_DIAGCROSS        5       /* xxxxx */
//	HS_SOLID			BS_SOLID+6		(6)
//	HS_NULL				BS_NULL+6		(7)
//	HS_BITMAP			BS_PATTERN+6	(9)

struct SG_CORE_API SG_REGION_ATTRIB:SG_LINE_ATTRIB
{
	
	SG_ULONG brStyle:4;			//brStyle==HS_BITMAPʱ��brColor�д洢���ǡ�λͼ���š����ڴ�����
	
	SG_ULONG brColor:(32-4);
	
	void SetRegionValue(SG_ULONG value)
	{
		brStyle=value&0x0f;
		brColor=value>>4;
	}
	
	SG_ULONG GetRegionValue()
	{
		SG_ULONG value;
		value = brColor*0x10;
		value += brStyle;
		return value;
	}
};
//����FeatureΪ���ֵ���ʾ���Խṹ
//struct SG_CORE_API SG_TEXT_ATTRIB
//{
//	SG_CHAR		fontname[SG_MAX_FONTNAME_LEN];
//	SG_USHORT	size;
//	SG_USHORT	angle;
//	SG_ULONG	color;
//	SG_ULONG	bkmode:2;
//	SG_ULONG	bkcolor:30;
//	SG_BOOL IsValid(){
//		return size>0 && fontname[0]!='\0' && bkmode>0 && bkmode<3;
//	}
//};


class CSgString;


//������ʾ���Խṹ�������Ͻṹ

struct SG_CORE_API ObjectDisplayAttribStruct
{
	
	SG_LINE_ATTRIB LineAttrib;
	
	SG_REGION_ATTRIB RegionAttrib;
	
	SG_POINT_ATTRIB PointAttrib;
	
	SG_TEXT_ATTRIB TextAttrib;
	
	ObjectDisplayAttribStruct(){memset(this,0,sizeof(ObjectDisplayAttribStruct));}
};


/***********************************************
	Part 12 ϵͳ�ض��ֶ��ڵ�ǰ���е��ֶ�ƫ�����ṹ
***********************************************/




typedef ObjType_IA_Cfg_Struct Sg_ObjType_InsideAttrib_Struct;

/***********************************************
		Part 15 ��ȡ�����кţ�ͨ����������type�ͻ�������id���ýṹ
***********************************************/

struct SG_CORE_API GetBaseObjRowStruct_Attrib
{
	
	SG_LONG BaseObjID;
	
	SG_LONG StartRow;
	
	SG_SHORT BaseObjType;
	
	SG_BOOL SafeCheck;
	
	GetBaseObjRowStruct_Attrib(){
		BaseObjID				=-1;
		StartRow				=-1;
		BaseObjType				=-1;
		SafeCheck				=true;
	}
};


struct SG_CORE_API GetBaseObjRowStruct_Layer:public GetBaseObjRowStruct_Attrib
{
	
	SG_SHORT GisIDFieldPos;
	
	SG_SHORT BaseObjTypeFieldPos;
	
	SG_SHORT BaseObjIDFieldPos;
	
	GetBaseObjRowStruct_Layer(){
		GisIDFieldPos			=-1;
		BaseObjTypeFieldPos		=-1;
		BaseObjIDFieldPos		=-1;
	}
};

/***********************************************
	Part 20 ʵʱ������ṹ
	 --- ң�����Ͷ���
	 --- ������Ͷ���
	 --- ң�����Ͷ���
***********************************************/

enum SCADA_COLLECTION_TYPE_DEF{
	// --- ң�ⶨ�忪ʼ
	SG_YC_VOLTAGE				=1,	//��ѹ
	SG_YC_VOLTAGE_AB			=2,	//AB�ߵ�ѹ
	SG_YC_VOLTAGE_BC			=3,	//BC�ߵ�ѹ
	SG_YC_VOLTAGE_CA			=4,	//CA�ߵ�ѹ
	//
	SG_YC_VOLTAGE_A				=7,	//A���ѹ
	SG_YC_VOLTAGE_B				=8,	//B���ѹ
	SG_YC_VOLTAGE_C				=9,	//C���ѹ
	SG_YC_VOLTAGE_0				=10,//0���ѹ
	//
	SG_YC_I						=11,//����
	SG_YC_I_A					=12,//A�����
	SG_YC_I_B					=13,//B�����
	SG_YC_I_C					=14,//C�����
	SG_YC_I_0					=15,//0�����
	//
	SG_YC_COS					=16,//��������
	SG_YC_COS_A					=17,//A�๦������
	SG_YC_COS_B					=18,//B�๦������
	SG_YC_COS_C					=19,//C�๦������
	//
	SG_YC_P						=21,//�й�����
	SG_YC_P_A					=22,//A���й�����
	SG_YC_P_B					=23,//B���й�����
	SG_YC_P_C					=24,//C���й�����
	SG_YC_P_0					=25,//0���й�����
	//
	SG_YC_Q						=26,//�޹�����
	SG_YC_Q_A					=27,//A���޹�����
	SG_YC_Q_B					=28,//B���޹�����
	SG_YC_Q_C					=29,//C���޹�����
	SG_YC_Q_0					=30,//0���޹�����
	//
	SG_YC_PHASE_ANGLE			=31,//���
	SG_YC_TEMPERATURE			=32,//�¶�

	SG_YC_3PHASE_UNBLANCE       =37,//���಻ƽ����

	//  ---- ң�Ŷ��忪ʼ
	SG_YX_OBJ_STATUS			=81,//�豸�ֶ�״̬
	SG_YX_COMM_STATUS			=82,//�豸ͨ��״̬
	SG_YX_OBJ_RUN_SATTUS			=83,//�豸����״̬
	SG_YX_PROTECT				=85,	//�����ź�

	//  ---- ң��-�ź������忪ʼ
	//ң���ź����������ʹ� 100  ��  200
	SG_YX_SIGNAL_BENGIN			=100,//�ź����������Ͷ��忪ʼ
	//����б�Ҫ���������֮��������Ӷ�������ң���źŵĶ���
	//SG_YX_SIGNAL_MYTYOE		=10?,
	SG_YX_SIGNAL_END			=200,//�ź����������Ͷ������
	
	
	//  ---- ��ȶ��忪ʼ
	SG_YC_KWH_P					=201,//�й����
	SG_YC_KWH_Q					=202,//�޹����
	SG_YC_KWH_P_FORWARD			=203,//�����й����
	SG_YC_KWH_P_BACKWARD		=204,//�����й����
	SG_YC_KWH_Q_FORWARD			=205,//�����޹����
	SG_YC_KWH_Q_BACKWARD		=206//�����޹����
};



/***********************************************
	Part 20 ����ʵ�������Խṹ
***********************************************/

//��һң��ṹ --- ң�����ʵʱ����

struct OneYaoCeInfo
{
	
	YaoCeAttribStruct Attrib;	//ң�������
	
	SG_SHORT Type;				//ң�������
	
	SG_FLOAT value;				//ң��ֵ
	
	SG_FLOAT ConvFact;			//ת��ϵ��
};

//ң��ṹ --- ң�����ʵʱ����

struct YaoCeInfo
{
	//ң�������
	
	SG_INT Nums;
	//ң�������
	
	OneYaoCeInfo *pYaoCe;
	//����
	
	YaoCeInfo(){
		Nums=0;pYaoCe=NULL;
	}
	//����
	
	~YaoCeInfo(){
		Nums=0;if(pYaoCe)free(pYaoCe);pYaoCe=NULL;
	}
	//����ң��
	
	void Add(OneYaoCeInfo*p)
	{
		if(Nums==0 || pYaoCe==NULL)
		{
			Nums = 0;
			pYaoCe = (OneYaoCeInfo *)malloc(sizeof(OneYaoCeInfo));
		}
		else
			pYaoCe = (OneYaoCeInfo *)realloc(pYaoCe,sizeof(OneYaoCeInfo)*(Nums+1));
		pYaoCe[Nums] = *p;
		Nums++;
	}
	//�����ͺż���һ��ң��
	
	OneYaoCeInfo *GetYaoCe(SG_SHORT type)
	{
		for(SG_INT i=0;i<Nums;i++)
			if(pYaoCe[i].Type == type)return &pYaoCe[i];
		return NULL;
	}
};
/***********************************************
	Part 30 �������Ա�����Ϣ�ṹ
***********************************************/
//�������Ա�����Ϣ�ṹ
/*
struct FieldInfoStruct{
	SG_FIELDNAME FieldName;
	SG_SHORT FieldType;
	SG_SHORT FieldLen;
	SG_SHORT SqlType;			// for oracle
	SG_USHORT ConPtr;			//�ֶ�������һ����¼�е���ֹ���λ��
	SG_UCHAR CanBeNull:1;
	SG_UCHAR Primary:1;
	SG_UCHAR UpdateFlag:1;		//����sql���ʱ�Ƿ���Ա�update
	SG_UCHAR ExtAttribFlag:1;	//����չ����Դ�е����Ա�ʾ--ֻ����LocalLib���ر�ע��Ϣ��
	SG_UCHAR CommonFlag:1;		//��������
	SG_UCHAR GraphFlag:1;		//�������Ա�־�����Զ�����еļ�����ֻ����ͨ�����νṹ��صķ�����ֵ
	SG_UCHAR SgGisOID:1;		//Ψһ����LocalLib��һ����¼���ֶ�
	SG_UCHAR ArcGisOID:1;		//ֻ���ֶα��
	SG_UCHAR ChangeFlag:1;		//��ֵ�Ƿ��޸�---StartEditTable��Ĳ�����
	//��������Ϣ�Ƿ�һ��
	SG_BOOL Equal(FieldInfoStruct *p){
		if(strcmp(FieldName,p->FieldName))return false;
		if(FieldType!=p->FieldType)return false;
		if(FieldLen!=p->FieldLen)return false;
		if(ConPtr!=p->ConPtr)return false;
		return true;
	}
	FieldInfoStruct(){memset(this,0,sizeof(FieldInfoStruct));UpdateFlag=true;}
};
*/
/***********************************************
	Part 40 ���������ϰ������Խṹ
	ϵͳ�����˼��㷽ʽ���Է�Ϊ�ض������ಢ��ţ�
	ÿ�ּ��㷽ʽ�¶����Ƿ�������ͨ����Ӧ�ı��λ��¼
***********************************************/
//

struct SG_CORE_API ObjectBarrierPointStruct{
	
	SG_UCHAR	CalStyle1:1;	//����͵�������ʱ��Ϊ��ֹ�豸
	
	SG_UCHAR	CalStyle2:1;
	
	SG_UCHAR	CalStyle3:1;
	
	SG_UCHAR	CalStyle4:1;
	
	SG_UCHAR	CalStyle5:1;
	
	SG_UCHAR	CalStyle6:1;
	
	SG_UCHAR	CalStyle7:1;
	
	SG_UCHAR	CalStyle8:1;
	
	SG_UCHAR	CalStyle9:1;
	
	SG_UCHAR	CalStyle10:1;
	
	SG_UCHAR	CalStyle11:1;
	
	SG_UCHAR	CalStyle12:1;
	
	SG_UCHAR	CalStyle13:1;
	
	SG_UCHAR	CalStyle14:1;
	
	SG_UCHAR	CalStyle15:1;
	
	SG_UCHAR	CalStyle16:1;
	
	ObjectBarrierPointStruct(SG_USHORT value=0){
		SetValue(value);
	}
	
	void SetValue(SG_USHORT value){
		SG_USHORT *p = (SG_USHORT*)this;
		*p = value;
	}
	
	SG_USHORT GetValue(){
		SG_USHORT *p = (SG_USHORT*)this;
		return *p;
	}
};



/*******************************************************
	Part 50	ƽ�漸��������ؽṹ
*******************************************************/

struct GeoMetrySelPara{
	
	SG_BOOL	PointFirst:1;		//�Ƿ�����Ȼ��������ȣ��Ե�ѡ��Ч
	
	SG_BOOL WholeContain:1;		//�Ƿ���ȫ�������Էǵ�ѡ��Ч
	
	SG_BOOL SearchAll:1;		//�Ƿ��������еĶ���
	
	SG_BOOL UseTolerance:1;		//��ѡ��Ч
	
	SG_BOOL AdvanceObjFirst:1;	//���Ӷ������� ������ usefulfunc.h �� IsAdvancetObj
	
	SG_BOOL SelectWhileVisible:1;//ͼ����ƿɼ�ʱ�ſ�ѡ��
								//ͼ����ƶ��󲻿�ѡʱ�϶�������ѡ��
	
	SG_BOOL OnlySelectBeDrawObj:1;	//����ѡ�� Draw��Ķ���

	SG_BOOL OnlySelectDispObj:1;	//������ʾ�ɼ��豸
	
	GeoMetrySelPara(){
		PointFirst	=	true;
		WholeContain = false;
		SearchAll = false;
		UseTolerance = true;
		AdvanceObjFirst = true;
		SelectWhileVisible = false;
		OnlySelectBeDrawObj	= false;
		OnlySelectDispObj	= false;
	}
};


///* ���Ͷ���ļ������Թ�����----������������� */
//class  CSgPoint
//{
//public:
//	CSgPoint();
//	~CSgPoint();
//	CSgPoint(const CSgPoint&xPoint);
//public:
//	/* ������� */
//	SG_INT pointnums;
//	/* ���е���ɶ��ĵ��������� */
//	SgPoint *pPoint;	
//	//�������Կ����ж�
//	SG_BOOL IsNull(){
//		if(pointnums<1)return true;
//		if(!pPoint)return true;
//		return false;
//	}
//	// --- ���е�λƫ��һ������
//	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset){
//		for(SG_INT i=0;i<pointnums;i++)
//			pPoint[i].Offset(xOffset,yOffset);
//	}
//public:
//	//���õ�����
//	virtual void SetPointNums(SG_UINT PointNums);
//	CSgPoint& operator = (const CSgPoint &p);
//	SG_BOOL operator == (const CSgPoint &p);
//	//�����ɶ���ĵ㵽һ�����С����͵�λ��
//	SG_DOUBLE GetMinLen(SgPoint *pInPoint,SG_INT *pPointPos=NULL);
//	//����ͬ��������
//	SG_INT GetStructLen();			//��õ��ͽṹ��ռ���ڴ��С
////	void CreateMem(void *pCon);	//���������ڴ�	�����ⴴ���ڴ�
////	void Build(void *pCon);		//�������紫������LocalLib�ع��ṹ
//	SG_BOOL Serialize(CSgArchive&ar);
//};

//���Ͷ���ļ������Թ�����
//�洢�ṹ (N��Part M����)��PartNums����Part0��...��PartN-1����Point0��...��PointM��1��
//class  CSgLine
//{
//public:	
//	CSgLine();
//	~CSgLine();
//	CSgLine(const CSgLine&);
//	
//public:
//	//�����ɼ������
//	SG_INT GetPartNums();
//	//ÿ�ε���ֹ�� �� Base 0
//	SG_INT *GetPartBound();
//	//�������Կ����ж�
//	SG_BOOL IsNull();
//	//����ܵ���
//	SG_INT GetPointNums();
//	//�����ʼ��
//	SgPoint *GetFirstPoint();
//	//�����ʼ��
//	SgPoint *GetSecondPoint();
//	//�����ֹ��
//	SgPoint *GetLastPoint();
//	//��õ����ڶ���
//	SgPoint *GetLastPoint1();
//	// --- ���е�λƫ��һ������
//	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset);
//	// --- У����λ,ʹ��λ��SDE���ύʱ�Ϸ�????? --- ��С��λΪ0.35um
//	void Correct();
//
//public:
//	// �ж϶��Ƿ�ֱ��
//	inline SG_BOOL SegmentIsLine(SG_SHORT i,SG_CHAR* desc,SG_SHORT descLength)
//	{
//		if(!desc || i>=descLength) return true;
//		SG_UCHAR seg_type = (SG_UCHAR)(desc[i]);
//		seg_type &= 0x0f;   // ����λ --- ����
//		switch(seg_type) 
//		{
//		case SG_FE_Arc:
//		case SG_FE_BezeirLine:
//		case SG_FE_Curve:
//			return false;
//			break;
//		}
//		return true;
//	}
//	SG_BOOL AddSegment(SG_SHORT&/*�ڼ���*/,SG_SHORT /*�����ߵڼ����㿪ʼ*/,SG_SHORT* /*ָ��,�ڼ��������*/);
//	SG_BOOL AddPoint(SgPoint pt,SG_SHORT /*�����ߵڼ���������*/);
//	SG_BOOL RemovePoint(SG_SHORT /*�����ߵڼ���������*/);
//	SG_BOOL SplitLine(SG_SHORT idx/*�����ߵڼ�����ֶ�*/,CSgLine&newline);
//	SG_BOOL SplitLine(SG_SHORT idx/*�����ߵڼ������ֶ�*/,SgPoint pt,CSgLine&newline);
//	SG_BOOL JoinSegment(SG_SHORT idx/*idx����ǰ�κϲ�*/);
//	SG_SHORT nth(SG_SHORT pt_idx/*idx�ǵڼ����ϵĵ�*/);
//	// --- ���Ӷ�
//	void AddPart(CSgLine &AddLine);
//	//���õ�����----����һ���ε��߶���
//	void SetPointNums(SG_INT PointNums);
//	//���õ�����----�����ε��߶���
//	void SetPointNums(SG_INT PartNums,SG_INT PointNums);
//	//���õ�����----�����ε��߶���
//	void SetPointNums(SG_INT PartNums,SG_INT*pPartBound,SgPoint*pPoint);
//	/* ����=�� */
//	CSgLine& operator = (const CSgLine &p);
//	/* ����==�� */
//	SG_BOOL operator == (const CSgLine &p);
//	/* ����!=�� */
//	SG_BOOL operator != (const CSgLine &p);
//	//�����ߵĳ���
//	SG_DOUBLE GetLength();
//	//����С�������
//	SG_BOOL LessThan(SG_FLOAT len);
//	//�����ߵ��߶����ж� --- posΪ���ϵ��߶�λ��
//	SG_BOOL IsPointOn(SgPoint*pInPoint,SG_SHORT pos=0);
//	//�����߶��ϵ�λ��
//	SG_INT PointOnLinePos(SgPoint*pInPoint);
//	//�Ǹ��ӱ��ϵĵ�
//	SG_BOOL IsOnEdgeObj(CSgPoint*pInPoint,SG_INT &PointPos);
//	//�Ǹ��ӱ��ϵ���
//	SG_BOOL IsOnEdgeObj(CSgLine*pInLine,SG_INT &PointPos);
//	//�����ɶ���ĵ㵽һ�����С����͵�λ��
//	SG_DOUBLE GetMinLen(SgPoint *pInPoint,SG_INT *pPointPos=NULL);
//	//��ת����
//	void ReversePoint();
////	void CreateMem(void *pCon);	//���������ڴ�	�����ⴴ���ڴ�
////	void Build(void *pCon);		//�������紫������LocalLib�ع��ṹ
//	SG_BOOL Serialize(CSgArchive&ar);
//
//public:
//	// --- ǿ���ƻ��ڴ�ָ��
//	void	SetMemPtrNull(){m_pMem=NULL;}
//	// --- ����������׵�ַ
//	SG_INT	*GetMemPtr(){return m_pMem;}
//	//������ͽṹ��ռ���ڴ��С
//	SG_INT GetStructLen();			//������ͽṹ��ռ���ڴ��С
//	// --- ��ýṹָ�벿�ַ�����ڴ泤��
//	SG_INT GetMemLen();
//private:
//	// --- �ڴ���׵�ַ
//	SG_INT *m_pMem;
//};



/*��CSgPoint�Ĳ�������
	1:��ռ���ڴ�ϴ�,����������Ҫ��̬�ı�������ʱ��Ч�ʽϸ�
	2:�������õ�����ʱ,����ʧԭ�ȵ�����
*/

class SG_CORE_API CSgSupperPoint
{
public:
	
	CSgSupperPoint(SG_INT step=3);
	
	~CSgSupperPoint();
public:
	
	SG_INT pointnums;
	
	SgPoint *pPoint;
protected:
	
	CSgSupperPoint(const CSgSupperPoint&);
	/* �����ڴ�ĳ���(����) */
	
	SG_INT MemLen;
	/* �����ڴ�Ĳ���(����) */
	
	SG_INT Step;
	//	
public:
	
	SG_BOOL IsNull(){
		if(pointnums<1)return true;
		if(!pPoint)return true;
		return false;
	}
public:
	//��õ�����
	
	SG_INT GetPointNums(){return pointnums;}
	//���õ�����
	
	void SetPointNums(SG_UINT PointNums);
	//�������ɵ��ߵĳ���
	
	SG_DOUBLE GetLength();
	//�Ⱦഴ��һ���
	
	void CreateSameLengthPoint(CSgPoint *InP,SG_DOUBLE *pLen);
	//
	
	CSgSupperPoint& operator = (const CSgSupperPoint &p);
};

/*******************************************************
	Part 60	ϵͳö�����Ͷ���
*******************************************************/

enum SG_ObjDispType{
	SG_OBJ_DISP_NORMAL	=	0,			//����
	SG_OBJ_DISP_POWEROFF,				//ʧ��
	SG_OBJ_DISP_NORMAL_SEL,				//������ѡ��
	SG_OBJ_DISP_POWEROFF_SEL,			//ʧ�类ѡ��
};

enum SG_TopControlType{
	TOP_CONTROL_TYPE_USEITONLAY		=0,	//�����ö������
	TOP_CONTROL_TYPE_ERROR_RETURN	=1,	//�ö���Ϊ�������ϵĶ���
	TOP_CONTROL_TYPE_STOP			=2,	//�ö���ֹͣ�������
	TOP_CONTROL_TYPE_OBJ			=3,	//�ö���ΪĿ�����
};

//	�ڿ����Եı�־λö��
enum SG_NetControlFlag
{
	NCF_TOP_USE				= 0x00000001,
	NCF_TOP_MAIN			= 0x00000002,
	NCF_TOP_STOP			= 0x00000004,
	NCF_TOP_ERR_DIR			= 0x00000008,

	NCF_SEARCH				= 0x00000010,
	NCF_TARGET				= 0x00000020,
	NCF_CHANGE				= 0x00000040,
	NCF_OVERLOAD			= 0x00000080,
};

//���ض��������������
enum SG_ObjOperErrorType
{
	SG_OBJ_OPER_ERROR_NOOBJ			=0,		//����δ�ҵ�
	SG_OBJ_OPER_ERROR_STATUSERROR	=1,		//���������
	SG_OBJ_OPER_ERROR_SAME			=2,		//��ǰ״̬��������״̬һ��,û�б�Ҫ����
	SG_OBJ_OPER_ERROR_MANSET		=3,		//��������,��ֹң��
	SG_OBJ_OPER_ERROR_SIGN			=4,		//����ҽ�ֹң��������
	SG_OBJ_OPER_ERROR_HASLOAD		=5,		//����������ɷֺ�
	SG_OBJ_OPER_ERROR_PUTGROUND		=6,		//ͣ�����������豸�ӵ�
	SG_OBJ_OPER_ERROR_HUAWANG		=7,		//�������»�������
	SG_OBJ_OPER_ERROR_SQUENCEOPER	=8,		//բ������˳������	
	SG_OBJ_OPER_ERROR_FORBIDOPER	=9,		//�豸���ɲ���
	SG_OBJ_OPER_ERROR_REVERSEPOWER  =10,    //��ѹ��������
	SG_OBJ_OPER_ERROR_RP_OPER       =11,     //��ѹ��������(���ؿɴ����ɲ���)
    SG_OBJ_OPER_ERROR_BIAODIAN      =12,     //����
	SG_OBJ_OPER_ERROR_NO_POWERNO	=13,     //�в���ͨ�����
	SG_OBJ_OPER_ERROR_NO_POWEROFF	=14,     //�в���ʧ�����
};

#define	OPERTYPE_YK			0
#define	OPERTYPE_MANSET		1

static const char *SG_ObjOperErrorInfo[] =
{
	"����δ�ڵ����������ҵ�",
	"�����״̬����",
	"��ǰ״̬��������״̬һ��",
	"��������,��ֹң��",
	"����ҽ�ֹң��������",
	"����������ɷֺ�",
	"ͣ�����������豸�ӵ�",
	"�������»�������",
	"բ������˳������",
	"���󲻿ɲ���",
	"��ѹ��������","",
    "ͣ���������б����豸"
};

//���Ƚӿ��㷨���
enum SG_MMI_TOKEN_FUNC_TYPE
{
    SG_MMI_TOKEN_FUNC_MANTOKEN		=1,			//������
    SG_MMI_TOKEN_FUNC_GROUNDTOKEN	=2,			//�ӵ���
    SG_MMI_TOKEN_FUNC_JIANXIU		=3,			//������
    SG_MMI_TOKEN_FUNC_NOTYK			=4,			//��ֹң��
    SG_MMI_TOKEN_FUNC_KAIDUAN		=5,			//����
    SG_MMI_TOKEN_FUNC_BAOANSUO		=6,			//��������
    SG_MMI_TOKEN_FUNC_BUGTOKEN		=7,			//ȱ����
    SG_MMI_TOKEN_FUNC_BUKEBING		=8,			//���ɲ���
    SG_MMI_TOKEN_FUNC_ZHONGYAOYONGHU=9,			//��Ҫ�û���
    SG_MMI_TOKEN_FUNC_LINSHIBAODIAN	=10,		//��ʱ����� 
    SG_MMI_TOKEN_FUNC_WEIXIANFU		=11,		//β�߷�
    SG_MMI_TOKEN_FUNC_ZIQIEFU		=12,		//���з� 
    SG_MMI_TOKEN_FUNC_DANQIEFU		=13,		//���з� 
    SG_MMI_TOKEN_FUNC_TINGYONGFU	=14,		//ͣ�÷� 
    SG_MMI_TOKEN_FUNC_SHOUDONGFU	=15,		//�ֶ��� 
    SG_MMI_TOKEN_FUNC_XINHAOFU		=16,		//�źŷ�  
    SG_MMI_TOKEN_FUNC_BAODIANFU		=17,		//�����
    SG_MMI_TOKEN_FUNC_YK			=18,		//��ң�ط�
    SG_MMI_TOKEN_FUNC_LINSHIFU		=19,		//��ʱ��
    SG_MMI_TOKEN_FUNC_FANGLEIFU		=20,		//���׷�
    SG_MMI_TOKEN_FUNC_KKD           =21         //���ڵ���(�ж����)
};
// GIS ��Ӧ�����Ͷ���
enum SG_TableAppType{
	SG_T_APPTYPE_SYS=0,		//ϵͳ�ṹ����
	SG_T_APPTYPE_GIS=1,		//ϵͳ̨������
	SG_T_APPTYPE_MNG=2,		//ϵͳ��������
	SG_T_APPTYPE_OPT=3		//ϵͳҵ������
};

// GIS ���ɻ�ͼͼԪ���Ͷ���
/*
create table SYS_OBJECT_NO 	-- �Ƕ����
(
	"ID" 					NUMBER(4) NOT null primary key ,--��ʶ��
	"NAME"		 			VARCHAR2(40) not null,			--�ⲿ��
	"LOAD_USE_WORLD_ID" 	NUMBER(3) default 0,			--����WorldIDװ��
	"UNIVERSE_VIEW"			NUMBER(9),						--��Universe���͵Ĺ�ϵ��
	"EXT_FEATURE_TYPE"		NUMBER(4),			---�Ƕ���ͼ����չ��������
	"SPATIAL_DS_TYPE"		NUMBER(9),			--�ռ�����Դ���ͣ�0�����пռ��������ԡ�1-SDE��2-Coverage��3-Shape��4-OracleSpatial��5-SelfDefTable��6-.DXF
	"SPATIAL_DS_INFO"		VARCHAR2(48),		--�ռ�����Դ��Ϣ��
	SG_SYS_O_SPATIAL_DS_TABLE_NAME	VARCHAR2(32),		--�ռ����ݱ���
	"BRUSH_ATTRIB"          NUMBER(10),
	"PEN_ATTRIB"            NUMBER(10),
	"PEN_WIDTH"             NUMBER(4)
);
grant select on SYS_OBJECT_NO to public;
create unique index SYS_OBJECT_NO_Ind on SYS_OBJECT_NO(NAME);
*/

//�ռ�����Դ����
enum SG_SDLoadType{
	SG_SPATIALTYPE_NONE		=	0,
	SG_SPATIALTYPE_SDE		=	1,
	SG_SPATIALTYPE_COVERAGE,
	SG_SPATIALTYPE_SHAPEFILE,
	SG_SPATIALTYPE_ORACLESPATIAL,
	SG_SPATIALTYPE_SELFDEFTABLE,
	SG_SPATIALTYPE_DXF,
	SG_SPATIALTYPE_MAPINFO,
	SG_SPATIALTYPE_SPATIALWARE
};
//��������Դ����
enum SG_ADLoadType{
	SG_DBF_TYPE_NONE=0,		//	0��������չ̨������
	SG_DBF_TYPE_ORACLE,		//	1-Oracle
	SG_DBF_TYPE_SYBASE,		//	2-Sybase
	SG_DBF_TYPE_SQLSERVER,	//	3-SqlServer
	SG_DBF_TYPE_DB2,		//	4-DB2
	SG_DBF_TYPE_SELFDS		//	5-Self Data Server������Ϊֻ����
};


// --- ����ģ�ͱ任��ʽ
enum SG_ModelChange_TYPE
{
	SG_MODELCHANGE_NONE 		=	0,	//������
	SG_MODELCHANGE_NORMAL		=	1,	//ȱʡ����
	SG_MODELCHANGE_PASSBY		=	2,	//ֱͨ����(��բ���������������˼�)
	SG_MODELCHANGE_TRANS4Point	=	3,	//������ĵ�ģ��
	SG_MODELCHANGE_TRANS2Point	=	4	//���������ģ��
};
//�������
enum SG_ObjectKind_TYPE
{
	SG_ObjectKind_BASEOBJ	=0,	//��������
	SG_ObjectKind_YAOCEOBJ	=1,	//ң��
	SG_ObjectKind_LABELOBJ	=2,	//��ע
	SG_ObjectKind_ExtObj	=3	//��չ����
};

//��������
enum SG_UniverseType
{
	SG_UNIVERSETYPE_GIS				=0x01,		//����ȫͼ
	SG_UNIVERSETYPE_SINGLELINE		=0x02,		//����ͼ
	SG_UNIVERSETYPE_MULTILINE		=0x04,		//����ͼ
	SG_UNIVERSETYPE_SCHEMATICS		=0x08,		//��������ͼ
	SG_UNIVERSETYPE_APPOINTOBJ		=0x10,		//ѡ��ͼ(ָ���������Բ���кź��γɵ�����ͼ)
	SG_UNIVERSETYPE_ZNJXT			=0x20,		//վ�ڽ���ͼ
	SG_UNIVERSETYPE_PLANE			=0x40,		//�������ͼ(���վ�������ͼ��ƽ�沼��ͼ����������д����ͼ)
	SG_UNIVERSETYPE_PIPEROUTE		=0x80,		//����ͨ��ͼ	
	SG_UNIVERSETYPE_MIRROR			=0x100,		//�豸����ͼ(����Ʊ/����������)
	SG_UNIVERSETYPE_CORRIDOR		=0x200,		//����ͼ
	SG_UNIVERSETYPE_ANVI			=0x400,		//����ͼ
    SG_UNIVERSETYPE_1JXT			=0x800,		//վ��һ��ͼ����ӳ����λ��,������
    SG_UNIVERSETYPE_SYMBOL			=0x1000,	//���ű༭ͼ
	SG_UNIVERSETYPE_OFFLINE			=0x2000,	//����ͼ(SYS_OBJECT�ж�����Universe�Ĺ�ϵ������Ч����Ը�������ͼ�����и����ӵĴ�����̣��ο�����Ҫ���_ͼ��ʵ�û��Ľ����еġ�����ͼ��֧�֡�һ��)
	SG_UNIVERSETYPE_PRINT_LAYOUT	=0x4000,	//��ӡ����ͼ,���ڴӲ�ͬ����ͼ��ѡ�񲿷���϶��ɵ���ͼ
	SG_UNIVERSETYPE_TEMPLATE		=0x8000,	//�༭ģ��ͼ
	SG_UNIVERSETYPE_LV_MULTILINES	=0X10000,	//��ѹ̨��ͼ
	SG_UNIVERSETYPE_STATION_RANGE	=0X20000,	//��վ�ֲ�ͼ
	SG_UNIVERSETYPE_GXMAP			=0X40000,	//�û����뷽��ͼ
	SG_UNIVERSETYPE_SUPPLYPOINT		=0X80000,	//�ӵ���ڲ�ͼ
	SG_UNIVERSETYPE_MEASURESPACE	=0X100000,	//�������ڲ�ͼ	
	SG_UNIVERSETYPE_GEO_LAYOUT		=0X200000,	//�滮��������ͼ
	SG_UNIVERSETYPE_PROTECTOR		=0X400000,	//��������ͼ
	SG_UNIVERSETYPE_THEME			=0x800000,	//ר��ͼ	

	SG_UNIVERSETYPE_PIPE_SECTION	=0x1000000,	//�ܵ�����ͼ
	SG_UNIVERSETYPE_GIS_BAY			=0x2000000,	//�滮�������ͼ
	SG_UNIVERSETYPE_SPECIAL			=0x3000000,	//����ͼ
	SG_UNIVERSETYPE_CUSTOM3			=0x4000000,	//δ��
	SG_UNIVERSETYPE_POLLUTE			=15,		//��ʱ����
	SG_UNIVERSETYPE_GUARDLINE		=25,		//��ʱ����
	SG_UNIVERSETYPE_LOOPED_NETWORT  =26,		//������û���ͼ	
	SG_UNIVERSETYPE_LV_MONITOR		=27,		//��ѹ�������ͼ
	SG_UNIVERSETYPE_LAYOUT_STA				=261,		//�Զ����ֵ�վ����ͼ
	SG_UNIVERSETYPE_LAYOUT_RANGE			=262,		//�Զ����ֹ��緶Χͼ
	SG_UNIVERSETYPE_LAYOUT_SCHEMATIC		=263,		//�Զ����ֵ�ϵͼ
	SG_UNIVERSETYPE_LAYOUT_SCHEMATIC_LINE	=264,		//�Զ����ֲ��ֵ�ϵ����ͼ
        SG_UNIVERSETYPE_LAYOUT_BREAKER_STA		=265,		//����վͼ
        SG_UNIVERSETYPE_REALTIME               =266,//ʵʱ����
        SG_UNIVERSETYPE_LAYOUT_SCHEMATIC_DETAIL_LINE	=267,//������ͼ
        SG_UNIVERSETYPE_LAYOUT_QWXTT			=268,		//ȫ��ר��ͼ
        SG_UNIVERSETYPE_LAYOUT_QWFT				=269,		//ȫ����ͼ
        SG_UNIVERSETYPE_LAYOUT_ROUTE			=270,		//��·ͼ
        SG_UNIVERSETYPE_MAN_HOLE_SECTION        =520,		//���¾�����ͼ
};

//��������
enum SG_NetWorkType{
	SG_NETWORKTYPE_NONE=1,			//��
	SG_NETWORKTYPE_GEO=2,			//��������
	SG_NETWORKTYPE_ELECTRIC=3,		//��������
	SG_NETWORKTYPE_STREET=4,		//·������
	SG_NETWORKTYPE_PIPELINE=5,		//��������
	SG_NETWORKTYPE_COMMULINE=6,		//ͨ������
	SG_NETWORKTYPE_WORK	= 7,		//��ҵ����
	SG_NETWORKTYPE_CARRIER = 8,		//�ز�����
	SG_NETWORKTYPE_TLINE = 9,		//��������
	SG_NETWORKTYPE_TNOLINE = 10,	//��������
	SG_NETWORKTYPE_LAYOUT = 11,		//�Զ����ֵ�ϵͼ����
	SG_NETWORKTYPE_WATER = 12,		//ˮ��
	SG_NETWORKTYPE_GAS = 13,		//����
	SG_NETWORKTYPE_HEATING = 14		//����
};

//World������ʾ����
enum SG_ActiveCenterType
{
	SG_ACTIVECENTERTYPE_NOCHANGE=0,			//���ı���Ұ��Χ
	SG_ACTIVECENTERTYPE_SETWIDTH=1,			//���趨����Ұ�ı���Ұ��Χ
	SG_ACTIVECENTERTYPE_AUTODEAL=2,			//��ǰ��������Ӧ����;
	SG_ACTIVECENTERTYPE_CONTAINER=3,		//������û�м������Ե����������,�����豸���ݹ飩���Ͼ��ж�λ��
};

//��ϵ����
enum SG_PowerType
{
	SG_POWERTYPE_NORMAL=0,				//ͨ������
	SG_POWERTYPE_POWERPOINT=1,			//����Ϊ��Դ��
	SG_POWERTYPE_GROUNDPOINT=2,			//��Ϊ�ӵص�
	SG_POWERTYPE_SUBPOWER=3,			//������Դ��
	SG_POWERTYPE_LINE_START=4,			//��Ϊ��·���
	SG_POWERTYPE_LINE_END=5,			//��Ϊ��·�յ�
	SG_POWERTYPE_CKKG=6,				//��Ϊ���ڿ���
	SG_POWERTYPE_LLKG=7,				//��Ϊ���翪��
	SG_POWERTYPE_CKLLKG=8				//������Ϊ���ڿ��أ��ֿ���Ϊ���翪��
};

enum SG_Ground_Attrib
{
	SG_GROUND_ATRRIB_COMMON		=0,		//������
	SG_GROUND_ATRRIB_TRANS		=1,		//��ѹ�����Ե�ӵ�
};

//��������
enum SG_ElectricType{
	SG_ELECTRICTYPE_NORMAL=0,			//һ���豸
	SG_ELECTRICTYPE_LINE=1,				//����
	SG_ELECTRICTYPE_BREAK=2,			//����
	SG_ELECTRICTYPE_TRANS=3,			//��ѹ
	SG_ELECTRICTYPE_BUS=4,				//����ϵͳĸ��
	SG_ELECTRICTYPE_SIGNAL=5,			//�ź�������
	SG_ELECTRICTYPE_LINKLINE=6,			//�����߶���
	SG_ELECTRICTYPE_LARGERESISTOR=7,	//��������
	SG_ELECTRICTYPE_DUMMY_POLE=8,		//�����
	SG_ELECTRICTYPE_CABLE=9,            //�����豸  
	SG_ELECTRICTYPE_FIBER_NODE=10,		//���½�ͷ���豸
	SG_ELECTRICTYPE_CAPACITOR=11,		//������
	SG_ELECTRICTYPE_SERI_REACTOR=12,	//�����翹��
	SG_ELECTRICTYPE_PARA_REACTOR=13,	//�����翹��
	SG_ELECTRICTYPE_MOTOR		=14		//�����

};

//��ʩ�豸����
enum SG_DeviceClass{
	SG_DEVICECLASS_ONCE			=1,		//һ���豸
	SG_DEVICECLASS_TWICE		=2,		//�̱��豸
	SG_DEVICECLASS_MONITOR		=3,		//�Զ����豸
	SG_DEVICECLASS_LINE			=4,		//��·�豸
	SG_DEVICECLASS_CABLE		=5,		//�����豸
	SG_DEVICECLASS_BUILDING		=6,		//�����豸
    SG_DEVICECLASS_PRINTWARE	=7,     //��ӡ�̼�
    SG_DEVICECLASS_1JXT			=8,     //һ��ͼ�豸
    SG_DEVICECLASS_INSPECT		=9,     //��ЧѲ���豸
	SG_DEVICECLASS_USERDEVICE	=10,    //�û��豸
    SG_DEVICECLASS_ASSISDEVICE	=11,	//�����豸���磺����˩���յ���GAP���������䡿
	SG_DEVICECLASS_DESIGN		=16,	//������豸
	SG_DEVICECLASS_GUARDLINE	=17,	//��������豸
	SG_DEVICECLASS_CITYPLAN		=18,	//���й滮����
	SG_DEVICECLASS_BPA		=19,		//BPA�豸
	SG_DEVICECLASS_PRODUCT		=20,	//�����豸(����)
	SG_DEVICECLASS_DUMMYDEVICE	=99		//�����豸
};

//��ͼ����
#ifdef AUTO_MAP
enum SG_DrawRule{

	SG_DRAWRULE_NONE=1,				//��
	SG_DRAWRULE_RECT,				//�������
	SG_DRAWRULE_ROUND_RECT,			//����Բ�Ǿ���
	SG_DRAWRULE_CLICK,				//���
	SG_DRAWRULE_PLINE,				//�켣��
	SG_DRAWRULE_TWOCLICK,			//�����豸���ͼ
	SG_DRAWRULE_LINE,				//�����豸,�߶�
	SG_DRAWRULE_MULTIDEVICE,		//��ѡ�豸
	SG_DRAWRULE_POLYGON,			//�����
	SG_DRAWRULE_TEMPLATE,			//��ģ������
	SG_DRAWRULE_CIRCLE,			//Բ�켣
	SG_DRAWRULE_ELLIPSE,			//��Բ�켣
	SG_DRAWRULE_BEZIER,			//����������
	SG_DRAWRULE_ARC,				//����
	SG_DRAWRULE_PIE,				//��
	SG_DRAWRULE_ANCHOR_LINE,		//ê����
	SG_DRAWRULE_TEXT_LINE,				//������
	SG_DRAWRULE_LINE_POLE,			//���߲�¼
	SG_DRAWRULE_CUSTOM_MESSAGE,		//��Ӧһ����Ϣ
	//SG_DRAWRULE_NONE=0x00,				//��
	//SG_DRAWRULE_RECT=0x01,				//����
	//SG_DRAWRULE_CLICK=0x02,				//���
	//SG_DRAWRULE_PLINE=0x04,				//�켣��
	//SG_DRAWRULE_TWOCLICK=0x08,			//�����豸���ͼ
	//SG_DRAWRULE_LINE=0x10,				//�����豸
	//SG_DRAWRULE_MULTIDEVICE=0x20,		//��ѡ�豸
	//SG_DRAWRULE_POLYGON=0x40,			//�����
	//SG_DRAWRULE_TEMPLATE=0x80,			//��ģ������
	//SG_DRAWRULE_CIRCLE=0x200,			//Բ�켣
	//SG_DRAWRULE_ELLIPSE=0x400,			//��Բ�켣
	//SG_DRAWRULE_BEZIER=0x800,			//����������
	//SG_DRAWRULE_ARC=0x1000				//����
};
#else
//��ͼ����
enum SG_DrawRule{
	SG_DRAWRULE_NONE=0x00,				//��
	SG_DRAWRULE_RECT=0x01,				//����
	SG_DRAWRULE_CLICK=0x02,				//���
	SG_DRAWRULE_PLINE=0x04,				//�켣��
	SG_DRAWRULE_TWOCLICK=0x08,			//�����豸���ͼ
	SG_DRAWRULE_LINE=0x10,				//�����豸
	SG_DRAWRULE_MULTIDEVICE=0x20,		//��ѡ�豸
	SG_DRAWRULE_POLYGON=0x40,			//�����
	SG_DRAWRULE_TEMPLATE=0x80,			//��ģ������
	SG_DRAWRULE_CIRCLE=0x200,			//Բ�켣
	SG_DRAWRULE_ELLIPSE=0x400,			//��Բ�켣
	SG_DRAWRULE_BEZIER=0x800,			//����������
	SG_DRAWRULE_ARC=0x1000,				//����
	SG_DRAWRULE_PIE=0x2000,				//��
	SG_DRAWRULE_ANCHOR_LINE=0x4000,		//ê����
	SG_DRAWRULE_TEXT_LINE=0x8000,			//������
	SG_DRAWRULE_LINE_POLE=0x10000,			//���߲�¼
	SG_DRAWRULE_CUSTOM_MESSAGE=0x20000,		//��Ӧһ����Ϣ
	SG_DRAWRULE_ROUND_RECT=0x40000
};
#endif


//�߷�������
enum SG_LineSymbolType{
	SG_LINESYMBOLTYPE_NORMALLINE=0,				//������
	SG_LINESYMBOLTYPE_NORMALSYMBOL=1,			//��β����í��ҷ���
	SG_LINESYMBOLTYPE_STARTPOINTSYMBOL=2,		//�׶˵�ҵ����
	SG_LINESYMBOLTYPE_ENDPOINTSYMBOL=3,			//ĩ�˵�ҵ����
	SG_LINESYMBOLTYPE_LINESYMBOL=4,				//�߷���
	SG_LINESYMBOLTYPE_TWOSYMBOL=5,				//��β�߶ζ��ҷ���(P0)-(P1)�ҷ��ţ�(Pl)-(Pl-1)�ҷ���+1
	SG_LINESYMBOLTYPE_TWOSYMBOL_AND_LINE=6,		//��β�߶ζ��ҷ����һ���
	SG_LINESYMBOLTYPE_CFGSYMBOL=7				//����SYMMODE��������Ϣȷ���Ƿ���Ҫ���Ʒ���			
};

enum SG_LineSymbol_SymMode{
	SG_LINESYMBOLTYPE_SYMMODE_NONE=0,				//������
	SG_LINESYMBOLTYPE_SYMMODE_START=1,			//�׵���í��ҷ���
	SG_LINESYMBOLTYPE_SYMMODE_END=2,			//β����í��ҷ���
	SG_LINESYMBOLTYPE_SYMMODE_BOTH=3			//��β����í��ҷ���				
};

//���������
enum SG_PointSymbolType{
	SG_POINTSYMBOLTYPE_NORMAL=0,				//�����----��������ͼ�Ĳ���Obj_Scale������ʾ��С��
	SG_POINTSYMBOLTYPE_SYMBOL=4						//�����----(����ĳߴ�ͽǶ��γɵ���í��)
};

//��ѡ������󣩵ķ���
enum SG_PointSelType{
	SG_POINTSELTYPE_TOLERANCE=0,			//���ݲ��Բ������λ
	SG_POINTSELTYPE_INREGION=1,				//��λ���ڶ����ͼ��������
};


//��ѡ����������󣩵ķ���
enum SG_LineRegionSel_Type{
	SG_LINEREGIONSELTYPE_TOLERANCE=0,			//���ݲ��Բ�ཻ������
	SG_LINEREGIONSELTYPE_INREGION=1,			//��λ���ڶ����ͼ��������
};

//"��������"���е��ڿ���������
enum SG_Obj_InsideAttrib_Type{
	SG_OBJ_INSIDEATTRIB_NONE=		0x00,			//��
	SG_OBJ_INSIDEATTRIB_LABEL=		0x01,			//�豸�ɱ�ע
	SG_OBJ_INSIDEATTRIB_COMMON=		0x02,			//һ������
	SG_OBJ_INSIDEATTRIB_VALUE=		0x04,			//ֵ����
	SG_OBJ_INSIDEATTRIB_YC=			0x08,			//ң������
	SG_OBJ_INSIDEATTRIB_MANSET=		0x10,			//��������
	SG_OBJ_INSIDEATTRIB_PUTSIGN=	0x20,			//��������
	SG_OBJ_INSIDEATTRIB_DIRECTION=	0x40,			//������������
	SG_OBJ_INSIDEATTRIB_OVERLOAD=	0x80,			//��������
};


//���˼��㷽ʽ
enum SG_TopCalType{
	SG_TOPCALTYPE_NONE=0x00,					//
	SG_TOPCALTYPE_TWOPOINT1=0x01,				//һ����·������֮���豸ͳ��
	SG_TOPCALTYPE_TWOPOINT2=0x02,				//����������·����֮���豸ͳ��
	SG_TOPCALTYPE_ONEPOINT=0x04,				//һ�㿪ʼ�򸺺ɲ��ͳ��
	SG_TOPCALTYPE_MAINPATH=0x08,				//����֮����·������
};

//�����ԣ����뷽ʽ
enum SysFieldInputMode{
	INPUTMODE_NONE		=0,		//����չ����
	INPUTMODE_BOOL,				//�Ƿ�����
	//���������ַ���-DoMain
	// CTableObj��ʵ��Ϊ��չ����,���TableName=="SYS_DOMAIN_TABLE",���ݲ��ü���,��CObjModel�л��
	//							����Ҫ����m_OtherTable���Ƿ��Ѽ���,��������
	//FuncStr�ֵ�����λѡ������.
	INPUTMODE_MATHINDEX		,
	//***���ѡ����� �����һ����������ڶ���Universe�г��ֵ���������
	//	���øò���,�����ֿ�ѡ���������Ͱ�λ��Ч,���Դ�����ϵͳ�ı�һ�Զ����⵼�µı���������.
	//���������ú�,�����INPUTMODE_MATHINDEX����������
	INPUTMODE_ORMULTIVALUE	,
	//ϵͳ�����еĶ����淶�������Ч�����������,����������������ʾ����Ҫ
	//	�����뷽ʽ��,FuncStr�д洢�仯ϵ������ʾ�ĵ�λ�ַ���.��","�ֿ�
	INPUTMODE_CHANGEUNIT	,	//***��λ�仯��
	INPUTMODE_COLOR	,			//��ɫֵ
	INPUTMODE_FONT	,			//����
	INPUTMODE_RELATIONTABLE	,	//��ϵ���ձ�����
	INPUTMODE_GISOBJNAME	,	//���GIS�����������
	INPUTMODE_DATE			,	//������
	INPUTMODE_TIME			,	//ʱ����
	INPUTMODE_BOUNDCHECK	,	//�߽�������
	INPUTMODE_CALCULATE		,	//���������
	INPUTMODE_RULE			,	//���������
	INPUTMODE_COUNT			,	//�Զ��ۼ�
	INPUTMODE_MANNAME		,	//������Ա��
	INPUTMODE_DYNAMIC_DOMAIN,	//��̬domain
    INPUTMODE_TREE          ,   //�豸��ѡ����
	INPUTMODE_DEPART        ,   //������Ա��������
	INPUTMODE_FMTYPE        ,   //����ѡ����
	INPUTMODE_WORKER        ,   //��Աѡ����
	INPUTMODE_COMPANY        ,   //��λѡ��
};

enum SYS_MANDATORY
{
    MT_OTHER					=0,		//����
    MT_COMMON 			        =1,		//һ��
    MT_IMPORTANT   			    =2,		//��Ҫ
    MT_DELETE        			=3,		//��ɾ��
    MT_NECESSARY        		=4	    //����
};
//������Դ����
enum SysDataFrom{
	SysDataFrom_Man		=0,		//�ֹ�����
	SysDataFrom_CHY		=1,		//���Ժ
	SysDataFrom_3D		=2,		//��ά����
};

//���紫���ö���
enum SG_NET_DEF
{
	SG_NET_DATASET_RELOAD   =0,
	SG_NET_DATASET_INSERT	=1,
	SG_NET_DATASET_UPDATE	=2,
	SG_NET_DATASET_DELETE	=3,
	SG_NET_ATTRIB_CREATE	=4,
	SG_NET_ATTRIB_MODIFY	=5,
	SG_NET_ATTRIB_DELETE	=6,
	SG_NET_OBJ_ARRAY		=7,//�������
	SG_NET_DATASET_ORI		=8,//�޸�ǰ��ԭʼ����
	SG_NET_FDU_CHANGE		=9,//FDU���ͬ������
	SG_NET_WHOLE_CHANGE		=10, //������
};

//�����޸ı�� --- �ް汾����ʱͨ���������ֶ��������
enum SG_OBJ_EDIT_DEF
{
	SG_OBJ_EDIT_NOCHANGE	=0,
	SG_OBJ_EDIT_ADD			=1,
	SG_OBJ_EDIT_MODI		=2,
	SG_OBJ_EDIT_DELETE		=3,
};


// --- �ռ����ݼ��ط�ʽ
enum	SG_SYS_SDE_LOAD
{
	SG_SYS_SDE_LOAD_NULL	=0,		//������
	SG_SYS_SDE_LOAD_STRUCT	=1,		//ֻ���ؽṹ
	SG_SYS_SDE_LOAD_ALL		=2,		//ȫ������
	SG_SYS_SDE_LOAD_WORLDID	=3,		//����WorldID����
	SG_SYS_SDE_LOAD_RANGE	=4,		//���տռ䷶Χ
	SG_SYS_SDE_LOAD_FATHER	=5	,	//'���豸�������'
	SG_SYS_SDE_LOAD_CHILD	=6	,	//'�����������'
	SG_SYS_SDE_LOAD_COMPANY	=7	,	//'����������˾����'
	SG_SYS_SDE_LOAD_VOLTLEVEL=8	,	//���յ�ѹ�ȼ�����
	SG_SYS_SDE_LOAD_SQL		=9,		//��׼Sql��䷽ʽ���Ƽ���
	SG_SYS_SDE_LOAD_THROUGH	=10,	//ֱͨģʽ���أ�����˽���Ϊ͸��ͨ��������˲������κ�����
    SG_SYS_SDE_LOAD_RANGE_AND1=11,  //����Χ��(��������)
    SG_SYS_SDE_LOAD_OBJNODE=12,     //�������豸��NODE����(�絼�ߴ�ͷ)
	SG_SYS_SDE_LOAD_RANGE1_AND=13  //����Χ��(��Χ����)
};
// --- �������ݼ��ط�ʽ
enum	SG_SYS_FM_LOAD
{
	SG_SYS_FM_LOAD_NULL		=0	,		//'������'
	SG_SYS_FM_LOAD_FATHER	=1	,		//'���豸�������'
	SG_SYS_FM_LOAD_CHILD	=2	,		//'�����������'
	SG_SYS_FM_LOAD_COMPANY	=3	,		//'����������˾����'
	SG_SYS_FM_LOAD_IDRANGE	=4	,		//'����ID��Χ����'
};

// ��·�� SUBTYPE ����
enum SG_SYS_LINE_SUBTYPE
{
	SG_SYS_LINE_NULL		= 0 ,
	SG_SYS_LINE_OVERHEAD	= 1	,		// �ܿ���·
	SG_SYS_LINE_CABLE		= 2	,		// ������·, �����·
};

enum SG_DynamicLoadType
{
	fullLoad		=0,					//	ȫ����
	fullDynamicLoad =1,					//	ȫ��̬����
	halfDynamicLoad =2,					//  �붯̬����
	worldLoad		=3,					//  ��WORLD����
	fduLoad			=4,					//  fdu��ʽ����
	customLoad		=5					//  �Զ������
};

enum SG_DataShareMode
{
	DataModeNormal	=0,					//	��ͨ���Բ�����
	DataModeShared	=1,					//	�������Բ�����
};

/*******************************************************
	Part 90	��SCADA�ӿڽṹ����
*******************************************************/
	

struct SG_SCADA_PACK_HEAD{
	
	unsigned SG_CHAR CompanyID;
	
	unsigned SG_CHAR ScadaID;
	
	unsigned SG_CHAR DataType;
	
	unsigned SG_CHAR RecordLen;
	
	unsigned short RecordNums;
};

/*******************************************************
	Part 100 ��ͼ��Ӧ�ýṹ����
*******************************************************/
#define		SG_SYS_VOLT_LEVEL_NUMS		100		//ϵͳ��ѹ�ȼ����������������ֵ


struct SG_LAYER_ATTRIB
{
	
	SG_BOOL		visible;		//�ɼ�
	
	SG_BOOL		selectAble;		//��ѡ��
	
	SG_BOOL		editAble;		//�ɱ༭
	
	SG_BOOL		labelAble;		//��ע��ʾ
	
	SG_LAYER_ATTRIB()
	{
		visible=true;
		selectAble=true;
		editAble=false;
		labelAble=true;
	}
};

//
//��������Ե������

struct SG_LINE_ATTRIB_GET_PARA
{
	
	ObjAttribStruct_Base *pObjAttrib;	//�ڿ�����
	
	ObjType_IA_Cfg_Struct*pObjConfig;	//���ò���
	
	SG_LINE_ATTRIB*		  pLineConfig;	//�߶���ȱʡ���ò���
	
	SG_UCHAR CalStatus;					//����״̬
	
	SG_UCHAR Disp_Type;					//��ʾ��ʽ
	
	SG_SHORT Volt_Level;					//��ѹ�ȼ�

	//���� by lanbb 2015-12-14 ר��ͼ����Ĺ����Ļ���������ڿ����ԣ�ר��ͼ�Ĵ���״̬ȡ���ڹ����ĵ���ͼ
	//��Ϊ��
	ObjAttribStruct_Base *pBaseObjAttrib;	//����������ڿ�����
	SG_LINE_ATTRIB_GET_PARA()
	{
		pObjAttrib = NULL;
		pObjConfig = NULL;
		pLineConfig = NULL;
		pBaseObjAttrib = NULL;
	}
};

/*******************************************************
	Part 110 ��ͼ���ö�����Ͷ���
*******************************************************/
//���紦�ڵ�״̬
enum SG_WORLD_STATUS{
	SG_WORLD_STATUS_VIWER = 0,		//���
	SG_WORLD_STATUS_EDIT,			//�༭
    SG_WORLD_STATUS_PRINT,          //��ӡ
	//����
	SG_WORLD_STATUS_SAFE,           //��ȫ����ģʽ
	SG_WORLD_STATUS_STUDY           //ģ��̬
};
//ϵͳ��ʾ����
enum SG_WORLD_DISP_TYPE{
	SG_WORLD_DISP_TYPE_DEFAULT=0,	//ȱʡ�����豸�����趨��ͼ����ɫ��ʾ
	SG_WORLD_DISP_TYPE_REAL,		//ʵʱ���պ���̷ֵ�ԭ��̬��ɫ
	SG_WORLD_DISP_TYPE_LINE,		//����·��ɫ����ɫ��̬��ɫ
	SG_WORLD_DISP_TYPE_POWERPOINT,	//���յ�Դ��ĸ��Ƿ�Χ��̬��ɫ
	SG_WORLD_DISP_TYPE_PROMIN,		//ϵͳ�趨�ķ�ʽ������ʾ�����ض���ǵĶ���
	SG_WORLD_DISP_VOLTAGE_LEVEL,	//���յ�ѹ�ȼ���ʽ��Ŀǰֻ��ռλ
	SG_WORLD_DISP_INTERSEPT_BMP,	//��ȡλͼʱ����ʾ��ʽ�������豸Ϊ��ɫ��������Ϊ��ɫ	
};

enum SG_MAINT_STATUS
{
	SG_M_STATUS_TRUE_ADD			=1,		//ʵ�����Ӳ�������ļ�¼����
	SG_M_STATUS_TRUE_DELETE_BASEOBJ	=2,		//ʵ��ɾ��������,�Ի����ɾ��
	SG_M_STATUS_TRUE_DELETE_A_OBJ	=3,		//ʵ��ɾ��������,��A���ɾ��
	SG_M_STATUS_MODI_DELETE_BASEOBJ	=4,		//�޸ĵ��µ�ɾ��,�Ի����ɾ��
	SG_M_STATUS_MODI_ADD_BASEOBJ	=5,		//�޸ĵ��µ�����,�Ի��������
	SG_M_STATUS_MODI_DELETE_A_OBJ	=6,		//�޸ĵ��µ�ɾ��,��A���ɾ��
	SG_M_STATUS_MODI_ADD_A_OBJ		=7		//�޸ĵ��µ�����,��A�������
};

/*******************************************************
	part 130 ϵͳ�ض���ṹ
*******************************************************/
//�ƶ������Թ̶��ֶ� �� csignlayer.h �е�����

struct SG_SIGN_LAYER_STRUCT
{
	
	SG_SHORT	id;
	
	SG_SHORT	BaseObjType;
	
	SG_SHORT	BaseObjID;
	
	SG_SHORT	SignType;
	
	SG_SHORT	Offsetx;
	
	SG_SHORT	Offsety;
	
	SG_SHORT	LineColor;
};
//�����ʹ̶��ֶ� �� csignlayer.h �е�����

struct SG_SIGN_ATTRIB_STRUCT
{
	
	SG_SHORT	id;
	
	SG_SHORT	name;
	
	SG_SHORT	OperPowerOn;
	
	SG_SHORT	OperPowerOff;
	
	SG_SHORT	OperManset;
	
	SG_SHORT	RefuseYk;
	
	SG_SHORT	PutGround;
	
	SG_SHORT	BreakOpen;
	
	SG_SHORT	MmiFuncCheck;
};
//����������չ��ע�ֶ�����
enum SGF_EXTEND_POS
{
	SG_FETCH_PARENT_OBJ_FDPOS=501,   //��ȡ��������ֶ�POS
	SG_FETCH_GRANDPA_OBJ_FDPOS
};

// --- ���������ؿ��Ʋ���

struct	SG_CORE_API LoadControlPara
{
	
	SG_SHORT	ObjType;		//����(����չ����)������
	
//	SG_UCHAR	IsObj;			//�Ƿ��Ƕ���(�������չ����)
	
	SG_UCHAR	SdeLoadType;	//�������Լ�������
	SG_UCHAR    IsWorldLoad;    //WORLD�Ƿ��Ѽ���
	SG_UCHAR	IsPluginLoad;	//�Ƿ��ڲ�����Ѽ���
	
	SG_LONG		WorldID;		//��ǰ��WorldID
	
	CSgString	FieldName;		//���ص��ֶ���Ϊ�ջ���ַ���ʱȱʡѡ�������ֶ�
	
	CSgString	WhereClause;	//���ص�Where�Ӿ�
	
	SG_UCHAR	OnlyLoadTableInfo;	//�����ر�ṹ

	SG_UCHAR	IsLoadVer;
	
	LoadControlPara(){
		ObjType = 0;
//		IsObj	= true;
		SdeLoadType = SG_SYS_SDE_LOAD_ALL;
//Ϊͼ�ΰ汾���� start
		IsWorldLoad=false;
//Ϊͼ�ΰ汾���� end
		WorldID = 0;
		OnlyLoadTableInfo=0;
		IsPluginLoad=0;
		IsLoadVer = 0;
	}
	
	virtual SG_BOOL Serialize(CSgArchive&ar);
	virtual SG_BOOL Serialize2(CSgArchive&ar);
};

// --- �����շ����ݼ�ɾ����֯�ṹ
//ע�⣺���ͺͽ��ղ��Գ�  ����ʱ����ȡFlag������ʱ����Flag

struct SG_CORE_API NetSendDbfDeleteStruct{
	
	SG_INT		VersionNo;		// --- �汾��
	
	SG_INT		Flag;			// --- ɾ����־
	
	CSgString	m_TableName;	// --- ����
	
	CSgObjects	m_IDs;			// --- ����ID
	
	SG_BOOL Serialize(CSgArchive&ar);
	
	NetSendDbfDeleteStruct();
	
	SG_CHAR*GetName(){
		return m_TableName.GetSafeBuffer();
	}
};

//////////////////////////////////////////////////////////////////////////
struct SG_CORE_API RefObject
{
	SG_SHORT	ObjType;
	SG_LONG		ObjID;
	SG_SHORT	status;
	RefObject(){
		ObjType=0;
		ObjID=0;
		status=-1;
	}
	
};

struct SG_CORE_API RefObjectSet
{
	SG_UINT MemNums;
	SG_UINT ObjNums;
	RefObject *pObj;
	RefObjectSet(){MemNums=0;ObjNums=0;pObj=0;}
	~RefObjectSet(){
		if(pObj)free(pObj);
		pObj = NULL;
	}
	void SetSize(SG_UINT nums){
		if(nums<=MemNums){
			if(pObj!=NULL)return;
		}
		if(pObj==NULL)
			pObj = (RefObject*)malloc(sizeof(RefObject)*nums);
		else{
			SG_CHAR*p = (SG_CHAR*)malloc(sizeof(RefObject)*nums);
			memcpy(p,pObj,sizeof(RefObject)*MemNums);
			free(pObj);
			pObj=(RefObject*)p;
		}
		MemNums=nums;
	}
	void Add(RefObject obj){
		if(obj.ObjType<0 || obj.ObjID<0)return;
		if(ObjNums>=MemNums)
			SetSize(ObjNums+ObjNums/3+1);
		pObj[ObjNums].ObjType=obj.ObjType;
		pObj[ObjNums].ObjID=obj.ObjID;
		pObj[ObjNums].status=obj.status;
		ObjNums++;
	}
	void Add(SG_LONG OType,SG_LONG OID,SG_SHORT OStatus){
		if(OType<1||OID<0)return;
		if(ObjNums>=MemNums)
			SetSize(ObjNums+ObjNums/3+1);
		pObj[ObjNums].ObjType = OType;
		pObj[ObjNums].ObjID = OID;
		pObj[ObjNums].status = OStatus;
		ObjNums++;
	}
	//��ն���
	void ClearObj(SG_BOOL ResetFlag=true){
		ObjNums = 0;
	}
	//������ptr����Ա�����һ����Ա�����ptrλ��
	void RemoveAt(SG_UINT ptr)
	{
		if(ObjNums<1)return;
		if(ptr>=ObjNums)return;
		if(ptr<ObjNums-1)
		{
			pObj[ptr] = pObj[ObjNums-1];
		}
		ObjNums--;
	}

	int GetObjPtr(int nObjType,int nObjID)
	{
		for(int i =0; i< ObjNums; i++)
		{
			if(pObj[i].ObjType == nObjType && pObj[i].ObjID == nObjID)
				return i;
		}
		return -1;
	}

	int GetObjPtr(int nObjType,int nObjID,int nStatus)
	{
		for(int i =0; i< ObjNums; i++)
		{
			if(pObj[i].ObjType == nObjType 
				&& pObj[i].ObjID == nObjID && pObj[i].status == nStatus)
				return i;
		}
		return -1;
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{		
		SG_SHORT type;SG_LONG  id;
		SG_SHORT	status;
		SG_LONG num=0;
		if(ar.IsLoading())
		{
			ar>>num;
			if(num>0){
				SetSize(num);
				for(SG_INT i=0;i<num;i++)
				{
					ar>>type;
					ar>>id;
					ar>>status;
					pObj[i].ObjType = type;
					pObj[i].ObjID = id;
					pObj[i].status =status;
				}
				ObjNums = num;
			}
			else{
				ClearObj();
			}
		}
		else
		{
			if(ObjNums>0)
			{
				num = ObjNums;
				ar<<num;
				for(SG_INT i=0;i<ObjNums;i++)
				{
					type	=	pObj[i].ObjType;
					id		=	pObj[i].ObjID;
					status	=	pObj[i].status;
					ar<<type;
					ar<<id;
					ar<<status;
				}
			}
			else{
				ar<<num;
			}
		}
		return true;
	}
};

//ͣ����϶���ṹ����
struct S_EventObjs
{
	CSgString		EventDesc;
	SG_Date			EventDate;
	SG_INT			nRid;
	RefObjectSet	EventObjs;

	S_EventObjs()
	{
		nRid		=0;
		EventDesc	="";
		EventObjs.ClearObj();
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>nRid;		
		else
			ar<<nRid;		
		EventDesc.Serialize(ar);
		EventDate.Serialize(ar);
		EventObjs.Serialize(ar);
		return true;
	}
};

//����ڵ����ṹ����
struct S_NetNodeChange
{
	SG_SHORT		NetWorkType;	
	CSgObjects		NodeChangePair; //�ڵ������У�Ϊż�����ϡ�����Ϊԭʼֵ�����ڵ�ż��ֵΪ��ֵ��

	S_NetNodeChange()
	{
		NetWorkType		=0;
		NodeChangePair.ClearObj();
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>NetWorkType;		
		else
			ar<<NetWorkType;		
		NodeChangePair.Serialize(ar);
		return true;
	}
};

//����ڵ����ṹ����
struct S_TaskDevSync
{
	SG_SHORT		SyncType; //0--ͼ�η���ţ�����ͼ�η������SyncList�У�1--����˾ȫ��ͬ������˾����SyncList��
							  //2--���豸ͬ���������豸��SyncList�У�3--�����񣬾���������SyncList��
	CSgString		SyncList; //��ΪSyncType=2ʱ��Ϊ��������PMSID�Ķ��У���SyncType=3ʱ��Ϊ�������,���������";"�ָ�

	S_TaskDevSync()
	{
		SyncType		=0;
	}

	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())		
			ar>>SyncType;		
		else
			ar<<SyncType;
		SyncList.Serialize(ar);
		return true;
	}
};

enum   //���Ż�ͼ״̬ draw status
{
    SG_SYMBOL_DS_NORMAL				=	0x00000001,	//
	SG_SYMBOL_DS_SELECT				=	0x00000002,	//���ȼ� 3
	SG_SYMBOL_DS_MOVING				=	0x00000004,	//���ȼ� 1
	SG_SYMBOL_DS_BLACKWHITEPRT		=	0x00000008,	//���ȼ� 2
	SG_SYMBOL_DS_NORMALPRT			=	0x00000010,	//���ȼ� 2.5
	SG_SYMBOL_DS_CUSTOM				=	0x00000020,	//�û�ָ����ɫ
	SG_SYMBOL_DS_ONPOWER			=	0x00000800,	//����״̬
	SG_SYMBOL_DS_POINT				=	0x00001000	//���豸״̬
};
//
//

enum SG_ObjDispColor
{
	PEN_COLOR_VOLT_NONE = MYRGB( 255 , 255 , 255 ),	// ��ɫ���е�ѹ�ȼ��ֶΣ���ֵ��Ч
	PEN_COLOR_DEFAULT	= MYRGB( 255 ,   0 ,   0 ),	// ȱʡ�޵�ѹ�ȼ���������ɫ
	PEN_COLOR_POWEROFF	= MYRGB( 192 , 192 , 192 ),	// ʧ��&�ӵ�
	PEN_COLOR_SELECT	= MYRGB( 255 ,   0 , 255 ),	// ѡ��
	PEN_COLOR_MANSET    = MYRGB( 255 ,   0 , 255 ),	// ������ɫ

	PEN_COLOR_BLACK		= MYRGB(   0 ,   0 ,   0 ),
	PEN_COLOR_RED		= MYRGB( 255 ,   0 ,   0 ),
	PEN_COLOR_GREEN		= MYRGB(   0 , 255 ,   0 ),
	PEN_COLOR_BLUE		= MYRGB(   0 ,   0 , 255 ),
	PEN_COLOR_YELLOW	= MYRGB( 255 , 255 ,   0 ),
	PEN_COLOR_FUCHSIA	= MYRGB( 255 ,   0 , 255 ),
	PEN_COLOR_CYAN		= MYRGB(   0 , 255 , 255 ),
	PEN_COLOR_WHITE		= MYRGB( 255 , 255 , 255 )
};


struct SG_SAFE_OPER_INFO 
{
	
	SG_CHAR   target_status;  //target_status--��Ҫ�ı�ɵ�״̬; 
	
	SG_CHAR   current_status; //current_status--��ǰ��״̬;
	
	SG_CHAR   operate_type;
	
	SG_UCHAR  error_type;
	
	SG_CHAR   bOperWithload;  //���Դ����ɲ���
	
	SG_CHAR   error_info[511];
	
	SG_OBJECT error_obj;
	
	SG_SAFE_OPER_INFO(){error_info[0]='\0';}
};

enum cyc_connect_strategy
{
	no_wait=1,       //������
	wait_10times,  //10��
	wait_5min,     //5����
	wait_forever   //��Զ����
};
//----�ռ���������͡�
enum GDBSRV_TYPE
{
	GDBSRV_TYPE_GAP		=1, //GAP�ռ�����
	GDBSRV_TYPE_PSP		=2  //PSP�ռ�����
};

//----�ͻ������ݼ��ط�ʽ��
enum CLIENT_LOAD_TYPE
{
	LOAD_FROM_GDBSRV	=1, //�ͻ��˴ӿռ��������
	LOAD_FROM_SDE		=2, //�ͻ��˴�SDE�м���
	LOAD_FROM_DBF		=3	//�ͻ��˴�DBF�м���	
};
//
enum CLIENT_LOAD_FILTER
{
	CLIENT_LOAD_ALL			=1,		//ȫ������
	CLIENT_LOAD_BY_TASK		=2,		//��������ż���
	CLIENT_LOAD_BY_RANGE	=3,	//���տռ䷶Χ����(ֻ�Դ�SDE���м���������)
	CLIENT_LOAD_BY_SQL		=4	//SQL
};
//�����㳤��ֵ
//static SG_DOUBLE DISTANC_ZERO;
#endif /* SG_Def_h */

//���屾����չ�����
#define	LOCAL_POLYGON_TYPE	  4500
#define LOCAL_EX_POLYGON_NAME "������չ�����"
#define POINT_SIZE_AS_REGION	2