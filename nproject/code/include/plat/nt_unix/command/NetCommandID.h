
#ifndef _NETCOMMANDID_H_
#define _NETCOMMANDID_H_
namespace NetCommand
{
	enum DBCommandID	
	{
		SRVCMD_Stop						=	0,
		DBCMD_StartID					=	1,
		DBCMD_ReadRecorder				=	DBCMD_StartID+0,
		DBCMD_InsertRecorder			=	DBCMD_StartID+1,
		DBCMD_UpdateRecorder			=	DBCMD_StartID+2,
		DBCMD_DeleteRecorder			=	DBCMD_StartID+3,
		DBCMD_ExecSQL					=	DBCMD_StartID+4,
		DBCMD_MergeRecorder				=	DBCMD_StartID+5,
		DBCMD_TransOper					=	DBCMD_StartID+6,
		DBCMD_ReadLobField				=	DBCMD_StartID+7,
		DBCMD_WriteLobField				=	DBCMD_StartID+8,
		DBCMD_GetSysDate				=	DBCMD_StartID+9,
		DBCMD_GetIDVal					=	DBCMD_StartID+10,
		DBCMD_ReadLobRecorder			=	DBCMD_StartID+11,
		DBCMD_InsertLobRecorder			=	DBCMD_StartID+12,
		DBCMD_UpdateLobRecorder			=	DBCMD_StartID+13,
		DBCMD_MergeLobRecorder			=	DBCMD_StartID+14,
		DBCMD_ReadGeoRecorder			=	DBCMD_StartID+15,
		DBCMD_InsertGeoRecorder			=	DBCMD_StartID+16,
		DBCMD_UpdateGeoRecorder			=	DBCMD_StartID+17,
		DBCMD_MergeGeoRecorder			=	DBCMD_StartID+18,
		DBCMD_GetSDEOwner				=	DBCMD_StartID+19,
		DBCMD_Geo_Overlay				=	DBCMD_StartID+20,
		DBCMD_Geo_CalGeoBuffer			=	DBCMD_StartID+21,
		DBCMD_MultiDBTransOper			=	DBCMD_StartID+22,
		DBCMD_Geo_CalLineGeoBuffer		=	DBCMD_StartID+23,
		DBCMD_ReadTableNames			=	DBCMD_StartID+24,
		DBCMD_CreateTable				=	DBCMD_StartID+25,
		DBCMD_File_Upload				=	DBCMD_StartID+26,
		DBCMD_File_Download				=	DBCMD_StartID+27,
		DBCMD_File_Remove				=	DBCMD_StartID+28,
		DBCMD_GetFileInfo				=	DBCMD_StartID+29,
		DBCMD_GetFileName				=	DBCMD_StartID+30,
		DBCMD_ExecSQL_NotTrigger		=	DBCMD_StartID+31,
		DBCMD_BatchReadRecorder			=	DBCMD_StartID+32,
		DBCMD_GetIDVal_New				=	DBCMD_StartID+33,
		DBCMD_GetDBType					=	DBCMD_StartID+34,
		DBCMD_GetDBLinkStat				=	DBCMD_StartID+35,
		DBCMD_CompileReadRecorder		=	DBCMD_StartID+36,
		DBCMD_CompileReadLobRecorder	=	DBCMD_StartID+37,
		DBCMD_CompileExecSQL				=	DBCMD_StartID+38,
		DBCMD_ReadVerRecorder			= DBCMD_StartID + 39,
		DBCMD_InsertVerRecorder = DBCMD_StartID + 40,
		DBCMD_UpdateVerRecorder = DBCMD_StartID + 41,
		DBCMD_MergeVerRecorder = DBCMD_StartID + 42,
		DBCMD_DeleteVerRecorder = DBCMD_StartID + 43,
		DBCMD_CommitDatVer2BaseVer = DBCMD_StartID + 44, //提交到基版本
		DBCMD_RollBackDatVer = DBCMD_StartID + 45, //删除一个版本
		DBCMD_CompareDatVer = DBCMD_StartID + 46, //版本比较
		DBCMD_CopyDatVer = DBCMD_StartID + 47, //版本拷贝
		DBCMD_MultiDBTransVerOper = DBCMD_StartID + 48, //批提交版本数据
		DBCMD_ReadTableInfo = DBCMD_StartID + 49, 
		DBCMD_EndID						=	200,
	};
	enum HSDACommandID	
	{
		HSDACMD_StartID					=	201,
		HSDACMD_ReadRecorder			=	HSDACMD_StartID+0,
		HSDACMD_ReadTblRecorder			=	HSDACMD_StartID+1,
		HSDACMD_ExecSQL					=	HSDACMD_StartID+2,
		HSDACMD_SendStreamProc          =	HSDACMD_StartID+20,
		HSDACMD_UpdateRecorder			=	HSDACMD_StartID+25,
		HSDACMD_SubscribeData			=	HSDACMD_StartID+33,
		HSDACMD_CancelSubscribe			=	HSDACMD_StartID+34,
		HSDACMD_GetChangeData			=	HSDACMD_StartID+35,
		HSDACMD_OperRDBMem				=  HSDACMD_StartID + 36,
		HSDACMD_InsertRecorder			= HSDACMD_StartID +37,
		HSDACMD_DeleteRecorder			= HSDACMD_StartID + 38,
		HSDACMD_NewCCRtDB					= HSDACMD_StartID + 39,
		HSDACMD_DeleteCCRtDB				= HSDACMD_StartID + 40,
		HSDACMD_GetNewShcemaHandler = HSDACMD_StartID + 41,
		HSDACMD_EndID					=	400,
	};
	enum TSDACommandID	
	{
		TSDACMD_StartID						=	401,
		TSDACMD_QueryDataByPoint			=	TSDACMD_StartID+0,
		TSDACMD_QueryStatByPoint			=	TSDACMD_StartID+1,
		TSDACMD_QueryDataByDevice			=	TSDACMD_StartID+2,
		TSDACMD_QueryStatByDevice			=	TSDACMD_StartID+3,
		TSDACMD_QueryValuesByPoint			=	TSDACMD_StartID+4,
		TSDACMD_QueryValuesByDevice			=	TSDACMD_StartID+5,
		TSDACMD_SaveDataByPoint				=	TSDACMD_StartID+6,
		TSDACMD_SaveDataByDevice			=	TSDACMD_StartID+7,
		TSDACMD_DeleteDataByPoint			=	TSDACMD_StartID+8,
		TSDACMD_DeleteDataByDevice			=	TSDACMD_StartID+9,
		TSDACMD_ProcOver					=	TSDACMD_StartID+10,
		TSDACMD_Notify						=	TSDACMD_StartID+11,
		TSDACMD_QueryDataByPoint_New		=	TSDACMD_StartID+12,
		TSDACMD_QueryDataByDevice_New		=	TSDACMD_StartID+13,
		TSDACMD_QueryDataByPoint_Append		=	TSDACMD_StartID+14,
		TSDACMD_GetDBLinkStat				=	TSDACMD_StartID+15,
		TSDACMD_QueryDataByDevice_Append	= TSDACMD_StartID + 16,
		TSDACMD_EndID						=	600,
	};
	enum DataServerCommandID
	{
		DPSCMD_StartID						=	601,
		DPSCMD_GetMiniBoxLinkNode			=	DPSCMD_StartID+0,
		DPSCMD_Operator						=	DPSCMD_StartID+1,
		DPSCMD_SetValue						=	DPSCMD_StartID+2,
		DPSCMD_MiniBox_LinkCmd				=	DPSCMD_StartID+5,
		DPSCMD_MiniBox_CommSrvCmd			=	DPSCMD_StartID+6,
		DPSCMD_MiniBox_Operator				=	DPSCMD_StartID+7,
		DPSCMD_MiniBox_UpdateRecorder		=	DPSCMD_StartID+10,
		DPSCMD_MiniBox_MultiDBTransOper		=	DPSCMD_StartID+12,
		DPSCMD_MiniBox_ExeShellCmd			=	DPSCMD_StartID+14,
		DPSCMD_Login_New					=	DPSCMD_StartID+30,
		DPSCMD_UnLogin_New					=	DPSCMD_StartID+31,
		DPSCMD_Operator_New					=	DPSCMD_StartID+32,
		DPSCMD_SetValue_New					=	DPSCMD_StartID+33,
		DPSCMD_RawRtDat_New					=	DPSCMD_StartID+34,
		DPSCMD_RawHisDat_New				=	DPSCMD_StartID+35,
		DPSCMD_CommSrvCmd					=	DPSCMD_StartID+36,
		DPSCMD_RawRtDat_FertSend			=	DPSCMD_StartID+37,
		DPSCMD_RawHisDat_FertSend			=	DPSCMD_StartID+38,
		DPSCMD_RawEvt_FertSend				=	DPSCMD_StartID+39,
		DPSCMD_UpdateRecorder2MiniBox		=	DPSCMD_StartID+40,
		DPSCMD_MultiDBTransOper2MiniBox		=	DPSCMD_StartID+41,
		DPSCMD_RawSendFile					=	DPSCMD_StartID+42,
		DPSCMD_RawSendFile_FertSend			=	DPSCMD_StartID+43,
		DPSCMD_CommSrvCmd_New				=	DPSCMD_StartID+44,
		DPSCMD_MiniBox_CommSrvCmd_New		=	DPSCMD_StartID+46,
		DPSCMD_ExeShellCmd2MiniBox			=	DPSCMD_StartID+47,
		DPSCMD_SendMiniBoxACmd				=	DPSCMD_StartID+48,
		DPSCMD_EndID						=	680,
	};
	enum CommServerCommandID
	{
		CommCMD_StartID						=	681,
		CommCMD_Operator					=	CommCMD_StartID+1,
		CommCMD_WriteProtSetting			=	CommCMD_StartID+2,
		CommCMD_ReadProtSetting				=	CommCMD_StartID+3,
		CommCMD_ReadHisDat					=	CommCMD_StartID+4,
		CommCMD_TaskCmd						=	CommCMD_StartID+5,
		CommCMD_TaskCmd_New					=	CommCMD_StartID+6,
		CommCMD_EndID						=	700,
	};
	enum FileServerCommandID
	{
		FPSCMD_StartID						=	701,
		FPSCMD_Download						=	FPSCMD_StartID + 1,
		FPSCMD_Publish						=	FPSCMD_StartID + 2,
		FPSCMD_EndID						=	800,
	};
	enum CpsCommandID
	{
		CPSCMD_StartID						=	801,
		CPSCMD_ProcOver						=	CPSCMD_StartID+0,
		CPSCMD_Notify						=	CPSCMD_StartID+1,
		CPSCMD_QueryRealEvtWritePt			=	CPSCMD_StartID+2,
		CPSCMD_QueryRealEvt					=	CPSCMD_StartID+3,
		CPSCMD_ConfirmRealEvt				=	CPSCMD_StartID+4,
		CPSCMD_GetCenterID					=	CPSCMD_StartID+5,
		CPSCMD_GetLinkNum					=	CPSCMD_StartID+6,
		CPSCMD_EndID						=	900,
	};
	enum PCMCommandID
	{
		PCMCMD_StartID						=	901,
		PCMCMD_StartProc					=	PCMCMD_StartID+0,//启动进程命令
		PCMCMD_EndProc						=	PCMCMD_StartID+1,//停止进程命令
		PCMCMD_AskStatus					=	PCMCMD_StartID+2,//查询进程状态命令
		PCMCMD_AskSysEnvPath				=	PCMCMD_StartID+3,//查询系统运行目录
		PCMCMD_AskPathFileInfo				=	PCMCMD_StartID+4,//查询目录下的文件信息
		PCMCMD_FileOper						=	PCMCMD_StartID+5,//文件操作函数
		PCMCMD_DownLoad						=	PCMCMD_StartID+6,//文件上载
		PCMCMD_UpLoad						=	PCMCMD_StartID+7,//文件下载
		PCMCMD_RestartSrv					=	PCMCMD_StartID+8,//重启服务进程
		PCMCMD_ShellCmd						=	PCMCMD_StartID+9,//执行终端上的命令
		PCMCMD_GetFileInfo					=	PCMCMD_StartID+11,//获取文件信息
		PCMCMD_SETTIME					    =	PCMCMD_StartID + 14,//设置时间
		PCMCMD_StartCalcProc				 =	PCMCMD_StartID + 15,//启动计算进程
		PCMCMD_AskCalcProcState				= PCMCMD_StartID + 16,//查询计算进程状态
		PCMCMD_EndID						=	950,
	};
	enum REPCommandID
	{
		REPCMD_StartID					=	951,
		REPCMD_GetLogicCellVer			=	REPCMD_StartID+0,
		REPCMD_GetLogicCellDat			=	REPCMD_StartID+1,
		REPCMD_EndID					=	970,
	};
	enum EventCommandID
	{
		EVTCMD_StartID					=	971,
		EVTCMD_SendRawEvt				=	REPCMD_StartID+0,
		EVTCMD_EndID					=	975,
	};

