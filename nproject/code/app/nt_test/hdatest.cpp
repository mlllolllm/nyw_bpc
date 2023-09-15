#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "dppclient.h"
int TestHDARead(CGAP_HSDASrvClient &Client)
{
  CSgDataSet DatSet;
	CHSDA_ReadRecorder_Req ReadReq;
	CHSDA_ReadRecorder_Res ReadRes;
	ReadReq.SchemaHandler = 1;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select ID,NAME from NET_NODE");
	if (Client.HSDA_ReadRecorder(ReadReq, ReadRes) < 0)
	{
		return false;
	}
	CSgString sgstr;
	SG_INT64 ID;
	for (int i = 0; i < DatSet.GetRecordNums(); i++)
	{
		DatSet.PrintRecord(i); //打印DataSet的内容
		DatSet.GetAt(i, (SG_SHORT)0, &ID);
		DatSet.GetAt(i, (SG_SHORT)1, sgstr);
	}
	return true;
}
//游标方式读数
int TestHDACursorRead(CGAP_HSDASrvClient &Client)
{
	const int MaxRetRcdNum = 100;
	CSgDataSet DatSet;
	CHSDA_ReadRecorder_Req ReadReq;
	CHSDA_ReadRecorder_Res ReadRes;
	ReadReq.SchemaHandler = 1;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select ID,NAME from NET_NODE");
	ReadReq.HeadProcMode = SG_NETCMDHEAD_PROCMOD_USECURSOR;
	ReadReq.MaxRow = MaxRetRcdNum;
	if (Client.HSDA_ReadRecorder(ReadReq, ReadRes) < 0)
	{
		return false;
	}
	int CursorID = ReadRes.CursorID;
	int AllRcdNum = ReadRes.FrameLen;
	if (DatSet.GetRecordNums() < AllRcdNum)
	{
		int StartPos = DatSet.GetRecordNums();
		for (StartPos = DatSet.GetRecordNums(); StartPos < AllRcdNum; StartPos += MaxRetRcdNum)
		{
			DatSet.Reset();
			Client.GetCursorDatSet(CursorID, StartPos, MaxRetRcdNum, &DatSet);
			for (int i = 0; i < DatSet.GetRecordNums(); i++)
				DatSet.PrintRecord(i);
		}
	}
	Client.CloseCursor(CursorID);
	return true;

}
int TestHDAInert(CGAP_HSDASrvClient &Client)
{
	CSgDataSet DatSet;
	//获取表结构
	CHSDA_ReadRecorder_Req ReadReq;
	CHSDA_ReadRecorder_Res ReadRes;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select ID,NAME,ALIAS,TYPE from NET_NODE where 0=1");
	if (Client.HSDA_ReadRecorder(ReadReq, ReadRes) < 0)
		return false;
	DatSet.SetRecordNums(2);
	int TmpInt = 1;
	int i;
	CSgString sgstr;
	TmpInt = 3;
	SG_INT64 ID;
	for (i = 0; i < 2; i++)
	{
		ID = i + 1;
		DatSet.SetAt(i, (SG_SHORT)0, &ID);
		sgstr.Format("1234_%d",ID);
		DatSet.SetAt(i, (SG_SHORT)1, sgstr);
		sgstr.Format("567_%d", ID);
		DatSet.SetAt(i, (SG_SHORT)2, sgstr);
		DatSet.SetAt(i, (SG_SHORT)3, &TmpInt);

	}

	//插入数据库
	CDBCmd_InsertRecorder_Req Req;
	CDBCmd_InsertRecorder_Res Res;
	Req.pDatSet = &DatSet;
	Req.SchemaHandler = 1;
	Req.SchemaHandler = 1;
	Req.HeadProcMode = SG_NETCMDHEAD_PROCMOD_TOUPDB;

	if (Client.HSDA_InsertRecorder(Req, Res) < 0)
	{
		return false;
	}
	return true;
}
int TestHDAUpdate(CGAP_HSDASrvClient &Client)
{
	CSgDataSet DatSet;
	//获取表结构
	CHSDA_ReadRecorder_Req ReadReq;
	CHSDA_ReadRecorder_Res ReadRes;
	ReadReq.SchemaHandler = 1;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select ID,ALIAS from NET_NODE where 0=1");
	if (Client.HSDA_ReadRecorder(ReadReq, ReadRes) < 0)
		return false;
	DatSet.SetRecordNums(2);
	int i;
	SG_INT64 ID;
	CSgString sgstr;
	for (i = 0; i < 2; i++)
	{
		ID = i + 1;
		DatSet.SetAt(i, (SG_SHORT)0, &ID);
		sgstr.Format("Alias_%d", i);
		DatSet.SetAt(i, (SG_SHORT)1, sgstr);
	}
	
	DatSet.SetUpdateFlag(true);
	DatSet.SetChangeFlag(true);
	//修改数据库
	CDBCmd_UpdateRecorder_Req Req;
	CDBCmd_UpdateRecorder_Res Res;
	Req.pDatSet = &DatSet;
	Req.SchemaHandler = 1;
	Req.HeadProcMode = SG_NETCMDHEAD_PROCMOD_TOUPDB;
	if (Client.HSDA_UpdateRecorder(Req, Res) < 0)
	{
		return false;
	}
	return true;
}
int TestHDADelete(CGAP_HSDASrvClient &Client)
{
	CSgDataSet DatSet;
	DatSet.SetFieldNums(1);
	DatSet.SetFieldName(0, "ID");
	DatSet.SetFieldType(0, SG_FIELDTYPE_INT64);
	DatSet.SetFieldLen(0, sizeof(SG_INT64));
	DatSet.BuildTableInfo();
	DatSet.SetTableName("NET_NODE");//表格名
	DatSet.SetRecordNums(1);
	int ID = 1;
	DatSet.SetAt(0, (SG_SHORT)0, &ID);
	//插入数据库
	CDBCmd_DeleteRecorder_Req Req;
	CDBCmd_DeleteRecorder_Res Res;
	Req.pDatSet = &DatSet;
	Req.SchemaHandler = 1;
	Req.HeadProcMode = SG_NETCMDHEAD_PROCMOD_TOUPDB;
	if (Client.HSDA_DeleteRecorder(Req, Res) < 0)
	{
		return false;
	}
	return true;
}
int TestHDASubscribeData(CGAP_HSDASrvClient &Client)
{
	//先订阅数据
	CHSDA_SubscribeData_Req Req1;
	CHSDA_SubscribeData_Res Res1;
	Req1.SchemaHandler = 1;
	Req1.TableName = "NET_NODE";
	Req1.Fields = "ID,ALIAS";
	Req1.DatSet.SetFieldNums(1);
	Req1.DatSet.SetFieldName(0, "ID");
	Req1.DatSet.SetFieldType(0, SG_FIELDTYPE_INT64);
	Req1.DatSet.SetFieldLen(0, sizeof(SG_INT64));
	Req1.DatSet.BuildTableInfo();
	Req1.DatSet.SetTableName("NET_NODE");//表格名
	Req1.DatSet.SetRecordNums(2);
	int ID = 1;
	Req1.DatSet.SetAt(0, (SG_SHORT)0, &ID);
	ID = 2;
	Req1.DatSet.SetAt(1, (SG_SHORT)0, &ID);
	CSgDataSet RetDat;
	Res1.pRetDat = &RetDat;
	if (Client.HSDA_SubscribeData(Req1, Res1) < 0)
		return false;
	SG_INT StreamHandler = Res1.SchemaHandler;
	int i,No;
	//查看订阅返回的全数据
	for (i = 0; i < RetDat.GetRecordNums(); i++)
		RetDat.PrintRecord(i);
	CHSDA_GetChangeData_Req Req2;
	CHSDA_GetChangeData_Res Res2;
	Req2.SchemaHandler = 1;
	Req2.StreamHandle = StreamHandler;
	Res2.pRetDat = &RetDat;
	//定时调用获取变化数据
	for (No = 0; No < 10; No++)
	{
		RetDat.Reset();
		if (Client.HSDA_GetChangeData(Req2, Res2) >= 0)
		{
			for (i = 0; i < RetDat.GetRecordNums(); i++)
				RetDat.PrintRecord(i);

		}
		SG_OS_Sleep(3);
	}

	//取消订阅
	CHSDA_CancelSubscribe_Req Req3;
	CHSDA_CancelSubscribe_Res Res3;
	Req3.SchemaHandler = 1;
	Req3.StreamHandle = StreamHandler;
	if (Client.HSDA_CancelSubscribe(Req3, Res3) < 0)
		return false;
	return true;
}
int TestNewCCRtDB(CGAP_HSDASrvClient &Client)
{
	//获取一个算例实时库句柄
	CHSDA_GetNewSchemaHandler_Req GetReq;
	CHSDA_GetNewSchemaHandler_Res GetRes;
	if (Client.HSDA_GetNewSchemaHandler(GetReq, GetRes) < 0)
		return false;

	CHSDA_RDB_NewCCRtDB_Req NewReq;
	CHSDA_RDB_NewCCRtDB_Res NewRes;
	NewReq.SchemaHandler = GetRes.SchemaHandler;
	NewReq.LoadPara.SrvTypeStr = "3";
	NewReq.LoadPara.LoadType = 0;
	NewReq.LoadPara.SchemaDBNo = 2;
	if (Client.HSDA_NewCCRtDB(NewReq, NewRes) < 0)
		return false;
	return true;
}
int TestDeleteCCRtDB(CGAP_HSDASrvClient &Client)
{
	CHSDA_RDB_DeleteCCRtDB_Req DelReq;
	CHSDA_RDB_DeleteCCRtDB_Res DelRes;
	DelReq.SchemaHandler = 10002; //已知的一个算例实时库句柄
	if (Client.HSDA_DeleteCCRtDB(DelReq, DelRes) < 0)
		return false;

	return true;

}
int TestHDAExeSQL(CGAP_HSDASrvClient &Client)
{
	CHSDA_ExecSQL_Req Req;
	CHSDA_ExecSQL_Res Res;
	Req.SchemaHandler = 1;
	Req.SQLBuf.Format("update NET_NODE set Name='ExeName1' where ID=1");
	if (Client.HSDA_ExecSQL(Req, Res) < 0)
		return false;
	return true;
}
int StreamNotify(SG_UINT64 StreamHandler, CSgDataSet *pDatSet)
{
	if (pDatSet == NULL)
		return true;
    //按需求处理记录集内容
	//......

	if (pDatSet->GetRecordNums() > 0)
		pDatSet->PrintRecord(0);
	return true;
}
int TestHSDAStream()
{
	CGAP_RDBStream RDBStream;
	RDBStream.SetIPString("192.168.122.17:6114");
	RDBStream.Open();
	RDBStream.BindStreamEventFunc(StreamNotify);
	CSgString KeyField, RetFields;
	SET_INT64 KIDList;
	KeyField = "ID";
	RetFields = "ID,NAME,TOPO_ISLAND";
	KIDList.insert(207000000000231);
	KIDList.insert(207000000000232);
	SG_UINT64 StreamHandler1 = RDBStream.Subscibe(1, "MODEL_D_BUSBAR_SECTION", KeyField, RetFields, KIDList);
	RetFields = "ID,NAME,TOPO_ISLAND";
	KIDList.clear();
	KIDList.insert(204000000000254);
	SG_UINT64 StreamHandler2 = RDBStream.Subscibe(1, "MODEL_D_TRANSFORMER", KeyField, RetFields, KIDList);
	int Cnt = 0;
	while (true)
	{
		Cnt++;
		if (Cnt > 100000)
			break;
		//.......进程执行
		SG_OS_Sleep(10);
	}
	RDBStream.CloseStream(StreamHandler1);
	RDBStream.Close();
	return true;
}

int main( int argc, char ** argv )
{
	CGAP_HSDASrvClient Client;
	//设置数据库服务的IP地址
	Client.SetIPString("192.168.122.17:6114");
  //读数据库数据
	TestHDARead(Client);
	//游标方式读数
	TestHDACursorRead(Client);
	//执行语句
	TestHDAExeSQL(Client);
	//插入记录
	TestHDAInert(Client);
	//修改记录
	TestHDAUpdate(Client);
	//删除记录
	TestHDADelete(Client);
	//订阅数据
	TestHDASubscribeData(Client);
	//创建一个算例实时库
	TestNewCCRtDB(Client);
	//删除一个算例实时库
	TestDeleteCCRtDB(Client);
	//实时库流读取
	TestHSDAStream();
	return 0;
}

