#include "server.hpp"
#include <string>
#include <iostream>

using namespace std;

string server::control_protocol(string msg)
{
	// FIXME: the npos-part doesn't seem to work!
	size_t space = msg.find_first_of(' ');
	string cmd = (space == string::npos) ? msg
		: msg.substr(0, space);
	
	
	if(cmd == "USER") return "230 YEAH I DON'T CARE WHO YOU ARE";
	
	// current working directory - stub!
	if(cmd == "PWD") return "257 \"/\" (STUB; I'LL ALWAYS SAY THAT)";
	
	
	
	return "502 WAIT... WHAT?";
}
