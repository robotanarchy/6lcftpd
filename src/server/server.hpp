#pragma once
#include "../config/config.hpp"
#include "../socket/socket.hpp"
#include "../session/session.hpp"
#include <vector>
#include <list>


class server
{
	public:
		server(config& cfg, list<uint16_t> ports = {21, 2111, 2221,
			2121, 21111, 22221});
		void mainloop();
		~server();
	
	private:
		config& m_cfg;
		socket_listen* m_listen;
		vector<session*> m_sessions;
};
