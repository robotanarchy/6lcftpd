#include "socket.hpp"

socket::socket()
{
	m_socket_set_sdl = SDLNet_AllocSocketSet(1);
}


socket::socket(TCPsocket socket_sdl)
	: socket()
{
	m_socket_sdl = socket_sdl;
	SDLNet_TCP_AddSocket(m_socket_set_sdl, m_socket_sdl);
}


/*
	One would try to simply wrap "SDLNet_SocketReady()" here, but this
	doesn't work: "This function should only be used on a socket in a
	socket set, and that set has to have had SDLNet_CheckSockets [...]
	called upon it." (from the SDL_Net documentation).
	It really doesn't work without the socket set, I've tried it out.
	So we use one socket set per socket and check that for activity.
*/
bool socket::ready(uint32_t timeout_ms)
{
	int ret = SDLNet_CheckSockets(m_socket_set_sdl, timeout_ms);
	if(ret < 0)
		throw runtime_error(string("SDL: ") + SDLNet_GetError());
	return ret > 0;
}


socket_listen::socket_listen(uint16_t port)
{
	IPaddress ip;
	SDLNet_ResolveHost(&ip, nullptr, port);
	
	m_socket_sdl = SDLNet_TCP_Open(&ip);
	if(!m_socket_sdl)
		throw runtime_error(string("SDL: ") + SDLNet_GetError());
}


socket_ctrl* socket_listen::accept_ctrl()
{
	TCPsocket socket_sdl = SDLNet_TCP_Accept(m_socket_sdl);
	return socket_sdl ? new socket_ctrl(socket_sdl) : nullptr;
}

socket_data* socket_listen::accept_data()
{
	TCPsocket socket_sdl = SDLNet_TCP_Accept(m_socket_sdl);
	return socket_sdl ? new socket_data(socket_sdl) : nullptr;
}


string socket_ctrl::recv(uint16_t maxlen)
{	
	string line = "";
	char buffer;
	for(uint16_t i=0;i<maxlen;i++)
	{
		int ret = SDLNet_TCP_Recv(m_socket_sdl, &buffer, 1);
		if(ret < 1) throw runtime_error("Connection closed!");
		if(buffer == '\r') continue;
		if(buffer == '\n') break;
		line += buffer;
	}
	cout << "[" << this << "] recv: " << line << endl;
	return line;
}

void socket_ctrl::send(string line)
{
	cout << "[" << this << "] send: " << line << endl;
	
	line += "\r\n";
	SDLNet_TCP_Send(m_socket_sdl, line.data(), line.size());
}
