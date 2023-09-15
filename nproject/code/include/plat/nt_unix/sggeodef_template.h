

/*******************************************************************************
*	创建日期:	2005/07/03
*	创建时间:	10:14
*******************************************************************************/

#ifndef SG_GEODEF_H_
#define SG_GEODEF_H_

#include "sgconst.h"
#include "sgarchive.h"
//
#include "malloc.h"

#ifdef USE_ARCSDE
#include <sdeincludes.h>
#endif
#undef LONG
#undef ULONG
#undef SHORT
#undef USHORT
#undef CHAR
#undef UCHAR
#undef FLOAT
#ifdef WIN32
#undef BOOL
#endif
/*
#ifdef SDE64
typedef int LONG;
#else
typedef long LONG;
#endif
*/
template <typename T>
class SgPointT
{
public:
	SgPointT(){}
	
	SgPointT(T X,T Y){x = X;y = Y;}
	SgPointT(const SgPointT<T>&pt){
		x = pt.x;
		y = pt.y;
	}
	T x,y;

	void Reset(){x=0;y=0;}
	SG_BOOL IsNull(){return x==0&&y==0;}
	SgPointT<T> & operator-(SgPointT<T> & p) {
		x-=p.x;
		y-=p.y;
		return *this;
	}
	void Offset(T xOffset,T yOffset,T zOffset=0)
	{
		x += xOffset;
		y += yOffset;
	}
	
	void Set(T X,T Y,T Z=0)
	{
		x = X;y=Y;
	}
	
	void Get(T&X,T&Y,T&Z)
	{
		X=x;Y=y;
	}
	
	SG_BOOL operator ==(SgPointT<T> &point)
	{
		if(x == point.x && y == point.y) return true;
		else return false;
	}
	
	SG_BOOL operator !=(SgPointT<T> &point)
	{
		if(x == point.x && y == point.y) return false;
		else return true;
	}
	
	void operator +=(SgPointT<T> &point)
	{
		x += point.x;
		y += point.y;
	}
	
	void operator -=(SgPointT<T> &point)
	{
		x -= point.x;
		y -= point.y;
	}
	
	SgPointT<T> operator +(SgPointT<T> &point)
	{
		return SgPointT<T>(x+point.x,y+point.y);
	}
	
	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>x;ar>>y;
		}
		else
		{
			ar<<x;ar<<y;
		}
		return true;
	}

	//严格判断两点相同
	
	inline SG_BOOL IsSame(const SgPointT<T>&xPt)
	{
		return ((x-xPt.x)*(x-xPt.x)+(y-xPt.y)*(y-xPt.y))<=T(DISTANCE_ZERO*DISTANCE_ZERO);
	}
	//判断两点符合复杂边上的点的约束
	
	inline SG_BOOL IsEdgeSame(const SgPointT<T>&xPt)
	{
		return ((x-xPt.x)*(x-xPt.x)+(y-xPt.y)*(y-xPt.y))<=T(SG_MAX_EDGE_TOLERANCE*SG_MAX_EDGE_TOLERANCE);
	}
	
	void OffSetX(T deltx)
	{
		if(x<0)
			x -= deltx;
		else
			x += deltx;
	}
	
    SG_DOUBLE LengthTo(const SgPointT<T>&xPt)
    {
        return sqrt((x-xPt.x)*(x-xPt.x)+(y-xPt.y)*(y-xPt.y));
    }
	
	static SG_BOOL Has3D(){
		return false;
	}	
};

template <typename T>
SG_BOOL operator==(const SgPointT<T> & lhs, SgPointT<T> & rhs){
	return (lhs.x==rhs.x && lhs.y==rhs.y);
}

template <typename T>
SG_BOOL operator> (const SgPointT<T> & lhs, SgPointT<T> & rhs){
	return (lhs.x > rhs.x);
}

#ifdef _WEB_CONTROL_
	typedef SgPointT<SG_FLOAT> SgPoint;
#else
#ifdef WIN32
	_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ SgPointT<SG_DOUBLE>;
#endif
	typedef SgPointT<SG_DOUBLE> SgPoint;
#endif



//z坐标暂不参与计算，仅做信息存储用

struct _DATASET_DLL_EXPORT_ Sg3DPoint:public SgPoint
{
	
	Sg3DPoint(){ Reset(); }
	
	Sg3DPoint(SgPoint&pt):SgPoint(pt){
		z =SG_DEFAULT_Z_VALUE;
	}
	
	Sg3DPoint(const Sg3DPoint&pt){
		x = pt.x; y= pt.y ; z = pt.z;
	}
	
	Sg3DPoint(SG_DOUBLE X,SG_DOUBLE Y,SG_FLOAT Z){x = X;y = Y;z=Z;}
	
	SG_FLOAT  z;
	
	void Reset(){x=0;y=0;z=SG_DEFAULT_Z_VALUE;}
	
	static SG_BOOL Has3D(){
		return true;
	}
	
	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset,SG_DOUBLE zOffset=0)
	{
		x += xOffset;
		y += yOffset;
		z += (SG_FLOAT)zOffset;
	}
	
	void Set(SG_DOUBLE X,SG_DOUBLE Y,SG_DOUBLE Z=SG_DEFAULT_Z_VALUE)
	{
		x = X;y=Y;z=(SG_FLOAT)Z;
	}
	
	void Get(SG_DOUBLE&X,SG_DOUBLE&Y,SG_DOUBLE&Z)
	{
		X=x;Y=y;Z=z;
	}
	//严格判断两点相同
	
	inline SG_BOOL IsSame(const Sg3DPoint&xPt)
	{
		return ((x-xPt.x)*(x-xPt.x)+(y-xPt.y)*(y-xPt.y)+(z-xPt.z)*(z-xPt.z))<=SG_DOUBLE(DISTANCE_ZERO*DISTANCE_ZERO);
	}
//	SG_BOOL IsNull(){return x==0&&y==0&&z==0;}
//	//
//	SG_BOOL operator ==(const Sg3DPoint &point)
//	{
//		if(x == point.x && y == point.y && z == point.z) return true;
//		else return false;
//	}
//	SG_BOOL operator !=(const Sg3DPoint &point)
//	{
//		if(x == point.x && y == point.y && z== point.z) return false;
//		else return true;
//	}
//	Sg3DPoint& operator +=(const Sg3DPoint &point)
//	{
//		x += point.x;
//		y += point.y;
//		z += point.z;
//		//
//		return *this;
//	}
//	Sg3DPoint& operator -=(const Sg3DPoint &point)
//	{
//		x -= point.x;
//		y -= point.y;
//		z -= point.z;
//		//
//		return *this;
//	}
	
	SG_BOOL Serialize(CSgArchive&ar)
	{
		if(ar.IsLoading())
		{
			ar>>x;
			ar>>y;
			ar>>z;
		}
		else
		{
			ar << x;
			ar << y;
			ar << z;
		}
		return true;
	}
};
//


