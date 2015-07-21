#pragma once
#include "config.hpp"
#include "tcp.hpp"


// FIXME: is there a better way than putting this in a define?
#define MAX_SOCKETS 100



class server
{
	public:
		server(config* cfg);
	
	private:
		config* cfg;
		tcp net{MAX_SOCKETS};
};
