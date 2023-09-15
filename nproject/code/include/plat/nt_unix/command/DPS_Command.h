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
//	ң�ء�ң���������·�����
struct CDPS_Operator_Req : public CDPS_Header
{
	ACE_UINT16	Operation;	//	0: ��Ч 1��ң�� 2��ң��
	ACE_UINT16	OperType;	//	0��ֱ��ִ�� 1��Ԥ�ã�ѡ�� 2��ִ�� 3��ȡ��	
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
//	ң�⡢ң������
struct CDPS_SetValue_Req : public CDPS_Header
{
	SG_USHORT	OperType;	//	0������ 1������ 2������	
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
//	��ʵʱ���ݴ���
struct CDPS_SendRawRtDat_Req : public CDPS_Header
{
	ACE_UINT32	ObjType;	//	500��yc 501��yx 502��kwh
	CSgDataSet  DatSet;		//  ���ݼ���  YC�����ֶ�:ID VALUE STATUS PROCTIME 
										//YX�����ֶ�:ID VALUE STATUS PROCTIME MS
										//KWH�����ֶ�:ID VALUE MARKVALUE STATUS PROCTIME MARKPROCTIME
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
//	��ʷ���ݴ���
struct CDPS_SendHisDat_Req : public CDPS_Header
{
	ACE_UINT32	ObjType;	//	500��yc 501��yx 502��kwh
	ACE_UINT32	TaskID;
	CSgDataSet  DatSet;		//  ���ݼ���  �����ֶ�:ID YMD,HMS,FLAG,STATUS,VALUE
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
//	���ݶ���Ҫ������Ƿ񽫺���ʵ������
#if !defined ( __DPS_INCLUDE_CPP__ )
#include "command/DPS_Command.inl"
#endif /* __DPS_INCLUDE_CPP__ */

//==================================================================================================

#endif//__DATA_PROCESS_SERVER_COMMAND_DECLARE_HEADER__
