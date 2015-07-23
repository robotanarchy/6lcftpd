#pragma once
#include "../socket/socket.hpp"
#include "../config/config.hpp"


using namespace std;

class session
{
	public:
		session(socket_ctrl& ctrl, config& cfg);
		~session();
		
	private:
		socket_ctrl& m_ctrl;
		config& m_cfg;
};
