

#ifndef _SET_SIGALS_H_
#define _SET_SIGALS_H_

// #ifdef _DEBUG
// 	#define FunctorT0 F0
// 	#define FunctorT1 F1
// 	#define FunctorT2 F2
// 	#define FunctorT3 F3
// 	#define FunctorT4 F4
// 	#define FunctorT5 F5
// 	#define FunctorT6 F6
// 
// 	#define SignalHandler0 H0
// 	#define SignalHandler1 H1
// 	#define SignalHandler2 H2
// 	#define SignalHandler3 H3
// 	#define SignalHandler4 H4
// 	#define SignalHandler5 H5
// 	#define SignalHandler6 H6
// 
// 	#define		signals	S
// 	#define		signal0 S0
// 	#define		signal1 S1
// 	#define		signal2 S2
// 	#define		signal3 S3
// 	#define		signal4 S4
// 	#define		signal5 S5
// 	#define		signal6 S6
// 
// #endif

#pragma warning (disable : 4231)
#pragma warning (disable : 4786)

#include <vector>
#include <algorithm>


namespace SET
{
	//signal hander base class
	template <typename ReturnT>
	class Func0
	{
	public:
		Func0(){ m_block = false; }
		virtual ReturnT notify() = 0;	
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};

	template <typename ReturnT,typename ParamT>
	class Func1
	{
	public:
		Func1(){ m_block = false; }
		virtual ReturnT notify(ParamT) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};

