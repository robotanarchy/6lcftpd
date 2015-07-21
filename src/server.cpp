#include "server.hpp"
#include <iostream>
#include <list>
#include <string>

using namespace std;

server::server(config* cfg)
{
	this->cfg = cfg;

	// bind the control port
	list<uint16_t> ports = {21, 2111, 2221, 2121, 21111, 22221};
	for(auto port: ports)
	{
		cout << "trying to host on port " << port << "...";
		try
		{
			/*this->sock_control_listen = */net.socket_open(port);
			cout << "OK!" << endl;
			break;
		}
		catch(exception &e)
		{
			cout << "NEXT! (" << e.what() << ")" << endl;
		}
	}
	
	cout << "server stub done." << endl;
}
