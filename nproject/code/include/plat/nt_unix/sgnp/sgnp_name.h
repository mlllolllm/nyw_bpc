
#ifndef	SGNP_NAME_H
#define	SGNP_NAME_H 


#include "sgnp_base.h"
#include "sgarchive.h"


#define STATIC_NAME_BINDING_SECTION "StaticNbs"
class SGNP_Export NAME_BINDING
{
public:
	enum { unique,mutex,main_n,back_n,static_n }; 

	NAME_BINDING(){ type1_ = unique;type2_ = back_n; }

	ACE_CString name_;
	ACE_CString value_;
	short		type1_;	//unique (type2:static_n),mutex(type2:main;back)
	short		type2_; //main,back
	//
	void serialize(CSgArchive&);
	int buf_size() { return name_.length()+value_.length()+2*sizeof(ACE_UINT32)+2*sizeof(short); }
	//
	void from_pmb(ACE_Message_Block*);
	void to_pmb(ACE_Message_Block*&,int);

};
//typedef list<NAME_BINDING>NAME_BINDINGS;
class  NAME_BINDINGS : public list<NAME_BINDING>
{
public:
	inline void serialize(CSgArchive &ar)
	{
		if(ar.IsLoading())
		{
			list<NAME_BINDING>::clear();
			ACE_UINT32 size =0;
			ar >> size;
			//
			for(ACE_UINT32 i=0;i<size;i++)
			{
				NAME_BINDING nb;
				nb.serialize(ar);
				list<NAME_BINDING>::push_back(nb);
			}
		}
		else
		{
			ACE_UINT32 size = list<NAME_BINDING>::size();
			ar << size;
			for(list<NAME_BINDING>::iterator  itr = list<NAME_BINDING>::begin();itr!=list<NAME_BINDING>::end();itr++)
				itr->serialize(ar);
		}	
	};
};
struct SGNP_Export SG_LINKNODE
{
	SG_Addr			node_addr;
	SG_LINKTYPE		link_type_;
	ACE_CString		link_time_;
	StringArray		mbs_n_;
	StringArray		mbs_i_;
	NAME_BINDINGS   nbs_;
	void serialize(CSgArchive&);
	void decode(const char*buf,ACE_UINT32 len);
};

class   SG_LINKNODES : public  list<SG_LINKNODE>
{
public:
	inline void serialize(CSgArchive &ar)
	{
		if(ar.IsLoading())
		{
			list<SG_LINKNODE>::clear();
			ACE_UINT32 size =0;
			ar >> size;
			//
			for(ACE_UINT32 i=0;i<size;i++)
			{
				SG_LINKNODE node;
				node.serialize(ar);
				list<SG_LINKNODE>::push_back(node);
			}
		}
		else
		{
			ACE_UINT32 size = list<SG_LINKNODE>::size();
			ar << size;
			for(list<SG_LINKNODE>::iterator  itr = list<SG_LINKNODE>::begin();itr!=list<SG_LINKNODE>::end();itr++)
				itr->serialize(ar);
		}
	};
};
//
struct SGNP_Export SG_AGENT_INFO
{
	PROC_INFO proc_info_;
	StringArray arMbs_l_;
	StringArray arMbs_n_;
	StringArray arMbs_i_;
	NAME_BINDINGS nbs_;
	//
	void serialize(CSgArchive&);
};

#endif
