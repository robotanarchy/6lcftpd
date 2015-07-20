#include "config.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

config::config()
{
	ifstream file;
	file.open("6lcftpd.cfg", ifstream::in);
	
	if(!file) throw runtime_error("6lcftpd demands the six line config"
		" file!\nPlease copy 6lcftpd.sample.cfg to 6lcftpd.conf and"
		" adjust it, then start the daemon again.");
	
	// TODO: read the file line by line etc.
	
	
	cout << "file found." << endl;
	
}
