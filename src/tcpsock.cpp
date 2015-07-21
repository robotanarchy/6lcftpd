#include "tcp.hpp"
#include <iostream>


tcpsock::tcpsock(uint16_t port, SDLNet_SocketSet socks_sdl2)
{
	// open the socket
	// NOTE: SDL_Net can only host on all interfaces at once!
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, port);
	
	this->sock_sdl2 = SDLNet_TCP_Open(&ip);
	if(!this->sock_sdl2)
		throw runtime_error(string("SDL: ") + SDLNet_GetError());
	SDLNet_TCP_AddSocket(socks_sdl2, this->sock_sdl2);
}

tcpsock::~tcpsock()
{
	cout << "destroying socket: " << this->sock_sdl2 << endl;
	if(this->sock_sdl2)
		SDLNet_TCP_Close(this->sock_sdl2);
}

bool tcpsock::ready()
{
	return SDLNet_SocketReady(this->sock_sdl2);
}

string recv(uint16_t len)
{
	cout << "stub: tcpsock.recv();" << endl;
	return "";
}
