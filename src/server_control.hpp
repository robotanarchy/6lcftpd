#pragma once
#include "tcp.hpp"
#include "config.hpp"


class server_control
{
	public:
		server_control(tcpsock* sock, config* config);
		string answer(string msg);
		
		tcpsock* get_sock();
		
	private:
		tcpsock* m_sock;
		string m_pwd;
		config* m_cfg;
};
