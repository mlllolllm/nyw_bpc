#ifndef _SGCONST_CLOUD_HHHH_
#define _SGCONST_CLOUD_HHHH_
typedef struct S_LOGICCELLINFO
{
	SG_INT		CellType;	//数据单元类型,对于实时库服务,即为配置启动时的实时库SrvTypeID对应的CellID; 缺省为0
	SG_INT		WorkSpace;	//WorkSpaceID 缺省为0
	S_TWOINT	TimeSection;	//时间段,缺省为0 0
	S_TWOINT	IDSection;	//数据主键ID段,缺省为0 0
	S_LOGICCELLINFO()
	{
		Init();
	};
	void Init()
	{
		CellType=WorkSpace=TimeSection.Val1=TimeSection.Val2=IDSection.Val1=IDSection.Val2=0;
	};
	static SG_INT	Compare(const S_LOGICCELLINFO &obj1,const S_LOGICCELLINFO &obj2)
	{
		SG_INT ret;
		if(obj1.CellType<obj2.CellType)
			return -1;
		if(obj1.CellType>obj2.CellType)
			return 1;
		if(obj1.WorkSpace<obj2.WorkSpace)
			return -1;
	    if(obj1.WorkSpace>obj2.WorkSpace)
			return 1;
		ret=S_TWOINT::Compare(obj1.TimeSection,obj2.TimeSection);
		if(ret!=0)
			return ret;
		ret=S_TWOINT::Compare(obj1.IDSection,obj2.IDSection);
		return ret;
	};
	SG_BOOL Serialize(CSgArchive &ar)
	{
		if(ar.IsLoading())
		{
			ar >> CellType;
			ar >> WorkSpace;
		}
		else
		{
			ar << CellType;
			ar << WorkSpace;
		}
		TimeSection.Serialize(ar);
		IDSection.Serialize(ar);
		return true;
	}
}S_LOGICCELLINFO;
struct CLogicCellInfoLess:
	public std::binary_function<S_LOGICCELLINFO, S_LOGICCELLINFO, bool> {
		bool operator()(const S_LOGICCELLINFO & obj1, const S_LOGICCELLINFO & obj2) const
		{
			if(S_LOGICCELLINFO::Compare(obj1,obj2)<0)
				return true;
			return false;
		}
};
typedef std::set<S_LOGICCELLINFO,CLogicCellInfoLess> SET_LOGICCELL;
typedef std::map<S_LOGICCELLINFO,SG_INT,CLogicCellInfoLess> MAP_LOGICCELL_INT;
typedef std::map<S_LOGICCELLINFO,S_TWOINT,CLogicCellInfoLess> MAP_LOGICCELL_TWOINT;
typedef std::map<S_LOGICCELLINFO,void *,CLogicCellInfoLess> MAP_LOGICCELL_VOIDPT;
typedef std::vector<S_LOGICCELLINFO > VECT_LOGICCELL;

#define SG_CLOUD_SRVCLASS_DB	1	//关系库
#define SG_CLOUD_SRVCLASS_RTDB	2	//实时库
#define SG_CLOUD_SRVCLASS_HDB	3	//历史库
#endif