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
		config cfg {{"issue", "share", "chown", "chmod", "socks",
			"write"}};
		
		tcp net {static_cast<uint16_t>(stoul(cfg.get_opt("socks")))};
		
		server srv(&cfg, &net);
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
