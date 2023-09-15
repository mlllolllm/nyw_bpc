//==================================================================================================
//  Summary:
//      Include ADAPTIVE Communication Environment Headers and Automic import library
//  
//  Comment:
//      <1> This header will be used for ADAPTIVE Communication Environment
//  ---------------------------------------------------------------------------------------------
//  Author: Arctos                      Version : 5.8.1                         Date: 2009-11-11
//==================================================================================================

#ifndef __THIRDPARTY_ADAPTIVE_COMMUNICATION_ENVIRONMENT_COMMON_HEADERS__
#define __THIRDPARTY_ADAPTIVE_COMMUNICATION_ENVIRONMENT_COMMON_HEADERS__

//==================================================================================================
//  Push current warning state on windows platform
#if defined( _MSC_VER ) && defined( _WIN32 )
#   pragma warning( push , 3 )
#   include <Win_Versions.h>
#endif /* _MSC_VER && _WIN32 */

//==================================================================================================
//	Include Standard Template Library Headers
#include <STL_Includes.h>

//==================================================================================================
//  ACE OS API Wrapper ( OS API Adapter )
#include <ace/ACE.h>
#include <ace/OS.h>

//==================================================================================================
//  ACE Codecs ( Only BASE64 )
#include <ace/Codecs.h>

//==================================================================================================
//  ACE CDR ( Common Data Stream Input / Output )
#include <ace/CDR_Stream.h>

//==================================================================================================
//  Containers
#include <ace/Array.h>
#include <ace/Containers.h>
#include <ace/Hash_Map_Manager.h>
#include <ace/Filecache.h>
#include <ace/Free_List.h>
#include <ace/Managed_Object.h>
#include <ace/Map_Manager.h>
#include <ace/Object_Manager.h>
#include <ace/SString.h>

//==================================================================================================
//  Concurrency
#include <ace/Activation_Queue.h>
#include <ace/Future.h>
#include <ace/Method_Request.h>
#include <ace/Process.h>
#include <ace/Process_Manager.h>
#include <ace/Sched_Params.h>
#include <ace/Synch.h>
#include <ace/Synch_Options.h>
#include <ace/Synch_T.h>
#include <ace/Thread.h>
#include <ace/Thread_Manager.h>
#include <ace/Token.h>

//==================================================================================================
//  Configuration
#include <ace/Configuration_Import_Export.h>

//==================================================================================================
//  IPC_SAP ( Addr / FIFO_SAP / SOCK_SAP / SPIPE_SAP / UPIPE_SAP / Misc ) ( TLI & LSOCK Removed )
#include <ace/FIFO_Recv_Msg.h>
#include <ace/FIFO_Send_Msg.h>

#include <ace/SOCK_CODgram.h>
#include <ace/SOCK_Dgram_Bcast.h>
#include <ace/SOCK_Dgram_Mcast.h>

#include <ace/SPIPE_Acceptor.h>
#include <ace/SPIPE_Connector.h>

#include <ace/UPIPE_Acceptor.h>
#include <ace/UPIPE_Connector.h>

#include <ace/MEM_Acceptor.h>
#include <ace/MEM_Connector.h>

#include <ace/IOStream.h>
#include <ace/Signal.h>
#include <ace/Pipe.h>

//==================================================================================================
//  Connection
#include <ace/Acceptor.h>
#include <ace/Asynch_Acceptor.h>
#include <ace/Asynch_IO.h>
#include <ace/Connector.h>
#include <ace/Dynamic_Service.h>
#include <ace/Strategies.h>
#include <ace/Strategies_T.h>
#include <ace/Svc_Handler.h>

//==================================================================================================
//  IO_SAP ( DEV_SAP / FILE_SAP ) 
#include <ace/DEV_Connector.h>
#include <ace/FILE_Connector.h>
#include <ace/Ping_Socket.h>
#include <ace/TTY_IO.h>

//==================================================================================================
//  Logging & Tracing
#include <ace/Dump.h>
#include <ace/Dump_T.h>
#include <ace/Log_Msg.h>
#include <ace/Log_Priority.h>
#include <ace/Log_Msg_Backend.h>
#include <ace/Log_Record.h>
#include <ace/Trace.h>

