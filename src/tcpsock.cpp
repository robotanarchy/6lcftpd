#include "tcp.hpp"
#include <iostream>


tcpsock::tcpsock(TCPsocket sock_sdl)
{
	m_sock_sdl = sock_sdl;
}

tcpsock::tcpsock(uint16_t port)
{
	// open the socket
	// NOTE: SDL_Net can only host on all interfaces at once!
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, port);
	
	m_sock_sdl = SDLNet_TCP_Open(&ip);
	if(!m_sock_sdl)
		throw runtime_error(string("SDL: ") + SDLNet_GetError());
}

tcpsock::~tcpsock()
{
	// FIXME: Somehow this gets called to often and results in a
	// segfault. When commented out, we have a memory leak of course.
	// if(m_sock_sdl)
	//	SDLNet_TCP_Close(m_sock_sdl);
}

bool tcpsock::ready()
{
	return SDLNet_SocketReady(m_sock_sdl);
}

string tcpsock::recv(uint16_t len)
{
	char buffer[len+1];
	int ret = SDLNet_TCP_Recv(m_sock_sdl, &buffer, len);
	if(ret <=0) throw runtime_error("Connection closed!");
	return string(buffer);
}

TCPsocket tcpsock::get_sdl()
{
	return m_sock_sdl;
}
