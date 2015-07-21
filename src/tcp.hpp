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
		tcpsock(uint16_t port, SDLNet_SocketSet sock_set_sdl);
		
		// wrapper for SDLNet_TCP_Close()
		~tcpsock();
		
		// wrapper for SDLNet_SocketReady()
		bool ready();
		
		// wrapper for SDLNet_TCP_Recv()
		string recv(uint16_t len);
		
	private:
		TCPsocket m_sock_sdl;
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
		uint16_t m_socks_max;
		SDLNet_SocketSet m_sockset_sdl;
		vector<tcpsock*> m_socks;
};
