#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"LogAccounts.h"

LogAccounts* LogAccounts::mpInstance = NULL;

////////////////////////////////////////////
////////////////////////////////////////////


LogAccounts::LogAccounts(string filename)
{
	mpFILE = fopen(filename.c_str(), "a+");
}


////////////////////////////////////////////
////////////////////////////////////////////


LogAccounts&LogAccounts::GetInstance()
{

	if (mpInstance == NULL)
	{
		mpInstance = new LogAccounts("C:/Users/Maria/Documents/git/test/Server/Server/Accounts.txt");
	}
	return *mpInstance;
}

////////////////////////////////////////////
////////////////////////////////////////////


void LogAccounts::Write(string cuv)
{
	fprintf(mpFILE, "%s", cuv.c_str());
	fflush(mpFILE);
}

////////////////////////////////////////////
////////////////////////////////////////////


LogAccounts::~LogAccounts()
{
	fclose(mpFILE);
}