#pragma once
#include "config.hpp"
#include "tcp.hpp"
#include <vector>


class server
{
	public:
		server(config* cfg, tcp* tcp_arg);
		void mainloop();
	
	private:
		config* m_cfg;
		tcp* m_tcp;
		tcpsock* m_ctrl_listen;
		
		vector<tcpsock*> m_ctrl_connected;
		
		void accept();
		string control_protocol(string msg);
};
