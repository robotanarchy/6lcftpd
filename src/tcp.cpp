#include "tcp.hpp"
#include <string>
#include <iostream>

tcp::tcp(uint16_t socks_max)
{
	this->socks_sdl2 = SDLNet_AllocSocketSet(socks_max);
	this->socks_max = socks_max;
}

tcp::~tcp()
{
	for(auto sock : this->socks)
		delete sock;
	SDLNet_FreeSocketSet(this->socks_sdl2);
}

tcpsock tcp::socket_open(uint16_t port)
{
	if(this->socks.size() >= this->socks_max)
		throw runtime_error("Socket limit reached, won't create a new"
			" one!");
	
	tcpsock* sock = new tcpsock(port, this->socks_sdl2);
	this->socks.push_back(sock);
	return *sock;
}



