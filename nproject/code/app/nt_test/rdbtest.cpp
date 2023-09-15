#include <iostream>
#include "rdbmem.h"
#include "auto_rtbl_plat.h"

using namespace std;

int OpenTable(CSgRDBTable& rdbTable)
{
    int ret = rdbTable.OpenTable("MODEL_BREAKER");
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

void InsertRecorder(CSgRDBTable& rdbTable)
{
    cout<<"--------InsertRecorder---------"<<endl;
    CSgDataSet datSet;
    char *pFieldName[] = {"ID","DESCRIPTION"};
    int fieldType[] = {SG_FIELDTYPE_INT64,SG_FIELDTYPE_VARCHAR};
    int fieldLen[] = {sizeof(SG_INT64),128};
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
	datSet.SetTableName("MODEL_BREAKER");

	datSet.SetRecordNums(2);
    SG_INT64 id;
    id = 123456789;
     CSgString sgstr;
     sgstr="测试开关1";
    datSet.SetAt((SG_SHORT)0, (SG_SHORT)0, &id);
	 datSet.SetAt((SG_SHORT)0, (SG_SHORT)1, sgstr);
    id = 987654321;
	sgstr = "测试开关2";
    datSet.SetAt((SG_SHORT)1, (SG_SHORT)0, &id);
	datSet.SetAt((SG_SHORT)1, (SG_SHORT)1, sgstr);

    if(rdbTable.ReOpenTable(1, 1))
    {
        cout<<"ReOpenTable sucessed"<<endl;
    }
    else
    {
        cout<<"ReOpenTable failed"<<endl;
    }
    if(rdbTable.InsertRecorder(datSet, false))
    {
        cout<<"InsertRecorder sucessed"<<endl;
    }
    else
    {
        cout<<"InsertRecorder failed"<<endl;
    }
    cout<<"-----------------------------"<<endl;
}

void DelRcdByKey(CSgRDBTable& rdbTable)
{
    VECT_INT64 KeyIDList;
    KeyIDList.push_back(123456789);
    //KeyIDList.push_back(987654321);
    if(rdbTable.DelRcdByKey(KeyIDList, false))
    {
        cout<<"DelRcdByKey sucessed"<<endl;
    }
    else
    {
        cout<<"DelRcdByKey failed"<<endl;
    }
    cout<<"-----------------------------"<<endl;
}

void GetTableInfo(CSgRDBTable& rdbTable)
{
    char * pTableName = rdbTable.GetTableName();
    cout<<"TableName:"<<pTableName<<endl;

    int len = rdbTable.GetRcdLen();
    cout<<"GetRcdLen:"<<len<<endl;

    int count = rdbTable.GetRcdNum();
    cout<<"GetRcdNum:"<<count<<endl;

    int fieldnum = rdbTable.GetFieldNum();
    cout<<"GetFieldNum:"<<fieldnum<<endl;

    int fieldindex = rdbTable.GetFieldPtr("OF_VOLT_LEVEL");
    cout<<"GetFieldPtr:"<<fieldindex<<endl;

    CSgString KeyField;
    rdbTable.GetKeyField(KeyField);
    cout<<"GetKeyField:"<<KeyField<<endl;

    int index = rdbTable.GetKeyFieldPtr();
    cout<<"GetKeyFieldPtr:"<<index<<endl;
}

void GetFieldInfo(CSgRDBTable& rdbTable)
{
    int fieldPtr=0;
    CRDBFieldInfo * pFieldInfo = rdbTable.GetFieldInfo(fieldPtr);
    if(NULL == pFieldInfo)
    {
        cout<<"GetFieldInfo is NULL"<<endl;
    }
    else
    {
        cout<<"----FieldInfo-----------------"<<endl;
        cout<<"  FieldName:"<<pFieldInfo->FieldName<<endl;
        cout<<"  TblCode:"<<pFieldInfo->TblCode<<endl;
        //cout<<"  FieldDesc:"<<pFieldInfo->FieldDesc<<endl;
        cout<<"  FieldMode:"<<to_string(pFieldInfo->FieldMode)<<endl;
        cout<<"  FieldType:"<<pFieldInfo->FieldType<<endl;
        cout<<"  FieldLen:"<<pFieldInfo->FieldLen<<endl;
        cout<<"  SqlType:"<<pFieldInfo->SqlType<<endl;
        //
        cout<<"  IsIndexField:"<<rdbTable.IsIndexField(fieldPtr)<<endl;
        cout<<"-----------------------------"<<endl;
    }
}

void GetFieldInfo2(CSgRDBTable& rdbTable)
{
    CRDBFieldInfo * pFieldInfo = rdbTable.GetFieldInfo("DESCRIPTION");
    if(NULL == pFieldInfo)
    {
        cout<<"GetFieldInfo is NULL"<<endl;
    }
    else
    {
        cout<<"----FieldInfo-----------------"<<endl;
        cout<<"  FieldName:"<<pFieldInfo->FieldName<<endl;
        cout<<"  TblCode:"<<pFieldInfo->TblCode<<endl;
        //cout<<"  FieldDesc:"<<pFieldInfo->FieldDesc<<endl;
        cout<<"  FieldMode:"<<to_string(pFieldInfo->FieldMode)<<endl;
        cout<<"  FieldType:"<<pFieldInfo->FieldType<<endl;
        cout<<"  FieldLen:"<<pFieldInfo->FieldLen<<endl;
        cout<<"  SqlType:"<<pFieldInfo->SqlType<<endl;
        cout<<"-----------------------------"<<endl;
    }
}

void GetUniqueKeyList(CSgRDBTable& rdbTable)
{
    cout<<"---------GetUniqueKeyList---------"<<endl;

    VECT_INT keyPtrList;
    if(rdbTable.GetUniqueKeyList(keyPtrList))
    {
        for(int i=0;i<keyPtrList.size();i++)
        {
            cout<<"UniqueKey Index = "<<keyPtrList[i]<<endl;
        }       
    }
   
    cout<<"-----------------------------"<<endl;
}

void GetRcdDataSet(CSgRDBTable& rdbTable)
{
    cout<<"---------GetRcdDataSet---------"<<endl;
    CSgDataSet dataset;
    if(rdbTable.GetRcdDataSet(dataset))
    {
        SG_UINT	recsize = dataset.GetRecordSize();
        int index;
        for(int i=0;i<recsize;i++)
        {
            SG_INT64 id,volt,station;
            CSgString desc;
            dataset.GetAt(i, (SG_SHORT)0, &id);
            dataset.GetAt(i, (SG_SHORT)1, desc);
            index = rdbTable.GetFieldPtr("OF_VOLT_LEVEL");
            dataset.GetAt(i, (SG_SHORT)index, &volt);
            index = rdbTable.GetFieldPtr("OF_SUBSTATION");
            dataset.GetAt(i, (SG_SHORT)index, &station);
            cout<<"ID="<<id<<",DESCRIPTION="<<desc<<",OF_VOLT_LEVEL="<<volt<<",OF_SUBSTATION="<<station<<endl;
        }
    }
    cout<<"-----------------------------"<<endl;  
}

void GetRcdNoByFieldVal1(CSgRDBTable& rdbTable)
{
    cout<<"-----GetRcdNoByFieldVal(FieldValList)-----"<<endl;
    VECT_STRINT64 FieldValList;
    S_STRINT64 FieldVal;
    /*FieldVal.StrVal="ID";
    FieldVal.IntVal=110800000000004118;
    FieldValList.push_back(FieldVal);*/
    FieldVal.StrVal="OF_SUBSTATION";
    FieldVal.IntVal=100300000000000147;
    FieldValList.push_back(FieldVal);
    FieldVal.StrVal="OF_VOLT_LEVEL";
    FieldVal.IntVal=101400000000000114;
    FieldValList.push_back(FieldVal);
    VECT_INT RcdNoList;
    if (rdbTable.GetRcdNoByFieldVal(FieldValList, RcdNoList))
    {
        int RcdNo;
        SG_INT64 id;
        CSgString desc;
        SG_INT type = 1;
        for (int i = 0; i < RcdNoList.size(); i++)
        {
            RcdNo = RcdNoList[i];
            rdbTable.GetAt(RcdNo, (SG_SHORT)0, &id);
            rdbTable.GetAt(RcdNo, (SG_SHORT)1, desc);
            rdbTable.GetAt(RcdNo, (SG_SHORT)4, &type);//数据库中原来的值都是0
            //rdbTable.SetAt(RcdNo, (SG_SHORT)4, &type);
            cout<<"ID="<<id<<",Description="<<desc<<",Type="<<type<<endl;
        }
    }
    cout<<"-----------------------------"<<endl;
}

void GetRcdNoByFieldVal2(CSgRDBTable& rdbTable)
{
    cout<<"-----GetRcdNoByFieldVal(DBCondList)-----"<<endl;
    VECT_RDBCOND DBCondList;
    SG_RDB_CONDINFO DBCond;
    DBCond.LogicOpt = SG_RDB_LOGIC_COND_AND; 
    DBCond.RelOpt = SG_RDB_COND_SMALLEQU;//小于等于
    DBCond.Val.DatType = SG_FIELDTYPE_INT64;
    DBCond.Code = "OF_SUBSTATION";
    DBCond.Val.NumVal.IntVal = 100300000000000147;
    DBCondList.push_back(DBCond);
    DBCond.RelOpt = SG_RDB_COND_EQU;//等于
    DBCond.Code = "OF_VOLT_LEVEL";
    DBCond.Val.NumVal.IntVal = 101400000000000113;
    DBCondList.push_back(DBCond);
    VECT_INT RcdNoList;
    if (rdbTable.GetRcdNoByFieldVal(DBCondList, RcdNoList))
    {
        int RcdNo;
        SG_INT64 id;
        CSgString desc;
        for (int i = 0; i < RcdNoList.size(); i++)
        {
            RcdNo = RcdNoList[i];
            rdbTable.GetAt(RcdNo, (SG_SHORT)0, &id);
            rdbTable.GetAt(RcdNo, (SG_SHORT)1, desc);
            cout<<"ID="<<id<<",Description="<<desc<<endl;
        }
    }
    cout<<"-----------------------------"<<endl;
}

void GetRcdNoByKey(CSgRDBTable& rdbTable)
{
    cout<<"-------GetRcdNoByKey--------"<<endl;

    SG_INT64 KeyID = 110800000000004118;
    int recno = rdbTable.GetRcdNoByKey(KeyID);
    if(recno)
    {
        cout<<"PrimaryKey="<<KeyID<<", RcdNo="<<recno<<endl;
    }
    else
    {
        cout<<"PrimaryKey="<<KeyID<<", RcdNo not found."<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void GetPrimaryKeyValue(CSgRDBTable& rdbTable)
{
    cout<<"-------GetPrimaryKeyValue--------"<<endl;

    int recno = 55;
    SG_UINT64 keyValue = rdbTable.GetPrimaryKeyValue(recno);
    if(keyValue)
    {
        cout<<"RcdNo="<<recno<<", PrimaryKey="<<keyValue<<endl;
    }
    else
    {
        cout<<"RcdNo="<<recno<<", PrimaryKey not found."<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void GetRcdByKey(CSgRDBTable& rdbTable)
{
    cout<<"-------GetRcdByKey--------"<<endl;

    SG_INT64 KeyID = 110800000000004118;
    void * p = rdbTable.GetRcdByKey(KeyID);
    if(p!=NULL)
    {        
        cout<<"PrimaryKey="<<KeyID<<", p="<<p<<endl;
        MODEL_BREAKER * breaker = (MODEL_BREAKER*)p;        
        cout<<"ID="<<breaker->ID<<",DESCRIPTION="<<breaker->DESCRIPTION<<",OF_VOLT_LEVEL="<<breaker->OF_VOLT_LEVEL<<",OF_SUBSTATION="<<breaker->OF_SUBSTATION<<endl;
    }
    else
    {
        cout<<"pointer is null."<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void GetRcdByNo(CSgRDBTable& rdbTable)
{
    cout<<"-------GetRcdByNo--------"<<endl;

    int recno = 55;
    void * p = rdbTable.GetRcdByNo(recno);
    if(p!=NULL)
    {
        cout<<"RcdNo="<<recno<<", p="<<p<<endl;
        MODEL_BREAKER * breaker = (MODEL_BREAKER*)p;
        cout<<"ID="<<breaker->ID<<",DESCRIPTION="<<breaker->DESCRIPTION<<",OF_VOLT_LEVEL="<<breaker->OF_VOLT_LEVEL<<",OF_SUBSTATION="<<breaker->OF_SUBSTATION<<endl;
    }
    else
    {
        cout<<"pointer is null."<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void GetRcdByNo2(CSgRDBTable& rdbTable)
{
    cout<<"-------GetRcdByNo2--------"<<endl;

    int len = rdbTable.GetRcdLen();
    int recno = 55;
    char pRcdDat[len];
    if(rdbTable.GetRcdByNo(recno, pRcdDat))
    {
        MODEL_BREAKER * breaker = (MODEL_BREAKER*)pRcdDat;
        cout<<"ID="<<breaker->ID<<",DESCRIPTION="<<breaker->DESCRIPTION<<",OF_VOLT_LEVEL="<<breaker->OF_VOLT_LEVEL<<",OF_SUBSTATION="<<breaker->OF_SUBSTATION<<endl;
    }
    else
    {
        cout<<"pointer is null."<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void PutRcdByNo(CSgRDBTable& rdbTable)
{
    cout<<"-------PutRcdByNo--------"<<endl;

    int len = rdbTable.GetRcdLen();
    int recno = 55;
    char pRcdDat[len];
	CSgString sgstr;
    if(rdbTable.GetRcdByNo(recno, pRcdDat))
    {
        MODEL_BREAKER * breaker = (MODEL_BREAKER*)pRcdDat;
        strcpy(breaker->DESCRIPTION, "10kV鱼月乙线F10开关333");
        char * pRcdDat = (char*)breaker;
        if(rdbTable.PutRcdByNo(recno, pRcdDat))
        {           
            cout<<"PutRcdByNo sucessed."<<endl;
        }
        else
        {
            cout<<"PutRcdByNo failed."<<endl;
        }
    }    

    cout<<"-----------------------------"<<endl;
}

void GetFirstRcd(CSgRDBTable& rdbTable)
{
    cout<<"-------GetFirstRcd--------"<<endl;

    void * p = rdbTable.GetFirstRcd();
    if(p!=NULL)
    {
        cout<<"p="<<p<<endl;
        MODEL_BREAKER * breaker = (MODEL_BREAKER*)p;
        for(int i=0;i<10;i++,breaker++)
        {
            cout<<"breaker pointer="<<breaker<<endl;     
            cout<<"ID="<<breaker->ID<<",DESCRIPTION="<<breaker->DESCRIPTION<<",OF_VOLT_LEVEL="<<breaker->OF_VOLT_LEVEL<<",OF_SUBSTATION="<<breaker->OF_SUBSTATION<<endl;
        }
    }
    else
    {
        cout<<"pointer is null."<<endl;
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

void SelectBySql(CSgRDBSqlOper& rdbSQL)
{
    cout<<"-------ExecSqlCmd(select)--------"<<endl;

    char sql[1024];
    strcpy(sql,"select * from MODEL_BREAKER where ID>110800000000004110");
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

void InsertBySql(CSgRDBSqlOper& rdbSQL)
{
    cout<<"-------ExecSqlCmd(insert)--------"<<endl;

    char sql[1024];
    strcpy(sql,"insert into MODEL_BREAKER (ID,DESCRIPTION) values(888,'break_test')");
    int ret = rdbSQL.ExecSqlCmd(sql, NULL);
    if(ret)
    {
        cout<<"insert sucessed"<<endl;       
    }
    else
    {
        cout<<"insert failed"<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void UpdateBySql(CSgRDBSqlOper& rdbSQL)
{
    cout<<"-------ExecSqlCmd(update)--------"<<endl;

    char sql[1024];
    strcpy(sql,"update MODEL_BREAKER set type=0 where ID=110800000000004118");
    int ret = rdbSQL.ExecSqlCmd(sql, NULL);
    if(ret)
    {
        cout<<"update sucessed"<<endl;       
    }
    else
    {
        cout<<"update failed"<<endl;
    }

    cout<<"-----------------------------"<<endl;
}

void DeleteBySql(CSgRDBSqlOper& rdbSQL)
{
    cout<<"-------ExecSqlCmd(delete)--------"<<endl;

    char sql[1024];
    strcpy(sql,"delete from MODEL_BREAKER where ID=987654321 or ID=888");
    int ret = rdbSQL.ExecSqlCmd(sql, NULL);
    if(ret)
    {
        cout<<"delete sucessed"<<endl;       
    }
    else
    {
        cout<<"delete failed"<<endl;
    }

    cout<<"-----------------------------"<<endl;
}



int main()
{
    int ret = 0;

    //创建实时库
    CSgRDBMemOverall rdbmem(1);
    ret = rdbmem.CreateShareMemory();
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
    CSgRDBTable rdbTable(1);    
    if(!OpenTable(rdbTable))
        return -1;

    //实时库表有效性
    TableCanUse(rdbTable);

    //实时库表信息获取的相关函数
    GetTableInfo(rdbTable);

    //获取字段信息
    GetFieldInfo(rdbTable);

    //获取字段信息
    GetFieldInfo2(rdbTable);

    //获取唯一索引键的序号
    GetUniqueKeyList(rdbTable);

    //插入表记录
    InsertRecorder(rdbTable);

    //获取表的数据集
    GetRcdDataSet(rdbTable);

    //删除表记录
    DelRcdByKey(rdbTable);

    //获取表的数据集
    GetRcdDataSet(rdbTable);

    //按条件查找
    GetRcdNoByFieldVal1(rdbTable);

    //按条件查找
    GetRcdNoByFieldVal2(rdbTable);

    //按主键获取记录号
    GetRcdNoByKey(rdbTable);

    //获取记录主键值
    GetPrimaryKeyValue(rdbTable);

    //获取表的数据指针
    GetRcdByKey(rdbTable);

    //获取表的数据指针
    GetRcdByNo(rdbTable);

    //获取表的数据内容
    GetRcdByNo2(rdbTable);

    //修改表的数据
    PutRcdByNo(rdbTable);

    //获取首记录数据指针
    GetFirstRcd(rdbTable); 

    //关闭表
    CloseTable(rdbTable);    

    //SQl
    CSgRDBSqlOper rdbSQL(1);
    rdbSQL.SetUser("sa", "rdb200025");

    //通过SQL查询
    SelectBySql(rdbSQL);

    //通过SQL插入
    InsertBySql(rdbSQL);

    //通过SQL更新
    UpdateBySql(rdbSQL);

    //通过SQL删除
    DeleteBySql(rdbSQL);

    ret = rdbmem.FreeShareMemory();
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

    return 0;
}
