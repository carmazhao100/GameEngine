#include "NetWorker.h"

IMPLEMENT_OBJ_POOL(NetMsg)
NetMsg::NetMsg(){
	if (m_data == NULL)
	{
			m_data = new int_8[INI_LENGTH];
	}
	m_cur = m_data;
	m_limit = INI_LENGTH;
	m_data_size = 0;
}
NetMsg::~NetMsg(){
}

int_32	NetMsg::get_data_size() {
	return m_data_size;
}
int_8*	NetMsg::get_data() {
	return m_data;
}


void NetMsg::write_int_32(int_32  _data) {
	int_32			_needed_size = 0;

	_data = htonl(_data);
	if (NULL == m_data)
	{
			return;
	}
	_needed_size = m_data_size + sizeof(_data);

	if(_needed_size > m_limit) {
		expand_mem();
	}
	memcpy(m_cur , &_data , sizeof(_data));
	m_cur += sizeof(_data);
	m_data_size += sizeof(_data);
}


void NetMsg::write_int_8(int_8 _data) {
	int_32			_needed_size = 0;

	if (NULL == m_data)
	{
		return;
	}
	_needed_size = m_data_size + sizeof(_data);

	if(_needed_size > m_limit) {
		expand_mem();
	}
	memcpy(m_cur , &_data , sizeof(_data));
	m_cur += sizeof(_data);
	m_data_size += sizeof(_data);
}

void NetMsg::write_str(int_8* _str, uint_32  _size) {
	int_32			_needed_size = 0;
 
	_needed_size = m_data_size;
	_needed_size += _size;
	_needed_size += sizeof(_size);

	if (NULL == m_data)
	{
		return;
	}

	if(_needed_size > m_limit) {
		expand_mem();
	}
//change to net size
	_size = htonl(_size);
	memcpy(m_cur , &_size, sizeof(_size));
	m_cur += sizeof(_size);
//change to host size
	_size = ntohl(_size);
	
	memcpy(m_cur , _str, _size);
	m_cur += _size;

	m_data_size += sizeof(_size);
	m_data_size += _size;
}
 
void NetMsg::expand_mem() {
	int_8*			_temp = NULL;
	
	m_limit = m_limit + INTER;
	_temp = new int_8[m_limit];
	memcpy(_temp , m_data , m_data_size);
	delete m_data;
	m_data = _temp;
	m_cur = m_data + m_data_size;
}
/*=================NET  QUEUE==========================*/
IMPLEMENT_SINGLE_MODEL(MsgQueue)

MsgQueue::MsgQueue() {
	m_mutex = CreateMutex(NULL , false , (LPCWSTR)MUTEX_NAME);
	if(!m_mutex) { 
		if(ERROR_ALREADY_EXISTS==GetLastError()) { 
			std::cout<<"repeated mutex name in:MsgQueue!"<<std::endl; 
			return; 
		} 
	}
}

MsgQueue::~MsgQueue() {
	
}

void	MsgQueue::push_in(proxyMsg * _msg) {
	 WaitForSingleObject(m_mutex , INFINITE);
	if (m_queue.size() > MAX_AFFAIR_NUM)
	{
		ReleaseMutex(m_mutex);
		return;
	}
	m_queue.push(_msg);
	ReleaseMutex(m_mutex);	
}

proxyMsg* MsgQueue::pop_out() {
	proxyMsg*		_result = NULL;
	DWORD					_res;

	_res = WaitForSingleObject(m_mutex , 0);
	if(_res == WAIT_TIMEOUT) {
		ReleaseMutex(m_mutex);
		return NULL;
	}
	if(m_queue.size() != 0) {
		_result = m_queue.front();
		m_queue.pop();
	}
	ReleaseMutex(m_mutex);
	return _result;
}
/*=================NET  WORKER==========================*/

IMPLEMENT_SINGLE_MODEL(NetWorker)
NetWorker::NetWorker(){
	m_msg_buff = NULL;
}

NetWorker::~NetWorker(){
}

int_32 NetWorker::connect_server() {
	int_32				_res = 0;
	WSADATA				_wsdata;
	struct sockaddr_in	_addr; 

	if ( WSAStartup(MAKEWORD(2,2), &_wsdata) != 0 ){
		std::cout<<"Init Windows Socket Failed::"<<GetLastError()<<std::endl;
			return INITIAL_SOCKE_ERROR;
	}

	m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( m_fd == INVALID_SOCKET ){
		std::cout<<"Create Socket Failed::"<<GetLastError()<<std::endl;
		return CREATE_SOCKET_ERROR;
	}


	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr("192.168.1.115");
	_addr.sin_port = htons(8801);
	memset(_addr.sin_zero, 0x00, 8);

	_res = connect(m_fd,(struct sockaddr*)&_addr, sizeof(_addr));
	if ( _res == SOCKET_ERROR ){
		std::cout<<"Connect Error::"<<GetLastError()<<std::endl;
		return SOCKET_CONNECT_ERROR;
	}
	return 0;
}

void NetWorker::send_msg(NetMsg *_msg) {
	int_32		_res = 0;

	_res =  send(m_fd ,_msg->get_data() , _msg->get_data_size() , 0);
	if (!_res)
	{
		std::cout<<"Send Info Error::"<<GetLastError()<<std::endl;
	}
}

DWORD WINAPI rev_thread(LPVOID _lpParameter) {
	(static_cast<NetWorker*>(_lpParameter))->rev_deal();
	return 0;
}

void NetWorker::create_rev_thread() {
	m_thread = CreateThread(NULL , 0 , rev_thread , (LPVOID)this , 0 , NULL);
	if ( m_thread == NULL ){
		std::cout<<"Create Thread Failed!"<<std::endl;
	}
}

void NetWorker::rev_deal() {
	int_8*			_cur_pos = NULL;
	int_32			_res = 0;
	int_32			_size = 0;
	proxyMsg*		_p_msg = NULL;
	while (true)
	{
		memset(m_buff , 0 , MAX_PATH);
		_res = recv(m_fd , m_buff , MAX_PATH , 0);
		if(_res == 0 || _res == SOCKET_ERROR) {
			std::cout<<"rev thread receive error!"<<std::endl;
		}
		_cur_pos = m_buff;
		if(m_msg_buff == NULL) {
			m_msg_buff = new int_8[INI_MSG_LENGTH];
			m_msg_buff_size = INI_MSG_LENGTH;
		}

		while (_res > 0){
			memcpy(&_size , _cur_pos , sizeof(_size));
			_size = ntohl(_size);

			_cur_pos += sizeof(_size);
			_res -= sizeof(_size);

			if(m_msg_buff_size < _size) {
				delete m_msg_buff;
				m_msg_buff_size += INTER_MSG;
				m_msg_buff = new int_8[m_msg_buff_size];
			}
			if(m_msg_buff == NULL) {
				return;
			}
			memcpy(m_msg_buff , _cur_pos , _size);
			_cur_pos += _size;

			_res -= _size;

			_p_msg = new proxyMsg(m_msg_buff , _size);
			MsgQueue::get_instance()->push_in(_p_msg);
		}
	}
}

