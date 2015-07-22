#include "server_control.hpp"
#include <string>
#include <iostream>

using namespace std;


// reference:
// https://tools.ietf.org/html/rfc959

string server_control::answer(string msg)
{
	size_t space = msg.find_first_of(' ');
	string cmd = (space == string::npos) ? msg
		: msg.substr(0, space);
	
	
	if(cmd == "USER") return "230 YEAH I DON'T CARE WHO YOU ARE";
	
	// current working directory (TODO: escape special characters)
	if(cmd == "PWD") return "257 \""+m_pwd+"\"";
	
	if(cmd == "TYPE") return "200 WHATEVER";
	
	return "502 WAIT... WHAT?";
}




server_control::server_control(tcpsock* sock, config* config)
{
	m_sock = sock;
	m_pwd = "/";
	m_cfg = config;
	
	sock->send_line("220 "+m_cfg->get_opt("issue"));
}


tcpsock* server_control::get_sock()
{
	return m_sock;
}