template <typename TPoint>
class  CSgPointT
{
public:
	CSgPointT();
	CSgPointT(const CSgPointT<TPoint>&xPoint);
	~CSgPointT();
	//
	SG_BOOL IsNull();
	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset,SG_DOUBLE zOffset=0);
	//设置点数量
	void SetPointNums(SG_UINT PointNums);
	inline TPoint* GetFirstPoint() { return pPoint; }
	inline SG_UINT GetPointNums() { return pointnums; }
	CSgPointT<TPoint>& operator = (const CSgPointT<TPoint> &p);
	//
	SG_BOOL operator == (const CSgPointT<TPoint> &p);
	SG_BOOL operator != (const CSgPointT<TPoint> &p);
	//获得组成对象的点到一点的最小距离和点位置
	SG_DOUBLE GetMinLen(TPoint *pInPoint,SG_INT *pPointPos=NULL);
	//网络同步传输用
	SG_INT GetStructLen();
	SG_BOOL Serialize(CSgArchive&ar);
	//
	
	void	SetMemPtrNull(){ pPoint=NULL; };
	//
//	LONG FromShape(void*shape);
//	LONG ToShape(void*sh,SG_UCHAR ft);
	CSgPointT<SgPoint> * To2D(CSgPointT<SgPoint>*p2DGeoTrans);
	SG_BOOL From2D(CSgPointT<SgPoint>*p2DGeoTrans);
	//
public:
	
	static SG_BOOL Has3D(){return TPoint::Has3D();}
	
	static SG_BOOL IsLine(){ return false;}
public:
	
	SG_UINT pointnums;
	
	TPoint * pPoint;
};

template <typename TPoint>
CSgPointT<TPoint>::CSgPointT()
{
	pointnums =0;
	pPoint=NULL;
}

template <typename TPoint>
CSgPointT<TPoint>::CSgPointT(const CSgPointT<TPoint>&xPoint)
{
	pointnums = xPoint.pointnums;
	if(pointnums>0)
	{
		pPoint = new TPoint[pointnums];
		memcpy(pPoint,xPoint.pPoint,sizeof(TPoint)*pointnums);
	}
}

template <typename TPoint>
CSgPointT<TPoint>::~CSgPointT()
{
	if(pPoint)
	{
		delete [] pPoint;
		pPoint=NULL;
	}
}

template <typename TPoint>
SG_BOOL CSgPointT<TPoint>::IsNull()
{
	if(pointnums<1)return true;
	if(!pPoint)return true;
	return false;
}

template <typename TPoint>
void CSgPointT<TPoint>::Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset,SG_DOUBLE zOffset)
{
	SG_UINT i;
	for(i=0;i<pointnums;i++)
		pPoint[i].Offset(xOffset,yOffset,zOffset);
}

template <typename TPoint>
void CSgPointT<TPoint>::SetPointNums(SG_UINT PointNums)
{
	if(PointNums==0)
	{
		pointnums = PointNums;
		return;
	}
	if(PointNums>pointnums)
	{
		if(pPoint)delete [] pPoint;
		pPoint = new TPoint[PointNums];
	}
	pointnums = PointNums;
}

template <typename TPoint>
CSgPointT<TPoint>& CSgPointT<TPoint>::operator = (const CSgPointT<TPoint> &p)
{
	if(this==&p) return *this;
	pointnums = p.pointnums;
	if(pPoint!=NULL)
	{
		delete pPoint;
		pPoint =NULL;
	}
	if(pointnums>0)
	{
		pPoint = new TPoint[pointnums];
		memcpy(pPoint,p.pPoint,sizeof(TPoint)*pointnums);
	}
	return *this;
}



template <typename TPoint>
SG_BOOL CSgPointT<TPoint>::operator == (const CSgPointT<TPoint> &p)
{
	if(this==&p) return true;
	if(pointnums!=p.pointnums)return false;
	SG_UINT i;
	for(i=0;i<pointnums;i++)
	{
		if(pPoint[i] != p.pPoint[i])return false;
	}
	return true;
}

template <typename TPoint>
SG_BOOL CSgPointT<TPoint>::operator != (const CSgPointT<TPoint> &p)
{
	if(this==&p) return false;
	if(pointnums!=p.pointnums)return true;
	//
	SG_UINT i;
	for(i=0;i<pointnums;i++)
	{
		if(pPoint[i] != p.pPoint[i]) return true;
	}
	return false;
}

template <typename TPoint>
SG_DOUBLE CSgPointT<TPoint>::GetMinLen(TPoint *pInPoint,SG_INT *pPointPos)
{
	if(IsNull())return 0;
	SG_DOUBLE len,templen;
	SG_UINT Pos=0;
	SG_UINT i;
	for(i=0;i<pointnums;i++)
	{
		if(i==0)
		{
			Pos = 0;
			len = sqrt((pPoint[i].x-pInPoint->x)*(pPoint[i].x-pInPoint->x)+
				(pPoint[i].y-pInPoint->y)*(pPoint[i].y-pInPoint->y));
		}
		else
		{
			templen = sqrt((pPoint[i].x-pInPoint->x)*(pPoint[i].x-pInPoint->x)+
				(pPoint[i].y-pInPoint->y)*(pPoint[i].y-pInPoint->y));
			if(templen<len)
			{
				len = templen;
				Pos = i;
			}
		}
	}
	if(pPointPos!=NULL)
		*pPointPos = Pos;
	return len;
}

template <typename TPoint>
SG_INT CSgPointT<TPoint>::GetStructLen()
{
	SG_INT len = sizeof(CSgPointT<TPoint>);
	if(pointnums>0)
	{
		len += pointnums * sizeof(TPoint);
	}
	return len;
}

template <typename TPoint>
SG_BOOL CSgPointT<TPoint>::Serialize(CSgArchive&ar)
{
	SG_INT len=0;
	//加载
	if(ar.IsLoading())
	{
		SG_INT ptNums=0;
		ar>>ptNums;
		SetPointNums(ptNums);
	}
	else//保存
	{
		ar<<pointnums;
		if(pointnums<=0)return false;
	}
	SG_UINT i;
	for(i=0;i<pointnums;i++)
		pPoint[i].Serialize(ar);
	return true;
}

template <typename TPoint>
CSgPointT<SgPoint> * CSgPointT<TPoint>::To2D(CSgPointT<SgPoint>*p2DGeoTrans)
{
	p2DGeoTrans->SetPointNums(this->pointnums);
	SG_UINT i=0;
	for(i=0;i<this->pointnums;i++)
	{
		p2DGeoTrans->pPoint[i].x=this->pPoint[i].x;
		p2DGeoTrans->pPoint[i].y=this->pPoint[i].y;
	}
	return p2DGeoTrans;
}

