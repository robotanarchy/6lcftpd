#include "server.hpp"
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

server::server(config* cfg, tcp* tcp_arg)
{
	m_cfg = cfg;
	m_tcp = tcp_arg;
	
	// bind the control port
	m_ctrl_listen = nullptr;
	list<uint16_t> ports = {21, 2111, 2221, 2121, 21111, 22221};
	for(auto port: ports)
	{
		cout << "trying to listen on port " << port << "...";
		
		try
		{
			m_ctrl_listen = m_tcp->listen(port);
			cout << "OK!" << endl;
			break;
		}
		catch(exception &e)
		{
			cout << "NEXT! (" << e.what() << ")" << endl;
		}
	}
	
	if(!m_ctrl_listen)
		throw runtime_error("Failed to listen on any FTP-ish port"
			" number, giving up.");
	
	
	cout << "server stub done." << endl;
}

void server::accept()
{
	tcpsock* sock = m_tcp->accept(m_ctrl_listen);
	if(!sock) return;
	
	
	m_ctrl_connected.push_back(new server_control(sock, m_cfg));
	
	cout << "(" << sock << ") connected!" << endl;
}


/*
	TODO:
		- I don't like how it currently accesses the sockets
		- Put that code in server_control.*
		- maybe create a tcpsocket_ctrl class that inherits tcpsocket?
*/

void server::mainloop()
{
	cout << "waiting for connections." << endl;
	while(1)
	{
		accept();
		
		if(!m_tcp->check(100)) continue;
		
		for(auto ctrl : m_ctrl_connected)
		{
			tcpsock* sock = ctrl->get_sock();
			try
			{
				string in = sock->recv_line();
				cout << "(" << ctrl << ") received: " << in << endl;
				string out = ctrl->answer(in);
				cout << "(" << ctrl << ") answered: " << out << endl;
				sock->send_line(out);
			}
			catch(exception e)
			{
				cout << "(" << ctrl << ") disconnected" << endl;
				m_tcp->del(sock);
				m_ctrl_connected.erase(remove(m_ctrl_connected.begin(),
					m_ctrl_connected.end(), ctrl),
					m_ctrl_connected.end());
				delete ctrl;
			}
		}
	}
}
