#include "server.hpp"
#include "config.hpp"
#include <iostream>


using namespace std;

int main()
{
	cout << "Six Lines of Config FTP Daemon" << endl
	     << "------------------------------" << endl;
	
	try
	{
		config cfg;
		server srv;
	}
	catch(exception &ex)
	{
		cout << "WHOOPS: " << ex.what() << endl << endl;
		cout << "Shutting down with error." << endl;
		return 1;
	}
	
	
	cout << "Shutting down normally." << endl;
	return 0;
}