template <typename TPoint>
SG_BOOL CSgPointT<TPoint>::From2D(CSgPointT<SgPoint>*p2DGeoTrans)
{
	int ptNums = p2DGeoTrans->pointnums;
	if(pointnums!=ptNums) this->SetPointNums(ptNums);
	for(int i=0;i<ptNums;i++)
	{
		this->pPoint[i].x = p2DGeoTrans->pPoint[i].x;
		this->pPoint[i].y = p2DGeoTrans->pPoint[i].y;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
//线型对象的几何属性管理类
//存储结构 (N个Part M个点)【PartNums】【Part0】...【PartN-1】【Point0】...【PointM－1】

template <typename TPoint>
class  CSgLineT
{
public:	
	//construct and destruct
	CSgLineT();
	CSgLineT(const CSgLineT<TPoint>&xLine);
	~CSgLineT();
public:
	//对象由几段组成
	SG_INT GetPartNums();
	//每段的终止点 － Base 0
	SG_INT *GetPartBound();
	//几何属性可用判断
	SG_BOOL IsNull();
	//获得总点数
	SG_INT GetPointNums();
	//获得起始点
	TPoint *GetFirstPoint();
	//获得起始点
	TPoint *GetSecondPoint();
	//获得终止点
	TPoint *GetLastPoint();
	//获得倒数第二点
	TPoint *GetLastPoint1();
	// --- 所有点位偏移一定距离
	void Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset,SG_DOUBLE zOffset=0);
	// --- 校正点位,使点位在SDE中提交时合法????? --- 最小单位为0.35um
	void Correct();

public:
	// 判断段是否直线
	
	inline SG_BOOL SegmentIsLine(SG_SHORT i,SG_CHAR* desc,SG_SHORT descLength)
	{
		if(!desc || i>=descLength) return true;
		SG_UCHAR seg_type = (SG_UCHAR)(desc[i]);
		seg_type &= 0x0f;   // 低四位 --- 类型
		switch(seg_type) 
		{
		case SG_FE_Arc:
		case SG_FE_BezeirLine:
		case SG_FE_Curve:
			return false;
			break;
		}
		return true;
	}
	SG_BOOL AddSegment(SG_SHORT&/*第几段*/,SG_SHORT /*整条线第几个点开始*/,SG_SHORT* /*指针,第几个点结束*/);
	SG_BOOL AddPoint(TPoint pt,SG_SHORT /*整条线第几个点后插入*/);
	SG_BOOL RemovePoint(SG_SHORT /*整条线第几个点移走*/);
	SG_BOOL SplitLine(SG_SHORT idx/*整条线第几个点分断*/,CSgLineT<TPoint>&newline);
	SG_BOOL SplitLine(SG_SHORT idx/*整条线第几个点后分断*/,TPoint pt,CSgLineT<TPoint>&newline);
	SG_BOOL JoinSegment(SG_SHORT idx/*idx段向前段合并*/);
	SG_SHORT nth(SG_SHORT pt_idx/*idx是第几段上的点*/);
	// --- 增加段
	void AddPart(CSgLineT<TPoint> &AddLine);
	//设置点数量----面向一个段的线对象
	void SetPointNums(SG_INT PointNums);
	//设置点数量----面向多段的线对象
	void SetPointNums(SG_INT PartNums,SG_INT PointNums);
	//设置点数量----面向多段的线对象
	void SetPointNums(SG_INT PartNums,SG_INT*pPartBound,TPoint*pPoint);
	/* 重载=号 */
	CSgLineT<TPoint>& operator = (const CSgLineT<TPoint> &p);
	/* 重载==号 */
	SG_BOOL operator == (const CSgLineT<TPoint> &p);
	/* 重载!=号 */
	SG_BOOL operator != (const CSgLineT<TPoint> &p);
	//计算线的长度
	SG_DOUBLE GetLength();
	//长度小于入参数
	SG_BOOL LessThan(SG_FLOAT len);
	//点在线的线段上判断 --- pos为线上的线段位置
	SG_BOOL IsPointOn(TPoint*pInPoint,SG_SHORT pos=0);
	//点在线段上的位置
	SG_INT PointOnLinePos(TPoint*pInPoint);
	//是否复杂边上的点
	//如果 IncludeTopPoint 为真，入参数的点为与拓扑点重合时返回正确
	//		否则	只有在中间非拓扑点上时返回正确
	SG_BOOL IsOnEdgeObj(CSgPointT<TPoint>*pInPoint,SG_INT &PointPos,SG_BOOL IncludeTopPoint);
	//是复杂边上的线
	//如果 IncludeTopPoint 为真，入参数的点为与拓扑点重合时返回正确
	//		否则	只有在中间非拓扑点上时返回正确
	SG_BOOL IsOnEdgeObj(CSgLineT<TPoint>*pInLine,SG_INT &PointPos,SG_BOOL IncludeTopPoint);
	//获得组成对象的点到一点的最小距离和点位置
	SG_DOUBLE GetMinLen(TPoint *pInPoint,SG_INT *pPointPos=NULL);
	//翻转点序
	void ReversePoint();
//	void CreateMem(void *pCon);	//创建传输内存	方法外创建内存
//	void Build(void *pCon);		//根据网络传输来的LocalLib重构结构
	SG_BOOL Serialize(CSgArchive&ar);
//	LONG FromShape(void*shape);
//	LONG ToShape(void*sh,SG_UCHAR ft);
	CSgLineT<SgPoint> * To2D(CSgLineT<SgPoint>*p2DGeoTrans);
	SG_BOOL From2D(CSgLineT<SgPoint>*p2DGeoTrans);
	//
public:
	
	static SG_BOOL Has3D(){return TPoint::Has3D();}
	
	static SG_BOOL IsLine(){ return true;}
public:
	// --- 强制破坏内存指针
	
	void	SetMemPtrNull(){m_pMem=NULL;}
	// --- 获得数据区首地址
	
	SG_INT	*GetMemPtr(){return m_pMem;}
	//获得线型结构的占用内存大小
	SG_INT GetStructLen();			//获得线型结构的占用内存大小
	// --- 获得结构指针部分分配的内存长度
	SG_INT GetMemLen();
private:
	// --- 内存的首地址
	
	SG_INT *m_pMem;
};

template <typename TPoint>
CSgLineT<TPoint>::CSgLineT()
{
	m_pMem = NULL;
}

template <typename TPoint>
CSgLineT<TPoint>::CSgLineT(const CSgLineT<TPoint>&xLine)
{
	CSgLineT<TPoint>*pLine = (CSgLineT<TPoint>*)&xLine;
	SG_INT Len = pLine->GetMemLen();
	if(Len<1){
		m_pMem = NULL;
	}
	else
	{
		SG_CHAR*p = (SG_CHAR*)xLine.m_pMem;
		m_pMem = (SG_INT*)malloc(Len);
		memcpy(m_pMem,p,Len);
	}
}

template <typename TPoint>
CSgLineT<TPoint>::~CSgLineT()
{
	if(m_pMem)free(m_pMem);
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::IsNull()
{
	if(!m_pMem)return true;
	return (*m_pMem<1);
}


template <typename TPoint>
SG_INT CSgLineT<TPoint>::GetPartNums()
{
	if(!m_pMem)return 0;
	return *m_pMem;
}

template <typename TPoint>
SG_INT* CSgLineT<TPoint>::GetPartBound()
{
	if(!m_pMem)return NULL;
	return m_pMem+1;
}

template <typename TPoint>
SG_INT CSgLineT<TPoint>::GetPointNums()
{
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return 0;
	return pPartBound[*m_pMem-1];
}


template <typename TPoint>
TPoint*CSgLineT<TPoint>::GetFirstPoint()
{
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return 0;
	return (TPoint*)&pPartBound[*m_pMem];
}


template <typename TPoint>
TPoint* CSgLineT<TPoint>::GetSecondPoint()
{
	TPoint*p = GetFirstPoint();
	if(!p)return NULL;
	return p+1;
}

template <typename TPoint>
TPoint* CSgLineT<TPoint>::GetLastPoint()
{
	SG_INT PointNums = GetPointNums();
	if(PointNums<2)return NULL;
	TPoint*p = GetFirstPoint();
	if(!p)return NULL;
	return p+(PointNums-1);
}


template <typename TPoint>
TPoint* CSgLineT<TPoint>::GetLastPoint1()
{
	SG_INT PointNums = GetPointNums();
	if(PointNums<2)return NULL;
	TPoint*p = GetFirstPoint();
	if(!p)return NULL;
	return p+(PointNums-2);
}


template <typename TPoint>
void CSgLineT<TPoint>::Offset(SG_DOUBLE xOffset,SG_DOUBLE yOffset,SG_DOUBLE zOffset)
{
	TPoint*p = GetFirstPoint();
	if(!p)return;
	SG_INT PoitnNums = GetPointNums();
	if(PoitnNums<1)return;
	SG_INT i;
	for(i=0;i<PoitnNums;i++)
		p[i].Offset(xOffset,yOffset,zOffset);
}


template <typename TPoint>
void CSgLineT<TPoint>::SetPointNums(SG_INT PointNums)
{
	if(m_pMem)free(m_pMem);
	m_pMem=NULL;
	if(PointNums<2){
		return;
	}
	m_pMem = (SG_INT*)malloc(sizeof(SG_INT)*2+sizeof(TPoint)*PointNums);
	*m_pMem = 1;
	*(m_pMem+1)=PointNums;
}


template <typename TPoint>
void CSgLineT<TPoint>::SetPointNums(SG_INT PartNums,SG_INT PointNums)
{
	if(m_pMem)free(m_pMem);
	m_pMem=NULL;
	if(PartNums<1)return;
	if(PointNums<2)return;
	m_pMem = (SG_INT*)malloc(sizeof(SG_INT)*(1+PartNums)+sizeof(TPoint)*PointNums);
	*m_pMem = PartNums;
	*(m_pMem+PartNums)=PointNums;
}


template <typename TPoint>
void CSgLineT<TPoint>::SetPointNums(SG_INT PartNums,SG_INT*pPartBound,TPoint*pPoint)
{
	if(m_pMem)free(m_pMem);
	m_pMem=NULL;
	SG_INT PointNums;
	if(PartNums<1||!pPartBound||!pPoint)return;
	PointNums = pPartBound[PartNums-1];
	if(PointNums<2)return;
	//
	m_pMem = (SG_INT*)malloc(sizeof(SG_INT)*(PartNums+1)+sizeof(TPoint)*PointNums);
	*m_pMem = PartNums;
	memcpy(m_pMem+1,pPartBound,sizeof(SG_INT)*(PartNums));
	memcpy(m_pMem+1+PartNums,pPoint,sizeof(TPoint)*(PointNums));
}



template <typename TPoint>
void CSgLineT<TPoint>::Correct()
{
	static SG_DOUBLE MinLen = DISTANCE_ZERO;
	TPoint*p = GetFirstPoint();
	if(!p)return;
	if(GetPointNums()==2)
	{
		if(p[0].IsSame(p[1]))
		{
			p[1].x = p->x+MinLen/2;
			p[1].y = p->y+MinLen/2;
		}
	}
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::AddSegment(SG_SHORT&iseg,SG_SHORT from,SG_SHORT*p_to_index)
{
	//支持线分段
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return false;
	//如果只传入一个点的情况可根据点序计算段序
	SG_SHORT to = p_to_index?(*p_to_index):from;
	if(iseg<0 || iseg>=partnums)
	{
		//根据from获取段序
		SG_SHORT start=0;
		SG_INT i;
		for(i=0; i<partnums; i++)
		{
			if(from>=start && to<=pPartBound[i]-1)
			{
				iseg=i;
				break;
			}
			start=pPartBound[i];
		}
	}
	if(iseg<0 || iseg>=partnums)
		return false;
	TPoint*pPoint = GetFirstPoint();
	SG_INT start=(iseg>0)?pPartBound[iseg-1]:0;
	SG_INT end=pPartBound[partnums-1]-1; //线末点
	SG_INT seg_end=pPartBound[iseg]-1;  //段末点
	if(from<start || to>seg_end) return false;
	if(p_to_index)
	{
		if(to<=from || to-from<1) return false;
		if(from==start && to==seg_end) return false;  //与原来一样，不予处理
	}
	else
	{
		if(from==start || to==seg_end)return false;  //与原来一样，不予处理
	}
	CSgLineT<TPoint> line;
	if(0==p_to_index/*只传入一个点的情况*/ || 
		from==start/*两点，起点与段首点相同*/)
	{
		//增加一个点,一段
		line.SetPointNums(partnums+1,GetPointNums()+1);
		//段前
		SG_INT cur_start=0;
		if(iseg>0)
		{
			cur_start=pPartBound[iseg-1];
			memcpy(line.GetPartBound(),pPartBound,sizeof(SG_INT)*iseg);
			memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*cur_start);
		}
		//
		line.GetPartBound()[iseg]=to+1;  // 一个点的情况 from==to
		SG_INT i;
		for(i=cur_start; i<=to; i++)
			line.GetFirstPoint()[i]=pPoint[i];
		//当前段以后
		for(i=iseg+1; i<line.GetPartNums(); i++)
			line.GetPartBound()[i]=pPartBound[i-1]+1;
		for( i=to; i<=end; i++)
			line.GetFirstPoint()[i+1]=pPoint[i];
	}
	else if(to==seg_end)
	{
		//增加一个点,一段
		line.SetPointNums(partnums+1,GetPointNums()+1);
		//段前
		memcpy(line.GetPartBound(),pPartBound,sizeof(SG_INT)*(iseg+1));
		line.GetPartBound()[iseg]=from+1;
		memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*(from+1));
		//
		line.GetFirstPoint()[from]=pPoint[from];
		//段后
		SG_INT i;
		for(i=iseg+1; i<line.GetPartNums(); i++)
			line.GetPartBound()[i]=pPartBound[i-1]+1;
		for( i=from; i<=end; i++)
			line.GetFirstPoint()[i+1]=pPoint[i];
	}
	else
	{
		//增加两个点,两段
		line.SetPointNums(partnums+2,GetPointNums()+2);
		//段前
		SG_INT cur_start=0;
		if(iseg>0)
		{
			cur_start=pPartBound[iseg-1];
			memcpy(line.GetPartBound(),pPartBound,sizeof(SG_INT)*iseg);
			memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*cur_start);
		}
		//
		//分割段前部分
		line.GetPartBound()[iseg]=from+1;
		SG_INT i;
		for(i=cur_start; i<=from; i++)
			line.GetFirstPoint()[i]=pPoint[i];
		//分割段后部分
		line.GetPartBound()[iseg+1]=to+2;
		for(i=from; i<=to; i++)
			line.GetFirstPoint()[i+1]=pPoint[i];
		//段后
		for(i=iseg+2; i<line.GetPartNums(); i++)
			line.GetPartBound()[i]=pPartBound[i-2]+2;
		for( i=to; i<=end; i++)
			line.GetFirstPoint()[i+2]=pPoint[i];
	}
	*this=line;
	return true;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::AddPoint(TPoint pt,SG_SHORT idx)
{
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return false;
	TPoint*pPoint = GetFirstPoint();
	//根据idx获取段序
	SG_SHORT iseg=-1;
	SG_SHORT start=0;
	SG_INT i;
	for(i=0; i<partnums; i++)
	{
		if(idx>=start && idx<pPartBound[i]-1)
		{
			iseg=i;
			break;
		}
		start=pPartBound[i];
	}
	if(iseg<0) return false;
	CSgLineT<TPoint> line;
	line.SetPointNums(partnums,GetPointNums()+1);
	for(i=0; i<partnums; i++)
	{
		if(i<iseg)
			line.GetPartBound()[i]=pPartBound[i];
		else
			line.GetPartBound()[i]=pPartBound[i]+1;
	}
	memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*(idx+1));
	line.GetFirstPoint()[idx+1]=pt;
	memcpy(line.GetFirstPoint()+idx+2,pPoint+idx+1,sizeof(TPoint)*(GetPointNums()-idx-1));
	*this=line;
	return true;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::RemovePoint(SG_SHORT idx)
{
	//每段必须大于2,每段的端点不予处理 
	//但第一段的起点和最后一段的末点处理 
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return false;
	TPoint*pPoint = GetFirstPoint();
	SG_SHORT start=0;
	SG_INT iseg;
	for(iseg=0; iseg<partnums; iseg++)
	{
		if(idx<start)
		{
			iseg=partnums;
			break;
		}
		SG_SHORT ptnums = pPartBound[iseg]-start;
		if(ptnums<3) 
		{
			start=pPartBound[iseg];
			continue;
		}
		if(iseg==0 ||iseg==partnums-1)
		{
			if(iseg==0 && idx>=start && idx<pPartBound[iseg]-1)
				break;
			if(iseg==partnums-1 && idx>start && idx<=pPartBound[iseg]-1)
				break;
		}
		else if(idx>start && idx<pPartBound[iseg]-1)
			break;
		start=pPartBound[iseg];
	}
	if(iseg>=partnums) return false;
	CSgLineT<TPoint> line;
	line.SetPointNums(partnums,GetPointNums()-1);
	SG_SHORT i;
	for(i=0; i<partnums; i++)
	{
		if(i<iseg)
			line.GetPartBound()[i]=pPartBound[i];
		else
			line.GetPartBound()[i]=pPartBound[i]-1;
	}
	if(idx>0) memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*idx);
	SG_SHORT pluspts=GetPointNums()-idx-1;
	if(pluspts>0) memcpy(line.GetFirstPoint()+idx,pPoint+idx+1,sizeof(TPoint)*pluspts);
	*this=line;
	return true;
}



