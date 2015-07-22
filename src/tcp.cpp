#include "tcp.hpp"
#include <string>
#include <iostream>
#include <algorithm>

tcp::tcp(uint16_t socks_max)
{
	m_sockset_sdl = SDLNet_AllocSocketSet(socks_max);
	m_socks_max   = socks_max;
}

tcp::~tcp()
{
	for(auto sock : m_socks)
		delete sock;
	SDLNet_FreeSocketSet(m_sockset_sdl);
}

void tcp::add(tcpsock* sock)
{
	if(m_socks.size() >= m_socks_max)
		throw runtime_error("Socket limit reached, throwing the new one"
			" away!");
	
	m_socks.push_back(sock);
	SDLNet_TCP_AddSocket(m_sockset_sdl, sock->get_sdl());
}

void tcp::del(tcpsock* sock)
{
	m_socks.erase(remove(m_socks.begin(), m_socks.end(), sock),
		m_socks.end());
	SDLNet_TCP_DelSocket(m_sockset_sdl, sock->get_sdl());
	delete sock;
}

tcpsock* tcp::listen(uint16_t port)
{
	tcpsock* sock = new tcpsock(port);
	add(sock);
	return sock;
}

tcpsock* tcp::accept(tcpsock* listen_sock)
{
	TCPsocket sock_sdl = SDLNet_TCP_Accept(listen_sock->get_sdl());
	if(!sock_sdl) return nullptr;
	
	tcpsock* sock = new tcpsock(sock_sdl);
	add(sock);
	return sock;
}

// Returns true when at least one socket has activity
bool tcp::check(uint32_t timeout_ms)
{
	return SDLNet_CheckSockets(m_sockset_sdl, timeout_ms) != -1;
}
