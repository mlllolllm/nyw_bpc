
#ifndef	SGNP_EVENT_H_
#define	SGNP_EVENT_H_

#include "sgnp_base.h"	

//��ע�����лص�����������������ƽ̨���߳��У�ע�⴦���������µ����ݱ���
class SgMail;
class SGNP_EventSlot
{
public:
	
	virtual ~SGNP_EventSlot(){};
	/*  
		���ܣ�����ϵͳ����ʱ�������ûص�
	*/
	virtual void OnSysEvent(SGNP_Event& event){}
	/*  
		���ܣ��������ʼ�����ʱ�����ʼ���������֮ǰ�������ûص�
		�������ֵΪ0������ʼ����ԣ����򲻽���
	*/
	virtual int OnMailEvent(SgMail*pMail){ return 0; }
	
};

#endif