template <typename TPoint>
SG_SHORT CSgLineT<TPoint>::nth(SG_SHORT idx/*idx是第几段上的点*/)
{
	//根据idx获取段序
	SG_SHORT iseg=-1;
	SG_SHORT start=0;
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound) return iseg;
	SG_INT i;
	for(i=0; i<partnums; i++)
	{
		if(idx>=start && idx<pPartBound[i])
		{
			iseg=i;
			break;
		}
		start=pPartBound[i];
	}
	return iseg;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::SplitLine(SG_SHORT idx/*整条线第几个点分断*/,CSgLineT<TPoint>&newline)
{
	//if(idx<1 || idx>=GetPointNums()-1) return false;
	//modi on 2011-02-19?? 首段和末端也需要截断
	if(idx<0 || idx>=GetPointNums()) return false;
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return false;
	TPoint*pPoint = GetFirstPoint();
	// 1) 段的端点
	// 2) 段的中间点
	SG_BOOL bTermal=false;
	SG_SHORT start=0;
	SG_SHORT i;
	for(i=0; i<partnums; i++)
	{
		if(idx==pPartBound[i] || idx==pPartBound[i]-1)
		{
			bTermal=true;
            break;
		}
		else if(idx>start && idx<pPartBound[i]-1)
			break;
		start=pPartBound[i];
	}
	if(i==partnums) return false;
	if(false==bTermal)
	{
		//分段,使之变成端点
		if(!AddSegment(i,idx,0))
			return false;
		pPartBound = GetPartBound();
		pPoint = GetFirstPoint();
		partnums = GetPartNums();
		for(i=0; i<partnums; i++)
		{
			if(idx==pPartBound[i] || idx==pPartBound[i]-1)
				break;
		}
		if(i==partnums) return false;
	}
	//从第i段后剖分（第i段属原来的线）
	CSgLineT<TPoint> line;
	line.SetPointNums(i+1,pPartBound[i]);
	memcpy(line.GetPartBound(),pPartBound,sizeof(SG_INT)*(i+1));
	memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*pPartBound[i]);
	// new line
	SG_SHORT ptnums=pPartBound[partnums-1]-pPartBound[i];
	newline.SetPointNums(partnums-i-1,ptnums);
	memcpy(newline.GetFirstPoint(),pPoint+pPartBound[i],sizeof(TPoint)*ptnums);
	SG_INT k;
	for(k=i+1; k<partnums; k++)
	{
		newline.GetPartBound()[k-i-1]=pPartBound[k]-pPartBound[i];
	}
	*this=line;
	return !(line.IsNull()||newline.IsNull());
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::SplitLine(SG_SHORT idx/*整条线第几个点后分断*/,TPoint pt,CSgLineT<TPoint>&newline)
{
	//先加入，再剖分
	if(!AddPoint(pt,idx)) return false;
	return SplitLine(idx+1,newline);
}

