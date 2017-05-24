#pragma once

#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<direct.h>
using namespace std;


static bool is_emptyy(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}
static void CreateDirectory(string name)
{
	string path = ".\\";
	//string path = "C:/Users/Maria/Documents/git/test/Server/Server/";
	path.append(name);
	_mkdir(path.c_str());
}
static void deleteFile(string FileName)
{
	char * writable = new char[FileName.size() + 1];
	std::copy(FileName.begin(), FileName.end(), writable);
	writable[FileName.size()] = '\0'; // don't forget the terminatination
	remove(writable);
	delete[] writable;
}
static bool deleteFromFile(string name, string FileName) {
	bool exist = false;
	vector<string> BackUpVector;
	string file = FileName.append(".txt");
	string line;
	ifstream InFile(file);
	if (InFile.good()) {
		while (getline(InFile, line)) {
			if (line == name || line.find(name) != string::npos) exist = true;
			else  BackUpVector.push_back(line);
		}
	}
	if (exist == true)
	{
		InFile.close();
		std::ofstream ofs;
		ofs.open(file, std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		ofstream OutPut;
		OutPut.open(file, std::ofstream::out | std::ofstream::app);
		for (int i = 0; i < BackUpVector.size(); i++) {
			OutPut << BackUpVector[i];
			OutPut << "\n";
		}
	}
	return exist;
}

static vector<string> split(const string &text, char sep) {
	vector<string> tokens;
	size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}