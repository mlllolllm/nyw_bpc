#include <iostream>
#include <vector>
#include "rdbmem.h"

#define OBJTYPE_BREAKER 209

using namespace std;

//����豸�Ķ����б�
int GetObjTerminal(CSgRDBObject &RDBObject, int64_t id)
{
    VECT_INT64 TerminalList;
    int ret = RDBObject.GetObjTerminal(id, TerminalList);

    if(ret)
    {
        cout<<"====================GetObjTerminal success"<<endl;
        for(VECT_INT64::iterator it = TerminalList.begin();it != TerminalList.end(); it++)
        {
            cout<<"Object ID="<<id<<", Terminal ID="<<*it<<endl;
        }
    }
    else
    {
        cout<<"====================GetObjTerminal failed"<<endl;
    }

    return ret;
}

//����豸�����ӽڵ�
int GetObjConnectNode(CSgRDBObject &RDBObject, int64_t id)
{
    VECT_INT64 ConNodeList;
    int ret = RDBObject.GetObjConnectNode(id, -1, ConNodeList);

    if(ret)
    {
        cout<<"====================GetObjConnectNode success"<<endl;
        for(VECT_INT64::iterator it = ConNodeList.begin();it != ConNodeList.end(); it++)
        {
            cout<<"Object ID="<<id<<", ConNode ID="<<*it<<endl;
        }
    }
    else
    {
        cout<<"====================GetObjConnectNode failed"<<endl;
    }

    return ret;
}

//��ú͸��豸�������豸
int GetObjConnectObj(CSgRDBObject &RDBObject, int64_t id)
{
    VECT_INT64 ObjList;
    int ret = RDBObject.GetObjConnectObj(id, 2, ObjList);

    if(ret)
    {
        cout<<"====================GetObjConnectObj success"<<endl;
        for(VECT_INT64::iterator it = ObjList.begin();it != ObjList.end(); it++)
        {
            cout<<"Object ID="<<id<<", ConnectObj ID="<<*it<<endl;
        }
    }
    else
    {
        cout<<"====================GetObjConnectObj failed"<<endl;
    }

    return ret;
}

//��ø��豸ģ����ֵ
int GetObjAnaRunVal(CSgRDBObject &RDBObject, int64_t id)
{
    int MeasyType = 21;     //P,�й�
    double RtVal;
    int ret = RDBObject.GetObjAnaRunVal(id, -1, MeasyType, &RtVal);

    if(ret)
    {
        cout<<"====================GetObjAnaRunVal success"<<endl;
         cout<<"Object ID="<<id<<", RtVal="<<RtVal<<endl;
    }
    else
    {
        cout<<"====================GetObjAnaRunVal failed"<<endl;
    }

    return ret;
}

//��ø��豸״̬��ֵ
int GetObjDigRunVal(CSgRDBObject &RDBObject, int64_t id)
{
    int MeasyType = 81;     //�豸����״̬
    int RtVal;
    int ret = RDBObject.GetObjDigRunVal(id, -1, MeasyType, &RtVal);

    if(ret)
    {
        cout<<"====================GetObjDigRunVal success"<<endl;
        cout<<"Object ID="<<id<<", RtVal="<<RtVal<<endl;
    }
    else
    {
        cout<<"====================GetObjDigRunVal failed"<<endl;
    }

    return ret;
}

//����豸�����豸�ļ�¼�ź�ID
int GetChildObjRcdNo(CSgRDBObject &RDBObject, int64_t id, int ChildObjType)
{
    VECT_INT ChildRcdNoList;
    VECT_INT64 ChildKIDList;
    int ret = RDBObject.GetChildObjRcdNo(id, ChildObjType, ChildRcdNoList, &ChildKIDList);

    if(ret)
    {
        cout<<"====================GetChildObjRcdNo success"<<endl;
        for(VECT_INT::iterator it = ChildRcdNoList.begin(); it != ChildRcdNoList.end(); it++)
        {
            cout<<"Object ID="<<id<<", ChildObjType="<<ChildObjType<<", ChildRcdNo ="<<*it<<endl;
        }
        for(VECT_INT64::iterator it = ChildKIDList.begin();it != ChildKIDList.end(); it++)
        {
            cout<<"Object ID="<<id<<", ChildObjType="<<ChildObjType<<", ChildKID ="<<*it<<endl;
        }
    }
    else
    {
        cout<<"====================GetChildObjRcdNo failed"<<endl;
    }

    return ret;
}

