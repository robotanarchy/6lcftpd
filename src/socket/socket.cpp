#include "socket.hpp"

socket::socket()
{
	m_socket_sdl = nullptr;
}

socket::socket(TCPsocket socket_sdl)
{
	m_socket_sdl = socket_sdl;
}


bool socket::ready()
{
	return SDLNet_SocketReady(m_socket_sdl);
}


socket_listen::socket_listen(uint16_t port)
{
	IPaddress ip;
	SDLNet_ResolveHost(&ip, nullptr, port);
	
	m_socket_sdl = SDLNet_TCP_Open(&ip);
	if(!m_socket_sdl)
		throw runtime_error(string("SDL: ") + SDLNet_GetError());
}


// FIXME: use templates? to combine these!

socket_ctrl* socket_listen::accept()
{
	TCPsocket socket_sdl = SDLNet_TCP_Accept(m_socket_sdl);
	return socket_sdl ? new socket_ctrl(socket_sdl) : nullptr;
}

/*
socket_data* socket_listen::accept()
{
	TCPsocket socket_sdl = SDLNet_TCP_Accept(m_socket_sdl);
	return socket_sdl ? new socket_data(socket_sdl) : nullptr;
}
*/

// </FIXME>

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
