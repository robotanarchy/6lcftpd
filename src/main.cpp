#include "server/server.hpp"
#include "config/config.hpp"
#include <iostream>


using namespace std;

int main()
{
	cout << "six lines of config ftp daemon" << endl
	     << "------------------------------" << endl;
	
	try
	{
		config cfg{};
		server srv{cfg};
		srv.mainloop();
	}
	catch(exception &e)
	{
		cout << "PRO-TIP: " << e.what() << endl << endl;
		cout << "shutting down with error." << endl;
		return 1;
	}
	
	
	cout << "shutting down normally." << endl;
	return 0;
}
