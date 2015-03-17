#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <SDL2/SDL_timer.h>

using namespace std;
enum LogLevel
{
	DEBUG,
	INFO,
	ERROR,
	WARNING
};

class LogService
{
public:


	LogService(string filename, bool DEBUG=false);
	virtual ~LogService();

	virtual void write(LogLevel ll, const string& str);


private:
	string filename;
	ofstream logfile;

	Uint32 start_time;

	streambuf *oldbuf = nullptr;
};


