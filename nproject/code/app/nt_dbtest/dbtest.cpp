#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auto_rtbl_plat.h"
#include "sgdebuginfo.h"
#include "dppclient.h"
#include "rdbmem.h"
using namespace std;

int OpenTable(CSgRDBTable &rdbTable)
{
    int ret = rdbTable.OpenTable("model_terminal");
    if (ret)
    {
        cout << "OpenTable sucessed" << endl;
    }
    else
    {
        cout << "OpenTable failed" << endl;
    }

    return ret;
}
void TableCanUse(CSgRDBTable &rdbTable)
{
    int ret = rdbTable.TableCanUse();
    if (ret)
    {
        cout << "Table Can Use" << endl;
    }
    else
    {
        cout << "Table Can not Use" << endl;
    }
}
void SelectBySql(CSgRDBSqlOper &rdbSQL)
{
    cout << "-------ExecSqlCmd(select)--------" << endl;

    char sql[1024];
    strcpy(sql, "select * from model_energy_consumer");
    CSgDataSet dataset;
    int ret = rdbSQL.ExecSqlCmd(sql, &dataset);
    if (ret)
    {
        SG_UINT recsize = dataset.GetRecordSize();
        int index;
        for (int i = 0; i < recsize; i++)
        {
            SG_INT64 id, volt, station;
            CSgString desc;
            dataset.GetAt(i, (SG_SHORT)0, &id);
            dataset.GetAt(i, (SG_SHORT)1, desc);
            cout << "ID=" << id << ",DESCRIPTION=" << desc << endl;
        }
    }

    cout << "-----------------------------" << endl;
}
void CloseTable(CSgRDBTable &rdbTable)
{
    if (rdbTable.CloseTable())
    {
        cout << "CloseTable sucessed" << endl;
    }
    else
    {
        cout << "CloseTable failed" << endl;
    }
    cout << "-----------------------------" << endl;
}

int main()
{
    int ret = 0;

    CRDBLoadSetting LoadSetting;
    LoadSetting.SchemaProcMode = SG_RDB_SCHEMA_PROCMODE_CANFREE;
    LoadSetting.SchemaType = SG_RDB_DBTYPE_CALCCASE; // schema处理模式
    LoadSetting.RtDBVerNo = 2;
    LoadSetting.SchemaDBNo = 2;
    LoadSetting.LoadType = 0; // 0: 从数据库加载 1：从文件加载
    LoadSetting.SrvTypeStr = "3";
    CSgRDBMemCalcCase CalcMemDB2(1001);
    ret = CalcMemDB2.CreateShareMemory(LoadSetting);
    // CalcMemDB1.FreeShareMemory();

    if (!ret)
    {
        cout << "\r\CreateShareMemory failed" << endl;
        return -1;
    }
    else
    {
        cout << "\r\CreateShareMemory sucessed" << endl;
    }
    // 打开表
    CSgRDBTable rdbTable(1001);
    OpenTable(rdbTable);
    CSgDataSet datSet;

   cout << "==============================" << endl;
    cout << "num:" << datSet.GetRecordNums() << endl;
    if (rdbTable.GetRcdDataSet(datSet))
    {
        SG_UINT recsize = datSet.GetRecordNums();
        int index;
        for (int i = 0; i < recsize; i++)
        {
            SG_INT64 id, volt, station;
            SG_INT64 conn_node_id;
            CSgString desc;
            datSet.GetAt(i, (SG_SHORT)0, &id);
            index=datSet.GetFieldPtr("CONN_NODE_ID");
            datSet.GetAt(i,(SG_SHORT)index,&conn_node_id);
            cout << "ID=" << id << "         "<<"CONN_NODE_ID:"<<conn_node_id<<endl;
        }
    }

    char *pFieldName[] = {"ID", "TERMINAL_TYPE", "OF_DEVICE", "CONN_NODE_ID"};
    int fieldType[] = {SG_FIELDTYPE_INT64, SG_FIELDTYPE_INT64, SG_FIELDTYPE_INT64, SG_FIELDTYPE_INT64};
    int fieldLen[] = {sizeof(SG_INT64), sizeof(SG_INT64), sizeof(SG_INT64), sizeof(SG_INT64)};
    int fieldNum = sizeof(pFieldName) / sizeof(char *);
    datSet.SetFieldNums(fieldNum);
    for (int i = 0; i < fieldNum; i++)
    {
        datSet.SetFieldName(i, pFieldName[i]);
        datSet.SetFieldType(i, fieldType[i]);
        datSet.SetFieldLen(i, fieldLen[i]);
    }
    datSet.SetFieldPrimary(0, true);
    datSet.BuildTableInfo();
    datSet.SetTableName("model_terminal");

    datSet.SetRecordNums(1);
    SG_INT64 n_id = 171000000000430;
    SG_INT64 n_terminal_type = 1;
    SG_INT64 n_of_devicer = 301000000000063;
    SG_INT64 n_conn_node_id = 172000000000158;
    int index;
    int n = 0;
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)0, &n_id);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)1, &n_terminal_type);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)2, &n_of_devicer);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)3, &n_conn_node_id);

    if (rdbTable.ReOpenTable(1, 1))
    {
        cout << "ReOpenTable sucessed" << endl;
    }
    else
    {
        cout << "ReOpenTable failed" << endl;
    }
    if (rdbTable.InsertRecorder(datSet, false))
    {
        cout << "InsertRecorder sucessed" << endl;
    }
    else
    {
        cout << "InsertRecorder failed" << endl;
    }
    cout << "-----------------------------" << endl;

    cout << "==============================" << endl;
    cout << "num:" << datSet.GetRecordNums() << endl;
    
    if (rdbTable.GetRcdDataSet(datSet))
    {
        SG_UINT recsize = datSet.GetRecordNums();
        int index;
        for (int i = 0; i < recsize; i++)
        {
            SG_INT64 id, volt, station;
            SG_INT64 conn_node_id;
            CSgString desc;
            datSet.GetAt(i, (SG_SHORT)0, &id);
            index=datSet.GetFieldPtr("CONN_NODE_ID");
            datSet.GetAt(i,(SG_SHORT)index,&conn_node_id);
            cout << "ID=" << id << "         "<<"CONN_NODE_ID:"<<conn_node_id<<endl;
        }
    }

    cout<<"-------PutRcdByNo--------"<<endl;

    

    cout << "==============================" << endl;
    cout << "num:" << datSet.GetRecordNums() << endl;
    if (rdbTable.GetRcdDataSet(datSet))
    {
        SG_UINT recsize = datSet.GetRecordNums();
        int index;
        for (int i = 0; i < recsize; i++)
        {
            SG_INT64 id, volt, station;
            SG_INT64 conn_node_id;
            CSgString desc;
            datSet.GetAt(i, (SG_SHORT)0, &id);
            index=datSet.GetFieldPtr("CONN_NODE_ID");
            datSet.GetAt(i,(SG_SHORT)index,&conn_node_id);
            cout << "ID=" << id << "         "<<"CONN_NODE_ID:"<<conn_node_id<<endl;
        }
    }

    // 关闭表
    CloseTable(rdbTable);

    ret = CalcMemDB2.FreeShareMemory();
    if (!ret)
    {
        cout << "FreeShareMemory failed" << endl;
        return -1;
    }
    else
    {
        cout << "FreeShareMemory sucessed" << endl;
    }

    cout << "============end==============" << endl;
    // CSgRDBMemCalcCase::FreeAllShareMemory();
}