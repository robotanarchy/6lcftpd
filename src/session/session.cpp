#include "session.hpp"

/*
	Note about session types:
		- FTP has active and passive modes. For active, the client would
			open a port and then the server would connect to it. Doesn't
			work behind NAT, so we won't do that.
		- passive mode can be divided in PASV (where the server needs to
			tell the client the IPv4 listen IP again - SDL_Net can't do
			that!) and EPSV (extended passive, works with ipv6 too and
			doesn't need to tell the IP again).
		- FileZilla FTP Client only does EPSV when using IPv6 or a proxy
			(maybe we should make a bug report).
		- FileZilla doesn't support the EPSV answer to a PASV request

*/

string session::answer(string msg)
{
	size_t space = msg.find_first_of(' ');
	string cmd = (space == string::npos) ? msg
		: msg.substr(0, space);
	
	// simple returns
	if(cmd == "USER") return "230 YEAH I DON'T CARE WHO YOU ARE";
	if(cmd == "PWD") return "257 \""+m_pwd+"\"";
	if(cmd == "TYPE") return "200 WHATEVER"; // FIXME
	
	
	// tell the client that we know the EPSV command. GCC throws up when
	// writing \n211, so we merge strings instead.
	if(cmd == "FEAT")
	{
		return string("211")
			+ "\r\n EPSV"
			+ "\r\n" + "211 End";
	}
	
	// only extended passive mode is supported!
	if(cmd == "EPSV")
	{
		/*
			TODO:
				- create a data socket
				- send a message back in the format:
					229 Entering Extended Passive Mode (|||6446|)
				- maybe we can put a cooler text there.
		*/
		return "229 Entering Extended Passive Mode (|||2111|)";
	}
	
	// if(cmd == "LIST") return "150 WHY DON'T YOU WAIT FOR A DATA CONNECTION";
	
	return "502 WAIT... WHAT?";
}



void session::thread_method()
{
	try
	{
		cout << "# session " << this << " started #" << endl;
		m_ctrl->send("220 " + m_cfg.get_opt("issue"));
		while(1)
		{
			// talk back to incoming text
			m_ctrl->send(answer(m_ctrl->recv()));
			
		}
	}
	catch(exception e)
	{
		cout << "# session " << this << " closed #" << endl;
	}
}


session::session(socket_ctrl* ctrl, config& cfg)
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
