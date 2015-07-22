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

string tcpsock::recv_line(uint16_t maxlen)
{
	string line = "";
	char buffer;
	for(uint16_t i=0;i<maxlen;i++)
	{
		int ret = SDLNet_TCP_Recv(m_sock_sdl, &buffer, 1);
		if(ret <=0) throw runtime_error("Connection closed!");
		if(buffer == '\r') continue;
		if(buffer == '\n') break;
		line += buffer;
	}
	return line;
}

void tcpsock::send_line(string line)
{
	line = line + "\r\n";
	SDLNet_TCP_Send(m_sock_sdl, line.data(), line.size());
}

TCPsocket tcpsock::get_sdl()
{
	return m_sock_sdl;
}
