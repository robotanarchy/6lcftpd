#include "server.hpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

server::server(config& cfg, list<uint16_t> ports)
	: m_cfg{cfg}
{
	// bind the control port
	for(auto port: ports)
	{
		cout << "trying to listen on port " << port << "...";
		try
		{
			m_listen = new socket_listen(port);
			cout << "OK!" << endl;
			break;
		}
		catch(exception &e)
		{
			cout << "NEXT! (" << e.what() << ")" << endl;
		}
	}
	
	if(!m_listen)
		throw runtime_error("Failed to listen on any FTP-ish port"
			" number, giving up.");
}

server::~server()
{
	delete m_listen;
}

void server::mainloop()
{
	cout << "waiting for connections." << endl;
	
	while(1)
	{
		// TODO: accept connections, spawn sessions, sleep, repeat
		// also fill a vector of sessions.
		
		socket_ctrl* ctrl = m_listen->accept_ctrl();
		if(!ctrl)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		
		session* s = new session(*ctrl, m_cfg);
		m_sessions.push_back(s);
	}
}
