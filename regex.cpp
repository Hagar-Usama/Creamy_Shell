#include <iostream>
#include <fstream>
#include <ctype.h>
#include <regex>


using namespace std;

int get_matched(string s , regex reg , string &mat);

class aa{
	
	string a;
	
	
	}

int main(){
	
	aa _s;
	get_matched(_s);
	
	
return 0;	
	
}


int get_matched(string s , regex reg , string &mat){
	smatch match;
	if(regex_search(s,match,reg) == true){
		mat = match.str(0);
		return 1;
		}
	return 0;
	
		 }
