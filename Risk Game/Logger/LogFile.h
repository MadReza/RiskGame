#ifndef LOG_FILE_H
#define LOG_FILE_H

#include "../Observer.h"
#include "Logger.h"

#include <fstream>
#include <iostream>
#include <string>

using std::string;
using std::ofstream;
using std::ios;

class LogFile : public Logger
{
private:
	ofstream myFile;
public:
	LogFile();
	~LogFile();

	void output(string msg);
};

#endif // !LOG_H
