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
		tcpsock(TCPsocket sock_sdl);
	
		// Create a listen socket (server-side!)
		// wrapper for SDLNet_ResolveHost() and SDLNet_TCP_Open(),
		// throws SDLNet_GetError() as exception
		tcpsock(uint16_t port);
		
		// wrapper for SDLNet_TCP_Close()
		~tcpsock();
		
		// wrapper for SDLNet_SocketReady()
		bool ready();
		
		// wrapper for SDLNet_TCP_Recv()
		// throws an exception when the connection has been closed
		string recv_line(uint16_t maxlen = 100);
		
		// wrapper for SDLNet_TCP_Send()
		void send_line(string line);
		
		TCPsocket get_sdl();
		
		// TODO: get_peer_addr()
		
	private:
		TCPsocket m_sock_sdl;
};

class tcp
{
	public:
		// Wrapper for SDLNet_AllocSocketSet()
		tcp(uint16_t socks_max);
		
		tcpsock* listen(uint16_t port);
		
		tcpsock* accept(tcpsock* listen_sock);
		
		// Wrapper for SDLNet_FreeSocketSet()
		~tcp();
		
		// Wrapper for SDLNet_CheckSockets()
		// Returns true when at least one socket has activity
		bool check(uint32_t timeout_ms=100);
		
		// Wrapper for SDLNet_TCP_DelSocket()
		void del(tcpsock* sock);
		
	private:
		uint16_t m_socks_max;
		SDLNet_SocketSet m_sockset_sdl;
		vector<tcpsock*> m_socks;
		
		void add(tcpsock* sock);
		// void delete(tcpsock* sock);
};
