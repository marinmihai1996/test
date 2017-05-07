
#ifndef _HEADER_3243234
#define _HEADER_3243234
#include<iostream>
#include<string>
using namespace std;

class LogClass
{
private:
	FILE *mpFILE;
	LogClass(string filename);
	static LogClass *mpInstance;
	~LogClass();
public:
	static LogClass& GetInstance(); 
	void Write(string);
	//void Write(int);
	//static void OpenLogFile();

};
#endif