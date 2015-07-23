/*
	Simple Wrapper around SDLNet TCP sockets.
	
	See also:
		http://www.libsdl.org/projects/SDL_net/docs
	
	Note:
		TCPsocket is actually a pointer!
*/


#pragma once
#include <string>
#include <iostream>
extern "C"
{
   #include <SDL2/SDL_net.h>
}

using namespace std;

class socket
{
	public:
		socket(TCPsocket socket_sdl);
		socket();
		bool ready();
	protected:
		TCPsocket m_socket_sdl;
		
};


class socket_ctrl : socket
{
	public:
		string recv(uint16_t maxlen = 100);
		void send(string line);
};


class socket_data : socket
{
	
};

class socket_listen : socket
{
	public:
		socket_listen(uint16_t port);
		socket_ctrl* accept(); // may be nullptr!
		socket_data* accept(); // may be nullptr!
};
