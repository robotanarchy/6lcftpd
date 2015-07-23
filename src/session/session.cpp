#include "session.hpp"

string session::answer(string msg)
{
	size_t space = msg.find_first_of(' ');
	string cmd = (space == string::npos) ? msg
		: msg.substr(0, space);
	
	if(cmd == "USER") return "230 YEAH I DON'T CARE WHO YOU ARE";
	
	if(cmd == "PWD") return "257 \""+m_pwd+"\"";
	
	if(cmd == "TYPE") return "200 WHATEVER";
	
	if(cmd == "PASV")
	{
		/*
			TODO:
				- create a data socket
				- send a message back in the format:
					227 Entering Passive Mode (127,0,0,1,po,rt)
				- maybe we can put a cooler text there.
		*/
		return "227";
	}
	
	// if(cmd == "LIST") return "150 WHY DON'T YOU WAIT FOR A DATA CONNECTION";
	
	return "502 WAIT... WHAT?";
}



void session::thread_method()
{
	try
	{
		cout << "# session " << this << " started #" << endl;
		m_ctrl.send("220 " + m_cfg.get_opt("issue"));
		while(1)
		{
			// talk back to incoming text
			m_ctrl.send(answer(m_ctrl.recv()));
			
		}
	}
	catch(exception e)
	{
		cout << "# session " << this << " closed #" << endl;
	}
}


session::session(socket_ctrl& ctrl, config& cfg)
	: m_ctrl{ctrl}
	, m_cfg{cfg}
	, m_thread{&session::thread_method, this}
{
}


session::~session()
{
	m_thread.join();
	delete &m_ctrl;
}
