#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sgdebuginfo.h"
#include "dppclient.h"
#include "rdbmem.h"
using namespace std;

int OpenTable(CSgRDBTable& rdbTable)
{
    int ret = rdbTable.OpenTable("MODEL_D_BUSBAR_SECTION");
    if(ret)
    {
        cout<<"OpenTable sucessed"<<endl;
    }
    else
    {        
        cout<<"OpenTable failed"<<endl;
    }

    return ret;
}
void TableCanUse(CSgRDBTable& rdbTable)
{
    int ret = rdbTable.TableCanUse();
    if(ret)
    {
        cout<<"Table Can Use"<<endl;
    }
    else
    {
        cout<<"Table Can not Use"<<endl;
    }
}
void SelectBySql(CSgRDBSqlOper& rdbSQL)
{
    cout<<"-------ExecSqlCmd(select)--------"<<endl;

    char sql[1024];
    strcpy(sql,"select * from MODEL_D_BUSBAR_SECTION where BASE_VOLTAGE=22");
    CSgDataSet dataset;
    int ret = rdbSQL.ExecSqlCmd(sql, &dataset);
    if(ret)
    {
        SG_UINT	recsize = dataset.GetRecordSize();
        int index;
        for(int i=0;i<recsize;i++)
        {
            SG_INT64 id,volt,station;
            CSgString desc;
            dataset.GetAt(i, (SG_SHORT)0, &id);
            dataset.GetAt(i, (SG_SHORT)1, desc);            
            cout<<"ID="<<id<<",DESCRIPTION="<<desc<<endl;
        }
    }

    cout<<"-----------------------------"<<endl;
}
void CloseTable(CSgRDBTable& rdbTable)
{
    if(rdbTable.CloseTable())
    {
        cout<<"CloseTable sucessed"<<endl;
    }
    else
    {
        cout<<"CloseTable failed"<<endl;
    }
    cout<<"-----------------------------"<<endl;
}
int main()
{
    int ret =0;

    CRDBLoadSetting LoadSetting;
    // CSgString FileName;
    // FileName = "f:/aaa.dat";
    // LoadSetting.RtDBVerNo = 2;
    // LoadSetting.SchemaType = SG_RDB_DBTYPE_CALCCASE;
    // LoadSetting.SchemaDBNo = 2;
    // LoadSetting.SchemaProcMode = SG_RDB_SCHEMA_PROCMODE_CANFREE;
    // LoadSetting.LoadType = 1; // 0: 从数据库加载 1：从文件加载
    // LoadSetting.SrvTypeStr = FileName.GetSafeBuffer();
    // CSgRDBMemCalcCase CalcMemDB1(1002);
    //CalcMemDB1.CreateShareMemory(LoadSetting);
    LoadSetting.RtDBVerNo = 2;
    LoadSetting.SchemaType = SG_RDB_DBTYPE_CALCCASE;
    LoadSetting.SchemaDBNo = 2;
    LoadSetting.SchemaProcMode = SG_RDB_SCHEMA_PROCMODE_CANFREE;
    LoadSetting.LoadType = 0; // 0: 从数据库加载 1：从文件加载
    LoadSetting.SrvTypeStr = "3";
    CSgRDBMemCalcCase CalcMemDB2(1001);
    ret = CalcMemDB2.CreateShareMemory(LoadSetting);
    //CalcMemDB1.FreeShareMemory();
    
    
    if(!ret)
    {
        cout<<"\r\CreateShareMemory failed"<<endl;
        return-1;
    }
    else
    {
        cout<<"\r\CreateShareMemory sucessed"<<endl;
    }
    //打开表
    CSgRDBTable rdbTable(1001);    
    if(!OpenTable(rdbTable))
        return -1;

    //实时库表有效性
    TableCanUse(rdbTable);
    CSgRDBSqlOper rdbSQL(1001);
    rdbSQL.SetUser("sa", "rdb200025");
    //通过SQL查询
    SelectBySql(rdbSQL);
    //关闭表
    CloseTable(rdbTable);   
    ret=CalcMemDB2.FreeShareMemory();
    if(!ret)
    {
        cout<<"FreeShareMemory failed"<<endl;
        return-1;
    }
    else
    {
        cout<<"FreeShareMemory sucessed"<<endl;
    }

    cout<<"============end=============="<<endl;
    //CSgRDBMemCalcCase::FreeAllShareMemory();
}