	enum IDMapCommandID
	{
		IDMAPCMD_StartID					=	1001,
		IDMAPCMD_Self2Other					=	IDMAPCMD_StartID+0,
		IDMAPCMD_Other2Self					=	IDMAPCMD_StartID+1,
		IDMAPCMD_EndID						=	1010,
	};
	enum TopoSrvCommandID
	{
		TOPOSRVCMD_StartID					=	1011,
		TOPOSRVCMD_Notify					=	TOPOSRVCMD_StartID+0,
		TOPOSRVCMD_ProcOver					=	TOPOSRVCMD_StartID+1,
		TOPOSRVCMD_EndID						=	1060,
	};
	enum MiniBoxManCommandID
	{
		MINIBOXMANCMD_StartID					=	1061,
		MINIBOXMANCMD_Login						=	MINIBOXMANCMD_StartID+0,
		MINIBOXMANCMD_SendACmd					=	MINIBOXMANCMD_StartID+1,
		MINIBOXMANCMD_ProcOver					=	MINIBOXMANCMD_StartID+2,
		MINIBOXMANCMD_GetLinkNodeID				=	MINIBOXMANCMD_StartID+3,
		MINIBOXMANCMD_SendBoxStatus				=	MINIBOXMANCMD_StartID+4,
		MINIBOXMANCMD_SendHearBeat				=	MINIBOXMANCMD_StartID+5,
		MINIBOXMANCMD_SendBoxDiskStatus			=	MINIBOXMANCMD_StartID+6,
		MINIBOXMANCMD_EndID						=	1070,
	};
	enum GapCommCommandID
	{
		GAPCOMMCMD_StartID = 1091,
		GAPCOMMCMD_ProcOver = GAPCOMMCMD_StartID + 0,	//处理完成
		GAPCOMMCMD_NetRecv	 = GAPCOMMCMD_StartID + 2,	//网络接收
		GAPCOMMCMD_PassThrough = GAPCOMMCMD_StartID + 1,	//透明传输
		GAPCOMMCMD_EndID = 1095,
	};
	enum SGNetCommandID
	{
		SGNETCMD_HeartBeat							= 1100,
	};
	enum DBSCommandID
	{
		DBSCMD_SyncOneTable						=	1,
		DBSCMD_SyncAllTables					=	2,
		DBSCMD_SyncOneScrip						=	3,
		DBSCMD_SyncAllScrip						=	4
	};

