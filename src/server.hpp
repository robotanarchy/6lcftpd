#pragma once
#include "config.hpp"
#include <asio.hpp>


using namespace asio::ip;

class server
{
	public:
		server(config* cfg);
	
	private:
		config* cfg;
		tcp::endpoint end;
};
