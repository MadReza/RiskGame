#include "LogFile.h"

LogFile::LogFile()
{
	myFile.open("logger.txt", ios::in | ios::app);
}

LogFile::~LogFile()
{
	myFile.close();
}

void LogFile::output(string msg)
{
	myFile << "File Log:: " << msg << "\n";
	myFile.flush();
}