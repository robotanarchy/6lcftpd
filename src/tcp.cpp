#include "tcp.hpp"
#include <string>
#include <iostream>

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

tcpsock* tcp::socket_open(uint16_t port)
{
	if(m_socks.size() >= m_socks_max)
		throw runtime_error("Socket limit reached, won't create a new"
			" one!");
	
	tcpsock* sock = new tcpsock(port, m_sockset_sdl);
	m_socks.push_back(sock);
	return sock;
}