template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::JoinSegment(SG_SHORT idx/*idx段向前段合并*/)
{
	if(idx<1) return false;
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return false;
	TPoint*pPoint = GetFirstPoint();
	CSgLineT<TPoint> line;
	line.SetPointNums(partnums-1,GetPointNums()-1);
	SG_SHORT i;
	for(i=0; i<line.GetPartNums(); i++)
	{
		if(i<idx-1)
			line.GetPartBound()[i]=pPartBound[i];
		else
			line.GetPartBound()[i]=pPartBound[i+1]-1;
	}
	memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*pPartBound[idx-1]);
	SG_SHORT ptnums=GetPointNums()-1-pPartBound[idx-1];
	memcpy(line.GetFirstPoint()+pPartBound[idx-1],pPoint+pPartBound[idx-1]+1,sizeof(TPoint)*ptnums);
	*this=line;
	return true;
}

template <typename TPoint>
void CSgLineT<TPoint>::AddPart(CSgLineT<TPoint> &AddLine)
{
	if(AddLine.IsNull())
		return;
	//
	SG_INT partnums = GetPartNums();
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound||partnums<1){
		*this = AddLine;
		return;
	}
	TPoint*pPoint = GetFirstPoint();
	SG_INT AddPointNums = AddLine.GetPointNums();
	SG_INT AddPartNums  = AddLine.GetPartNums();
	CSgLineT<TPoint> line;
	line.SetPointNums(partnums+AddPartNums,AddPointNums+GetPointNums());
	memcpy(line.GetPartBound(),pPartBound,sizeof(SG_INT)*partnums);
	// 合并段中点的索引
	SG_INT* pp1 = AddLine.GetPartBound();
	SG_INT* pp2 = new SG_INT[AddPartNums];
	SG_INT i;
	for(i=0; i<AddPartNums; i++)
	{
		pp2[i]=pp1[i]+pPartBound[partnums-1];
	}
	memcpy(line.GetPartBound()+partnums,pp2,sizeof(SG_INT)*AddPartNums);
	delete [] pp2;
	// 合并点
	memcpy(line.GetFirstPoint(),pPoint,sizeof(TPoint)*GetPointNums());
	memcpy(line.GetFirstPoint()+GetPointNums(),AddLine.GetFirstPoint(),sizeof(TPoint)*AddPointNums);
	*this = line;
}

