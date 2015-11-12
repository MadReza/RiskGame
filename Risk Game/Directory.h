#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <vector>

#include <direct.h>
#define GetCurrentDir _getcwd

using std::vector;
using std::string;

namespace Directory	//Not class because http://stackoverflow.com/a/112451
{
	vector<string> GetFilesNamesFrom(string folder);
	string GetCurrentWorkingDirectory();
	string CombinePaths(int amount, const char* args...);	//http://en.cppreference.com/w/cpp/utility/variadic
};