	enum MSGCommandID
	{
		MSGCMD_Post								=10000
	};
	enum GDBCommandID	
	{
		GDBCMD_StartID							= 20000,	//
		GDBCMD_EndID							= 30000,	//
	};
	enum DA_CMD
	{
		dacmd_invalid			=GDBCMD_StartID+0,
		/*
		 *	SDE的访问代理命令【1~30】
		 */
		readRecordAsNormal_sde	=GDBCMD_StartID+1,
		//getRecordNums_sde		=GDBCMD_StartID+2,
		readRecorder_sde		=GDBCMD_StartID+3,
		startTrans_sde			=GDBCMD_StartID+4,
		commitTrans_sde			=GDBCMD_StartID+5,
		rollbackTrans_sde		=GDBCMD_StartID+6,
		insertRecord_sde		=GDBCMD_StartID+7,
		updateRecord_sde		=GDBCMD_StartID+8,
		deleteRecord_sde		=GDBCMD_StartID+9,
		execute_sde				=GDBCMD_StartID+10,
		getSdeLayers			=GDBCMD_StartID+11,
		SDE_MAX_ID				=GDBCMD_StartID+30,
		/*
		 *	商用数据库的访问代理命令【31~50】
		 */
		 DBF_MIN_ID				=GDBCMD_StartID+31,
		//getFieldsName			=GDBCMD_StartID+31,
		//readTableInfo			=GDBCMD_StartID+32,
		readRecord				=GDBCMD_StartID+33,
		sqlReadRecord			=GDBCMD_StartID+34,
		updateRecord			=GDBCMD_StartID+35,
		deleteRecord			=GDBCMD_StartID+36,
		insertRecord			=GDBCMD_StartID+37,
		execute					=GDBCMD_StartID+38,
		startTrans				=GDBCMD_StartID+39,
		commitTrans				=GDBCMD_StartID+40,
		rollbackTrans			=GDBCMD_StartID+41,
		DBF_MAX_ID				=GDBCMD_StartID+50,
		/*
		 *	gdb对象属性的获得,对象增删修改,短事务操作【100~109】
		 */
		 GDB_OBJ_MIN_ID			=GDBCMD_StartID+100,
		readObjTableInfo		=GDBCMD_StartID+105,
		readObjAttrib_Oracle	=GDBCMD_StartID+106,
		GDB_OBJ_MAX_ID			=GDBCMD_StartID+109,
		/*
		 *	空间引擎属性获得命令【110~125】
		 */
		 GDB_ATTRIB_MIN_ID		=GDBCMD_StartID+110,
		getGdbName				=GDBCMD_StartID+110,	//空间引擎号和名称
		getMapExtend			=GDBCMD_StartID+111,	//空间引擎器管理的几何范围
		getFeatureLine			=GDBCMD_StartID+115,
		getFeatureStation		=GDBCMD_StartID+116,
		//
		getGdbObjsInfo			=GDBCMD_StartID+121,
		getDataSetContent		=GDBCMD_StartID+122,
		getGeoDataSetContent	=GDBCMD_StartID+123,
		getGeoDataSetUseSql		=GDBCMD_StartID+124,
		getMultiGeoDataSet		=GDBCMD_StartID+125,
		GDB_ATTRIB_MAX_ID		=GDBCMD_StartID+125,
		/*
		 *	杂乱命令【126~139】
		 */
		 NOT_RULE_MIN_ID			=GDBCMD_StartID+126,
		sde_insert				=GDBCMD_StartID+126,
		readSdetable			=GDBCMD_StartID+127,
		sde_overlay             =GDBCMD_StartID+128,
		syncIDChange			=GDBCMD_StartID+129,
		sde_modify				=GDBCMD_StartID+130,
		sde_delete				=GDBCMD_StartID+131,
		comm_trans				=GDBCMD_StartID+132,	//提交一次事务处理
		sde_calbuffer			=GDBCMD_StartID+133,
		sde_calbuffer_mline		=GDBCMD_StartID+134,
		NOT_RULE_MAX_ID			=GDBCMD_StartID+139,
		
