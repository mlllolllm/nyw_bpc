#include "rdbmem.h"
#include "auto_rtbl_plat.h"
#include "avc/avcdataimport.h"

#ifdef _WIN64
#pragma comment (lib,"dppclientMD64.lib")
#pragma comment (lib,"MDBMD64.lib")
#pragma comment (lib,"sdbMD64.lib")
#else
#endif

using namespace std;

CAVCDataImport::CAVCDataImport()
{

}

CAVCDataImport::~CAVCDataImport()
{

}

void CAVCDataImport::SetRDBSchemaHandler(int schemaHandler)
{
	m_SchemaHandler = schemaHandler;
}

int CAVCDataImport::ReadModels(std::vector<MODEL_D_COMPENSATOR> vCompensators)
{
	CSgRDBTable rdbTable(m_SchemaHandler); 
	int ret = rdbTable.OpenTable("MODEL_D_COMPENSATOR",1,1,0);   
    if(!ret)
	{
		cout<<"OpenTable MODEL_D_COMPENSATOR failed"<<endl;
		return -1;   
	}

	int recNum = rdbTable.GetRcdNum(); 
	cout<<"MODEL_D_COMPENSATOR RecNum="<<recNum<<endl;
	if(recNum < 1)
	{		
		return -1;   
	}

	void * p = rdbTable.GetFirstRcd();
    if(p!=NULL)
    {
        cout<<"p="<<p<<endl;
        MODEL_D_COMPENSATOR * pCompensator = (MODEL_D_COMPENSATOR*)p;
        for(int i=0; i<recNum; i++, pCompensator++)
        {
            //cout<<"breaker pointer="<<breaker<<endl;     
            cout<<"ID="<<pCompensator->ID<<",NAME="<<pCompensator->NAME<<endl;
        }
    }
    else
    {
        cout<<"pointer is null."<<endl;
    }

	return 0;
}

int CAVCDataImport::ReadConfig(std::vector<DAS_CONFIG> dasConfigs, AVC_CONFIG &avcConfig)
{
	for (vector<DAS_CONFIG>::iterator it = dasConfigs.begin(); it != dasConfigs.end(); it++)
	{
		std::cout<<it->NAME<<std::endl;

#ifdef WIN64
		if (_stricmp(it->NAME, "avc_IsShortOptimConfirm") == 0)
		{
			avcConfig.avc_IsShortOptimConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (_stricmp(it->NAME, "avc_IsShortOptimCycleConfirm") == 0)
		{
			avcConfig.avc_IsShortOptimCycleConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (_stricmp(it->NAME, "avc_ShortOptimlCycleInterval") == 0)
		{
			avcConfig.avc_ShortOptimlCycleInterval = it->INTVALUE;
		}
		else if (_stricmp(it->NAME, "avc_IsLongOptimConfirm") == 0)
		{
			avcConfig.avc_IsLongOptimConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (_stricmp(it->NAME, "avc_IsLongOptimCycleConfirm") == 0)
		{
			avcConfig.avc_IsLongOptimCycleConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (_stricmp(it->NAME, "avc_LongOptimlCycleInterval") == 0)
		{
			avcConfig.avc_LongOptimlCycleInterval = it->INTVALUE;
		}
		else if (_stricmp(it->NAME, "avc_IsConsiderCB") == 0)
		{
			avcConfig.avc_IsConsiderCB = it->INTVALUE == 0 ? false : true;
		}
#else
		if (strcasecmp(it->NAME, "avc_IsShortOptimConfirm") == 0)
		{
			avcConfig.avc_IsShortOptimConfirm = it->INTVALUE == 0 ? false : true;
		}		
		else if (strcasecmp(it->NAME, "avc_IsShortOptimCycleConfirm") == 0)
		{
			avcConfig.avc_IsShortOptimCycleConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (strcasecmp(it->NAME, "avc_ShortOptimlCycleInterval") == 0)
		{
			avcConfig.avc_ShortOptimlCycleInterval = it->INTVALUE;
		}
		else if (strcasecmp(it->NAME, "avc_IsLongOptimConfirm") == 0)
		{
			avcConfig.avc_IsLongOptimConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (strcasecmp(it->NAME, "avc_IsLongOptimCycleConfirm") == 0)
		{
			avcConfig.avc_IsLongOptimCycleConfirm = it->INTVALUE == 0 ? false : true;
		}
		else if (strcasecmp(it->NAME, "avc_LongOptimlCycleInterval") == 0)
		{
			avcConfig.avc_LongOptimlCycleInterval = it->INTVALUE;
		}
		else if (strcasecmp(it->NAME, "avc_IsConsiderCB") == 0)
		{
			avcConfig.avc_IsConsiderCB = it->INTVALUE == 0 ? false : true;
		}
#endif
	}

	return 0;
}

