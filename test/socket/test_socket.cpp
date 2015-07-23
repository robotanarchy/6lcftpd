#include "../../src/socket/socket.hpp"

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
	cout << "waiting for a connection on port 2111..." << endl;
	
	
	socket_ctrl* ctrl;
	socket_listen listen {2111};
	while(1)
	{
		ctrl = listen.accept();
		if(ctrl) break;
		sleep();
	}
	
	ctrl->send("hello world!");
	
	cout << "waiting for an answer..." << endl;
	
	while(!ctrl->ready())
		sleep();
	
	ctrl->recv();
	
	cout << "that's it, shutting down." << endl;
	return 0;
}
