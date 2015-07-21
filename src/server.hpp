#pragma once
#include "config.hpp"
#include "tcp.hpp"


class server
{
	public:
		server(config* cfg, tcp* net);
	
	private:
		config* cfg;
		tcp* net;
};
