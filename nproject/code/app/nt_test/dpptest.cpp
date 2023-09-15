#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <sys/ioctl.h>
//#include <unistd.h>
#include <errno.h>
//#include <termios.h>

#include "dppclient.h"
int TestDBRead(CGAP_DppSrvClient &DBClient)
{
   CSgDataSet DatSet;
	CDBCmd_ReadRecorder_Req ReadReq;
	CDBCmd_ReadRecorder_Res ReadRes;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select ID,NAME from JAPP_CODE");
	if (DBClient.RDB_ReadRecorder(ReadReq, ReadRes) < 0)
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
int TestCursorDBRead(CGAP_DppSrvClient &DBClient)
{
	const int MaxRetRcdNum = 100;
	CSgDataSet DatSet;
	CDBCmd_ReadRecorder_Req ReadReq;
	CDBCmd_ReadRecorder_Res ReadRes;
	ReadRes.pRetDat = &DatSet;
	ReadReq.HeadProcMode = SG_NETCMDHEAD_PROCMOD_USECURSOR;
	ReadReq.MaxRow = MaxRetRcdNum;
	ReadReq.SQLBuf.Format("select * from JAPP_CODE");
	if (DBClient.RDB_ReadRecorder(ReadReq, ReadRes) < 0)
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
			DBClient.GetCursorDatSet(CursorID, StartPos, MaxRetRcdNum, &DatSet);
			for (int i = 0; i < DatSet.GetRecordNums(); i++)
				DatSet.PrintRecord(i);
		}
	}
	DBClient.CloseCursor(CursorID);
	return true;
}
//预编译执行SQL
int TestCompileExeSQL(CGAP_DppSrvClient &DBClient)
{
	CDBCmd_CompileExecSQL_Req Req;
	CDBCmd_CompileExecSQL_Res Res;
	Req.SQLBuf.Format("update JAPP_CODE set Name=? where ID=?");
	CSgString JsonPara;
	JsonPara = "{\"para\":[{\"v\":\"i1234\"},{\"v\":\"102\",\"t\":8}]}";
	GAP_ReadPara_Json2DatSet(JsonPara, Req.DataSet);

	if (DBClient.RDB_ExecSQL(Req, Res) < 0)
		return false;
	return true;

}

