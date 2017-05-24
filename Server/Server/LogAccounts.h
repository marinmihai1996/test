
#ifndef _HEADER_3243234
#define _HEADER_3243234
#include<iostream>
#include<string>
using namespace std;

class LogAccounts
{
private:
	FILE *mpFILE;
	LogAccounts(string filename);
	static LogAccounts *mpInstance;
	~LogAccounts();
public:
	static LogAccounts& GetInstance(); 
	void Write(string);
	void write(char a) { fprintf(mpFILE,"%c",a); };
	

};
#endif