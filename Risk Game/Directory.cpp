#include "Directory.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;

namespace Directory
{
	vector<string> GetFilesNamesFrom(string folder)
	{
		vector<string> names;
		char search_path[FILENAME_MAX];
		sprintf_s(search_path, "%s/*.*", folder.c_str());
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path, &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return names;
	}

	string Directory::GetCurrentWorkingDirectory()
	{
		char cCurrentPath[FILENAME_MAX];
		GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
		string str(cCurrentPath);
		return str;
	}

	string Directory::CombinePaths(int amount, const char* args...)
	{
		va_list list;
		va_start(list, args);

		char* next = (char*)args;
		string path;

		for (int i = 0; i < amount; i++)
		{
			path += next;
			path += "\\";
			next = va_arg(list, char*);
		}
		
		va_end(list);
		return path;
	}
}