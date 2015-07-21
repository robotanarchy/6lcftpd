#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;


class config
{	
	public:
		config(vector<string> keys);
		string get_opt(string key);
	
	private:
		map<string,string> opt;
};