//预编译读取数据库
int TestCompileDBRead(CGAP_DppSrvClient &DBClient)
{
	CSgDataSet DatSet;
	CDBCmd_CompileReadRecorder_Req ReadReq;
	CDBCmd_CompileReadRecorder_Res ReadRes;
	ReadRes.pRetDat = &DatSet;
	ReadReq.SQLBuf.Format("select * from JAPP_CODE where NAME=? and ID>?");
	CSgString JsonPara;
	JsonPara = "{\"para\":[{\"v\":\"abc\"},{\"v\":\"100\",\"t\":8}]}";
	GAP_ReadPara_Json2DatSet(JsonPara, ReadReq.DataSet);
	if (DBClient.RDB_ReadRecorder(ReadReq, ReadRes) < 0)
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

int BuildOneDatSet(CSgDataSet &DatSet,int BuildFieldNum)
{
	static char *pFieldName[] = { "ID",	"NAME" };
	static int FieldType[] = { SG_FIELDTYPE_INT64,    SG_FIELDTYPE_VARCHAR };
	static int FieldLen[] = { sizeof(SG_INT64),   64 };
	int i;
	const int FieldNum = sizeof(pFieldName) / sizeof(char *);
	//组装DatSet	
	int RealFieldNum = BuildFieldNum;
	if (RealFieldNum > FieldNum)
		RealFieldNum = FieldNum;
	DatSet.SetFieldNums(RealFieldNum);
	for (i = 0; i < RealFieldNum; i++)
	{
		DatSet.SetFieldName(i, pFieldName[i]);
		DatSet.SetFieldType(i, FieldType[i]);
		DatSet.SetFieldLen(i, FieldLen[i]);
	}
	DatSet.SetFieldPrimary(0, true); //把数据集的第1个字段（ID)设置成主键字段
	DatSet.BuildTableInfo();
	DatSet.SetTableName("JAPP_CODE");//表格名
	DatSet.SetRecordNums(2);
	CSgString sgstr;
	SG_INT64 ID;
	for (i = 0; i < 2; i++)
	{
		ID = i + 1;
		DatSet.SetAt(i, (SG_SHORT)0, &ID);
		if (RealFieldNum < 2)
			continue;
		sgstr.Format("Name%d", i + 1);
		DatSet.SetAt(i, (SG_SHORT)1, sgstr);
		DatSet.PrintRecord(i);
	}
	return true;
}
int TestExeSQL(CGAP_DppSrvClient &DBClient)
{
	CDBCmd_ExecSQL_Req Req;
	CDBCmd_ExecSQL_Res Res;
	Req.SQLBuf.Format("update JAPP_CODE set Name='ExeName1' where ID=1");
	if (DBClient.RDB_ExecSQL(Req, Res) < 0)
		return false;
	return true;
}

int TestDBInert(CGAP_DppSrvClient &DBClient)
{
	CSgDataSet DatSet;
	BuildOneDatSet(DatSet,2);

	//插入数据库
	CDBCmd_InsertRecorder_Req InsertReq;
	CDBCmd_InsertRecorder_Res InsertRes;
	InsertReq.pDatSet = &DatSet;
	if (DBClient.RDB_InsertRecorder(InsertReq, InsertRes) < 0)
	{
		return false;
	}
	return true;
}
int TestDBUpdate(CGAP_DppSrvClient &DBClient)
{
	CSgDataSet DatSet;
	BuildOneDatSet(DatSet,2);

	DatSet.SetUpdateFlag(true);
	DatSet.SetChangeFlag(true);
	//修改数据库
	CDBCmd_UpdateRecorder_Req Req;
	CDBCmd_UpdateRecorder_Res Res;
	Req.pDatSet = &DatSet;
	if (DBClient.RDB_UpdateRecorder(Req, Res) < 0)
	{
		return false;
	}
	return true;
}
int TestDBDelete(CGAP_DppSrvClient &DBClient)
{
	CSgDataSet DatSet;
	BuildOneDatSet(DatSet, 1);

	//插入数据库
	CDBCmd_DeleteRecorder_Req Req;
	CDBCmd_DeleteRecorder_Res Res;
	Req.pDatSet = &DatSet;
	if (DBClient.RDB_DeleteRecorder(Req, Res) < 0)
	{
		return false;
	}
	return true;
}
int TestBatchExec(CGAP_DppSrvClient &DBClient)
{
	CDBCmd_TransOper_Req Req;
	CDBCmd_TransOper_Res Res;
	CSgDataSet *pDatSet=new CSgDataSet;
	if (pDatSet == NULL)
		return false;
	Req.OperDatSetArray.Add(SG_OBJ_OPERTYPE_MERGE, pDatSet);
	BuildOneDatSet(*pDatSet,2);
	pDatSet = new CSgDataSet;
	if (pDatSet == NULL)
		return false;
	BuildOneDatSet(*pDatSet, 1);
	Req.OperDatSetArray.Add(SG_OBJ_OPERTYPE_DELETE, pDatSet);

	//批处理数据库
	if (DBClient.RDB_BatchExec(Req, Res) < 0)
	{
		return false;
	}
	return true;
}

int main( int argc, char ** argv )
{
	CGAP_DppSrvClient DBClient;
	//DBClient.SetUseLocalDB(true); 
	//设置数据库服务的IP地址
	DBClient.SetIPString("192.168.122.17:6118");
  //读数据库数据
	TestDBRead(DBClient);
	//执行操作
	TestExeSQL(DBClient);
	//插入记录
	TestDBInert(DBClient);
	//修改记录
	TestDBUpdate(DBClient);
	//删除记录
	TestDBDelete(DBClient);
	//批量操作
	TestBatchExec(DBClient);
	//预编译读取数据库
	TestCompileDBRead(DBClient);
	//预编译执行操作
	TestCompileExeSQL(DBClient);
	//游标读取
	TestCursorDBRead(DBClient);

	return 0;
}

