#pragma once
#include "config.hpp"
#include "server_control.hpp"
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
		
		vector<server_control*> m_ctrl_connected;
		
		void accept();
};