	template <typename ReturnT,typename ParamT1,typename ParamT2>
	class Func2
	{
	public:
		Func2(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};

	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3>
	class Func3
	{
	public:
		Func3(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2,ParamT3) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4>
	class Func4
	{
	public:
		Func4(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2,ParamT3,ParamT4) = 0;	
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5>
	class Func5
	{
	public:
		Func5(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6>
	class Func6
	{
	public:
		Func6(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};

	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6,typename ParamT7>
	class Func7
	{
	public:
		Func7(){ m_block = false; }
		virtual ReturnT notify(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7) = 0;
		void block(bool b)	{ m_block =b;}
		bool block(){return m_block; }

	protected:
		bool m_block;
	};

	//signal hander class
	template <typename ListenerT,typename ReturnT>
	class Listener0 : public Func0<ReturnT>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)();
		ListenerT* m_object;
		PtrMember m_member;
	
	public:
	
		Listener0(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify()
		{
			return (m_object->*m_member)();		
		}	
	};

	template <typename ListenerT,typename ReturnT,typename ParamT>
	class Listener1 : public Func1<ReturnT,ParamT>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
	
		Listener1(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT param)
		{
			return (m_object->*m_member)(param);		
		}	
	
	};

	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2>
	class Listener2 : public Func2<ReturnT,ParamT1,ParamT2>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener2(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2)
		{
			return (m_object->*m_member)(param1,param2);		
		}	
	};

	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3>
	class Listener3 : public Func3<ReturnT,ParamT1,ParamT2,ParamT3>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2,ParamT3);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener3(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2,ParamT3 param3)
		{
			return (m_object->*m_member)(param1,param2,param3);		
		}	

	};
	
	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4>
	class Listener4 : public Func4<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2,ParamT3,ParamT4);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener4(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4)
		{
			return (m_object->*m_member)(param1,param2,param3,param4);		
		}	
	};

	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5>
	class Listener5 : public Func5<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener5(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5)
		{
			return (m_object->*m_member)(param1,param2,param3,param4,param5);		
		}	
	};

	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6>
	class Listener6 : public Func6<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener6(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6)
		{
			return (m_object->*m_member)(param1,param2,param3,param4,param5,param6);		
		}
	};

	template <typename ListenerT,typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6,typename ParamT7>
	class Listener7 : public Func7<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7>
	{
		
		typedef ReturnT (ListenerT::*PtrMember)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7);
		ListenerT* m_object;
		PtrMember m_member;
		
	public:
		
		Listener7(ListenerT* object, PtrMember member)
			: m_object(object), m_member(member)
		{}
		
		ReturnT notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6,ParamT7 param7)
		{
			return (m_object->*m_member)(param1,param2,param3,param4,param5,param6,param7);		
		}
	};


	template <typename FunctorT,typename LockT=ACE_Null_Mutex>
	class signals
	{
	public:
		
		typedef FunctorT*	ListenerPtr;

		virtual ~signals()
		{
			ACE_GUARD(LockT,guard,m_lock);

			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				FunctorT* p = this->m_listeners[i];
				if(p) delete p;
			}
			this->m_listeners.clear();
		}

		bool disconnect(ListenerPtr h)
		{
			ACE_GUARD_RETURN(LockT,guard,m_lock,false);
			typename std::vector<FunctorT*>::iterator it=std::find(this->m_listeners.begin(),this->m_listeners.end(),h);
			if(it == this->m_listeners.end())	return false;
			//
			delete *it;
			*it =NULL;

			return true;
		}
		
		bool connected(ListenerPtr h)
		{
			ACE_GUARD_RETURN(LockT,guard,m_lock,false);
			typename std::vector<FunctorT*>::iterator it=std::find(this->m_listeners.begin(),this->m_listeners.end(),h);
			return it != this->m_listeners.end();
		}

	protected:

		void compress_i()
		{
			while(1)
			{
				FunctorT* p =NULL;
				typename std::vector<FunctorT*>::iterator it=std::find(this->m_listeners.begin(),this->m_listeners.end(),p);
				if(it == this->m_listeners.end()) break;
				this->m_listeners.erase(it);
			}
		}
		std::vector<FunctorT*> m_listeners;
		LockT m_lock;
	};


	template <typename ReturnT,typename LockT=ACE_Null_Mutex>
	class signal0 :public signals< Func0<ReturnT> ,LockT>
	{
		
	public:
		typedef Func0<ReturnT> ListenerPtr;
		
		template < typename ListenerT >
		ListenerPtr connect(ListenerT* object, ReturnT ( ListenerT::*member )( ) )
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);

			ListenerPtr p = new Listener0<ListenerT,ReturnT>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		virtual bool notify()
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify();
			}
			this->compress_i();
			return true;
		}
		
		//如果其中一个监听器失败，则停止执行其他监听器
		virtual bool notify_ex()
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify()) return false;
			}
			this->compress_i();
			return true;
		}
	};
	

	template <typename ReturnT,typename ParamT,typename LockT=ACE_Null_Mutex>
	class signal1 :public signals< Func1<ReturnT,ParamT> ,LockT>
	{

	public:
			
		typedef  Func1<ReturnT,ParamT> *ListenerPtr;
		
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p =new Listener1<ListenerT,ReturnT,ParamT>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
	
		virtual bool notify(ParamT param)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param);
			}
			this->compress_i();
			return true;
		}

		virtual bool notify_ex(ParamT param)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param)) return false;
			}
			this->compress_i();
			return true;
		}
	};


	//signal class
	template <typename ReturnT,typename ParamT1,typename ParamT2,typename LockT=ACE_Null_Mutex>
	class signal2 : public signals< Func2<ReturnT,ParamT1,ParamT2> ,LockT>
	{
		
	public:
		typedef Func2<ReturnT,ParamT1,ParamT2> *ListenerPtr;

		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener2<ListenerT,ReturnT,ParamT1,ParamT2>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		virtual bool notify(ParamT1 param1,ParamT2 param2)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2);
			}
			this->compress_i();
			return true;
		}
		
		virtual bool notify_ex(ParamT1 param1,ParamT2 param2)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2)) return false;
			}
			this->compress_i();
			return true;
		}
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename LockT=ACE_Null_Mutex>
	class signal3 : public signals< Func3<ReturnT,ParamT1,ParamT2,ParamT3> ,LockT>
	{
		
	public:
		
		typedef  Func3<ReturnT,ParamT1,ParamT2,ParamT3> *ListenerPtr;
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2,ParamT3))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener3<ListenerT,ReturnT,ParamT1,ParamT2,ParamT3>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		virtual bool notify(ParamT1 param1,ParamT2 param2,ParamT3 param3)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2,param3);
			}
			this->compress_i();
			return true;
		}	
		

		virtual bool notify_ex(ParamT1 param1,ParamT2 param2,ParamT3 param3)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2,param3)) return false;
			}
			this->compress_i();
			return true;
		}
	};

	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename LockT=ACE_Null_Mutex>
	class signal4 : public signals< Func4<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4> ,LockT>
	{
		
	public:
		typedef  Func4<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4> *ListenerPtr;
		
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2,ParamT3,ParamT4))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener4<ListenerT,ReturnT,ParamT1,ParamT2,ParamT3,ParamT4>(object,member);	
			this->m_listeners.push_back(p);
			return p;
		}
		
		
		virtual bool notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,true);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2,param3,param4);
			}
			this->compress_i();
			return true;
		}


		virtual bool notify_ex(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2,param3,param4)) return false;
			}
			this->compress_i();
			return true;
		}
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename LockT=ACE_Null_Mutex>
	class signal5 : public signals< Func5<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5>,LockT >
	{
		
	public:
		typedef Func5<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5> *ListenerPtr;
		
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener5<ListenerT,ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		virtual bool notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5)
		{
			for(size_t i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2,param3,param4,param5);
			}
			this->compress_i();
			return true;
		}	

		virtual bool notify_ex(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(size_t i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2,param3,param4,param5)) return false;
			}
			this->compress_i();
			return true;
		}
	};


	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6,typename LockT=ACE_Null_Mutex>
	class signal6 : public signals< Func6<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6>,LockT >
	{
		
	public:
		typedef Func6<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6> *ListenerPtr;
		
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener6<ListenerT,ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		
		virtual bool notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2,param3,param4,param5,param6);
			}
			this->compress_i();
			return true;
		}

		virtual bool notify_ex(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2,param3,param4,param5,param6)) return false;
			}
			this->compress_i();
			return true;
		}
	};

	template <typename ReturnT,typename ParamT1,typename ParamT2,typename ParamT3,typename ParamT4,typename ParamT5,typename ParamT6,typename ParamT7,typename LockT=ACE_Null_Mutex>
	class signal7 : public signals< Func7<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7>,LockT >
	{
		
	public:
		typedef Func7<ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7> *ListenerPtr;
		
		template <typename ListenerT>
		ListenerPtr connect(ListenerT* object,ReturnT (ListenerT::*member)(ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7))
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,NULL);
			ListenerPtr p = new Listener7<ListenerT,ReturnT,ParamT1,ParamT2,ParamT3,ParamT4,ParamT5,ParamT6,ParamT7>(object,member);
			this->m_listeners.push_back(p);
			return p;
		}
		
		
		virtual bool notify(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6,ParamT7 param7)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(p && !p->block()) p->notify(param1,param2,param3,param4,param5,param6,param7);
			}
			this->compress_i();
			return true;
		}
		
		virtual bool notify_ex(ParamT1 param1,ParamT2 param2,ParamT3 param3,ParamT4 param4,ParamT5 param5,ParamT6 param6,ParamT7 param7)
		{
			ACE_GUARD_RETURN(LockT,guard,this->m_lock,false);
			for(unsigned int i=0;i<this->m_listeners.size();i++)
			{
				ListenerPtr p=this->m_listeners[i];
				if(NULL==p || p->block()) continue;
				if(!p->notify(param1,param2,param3,param4,param5,param6,param7)) return false;
			}
			this->compress_i();
			return true;
		}
	};

}

#endif
