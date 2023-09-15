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
		DatSet.PrintRecord(i); //��ӡDataSet������
		DatSet.GetAt(i, (SG_SHORT)0, &ID);
		DatSet.GetAt(i, (SG_SHORT)1, sgstr);
	}
	return true;
}
//�α귽ʽ����
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
	//��ȡ��ṹ
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

	//�������ݿ�
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
	//��ȡ��ṹ
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
	//�޸����ݿ�
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
	DatSet.SetTableName("NET_NODE");//�����
	DatSet.SetRecordNums(1);
	int ID = 1;
	DatSet.SetAt(0, (SG_SHORT)0, &ID);
	//�������ݿ�
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
	//�ȶ�������
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
	Req1.DatSet.SetTableName("NET_NODE");//�����
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
	//�鿴���ķ��ص�ȫ����
	for (i = 0; i < RetDat.GetRecordNums(); i++)
		RetDat.PrintRecord(i);
	CHSDA_GetChangeData_Req Req2;
	CHSDA_GetChangeData_Res Res2;
	Req2.SchemaHandler = 1;
	Req2.StreamHandle = StreamHandler;
	Res2.pRetDat = &RetDat;
	//��ʱ���û�ȡ�仯����
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

	//ȡ������
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
	//��ȡһ������ʵʱ����
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
	DelReq.SchemaHandler = 10002; //��֪��һ������ʵʱ����
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
    //���������¼������
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
		//.......����ִ��
		SG_OS_Sleep(10);
	}
	RDBStream.CloseStream(StreamHandler1);
	RDBStream.Close();
	return true;
}

int main( int argc, char ** argv )
{
	CGAP_HSDASrvClient Client;
	//�������ݿ�����IP��ַ
	Client.SetIPString("192.168.122.17:6114");
  //�����ݿ�����
	TestHDARead(Client);
	//�α귽ʽ����
	TestHDACursorRead(Client);
	//ִ�����
	TestHDAExeSQL(Client);
	//�����¼
	TestHDAInert(Client);
	//�޸ļ�¼
	TestHDAUpdate(Client);
	//ɾ����¼
	TestHDADelete(Client);
	//��������
	TestHDASubscribeData(Client);
	//����һ������ʵʱ��
	TestNewCCRtDB(Client);
	//ɾ��һ������ʵʱ��
	TestDeleteCCRtDB(Client);
	//ʵʱ������ȡ
	TestHSDAStream();
	return 0;
}