//==================================================================================================
//  Memory ( Mem_Map / Shared_Malloc / Shared_Memory )
#include <ace/Malloc_T.h>
#include <ace/Memory_Pool.h>
#include <ace/Shared_Memory_MM.h>
#include <ace/Shared_Memory_SV.h>

//==================================================================================================
//  Utils
#include <ace/Obstack.h>
#include <ace/Read_Buffer.h>

//==================================================================================================
//  Misc
#include <ace/ARGV.h>
#include <ace/Auto_Ptr.h>
#include <ace/Date_Time.h>
#include <ace/Dynamic.h>
#include <ace/Get_Opt.h>
#include <ace/Registry.h>
#include <ace/Singleton.h>
#include <ace/System_Time.h>

//==================================================================================================
//  Name_Service
#include <ace/Local_Name_Space.h>
#include <ace/Local_Name_Space_T.h>
#include <ace/Name_Proxy.h>
#include <ace/Name_Request_Reply.h>
#include <ace/Name_Space.h>
#include <ace/Naming_Context.h>
#include <ace/Registry_Name_Space.h>
#include <ace/Remote_Name_Space.h>

//==================================================================================================
//  Reactor & Proactor
#include <ace/Event_Handler_T.h>
#include <ace/Handle_Set.h>
#include <ace/Priority_Reactor.h>
#include <ace/Proactor.h>
#include <ace/Reactor.h>
#include <ace/TP_Reactor.h>

//==================================================================================================
//  Service_Configurator
#include <ace/DLL.h>
#include <ace/Parse_Node.h>
#include <ace/Service_Config.h>
#include <ace/Service_Manager.h>
#include <ace/Service_Object.h>
#include <ace/Service_Repository.h>
#include <ace/Service_Types.h>
#include <ace/Shared_Object.h>
#include <ace/Svc_Conf.h>
#include <ace/Svc_Conf_Tokens.h>

//==================================================================================================
//  Streams
#include <ace/IO_Cntl_Msg.h>
#include <ace/Message_Queue_T.h>
#include <ace/Module.h>
#include <ace/Stream.h>
#include <ace/Stream_Modules.h>
#include <ace/Task_T.h>

//==================================================================================================
//  Timers
#include <ace/Profile_Timer.h>
#include <ace/Time_Value.h>
#include <ace/Timer_Hash.h>
#include <ace/Timer_Heap.h>
#include <ace/Timer_List.h>
#include <ace/Timer_Queue.h>
#include <ace/Timer_Queue_Adapters.h>
#include <ace/Timer_Wheel.h>

//==================================================================================================
//  Token_Service
#include <ace/Remote_Tokens.h>
#include <ace/Token_Collection.h>
#include <ace/Token_Manager.h>
#include <ace/Token_Request_Reply.h>
#include <ace/Token_Invariants.h>

//==================================================================================================
//  standalones
#include <ace/Vector_T.h>
#include <ace/Dirent.h>
#include <ace/UUID.h>

//==================================================================================================
//  Pops the last warning state on windows platform
#if defined( _MSC_VER ) && defined( _WIN32 )
#   pragma warning( pop )
#endif /* _MSC_VER && _WIN32 */

//==================================================================================================
//  Auto Import "ADAPTIVE Communication Environment" library with "Suffix"
#if defined( _MSC_VER ) && ! defined( _NOT_AUTO_IMPORT_ACE_LIBRARY_ )

#  include "Auto_Libraries.h"

#  if defined( ACE_AS_STATIC_LIBS )
#    define ACE_LIBRARY LIBRARY_STATIC_CRM( "ACE" )
#    define ACE_LINKAGE LIB_STATIC_LINKAGE
#  else
#    define ACE_LIBRARY LIBRARY_SHARED_CRM( "ACE" )
#    define ACE_LINKAGE LIB_SHARED_LINKAGE
#  endif

#  pragma message( LIB_IMPORT_MESSAGE ACE_LIBRARY ACE_LINKAGE )
#  pragma comment( lib , ACE_LIBRARY LIB_IMPORT_LINKAGE )

#endif /* _MSC_VER && ! _NOT_AUTO_IMPORT_ACE_LIBRARY_ */

//==================================================================================================
#endif /* __THIRDPARTY_ADAPTIVE_COMMUNICATION_ENVIRONMENT_COMMON_HEADERS__ */
