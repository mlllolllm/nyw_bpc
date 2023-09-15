//==================================================================================================
//
//
//
//
//
//
//==================================================================================================
#ifndef __DATA_PROCESS_SERVER_COMMAND_DECLARE_HEADER__
#define __DATA_PROCESS_SERVER_COMMAND_DECLARE_HEADER__

//==================================================================================================
#pragma once

#include "NetCommand.h"

//==================================================================================================
struct CDPS_Header
{
	//----------------------------------------------------------------------------------------------
	template< typename T > int Put( ACE_Message_Block & Message , T & Value )
	{
		ACE_OS::memcpy( Message.wr_ptr( ) , & Value , sizeof( T ) );
		Message.wr_ptr( sizeof( T ) );
		return 0;
	}

	template< typename T > int Get( ACE_Message_Block & Message , T & Value )
	{
		ACE_OS::memcpy( & Value , Message.rd_ptr( ) , sizeof( T ) );
		Message.rd_ptr( sizeof( T ) );
		return 0;
	}

	//----------------------------------------------------------------------------------------------
	int Get( ACE_Message_Block & Message , CSgString & Value );
	
	//----------------------------------------------------------------------------------------------
	int Load( ACE_Message_Block & Message );
	int Save( ACE_Message_Block & Message );

	//----------------------------------------------------------------------------------------------
	virtual size_t Length( ) const ;
};

//==================================================================================================
//	遥控、遥调等命令下发操作
struct CDPS_Operator_Req : public CDPS_Header
{
	ACE_UINT16	Operation;	//	0: 无效 1：遥控 2：遥调
	ACE_UINT16	OperType;	//	0：直接执行 1：预置（选择） 2：执行 3：取消	
	ACE_UINT32	ObjType;	//	
	ACE_UINT32	ObjID;		//	
	SG_DOUBLE	Value;		//	

	//----------------------------------------------------------------------------------------------
	CDPS_Operator_Req( ACE_UINT16 Operation = 1 , ACE_UINT16 OperType = 0 );
	int Save( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};

struct CDPS_Operator_Res : public CDPS_Header
{
	ACE_UINT32	ErrorCode;
	CSgString	Exception;

	//----------------------------------------------------------------------------------------------
	int Load( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};


//==================================================================================================
//	遥测、遥信设置
struct CDPS_SetValue_Req : public CDPS_Header
{
	SG_USHORT	OperType;	//	0：设置 1：锁定 2：解锁	
	ACE_UINT32	ObjType;	//	
	ACE_UINT32	ObjID;		//	
	SG_DOUBLE	Value;		//	

	//----------------------------------------------------------------------------------------------
	int Save( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};

struct CDPS_SetValue_Res : public CDPS_Header
{
	ACE_UINT32	ErrorCode;
	CSgString	Exception;

	//----------------------------------------------------------------------------------------------
	int Load( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};
//==================================================================================================
//	生实时数据传输
struct CDPS_SendRawRtDat_Req : public CDPS_Header
{
	ACE_UINT32	ObjType;	//	500：yc 501：yx 502：kwh
	CSgDataSet  DatSet;		//  数据集，  YC包含字段:ID VALUE STATUS PROCTIME 
										//YX包含字段:ID VALUE STATUS PROCTIME MS
										//KWH包含字段:ID VALUE MARKVALUE STATUS PROCTIME MARKPROCTIME
	CSgDataSet  *pDatSet;	//
	//----------------------------------------------------------------------------------------------
	CDPS_SendRawRtDat_Req();
	int Save( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};

struct CDPS_SendRawRtDat_Res : public CDPS_Header
{
	ACE_UINT32	ErrorCode;
	CSgString	Exception;

	//----------------------------------------------------------------------------------------------
	int Load( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};
//==================================================================================================
//	历史数据传输
struct CDPS_SendHisDat_Req : public CDPS_Header
{
	ACE_UINT32	ObjType;	//	500：yc 501：yx 502：kwh
	ACE_UINT32	TaskID;
	CSgDataSet  DatSet;		//  数据集，  包含字段:ID YMD,HMS,FLAG,STATUS,VALUE
	CSgDataSet  *pDatSet;	//
		//----------------------------------------------------------------------------------------------
	CDPS_SendHisDat_Req();
	int Save( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};


struct CDPS_SendHisDat_Res : public CDPS_Header
{
	ACE_UINT32	ErrorCode;
	CSgString	Exception;

	//----------------------------------------------------------------------------------------------
	int Load( ACE_Message_Block & Message );
	virtual size_t Length( ) const ;
};


//==================================================================================================
//	根据定义要求决定是否将函数实现内联
#if !defined ( __DPS_INCLUDE_CPP__ )
#include "command/DPS_Command.inl"
#endif /* __DPS_INCLUDE_CPP__ */

//==================================================================================================

#endif//__DATA_PROCESS_SERVER_COMMAND_DECLARE_HEADER__