//��ø��豸��¼��
int GetParentObjRcdNo(CSgRDBObject &RDBObject, int64_t id, int ParentObjType)
{
    SG_INT ParentRcdNo;
    SG_INT64 ParentKID;
    int ret = RDBObject.GetParentObjRcdNo(id, ParentObjType, ParentRcdNo, &ParentKID);

    if(ret)
    {
        cout<<"====================GetParentObjRcdNo success"<<endl;
        cout<<"Object ID="<<id<<", ParentObjType="<<ParentObjType<<", ParentRcdNo ="<<ParentRcdNo<<endl;
        cout<<"Object ID="<<id<<", ParentObjType="<<ParentObjType<<", ParentKID ="<<ParentKID<<endl;
    }
    else
    {
        cout<<"====================GetParentObjRcdNo failed"<<endl;
    }

    return ret;
}

//����豸�����豸���ݼ�
int GetChildObjInfo(CSgRDBObject &RDBObject, int64_t id, int ChildObjType)
{
    char RetFields[]="*";
    CSgDataSet DatSet;
    int ret = RDBObject.GetChildObjInfo(id, ChildObjType, RetFields, DatSet);

    if(ret)
    {
        cout<<"====================GetChildObjInfo success"<<endl;
        
    }
    else
    {
        cout<<"====================GetChildObjInfo failed"<<endl;
    }

    return ret;
}

//��ø��豸��¼����
int GetParentObjInfo(CSgRDBObject &RDBObject, int64_t id, int ParentObjType)
{
    char RetFields[]="*";
    CSgDataSet DatSet;
    int ret = RDBObject.GetParentObjInfo(id, ParentObjType, RetFields, DatSet);

    if(ret)
    {
        cout<<"====================GetParentObjInfo success"<<endl;
        
    }
    else
    {
        cout<<"====================GetParentObjInfo  failed"<<endl;
    }

    return ret;
}

int main(int argc, char *argv[])
{
    int schemaHandler = 1;

    //�����ڴ��
    CSgRDBMemOverall* pRdbmem = new CSgRDBMemOverall(schemaHandler);
    int ret = pRdbmem->CreateShareMemory();
    if(!ret)
    {
        cout<<"\r\CreateShareMemory failed"<<endl;
    }
    else
    {
        cout<<"\r\CreateShareMemory sucessed"<<endl;
    }

    //����ʵʱ�����
    CSgRDBObject BreakObject(schemaHandler);
    CSgRDBObject FeederObject(schemaHandler);

    ret = BreakObject.OpenTableByObjType(OBJTYPE_BREAKER);
    if(ret)
    {
        cout<<"====================OpenTableByObjType success"<<endl;
    }
    else
    {
        cout<<"====================OpenTableByObjType failed"<<endl;
    }
    ret = FeederObject.OpenTableByObjType(200);
    if(ret)
    {
        cout<<"====================OpenTableByObjType success"<<endl;
    }
    else
    {
        cout<<"====================OpenTableByObjType failed"<<endl;
    }

    int64_t FeederID = 200000000000002;
    int64_t BreakerID = 209000000000040;

    ret = GetObjTerminal(BreakObject, BreakerID);

    ret = GetObjConnectNode(BreakObject, BreakerID);

    ret = GetObjConnectObj(BreakObject, BreakerID);

    ret = GetObjAnaRunVal(BreakObject, BreakerID);

    ret = GetObjDigRunVal(BreakObject, BreakerID);

    ret = GetChildObjRcdNo(FeederObject, FeederID, 209);

    ret = GetParentObjRcdNo(BreakObject, BreakerID, 200);

    ret = GetChildObjInfo(FeederObject, FeederID, 209);

    ret = GetParentObjInfo(BreakObject, BreakerID, 200);

    //�ͷ�ʵʱ��
    ret = pRdbmem->FreeShareMemory();
    if(!ret)
    {
        cout<<"\r\FreeShareMemory failed"<<endl;
    }
    else
    {
        cout<<"\r\FreeShareMemory sucessed"<<endl;
    }

    if(pRdbmem) delete pRdbmem;

    return ret;
}