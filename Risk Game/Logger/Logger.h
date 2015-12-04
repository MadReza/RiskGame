#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using std::string;

class Logger
{
public:
	virtual void output(string msg) = 0;
};

#endif // !LOGGER_H