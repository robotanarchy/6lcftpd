#include "server.hpp"
#include "config.hpp"
#include <iostream>


using namespace std;

int main()
{
	cout << "six lines of config ftp daemon" << endl
	     << "------------------------------" << endl;
	
	try
	{
		config cfg {{"issue", "share", "chown", "chmod", "ipadr",
			"write"}};
		
		server srv(&cfg);
	}
	catch(exception &ex)
	{
		cout << "PRO-TIP: " << ex.what() << endl << endl;
		cout << "shutting down with error." << endl;
		return 1;
	}
	
	
	cout << "shutting down normally." << endl;
	return 0;
}
