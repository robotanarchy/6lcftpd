#include "config.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

config::config(vector<string> keys)
{	
	map<string,string> opt = this->options;
	
	// open the config file
	ifstream file;
	file.open("6lcftpd.cfg", ifstream::in);
	if(!file) throw runtime_error("6lcftpd demands the six line config"
		" file!\nPlease copy 6lcftpd.sample.cfg to 6lcftpd.cfg and"
		" adjust it, then start the daemon again.");
	
	
	// read it line by line
	string line;
	while(getline(file, line))
		for(size_t i=0;i<keys.size();i++)
		{
			string prefix = keys[i] + "=";
			if(line.compare(0,prefix.size(), prefix) != 0) continue;
			
			if(opt.find(keys[i]) != opt.end()) throw runtime_error
				("You've specified the config option '" + keys[i] + "'"
				+ " more than once. Don't do that!");
			
			opt.insert(make_pair(keys[i], line.substr(prefix.size())));
		}
	
	file.close();
	
	
	
	// TODO: validate the map, maybe add default values etc.
	
}
