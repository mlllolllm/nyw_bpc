#ifndef __SMART_GRID_TECHNOCHOGY_NETWORK_COMMAND_HELPER_MACRO_DEFINE_VERSION_01_000_0000_HEADER__
#define __SMART_GRID_TECHNOCHOGY_NETWORK_COMMAND_HELPER_MACRO_DEFINE_VERSION_01_000_0000_HEADER__

#pragma once

#include <vector>
#include <algorithm>

//==================================================================================================
// 计算大小的辅助宏
#define STR_SIZE( x ) (sizeof( SG_UINT ) + x.length())
#define BUF_SIZE( i , s , c ) (sizeof(SG_UINT) * i + sizeof(SG_SHORT) * s + sizeof(SG_CHAR) * c)
#define BUF_BASE( b ) b::buf_size()
#define OBJ_SIZE( o ) o.buf_size()

//==================================================================================================
// 序列号辅助宏
#define SERIALIZE_OBJECT( ar , obj ) obj.Serialize(ar);
#define SERIALIZE_PARENT( ar , cls ) cls::Serialize(ar);
#define SERIALIZE_MEMBER( ar , num ) if( ar.IsLoading() ){ ar >> num ; }else{ ar << num; }
#define SERIALIZE_BINARY( ar , dat , len ) if( ar.IsLoading() ){ ar.Read(dat,(len)) }else{ ar.Write(dat,(len)); }
#define SERIALIZE_RETURN( ar , err ) if( ar.IsLoading() ){ if( CNetResponse::err ) return false; }

//==================================================================================================
// 定义规划信息系统中的通用结构定义，请注意
template< typename T > struct NET_CMD_ARRAY : public std::vector< T >
{
	inline int buf_size()
	{
		return sizeof( ACE_UINT32 ) + sizeof( T ) * (int)this->size() ;
	}

	inline void Serialize( CSgArchive & ar )
	{
		if( ar.IsLoading() )
		{
			ACE_UINT32 nCount; ar >> nCount; this->reserve( nCount );
			for( ACE_UINT32 i = 0 ; i < nCount ; i ++ )
			{
				T var; ar >> var; this->push_back( var );
			}
		}
		else
		{
			ACE_UINT32 nCount = static_cast< ACE_UINT32 >( this->size() );
			
			ar << nCount;
			for( ACE_UINT32 i = 0 ; i < nCount ; i ++ )
			{
				//T var = at(i); 
				ar << this->at(i);
			}
		}
	}

	// 默认构造函数
	inline NET_CMD_ARRAY( ) { this->clear(); }

	//	复制构造函数
	inline NET_CMD_ARRAY( const NET_CMD_ARRAY & rhs )
	{
		this->assign( rhs.begin() , rhs.end() );
	}

	//	重载赋值操作符
	inline NET_CMD_ARRAY & operator = ( const NET_CMD_ARRAY & rhs )
	{
		if( & rhs != this ){ this->assign( rhs.begin() , rhs.end() ); }
		return * this;
	}

	//	重载比较操作符
	inline bool operator == ( const NET_CMD_ARRAY & rhs ) const
	{
		if( & rhs == this ) return true;
		if( this->size() != rhs.size() ) return false;
		return std::mismatch( this->begin() , this->end() , rhs.begin() ).first == this->end();
	}
};

//==================================================================================================
// 实现 ARR_UINT32 的基础序列化函数
struct ARR_UINT16 : public NET_CMD_ARRAY< ACE_UINT16 > { };
struct ARR_UINT32 : public NET_CMD_ARRAY< ACE_UINT32 > { };
struct ARR_UINT64 : public NET_CMD_ARRAY< ACE_UINT64 > { };

#endif//__SMART_GRID_TECHNOCHOGY_NETWORK_COMMAND_HELPER_MACRO_DEFINE_VERSION_01_000_0000_HEADER__