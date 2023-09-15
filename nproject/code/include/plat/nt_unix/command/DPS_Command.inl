//==================================================================================================
#include "command/DPS_Command.h"

//==================================================================================================
#ifdef __DPS_INCLUDE_CPP__
#	define DPS_INLINE 
#else
#	define DPS_INLINE inline
#endif

//==================================================================================================
#define DPS_SIZE_H( N ) ( ( N ) * sizeof( ACE_INT64 ) )
#define DPS_SIZE_L( N ) ( ( N ) * sizeof( ACE_INT32 ) )
#define DPS_SIZE_S( N ) ( ( N ) * sizeof( ACE_INT16 ) )
#define DPS_SIZE_B( N ) ( ( N ) * sizeof( ACE_UINT8 ) )

//==================================================================================================
#define DPS_SIZE_HL( H , L ) DPS_SIZE_H( H ) + DPS_SIZE_L( L )
#define DPS_SIZE_SB( S , B ) DPS_SIZE_S( S ) + DPS_SIZE_B( B )

//==================================================================================================
#define DPS_SIZE( H , L , S , B ) DPS_SIZE_HL( H , L ) + DPS_SIZE_SB( S , B )

//==================================================================================================
DPS_INLINE size_t CDPS_Header::Length( ) const { return DPS_SIZE( 0 , 1 , 0 , 1 ); }

//==================================================================================================
DPS_INLINE int CDPS_Header::Get( ACE_Message_Block & Message , CSgString & Value )
{
	ACE_UINT16 Length = 0; if( Get( Message , Length ) < 0 ){ return -1; }
	if( Message.rd_ptr( )[ Length ] != 0 ){ return -1 ; }
	Value = Message.rd_ptr( ); Message.rd_ptr( Length + 1 );	
	return 0 ;
}

//==================================================================================================
DPS_INLINE int CDPS_Header::Save( ACE_Message_Block & Message )
{
	ACE_UINT32 Length = this->Length( );
	int Caller = Message.size( Length );
	if( Caller == -1 ){ return Caller; }

	Message.wr_ptr( Message.base( ) );
	Message.rd_ptr( Message.base( ) );

	ACE_UINT8 Order = 0xF5;
	Put( Message , Length );
	Put( Message , Order );

	return 0;
}

//==================================================================================================
DPS_INLINE int CDPS_Header::Load( ACE_Message_Block & Message )
{
	ACE_UINT32 Length ; ACE_UINT8 Order;
	Get( Message , Length );
	Get( Message , Order );

	return 0;
}

//==================================================================================================
//	遥控、遥调等命令下发操作
DPS_INLINE CDPS_Operator_Req::CDPS_Operator_Req( ACE_UINT16 Operation , ACE_UINT16 OperType )
{
	this->Operation = Operation;  this->OperType = OperType;	
	this->ObjType = 0 ; this->ObjID = 0 ; this->Value = 0 ;			
}

//==================================================================================================
DPS_INLINE int CDPS_Operator_Req::Save( ACE_Message_Block & Message )
{
	CDPS_Header::Save( Message );

	ACE_UINT8 Entry = 0x01;
	Put( Message , Entry );

	Put( Message , Operation );
	Put( Message , OperType );
	Put( Message , ObjType );
	Put( Message , ObjID );
	Put( Message , Value );

	return 0;
}

//==================================================================================================
DPS_INLINE size_t CDPS_Operator_Req::Length( ) const
{
	return CDPS_Header::Length( ) + DPS_SIZE( 1 , 2 , 2 , 1 );
}

//==================================================================================================
DPS_INLINE int CDPS_Operator_Res::Load( ACE_Message_Block & Message )
{
	CDPS_Header::Load( Message );

	Get( Message , ErrorCode );
	Get( Message , Exception );

	return 0;
}

//==================================================================================================
DPS_INLINE size_t CDPS_Operator_Res::Length( ) const
{
	return CDPS_Header::Length( ) + DPS_SIZE( 0 , 1 , 0 , 1 );
}

//==================================================================================================
DPS_INLINE int CDPS_SetValue_Req::Save( ACE_Message_Block & Message )
{
	CDPS_Header::Save( Message );
	
	ACE_UINT8 Entry = 0x02 ;
	Put( Message , Entry );

	Put( Message , OperType );
	Put( Message , ObjType );
	Put( Message , ObjID );
	Put( Message , Value );

	return 0;	
}

//==================================================================================================
DPS_INLINE size_t CDPS_SetValue_Req::Length( ) const
{
	return CDPS_Header::Length( ) + DPS_SIZE( 1 , 2 , 1 , 1 );
}

//==================================================================================================
DPS_INLINE int CDPS_SetValue_Res::Load( ACE_Message_Block & Message )
{
	CDPS_Header::Load( Message );

	Get( Message , ErrorCode );
	Get( Message , Exception );

	return 0;
}

//==================================================================================================
DPS_INLINE size_t CDPS_SetValue_Res::Length( ) const
{
	return CDPS_Header::Length( ) + DPS_SIZE( 0 , 1 , 0 , 1 );
}

//==================================================================================================