		/*
		 *	老实时库命令【200~210】
		 */
		 OLD_RDB_MIN_ID			=GDBCMD_StartID+200,
		update_rdb				=GDBCMD_StartID+200,
		send_event				=GDBCMD_StartID+201,
		update_rdb_by_obj		=GDBCMD_StartID+202,	//根据基础设备类型和ID来更新实时数据
		OLD_RDB_MAX_ID			=GDBCMD_StartID+210,
		/*
		 *	动态加载相关命令【211~220】
		 */
		/************************************************************************/
		/*                                                      */
		/************************************************************************/
		DYNA_LOAD_MIN_ID		=GDBCMD_StartID+211,
		get_fdm_attrib			=GDBCMD_StartID+211,	//获得FDM中的FDU信息
		get_fdu_childobj		=GDBCMD_StartID+212,	//获得FDU中包含的对象信息
		get_fdm_attrib2			=GDBCMD_StartID+213,	//获得FDM信息，PSP中实现
		//
		getCellOverObjGeometry	=GDBCMD_StartID+214,	//获得Cell覆盖的对象几何属性
		getObjGeometry1			=GDBCMD_StartID+215,	//获得对象几何属性用ObjType、OID
		getObjGeometry2			=GDBCMD_StartID+216,	//获得对象几何属性用LocalName、OID
		get_fdu_childobj2		=GDBCMD_StartID+217,	//获得FDU中包含的对象信息,PSP中实现
		DYNA_LOAD_MAX_ID		=GDBCMD_StartID+220,
		/*
		 *	空间引擎维护命令【221~240】
		 */
		 GDB_MAINT_MIN_ID		=GDBCMD_StartID+221,
		getGdbConnection		=GDBCMD_StartID+221,//117,	//获得连接到空间引擎的客户端信息
		killGdbTread			=GDBCMD_StartID+222,//118,	//Kill Gdb_Mail_Handler Thread
		locallib_to_file		=GDBCMD_StartID+223,//133,	//保存到文件
		initGdbPara				=GDBCMD_StartID+224,//120,	//空间引擎参数初始化
		getDbConnectInfo		=GDBCMD_StartID+225,
		GDB_MAINT_MAX_ID		=GDBCMD_StartID+240,
		/*
		 *	本地库检测命令，测试命令【241~270】
		 */
		//空间引擎索引检测命令【子类型号0、1、2、3分别为全部、数据集索引、对象索引、网络拓扑索引】
		GDB_CHECK_MIN_ID		=GDBCMD_StartID+241,
		check_locallib_index	=GDBCMD_StartID+241,
		test_Object_Add			=GDBCMD_StartID+242,
		test_Object_Update		=GDBCMD_StartID+243,
		test_Object_Delete		=GDBCMD_StartID+244,
		NetCommand_Temp_ChildID=GDBCMD_StartID+245,
		NetCommand_Check_Station_Address=GDBCMD_StartID+246,
		NetCommand_Force_Do_Thing=GDBCMD_StartID+247,
		NetCommand_LobReader     = GDBCMD_StartID+248,
		NetCommand_LobWrite      = GDBCMD_StartID+249,
		NetCommand_AskPower      = GDBCMD_StartID+250,
		GDB_CHECK_MAX_ID		=GDBCMD_StartID+270,
		GdbHearbeat				=GDBCMD_StartID+280,			//图形服务心跳
	
