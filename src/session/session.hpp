#pragma once
#include "../socket/socket.hpp"
#include "../config/config.hpp"
#include <thread>


using namespace std;

class session
{
	public:
		session(socket_ctrl& ctrl, config& cfg);
		~session();
		
	private:
		void thread_method();
		string answer(string msg);
		
		socket_ctrl& m_ctrl;
		config& m_cfg;
		thread m_thread;
		string m_pwd = "/";
};
