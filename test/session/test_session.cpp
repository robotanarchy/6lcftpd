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
	cout << "hello world!" << endl;
	
	return 0;
}