		/*
		 *	网络应用服务端命令空间【300~400】
		 */
		NetUseCmdMin			= GDBCMD_StartID+300,	//
		NetUseCmdMax			= GDBCMD_StartID+400,	//

		/*
		 *	新的数据库操作图形服务端命令空间【401~499】
		 */
		GDB_DBCmdMin				=	GDBCMD_StartID+401,	//
		GDB_DBCmdMax				=	GDBCMD_StartID+499,	//
		GDB_DB_ReadRecorder			=	GDB_DBCmdMin+0,
		GDB_DB_InsertRecorder		=	GDB_DBCmdMin+1,
		GDB_DB_UpdateRecorder		=	GDB_DBCmdMin+2,
		GDB_DB_DeleteRecorder		=	GDB_DBCmdMin+3,
		GDB_DB_ExecSQL				=	GDB_DBCmdMin+4,
		GDB_DB_MergeRecorder		=	GDB_DBCmdMin+5,
		GDB_DB_TransOper			=	GDB_DBCmdMin+6,
		GDB_DB_ReadLobField			=	GDB_DBCmdMin+7,
		GDB_DB_WriteLobField		=	GDB_DBCmdMin+8,
		GDB_DB_GetSysDate			=	GDB_DBCmdMin+9,
		GDB_DB_GetIDVal				=	GDB_DBCmdMin+10,
		GDB_DB_ReadLobRecorder		=	GDB_DBCmdMin+11,
		GDB_DB_InsertLobRecorder	=	GDB_DBCmdMin+12,
		GDB_DB_UpdateLobRecorder	=	GDB_DBCmdMin+13,
		GDB_DB_MergeLobRecorder		=	GDB_DBCmdMin+14,
		GDB_DB_ReadGeoRecorder		=	GDB_DBCmdMin+15,
		GDB_DB_InsertGeoRecorder	=	GDB_DBCmdMin+16,
		GDB_DB_UpdateGeoRecorder	=	GDB_DBCmdMin+17,
		GDB_DB_MergeGeoRecorder		=	GDB_DBCmdMin+18,
		GDB_DB_GetSDEOwner			=	GDB_DBCmdMin+19,
		GDB_DB_Geo_Overlay			=	GDB_DBCmdMin+20,
		GDB_DB_Geo_CalGeoBuffer		=	GDB_DBCmdMin+21,
		GDB_DB_MultiDBTransOper		=	GDB_DBCmdMin+22,
		GDB_DB_Geo_CalLineGeoBuffer	=	GDB_DBCmdMin+23,
		GDB_DB_ReadTableNames		=	GDB_DBCmdMin+24,
		GDB_DB_CreateTable			=	GDB_DBCmdMin+25,
			
