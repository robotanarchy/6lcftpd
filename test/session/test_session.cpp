#include "../../src/session/session.hpp"

#include <iostream>
#include <thread>
#include <chrono>


using namespace std;

void sleep()
{
	this_thread::sleep_for(chrono::milliseconds(100));
}


int main()
{
	config cfg{};
	cout << "waiting for a connection on port 2111..." << endl;
	
	
	socket_ctrl* ctrl;
	socket_listen listen {2111};
	while(1)
	{
		ctrl = listen.accept_ctrl();
		if(ctrl) break;
		sleep();
	}
	
	session test_session{*ctrl, cfg};
	
	cout << "done." << endl;
}
