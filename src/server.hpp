#pragma once
#include "config.hpp"
#include "tcp.hpp"


class server
{
	public:
		server(config* cfg, tcp* tcp_arg);
	
	private:
		config* m_cfg;
		tcp* m_tcp;
};