		GDB_DB_File_Upload			=	GDB_DBCmdMin+26,
		GDB_DB_File_Download		=	GDB_DBCmdMin+27,
		GDB_DB_File_Remove			=	GDB_DBCmdMin+28,
		GDB_DB_GetFileInfo			=	GDB_DBCmdMin+29,
		GDB_DB_GetFileName			=	GDB_DBCmdMin+30,
		GDB_DB_ExecSQL_NotTrigger	=	GDB_DBCmdMin+31,
		GDB_DB_BatchReadRecorder	=	GDB_DBCmdMin+32,
		GDB_DB_GetIDVal_New			=	GDB_DBCmdMin+33,
		GDB_DB_GetDBType			=	GDB_DBCmdMin+34,
 	    GDB_DB_CompileReadRecorder	=	GDB_DBCmdMin+35,
  		GDB_DB_CompileReadLobRecorder=	GDB_DBCmdMin+36,
		GDB_DB_CompileExecSQL	=	GDB_DBCmdMin+37,
		GDB_DB_ReadVerRecorder = GDB_DBCmdMin + 38,
			 GDB_DB_InsertVerRecorder = GDB_DBCmdMin + 39,
			GDB_DB_UpdateVerRecorder = GDB_DBCmdMin + 40,
			GDB_DB_MergeVerRecorder = GDB_DBCmdMin + 41,
			GDB_DB_DeleteVerRecorder = GDB_DBCmdMin + 42,
			GDB_DB_CommitDatVer2BaseVer = GDB_DBCmdMin + 43,
			GDB_DB_RollBackDatVer = GDB_DBCmdMin + 44,
			GDB_DB_CompareDatVer = GDB_DBCmdMin + 45,
			GDB_DB_CopyDatVer = GDB_DBCmdMin + 46,
			GDB_DB_MultiDBTransVerOper = GDB_DBCmdMin + 47,
			GDB_DB_ReadTableInfo = GDB_DBCmdMin + 48,

