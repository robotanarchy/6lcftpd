#pragma once
#include "../socket/socket.hpp"


using namespace std;

class session
{
	public:
		session(socket_ctrl& ctrl);
		
	private:
		socket_ctrl& m_ctrl;
};
