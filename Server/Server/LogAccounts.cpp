#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"LogAccounts.h"

LogClass* LogClass::mpInstance = NULL;

////////////////////////////////////////////
////////////////////////////////////////////


LogClass::LogClass(string filename)
{
	mpFILE = fopen(filename.c_str(), "a+");
}


////////////////////////////////////////////
////////////////////////////////////////////


LogClass&LogClass::GetInstance()
{

	if (mpInstance == NULL)
	{
		mpInstance = new LogClass("Accounts.txt");
	}
	return *mpInstance;
}

////////////////////////////////////////////
////////////////////////////////////////////


void LogClass::Write(string cuv)
{
	fprintf(mpFILE, "%s", cuv.c_str());
	fflush(mpFILE);
}

////////////////////////////////////////////
////////////////////////////////////////////


LogClass::~LogClass()
{
	fclose(mpFILE);
}