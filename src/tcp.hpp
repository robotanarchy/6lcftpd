#pragma once
#pragma once
#include <string>
#include <vector>

extern "C"
{
   #include <SDL2/SDL_net.h>
}


using namespace std;


class tcpsock
{
	public:
		// wrapper for SDLNet_ResolveHost() and SDLNet_TCP_Open(),
		// throws SDLNet_GetError() as exception
		tcpsock(uint16_t port, SDLNet_SocketSet socks_sdl2);
		
		// wrapper for SDLNet_TCP_Close()
		~tcpsock();
		
		// wrapper for SDLNet_SocketReady()
		bool ready();
		
		// wrapper for SDLNet_TCP_Recv()
		string recv(uint16_t len);
		
	private:
		TCPsocket sock_sdl2;
};

class tcp
{
	public:
		// Wrapper for SDLNet_AllocSocketSet()
		tcp(uint16_t socks_max);
		
		tcpsock socket_open(uint16_t port);
		
		// Wrapper for SDLNet_FreeSocketSet()
		~tcp();
		
	private:
		uint16_t socks_max;
		SDLNet_SocketSet socks_sdl2;
		vector<tcpsock*> socks;
};
