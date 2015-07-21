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
		// TODO: ipadr gets ignored, because SDL_net can't do that.
		// So we'll need to find another config option instead. Maybe
		// the number of sockets?
		
		config cfg {{"issue", "share", "chown", "chmod", "ipadr",
			"write"}};
		
		server srv(&cfg);
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
