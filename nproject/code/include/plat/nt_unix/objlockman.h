// useappenv.h: interface for the CAppEnvMan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_OBJ_LOCK_MAN_H_)
#define _OBJ_LOCK_MAN_H_

#include "sgconst.h"
//#include "sgdef.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ACE_RW_Thread_Mutex;
#include <ace/Recursive_Thread_Mutex.h>
//��д��
class _DATASET_DLL_EXPORT_ CObjLock_RW
{
public:
	CObjLock_RW();
	virtual ~CObjLock_RW();
	
public:
	// --- �����Ʒ���
	void CreateLock();
	void LockRead();
	void LockWrite();
	void UnLock();
	SG_BOOL TryLockRead();
	SG_BOOL TryLockWrite();
	SG_BOOL IsLockExist();

private:
	ACE_RW_Thread_Mutex	*m_ObjLock;
};
//��д������
class _DATASET_DLL_EXPORT_ CObjLockMan_RW
{
public:
	CObjLockMan_RW(CObjLock_RW*p,SG_BOOL ReadLock=true);
	~CObjLockMan_RW();
protected:
	CObjLock_RW *m_pObjLock;
};


//����ݹ���
//,2008-08-15
//�ı�virtual����Ϊ��virtual
//�ı�˵�г�ԱΪ����
class _DATASET_DLL_EXPORT_ CObjLock_RCS
{
public:
	CObjLock_RCS()
	{
		m_ObjLock = NULL;
	}
	~CObjLock_RCS()
	{
		if(m_ObjLock) 
		{
			delete m_ObjLock;
			m_ObjLock=NULL;
		}
	}

public:

	//ȷ���ú����ڵ��̻߳����б�����
	void CreateLock()
	{
		if(!m_ObjLock)
			m_ObjLock = new ACE_Recursive_Thread_Mutex;
	}
	//void CObjLock_RCS::Lock()
	//{
	//	if(!m_ObjLock)return;
	//	m_ObjLock->acquire();
	//}
	void UnLock()
	{
		if(0==m_ObjLock) return;
		m_ObjLock->release();
	}

	SG_BOOL TryLock()
	{
		if(!m_ObjLock)return false;
		return m_ObjLock->tryacquire()!=-1;
	}

	SG_BOOL IsLockExist()
	{
		return m_ObjLock!=NULL;
	}

	void LockRead()
	{
		if(!m_ObjLock)return;
		m_ObjLock->acquire();
	}

	void LockWrite()
	{
		if(!m_ObjLock)return;
		m_ObjLock->acquire();
	}

	SG_BOOL TryLockRead()
	{
		if(!m_ObjLock)return false;
		return m_ObjLock->tryacquire()!=-1;
	}

	SG_BOOL TryLockWrite()
	{
		if(!m_ObjLock)return false;
		return m_ObjLock->tryacquire()!=-1;
	}

private:
	ACE_Recursive_Thread_Mutex	*m_ObjLock;
};

//�ݹ�������
class _DATASET_DLL_EXPORT_ CObjLockMan_RCS
{
public:
	CObjLockMan_RCS(CObjLock_RCS *p,SG_BOOL ReadLock=true);
	~CObjLockMan_RCS();
protected:
	CObjLock_RCS *m_pObjLock;
};


#endif // !defined(_OBJ_LOCK_MAN_H_)
