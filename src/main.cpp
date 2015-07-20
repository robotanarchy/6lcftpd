#include "server.hpp"
#include <iostream>


using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	
	server* srv = new server();
	
	delete srv;
	
	return 0;
}
