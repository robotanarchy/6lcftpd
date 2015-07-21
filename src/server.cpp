#include "server.hpp"
#include <iostream>
#include <list>
#include <string>

using namespace std;

server::server(config* cfg)
{
	this->cfg = cfg;
	tcp::endpoint end;
	
	// parse the IP
	try
	{
		address addr = addr.from_string(cfg->get_opt("ipadr"));
		cout << "listening on: " << addr << endl;
		end.address(addr);
	}
	catch(exception &e)
	{
		throw runtime_error("Failed to parse the IP address that you've"
			" specified.\nasio says: " + string(e.what()));
	}
	
	
	// bind the control port
	list<int> ports = {21, 2111, 2221, 2121, 21111, 22221};
	for(auto port: ports)
	{
		cout << "trying to host on port " << port << ": (stub)" << endl;
		end.port(port);
	}
	
	
	cout << "server stub done." << endl;
	this->end = end;
}
