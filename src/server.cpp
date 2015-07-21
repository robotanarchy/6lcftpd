#include "server.hpp"
#include <iostream>
#include <asio.hpp>
#include <list>
#include <string>

using namespace std;
using namespace asio::ip;

server::server(config* cfg)
{
	this->cfg = cfg;
	
	// parse the IP
	try
	{
		address addr = addr.from_string(cfg->get_opt("ipadr"));
		cout << "Listening on: " << addr << endl;
	}
	catch(exception &e)
	{
		throw runtime_error("Failed to parse the IP address that you've"
			" specified.\nasio says: " + string(e.what()));
	}
	
	
	
	// bind the control port
	tcp::endpoint ctrl;
	list<int> ports = {21, 2111, 2221, 2121, 21111, 22221};
	for(auto port: ports)
	{
		cout << "trying to host on port " << port << ":" << endl;
		
	}
	
	
	cout << "server stub done." << endl;
}
