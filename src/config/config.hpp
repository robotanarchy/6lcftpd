#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;


class config
{	
	public:
		config(vector<string> keys = {"issue", "share", "chown",
			"chmod", "socks", "write"});
		string get_opt(string key);
	
	private:
		map<string,string> opt;
};


