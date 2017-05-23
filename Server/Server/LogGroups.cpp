#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"LogGroups.h"

LogGroups* LogGroups::mpInstance = NULL;

////////////////////////////////////////////
////////////////////////////////////////////


LogGroups::LogGroups(string filename)
{
	mpFILE = fopen(filename.c_str(), "a+");
}


////////////////////////////////////////////
////////////////////////////////////////////


LogGroups&LogGroups::GetInstance()
{

	if (mpInstance == NULL)
	{
		mpInstance = new LogGroups("C:/Users/Marin/Documents/git/test/Server/Server/Groups.txt");
	}
	return *mpInstance;
}

////////////////////////////////////////////
////////////////////////////////////////////


void LogGroups::Write(string cuv)
{
	fprintf(mpFILE, "%s", cuv.c_str());
	fflush(mpFILE);
}

////////////////////////////////////////////
////////////////////////////////////////////


LogGroups::~LogGroups()
{
	fclose(mpFILE);
}