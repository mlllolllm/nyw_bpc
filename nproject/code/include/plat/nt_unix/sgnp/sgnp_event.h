
#ifndef	SGNP_EVENT_H_
#define	SGNP_EVENT_H_

#include "sgnp_base.h"	

//备注：所有回调函数都允许在网络平台的线程中，注意处理竞争环境下的数据保护
class SgMail;
class SGNP_EventSlot
{
public:
	
	virtual ~SGNP_EventSlot(){};
	/*  
		功能：当有系统事项时，激发该回调
	*/
	virtual void OnSysEvent(SGNP_Event& event){}
	/*  
		功能：当有新邮件来到时，在邮件进入邮箱之前，激发该回调
		如果返回值为0，则此邮件进对，否则不进对
	*/
	virtual int OnMailEvent(SgMail*pMail){ return 0; }
	
};

#endif
