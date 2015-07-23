/*
	Simple wrapper around SDLNet TCP sockets.
	
	See also:
		http://www.libsdl.org/projects/SDL_net/docs
	
	Notes:
		- TCPsocket is actually a pointer!
		- Each socket_sdl must be in a sdl socket set, otherwise the
			ready function won't work. So we simply create a socket set
			for each socket :p
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
		~socket();
		// timeout 0: instantly return when there's no activity
		bool ready(uint32_t timeout_ms=0);
		
	protected:
		socket();
		socket(TCPsocket socket_sdl);
		TCPsocket m_socket_sdl;
		SDLNet_SocketSet m_socket_set_sdl;
		
		
};


class socket_ctrl : public socket
{
	public:
		socket_ctrl(TCPsocket socket_sdl) : socket(socket_sdl) {};
		string recv(uint16_t maxlen = 100);
		void send(string line);
};


class socket_data : public socket
{
	public:
		socket_data(TCPsocket socket_sdl) : socket(socket_sdl) {};
};

class socket_listen : public socket
{
	public:
		socket_listen(uint16_t port);
		socket_ctrl* accept_ctrl(); // may be nullptr!
		socket_data* accept_data(); // may be nullptr!
};
