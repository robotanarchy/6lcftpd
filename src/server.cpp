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
	
	cout << "control socket connected! (count: "
		<< m_ctrl_connected.size() << ")" << endl;
	
	m_ctrl_connected.push_back(sock);
}

void server::mainloop()
{
	cout << "waiting for connections." << endl;
	while(1)
	{
		accept();
		
		if(!m_tcp->check(100)) continue;
		
		for(auto sock : m_ctrl_connected)
		{
			try
			{
				string in = sock->recv(5);
				cout << "(" << sock << ") received: " << in << endl;
			}
			catch(exception e)
			{
				cout << "(" << sock << ") disconnected" << endl;
				m_tcp->del(sock);
				m_ctrl_connected.erase(remove(m_ctrl_connected.begin(),
					m_ctrl_connected.end(), sock),
					m_ctrl_connected.end());
			}
		}
	}
}
