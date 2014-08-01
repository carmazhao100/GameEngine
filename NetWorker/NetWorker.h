/*==========================================
/!Author:	carmazhao
/!Date:		2011/12/29
/!Function:	the interface of the Socket module
		     and the netMsg to write data
===========================================*/
#ifndef NET_WORKER_HEAD_
#define NET_WORKER_HEAD_
#include "../Main/sysDef.h"
#include "../Msg/proxyMsg.h"
#include <queue>

#define INI_LENGTH 56
#define INTER      32

class NetMsg
{
	DEFINE_OBJ_POOL(NetMsg)
public:
	NetMsg();
	~NetMsg();

	void		write_int_32(int_32);
	void		write_int_8(int_8 );
	void		write_str(int_8* ,  uint_32 );

	int_32		get_data_size();
	int_8*		get_data();
private:
	int_32		m_limit;
	int_32		m_data_size;
	int_8*		m_cur;
	int_8*		m_data;

	void		expand_mem();
};

#define MUTEX_NAME "_msg_queue_mutex_name"
#define	MAX_AFFAIR_NUM	200
class MsgQueue {
	DEFINE_SINGLE_MODEL(MsgQueue)
private:
	std::queue<proxyMsg *>	m_queue;
	HANDLE					m_mutex;
	HANDLE					m_sem;

	MsgQueue();	
public:
	~MsgQueue();

	void				push_in(proxyMsg *);
	proxyMsg*			pop_out();
};

#define INI_MSG_LENGTH	56
#define	INTER_MSG		32
class NetWorker
{
	DEFINE_SINGLE_MODEL(NetWorker)
public:
	~NetWorker();
	int_32		connect_server();			//connect server
	void		send_msg(NetMsg*	_msg);	//send message
	void		rev_deal();					//get message
	void		create_rev_thread();		//open a thread
	
private:
	NetWorker();

	SOCKET		m_fd;
	HANDLE		m_thread;
	int_8		m_buff[MAX_PATH];		//buf to receive the data

	int_8*		m_msg_buff;				//buf of every cut msg
	int_32		m_msg_buff_size;		//size of msg buf
};
#endif