		 /*
		 *	版本命令【500~600】
		 */
		VerCmdMin					=GDBCMD_StartID+ 500,	//
		VerCmdMax					= GDBCMD_StartID+600,	//

		/*
		*   自动化事件命令【601~610】
		*/
		EvtCmdMin					=GDBCMD_StartID+ 601,	//
		EvtCmdMax					= GDBCMD_StartID+610,	//

		 /*
		 *	文件发布服务命令空间【2000~3000】
		 */

		fCmdMin					=GDBCMD_StartID+ 2000,	//
		fCmdMax					= GDBCMD_StartID+3000,	//
		 	
		/*
		 *	空间引擎端新命令空间【5000~6000】
		 */
		gdbCmdMin				=GDBCMD_StartID+ 5000,
		gdbCmdMax				=GDBCMD_StartID+ 6000,
		/*
		 *	BPA计算服务命令
		 */
		 BPACmdMin				=GDBCMD_StartID+6001,
		 BPACmdMax				=GDBCMD_StartID+6100,

		 /*
		 *	三相不平衡优化服务命令 王勇
		 */
		 UNBALANCECMD_AutoOptimize	=GDBCMD_StartID+7001,
		 UNBALANCECMD_ManualOptimize=GDBCMD_StartID+7100

	};
	enum InitGdb{
		initGdb			=0,
		initObjModel,
		initTableObj,
		initAllObj,
		initGdbBound,
		initSingleObj,
		initAllNotObj,
		initSingleNotObj,
		removeObj,
		removeNotObj,
		changeSrv,
	};
	enum GetGdbObjsInfo{
		getObjsInfo		=	0,
		getMemInfo,
		getDataSetInfo,
		getGeoNetInfo,
		getPipeNetInfo,
		getRoadNetInfo,
		checkLocalLibObjIndex,
		getSrvStatus,		//确定空间引擎是否是异常处理状态,"0","1"
	};
	enum EPCmd
	{
		login		=1,
		changePwd	=2,
		//
		start       =3,
		stop        =4,
		getdb		=5
	};
};

#endif
