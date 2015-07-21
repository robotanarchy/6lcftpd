#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;


class config
{	
	public:
		config(vector<string> keys);
	
	private:
		map<string,string> options;
};