template <typename TPoint>
CSgLineT<TPoint>& CSgLineT<TPoint>::operator= (const CSgLineT<TPoint> &p)
{
	if(this==&p)
		return *this;
	CSgLineT<TPoint>*pLine = (CSgLineT<TPoint>*)&p;
	SetPointNums(pLine->GetPartNums(),pLine->GetPartBound(),pLine->GetFirstPoint());
	return *this;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::operator == (const CSgLineT<TPoint> &p)
{
	if(this==&p)
		return true;
	CSgLineT<TPoint>*pLine = (CSgLineT<TPoint>*)&p;
	SG_INT MemLen = GetMemLen();
	if(MemLen!=pLine->GetMemLen())return false;
	if(MemLen<1)return true;
	//
	return memcmp(m_pMem,pLine->m_pMem,MemLen)==0;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::operator != (const CSgLineT<TPoint> &p)
{
	return !(*this==p);
}

template <typename TPoint>
SG_DOUBLE CSgLineT<TPoint>::GetLength()
{
	SG_INT partnums = GetPartNums();
	if(partnums<1)return 0;
	SG_INT*pPartBound = GetPartBound();
	if(!pPartBound)return 0;
	SG_DOUBLE totallen = 0;
	SG_INT PointNums = pPartBound[partnums-1]-1;
	TPoint *pPoint = GetFirstPoint();
	SG_DOUBLE deltx,delty;
	SG_INT i;
	for(i=0;i<PointNums;i++)
	{
		deltx = pPoint[i].x - pPoint[i+1].x;
		delty = pPoint[i].y - pPoint[i+1].y;
		totallen += sqrt(deltx*deltx+delty*delty);
	}
	return totallen;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::LessThan(SG_FLOAT len)
{
	if(len<=0)return false;
	SG_INT partnums = GetPartNums();
	if(partnums<1)return true;
	SG_INT *pPartBound = GetPartBound();
	if(!pPartBound)return true;
	SG_DOUBLE totallen = 0;
	SG_INT PointNums = pPartBound[partnums-1]-1;
	SG_DOUBLE deltx,delty;
	TPoint*pPoint = GetFirstPoint();
	SG_INT i;
	for(i=0;i<PointNums;i++)
	{
		deltx = pPoint[i].x - pPoint[i+1].x;
		delty = pPoint[i].y - pPoint[i+1].y;
		totallen += sqrt(deltx*deltx+delty*delty);
		if(totallen>len)return false;
	}
	return totallen<len;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::IsPointOn(TPoint*pInPoint,SG_SHORT pos)
{
	if(pos<0)return false;
	if(pos>=GetPointNums()-1)return false;
	TPoint*pPoint = GetFirstPoint();
	TPoint * p1 = &pPoint[pos];
	TPoint * p2 = &pPoint[pos+1];
	SG_DOUBLE MinX = MYMIN(p1->x,p2->x) - DISTANCE_ZERO;
	SG_DOUBLE MaxX = MYMAX(p1->x,p2->x) + DISTANCE_ZERO;
	SG_DOUBLE MinY = MYMIN(p1->y,p2->y) - DISTANCE_ZERO;
	SG_DOUBLE MaxY = MYMAX(p1->y,p2->y) + DISTANCE_ZERO;
	if(pInPoint->x>=MinX && pInPoint->x<=MaxX && pInPoint->y>=MinY && pInPoint->y<=MaxY)return true;
	return false;
}


template <typename TPoint>
SG_INT CSgLineT<TPoint>::PointOnLinePos(TPoint*pInPoint)
{
	TPoint*pPoint = GetFirstPoint();
	if(!pPoint)return -1;
	SG_INT i;
	for(i=GetPointNums()-1;i>=0;i--)
	{
		if(pPoint[i].IsEdgeSame(*pInPoint))return i;
	}
	return -1;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::IsOnEdgeObj(CSgPointT<TPoint>*pInPoint,SG_INT &PointPos,SG_BOOL IncludeTopPoint)
{
	if(!pInPoint || pInPoint->IsNull())return false;
	SG_UINT i;
	for(i=0;i<pInPoint->pointnums;i++)
	{
		PointPos = PointOnLinePos(&pInPoint->pPoint[i]);
		if(IncludeTopPoint)
		{
			if(PointPos>=0 && PointPos<GetPointNums())
				return true;
		}
		else
		{
			if(PointPos>0 && PointPos<GetPointNums()-1)
				return true;
		}
	}
	return false;
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::IsOnEdgeObj(CSgLineT<TPoint>*pInLine,SG_INT &PointPos,SG_BOOL IncludeTopPoint)
{
	if(!pInLine || pInLine->IsNull())return false;
	SG_INT InLinePointNums = pInLine->GetPointNums();
	SG_INT PointNums = GetPointNums();
	TPoint*pPoint = pInLine->GetFirstPoint();
	SG_INT i;
	for(i=0;i<InLinePointNums;i++)
	{
		PointPos = PointOnLinePos(&pPoint[i]);
		if(IncludeTopPoint)
		{
			if(PointPos>=0 && PointPos<PointNums)
				return true;
		}
		else
		{
			if(PointPos>0 && PointPos<PointNums-1)
				return true;
		}
	}
	return false;
}


template <typename TPoint>
SG_DOUBLE CSgLineT<TPoint>::GetMinLen(TPoint *pInPoint,SG_INT *pPointPos)
{
	TPoint*pPoint = GetFirstPoint();
	if(!pPoint)return 0;
	SG_DOUBLE len,templen;
	SG_INT PointNums,Pos=0;
	PointNums = GetPointNums();
	SG_INT i;
	for(i=0;i<PointNums;i++)
	{
		if(i==0)
		{
			Pos = 0;
			len = sqrt((pPoint[i].x-pInPoint->x)*(pPoint[i].x-pInPoint->x)+
				(pPoint[i].y-pInPoint->y)*(pPoint[i].y-pInPoint->y));
		}
		else
		{
			templen = sqrt((pPoint[i].x-pInPoint->x)*(pPoint[i].x-pInPoint->x)+
				(pPoint[i].y-pInPoint->y)*(pPoint[i].y-pInPoint->y));
			if(templen<len)
			{
				len = templen;
				Pos = i;
			}
		}
	}
	if(pPointPos!=NULL)
		*pPointPos = Pos;
	return len;
}


template <typename TPoint>
void CSgLineT<TPoint>::ReversePoint()
{
	TPoint*pPoint = GetFirstPoint();
	if(!pPoint)return;
	SG_INT *pPartBound = GetPartBound();
	SG_INT partnums = GetPartNums();
	SG_INT i;
	if(partnums>1)
	{
		SG_INT *pTemp = new SG_INT[partnums];
		for(i=0;i<partnums;i++)
		{
			if(i==0)
				pTemp[i] = pPartBound[0];
			else
				pTemp[i] = pPartBound[i]-pPartBound[i-1];
		}
		for(i=0;i<partnums;i++)
		{
			if(i==0)
				pPartBound[i] = pTemp[partnums-1];
			else
				pPartBound[i] = pTemp[partnums-1-i]+pPartBound[i-1];
		}
		delete [] pTemp;
	}
	//
	SG_INT nums = GetPointNums();
	TPoint pp;
	for(i=0;i<nums/2;i++)
	{
		pp = pPoint[i];
		pPoint[i] = pPoint[nums-i-1];
		pPoint[nums-i-1] = pp;
	}
}


template <typename TPoint>
SG_INT CSgLineT<TPoint>::GetStructLen()
{
	SG_UINT len = sizeof(CSgLineT<TPoint>);
	return len+GetMemLen();
}


template <typename TPoint>
SG_INT CSgLineT<TPoint>::GetMemLen()
{
	if(!m_pMem)return 0;
	if(*m_pMem<1)return 0;
	return m_pMem[*m_pMem]*sizeof(TPoint)+sizeof(SG_INT)*(*m_pMem+1);
}


template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::Serialize(CSgArchive&ar)
{
	SG_INT len=0;
	//加载
	if(ar.IsLoading())
	{
		//
		if(m_pMem)free(m_pMem);
		m_pMem=NULL;
		//
		SG_INT partnums;
		ar>>partnums;
		if(partnums<=0)return false;
		SG_INT *pPartBound=new SG_INT[partnums];
		SG_INT i;
		for(i=0;i<partnums;i++){
			ar>>pPartBound[i];
			if(pPartBound[i]<1){
				delete[]pPartBound;
				return false;
			}
		}
		TPoint*pPoint=new TPoint[pPartBound[partnums-1]];
		for(i=0;i<pPartBound[partnums-1];i++)
			pPoint[i].Serialize(ar);
		SetPointNums(partnums,pPartBound,pPoint);
		delete [] pPoint;
		delete [] pPartBound;
	}
	else//保存
	{
		SG_INT partnums = GetPartNums();
		if(partnums<=0)
		{
			ar<<partnums;
			return false;
		}
		TPoint*pPoint = GetFirstPoint();
		if(!pPoint){
			partnums=0;
			ar<<partnums;
			return false;
		}
		SG_INT *pPartBound = GetPartBound();
		ar<<partnums;
		SG_INT i;
		for(i=0;i<partnums;i++)
			ar<<pPartBound[i];
		for(i=0;i<pPartBound[partnums-1];i++)
			pPoint[i].Serialize(ar);
	}
	return true;
}

template <typename TPoint>
CSgLineT<SgPoint> * CSgLineT<TPoint>::To2D(CSgLineT<SgPoint>*p2DGeoTrans)
{
	int ptNums = this->GetPointNums();
	if(ptNums)
	{
		TPoint * pFirstPt = this->GetFirstPoint();
		SgPoint * pPoint = new SgPoint[ptNums];
		for(int i=0;i<ptNums;i++)
		{
			pPoint[i].x=pFirstPt[i].x;
			pPoint[i].y=pFirstPt[i].y;
		}
		p2DGeoTrans->SetPointNums(this->GetPartNums(),this->GetPartBound(),pPoint);
		delete[]pPoint;
	}
	else p2DGeoTrans->SetPointNums(0);
	//
	return p2DGeoTrans;
}

template <typename TPoint>
SG_BOOL CSgLineT<TPoint>::From2D(CSgLineT<SgPoint>*p2DGeoTrans)
{
	int pt2DNums = p2DGeoTrans->GetPointNums();
	int pt3DNums = this->GetPointNums();
	//
	SgPoint * p2DPoint = p2DGeoTrans->GetFirstPoint();
	if(pt3DNums==pt2DNums)
	{
		TPoint * p3DPoint = this->GetFirstPoint();
		for(int i=0;i<pt2DNums;i++)
		{
			p3DPoint[i].x = p2DPoint[i].x;
			p3DPoint[i].y = p2DPoint[i].y;
		}
	}
	else
	{
		if(m_pMem)
		{
			free(m_pMem);
			m_pMem=NULL;
		}
		if(pt2DNums)
		{
			TPoint * p3DPoint = new TPoint[pt2DNums];
			for(int i=0;i<pt2DNums;i++)
			{
				p3DPoint[i].x=p2DPoint[i].x;
				p3DPoint[i].y=p2DPoint[i].y;
			}
			SetPointNums(p2DGeoTrans->GetPartNums(),p2DGeoTrans->GetPartBound(),p3DPoint);
			delete [] p3DPoint;
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
/*#ifdef USE_ARCSDE
template <typename TPoint>
LONG CSgLineT<TPoint>::FromShape(void*sh)
{
	LONG rc=0;
	//
	SE_SHAPE shape =(SE_SHAPE)sh;
	LONG num_subparts,partnums;
	rc=SE_shape_get_num_parts(shape,(LONG*)&partnums,&num_subparts);
	if(rc!=SE_SUCCESS) return rc;
	//
	if(partnums<1 ) return SE_FAILURE;
	//
	LONG num_pts=0,bound=0;
	rc=SE_shape_get_num_points(shape,0,0,&num_pts);
	if(rc!=SE_SUCCESS) return rc;
	//
	if(num_pts<1) return SE_FAILURE  ;
	//
	LONG* parts = new LONG[partnums+1];
	LONG* subparts = new LONG[num_subparts+2];
	//
	TPoint * pPoint=new TPoint[num_pts];
	if(Has3D())
	{
		SgPoint*pP=new SgPoint[num_pts];
		LFLOAT * pZ = new LFLOAT [num_pts];
		rc=SE_shape_get_all_points(shape,SE_DEFAULT_ROTATION,parts,subparts,(SE_POINT*)pP,pZ,0);
		//
		if(SE_SUCCESS==rc)
		{
			for(int i=0;i<num_pts;i++){
				pPoint[i].Set(pP[i].x,pP[i].y,pZ[i]);
			}
		}
		delete [] pP;
		delete [] pZ;
	}
	else
	{
		rc=SE_shape_get_all_points(shape,SE_DEFAULT_ROTATION,parts,subparts,(SE_POINT*)pPoint,0,0);
	}
	if(SE_SUCCESS==rc)
	{
		subparts[num_subparts] = num_pts;
		SetPointNums(partnums,(int*)(subparts+1),pPoint);
	}
	//
	delete [] parts;
	delete [] subparts;
	delete [] pPoint;
	//
	return rc;
}

template <typename TPoint>
LONG CSgPointT<TPoint>::FromShape(void*sh)
{
	LONG rc=0;
	//
	SE_SHAPE shape =(SE_SHAPE)sh;
	LONG num_parts,num_subparts;
	rc=SE_shape_get_num_parts(shape,&num_parts,&num_subparts);
	if(rc!=SE_SUCCESS)  return rc;
	rc=SE_shape_get_num_points(shape,0,0,(LONG*)&pointnums);
	if(rc!=SE_SUCCESS)  return rc;
	//
	pPoint=new TPoint[pointnums];
	//
	LONG* part_offsets = new LONG[num_parts+1];
	LONG* subpart_offsets = new LONG[num_subparts+1];
	if(Has3D())
	{
		SgPoint*pP=new SgPoint[pointnums];
		LFLOAT * pZ = new LFLOAT [pointnums];
		rc=SE_shape_get_all_points(shape,SE_DEFAULT_ROTATION,part_offsets,subpart_offsets,(SE_POINT*)pP,pZ,0);
		//
		if(SE_SUCCESS==rc)
		{
			for(SG_UINT i=0;i<pointnums;i++){
				pPoint[i].Set(pP[i].x,pP[i].y,pZ[i]);
			}
		}
		delete [] pP;
		delete [] pZ;
	}
	else
	{
		rc=SE_shape_get_all_points(shape,SE_DEFAULT_ROTATION,part_offsets,subpart_offsets,(SE_POINT*)pPoint,NULL,NULL);
	}
	
	delete[]part_offsets;
	delete[]subpart_offsets;
	//
	return rc;
}

template <typename TPoint>
LONG CSgPointT<TPoint>::ToShape(void*sh,SG_UCHAR ft)
{ 
	LONG rc=0;
	SE_SHAPE shape =(SE_SHAPE)sh;
	//
	if(this->IsNull()) rc=SE_shape_make_nil(shape);
	else
	{
		if(Has3D())
		{	
			SgPoint*pP=new SgPoint[pointnums];
			LFLOAT * pZ = new LFLOAT [pointnums];
			for(SG_UINT i=0;i<pointnums;i++){
				pPoint[i].Get(pP[i].x,pP[i].y,pZ[i]);
			}
			rc=SE_shape_generate_point(pointnums,(SE_POINT*)pP,pZ,NULL,shape);
			delete [] pP;
			delete [] pZ;
		}
		else rc=SE_shape_generate_point(this->pointnums,(SE_POINT*)this->pPoint,NULL,NULL,shape);
	}
	return rc;
}


template <typename TPoint>
LONG CSgLineT<TPoint>::ToShape(void*sh,SG_UCHAR ft)
{
	LONG rc=0;
	SE_SHAPE shape =(SE_SHAPE)sh;
	//
	if(this->IsNull()) rc=SE_shape_make_nil(shape);
	else
	{
		this->Correct();
		//CSgLine <------> sde line struct
		SG_INT PartNums = this->GetPartNums();
		LONG* pPart = new LONG[PartNums];
		LONG ptnums = this->GetPointNums();
		pPart[0]=0;
		SG_INT *pPartBound = this->GetPartBound();
		SG_INT k;
		for(k=1; k<PartNums; k++)
			pPart[k]=pPartBound[k-1];
		//
		TPoint * pPoint = this->GetFirstPoint();
	
		if(Has3D())
		{
			SgPoint*pP=new SgPoint[ptnums];
			LFLOAT * pZ = new LFLOAT [ptnums];
			//
			for(int i=0;i<ptnums;i++){
				pPoint[i].Get(pP[i].x,pP[i].y,pZ[i]);
			}
			if(SG_B_Feature_3DREGION==ft||SG_B_Feature_REGION==ft) 
				rc=SE_shape_generate_polygon(ptnums,PartNums,pPart,(SE_POINT*)pP,pZ,NULL,shape);
			else 
				rc=SE_shape_generate_line(ptnums,PartNums,pPart,(SE_POINT*)pP,pZ,NULL,shape);
			//
			delete [] pP;
			delete [] pZ;
		}
		else
		{
			if(ft==SG_B_Feature_LINE)rc=SE_shape_generate_line(ptnums,PartNums,pPart,(SE_POINT*)pPoint,NULL,NULL,shape);
			else rc=SE_shape_generate_polygon(ptnums,PartNums,pPart,(SE_POINT*)pPoint,NULL,NULL,shape);
		}
		delete [] pPart;
	}
	return rc;
}
#else
template <typename TPoint>
LONG CSgPointT<TPoint>::FromShape(void*sh){ 
	return 0;
}
template <typename TPoint>
LONG CSgLineT<TPoint>::FromShape(void*sh){
	return 0;
}
template <typename TPoint>
LONG CSgPointT<TPoint>::ToShape(void*sh,SG_UCHAR ft){ 
	return 0;
}
template <typename TPoint>
LONG CSgLineT<TPoint>::ToShape(void*sh,SG_UCHAR ft){
	return 0;
}
#endif
*/
#ifdef WIN32
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ CSgPointT<SgPoint>;
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ CSgLineT<SgPoint>;
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ CSgPointT<Sg3DPoint>;
_TEMPLATE_EXPORT_ template class _DATASET_DLL_EXPORT_ CSgLineT<Sg3DPoint>;
#endif
//
typedef	SgPoint CDPoint;
typedef CSgPointT<SgPoint> CSgPoint;
typedef CSgLineT<SgPoint>  CSgLine;
typedef CSgPointT<Sg3DPoint> CSg3DPoint;
typedef CSgLineT<Sg3DPoint>  CSg3DLine;

#endif
