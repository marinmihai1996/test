#pragma once

#include<iostream>
#include<string>
using namespace std;

class LogGroups
{
private:
	FILE *mpFILE;
	LogGroups(string filename);
	static LogGroups *mpInstance;
	~LogGroups();
public:
	static LogGroups& GetInstance();
	void Write(string);
	void write(char a) { fprintf(mpFILE, "%c", a); };


};
