#pragma once
#include <string>

using namespace std;


class config
{	
	public:
		config();
		string	get_issue();
		string	get_share();
		string	get_chown();
		int		get_chmod();
		string	get_ipadr();
		bool	get_write();
	
	private:
		string	issue;
		string	share;
		string	chown;
		int		chmod;
		string	ipadr;
		bool	write;
};


