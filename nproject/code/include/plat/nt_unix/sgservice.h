#ifndef _SG_SERVICE_INCLUDED_
#define _SG_SERVICE_INCLUDED_

#ifdef ACE_WIN32
#include "NTService.h"
#endif
#include "sgnp_export.h"
class SG_Inifile;
class CP_ProcManager;
class SGNP_Export SG_Service
#ifdef ACE_WIN32
: public CNTService
#endif
{
	friend class QuitCmdTimer;
public:

	SG_Service(const char*svc_name,const char*dsp_name);
	virtual	~SG_Service();

public:	

	virtual int		run(int,char**);
	virtual void	Run(int, char**);
	virtual void	Stop();
	virtual int		load_module(int argc,char**argv);
//	virtual int		is_svc_installed(const char* svc_name);
protected:
private:
	int CheckLicense();
protected:
	virtual void	OnStart();
	virtual void	OnClose();
	int load_module_i(SG_Inifile&,const char*,const char*,int,const char*para=NULL);
	char * svc_name_;
	
	char * * svc_argv_;
	int svc_argc_;

	CP_ProcManager* pm_;
};

#endif
