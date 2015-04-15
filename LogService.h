#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <SDL2/SDL_timer.h>

#define LOGINFO ServiceLocator::getLogService()->info
#define LOGERR ServiceLocator::getLogService()->error
#define LOGWARN ServiceLocator::getLogService()->warning
#define LOGDEBUG ServiceLocator::getLogService()->debug

using namespace std;

/* Change the structure (thanks to http://stackoverflow.com/questions/27336335/c-cout-with-prefix) */

class TimePrefixBuf : public std::streambuf
{
public:
	TimePrefixBuf(std::string const& prefix, std::streambuf* sbuf);
	void setRdbuf(streambuf* sbuf) { this->sbuf = sbuf; }
	void setStartTime(Uint32 t) { start_time = t; }

private:
	std::string     _prefix;
	std::streambuf* sbuf;
	std::basic_string<char_type> buffer;
	Uint32 start_time;

	int sync() { return this->sbuf->pubsync(); }
	int overflow(int c);
};


class TimePrefixOStream : private virtual TimePrefixBuf, public std::ostream
{
public:
	TimePrefixOStream(std::string const& prefix, std::ostream& out)
		: TimePrefixBuf(prefix, out.rdbuf()), std::ios(static_cast<std::streambuf*>(this)), std::ostream(static_cast<std::streambuf*>(this)) 
	{}
	void setOstream(ostream& out) { TimePrefixBuf::setRdbuf(out.rdbuf()); }
	void setStartTime(Uint32 t) { TimePrefixBuf::setStartTime(t); }
};



class LogService
{
public:
	enum LogLevel
	{
		DEBUG,
		INFO,
		ERROR,
		WARNING
	};
	/*
	Construct with a filename or empty string to log to standart output
	You can also provide a filename and force the service to log to standart output, and later call switchDestOutput() to switch to the file
	*/
	LogService(string filename="", bool INCONSOLE=false);
	virtual ~LogService();

	/* kept for legacy purpose */
	virtual void write(LogLevel ll, const string& str);


	TimePrefixOStream debug;
	TimePrefixOStream info;
	TimePrefixOStream error;
	TimePrefixOStream warning;

	/* switch output to the file or to standart output (toggle) */
	void switchDestOutput();

private:
	string filename;
	ofstream logfile;

	Uint32 start_time;

	streambuf *oldbuf = nullptr;
	bool _to_file;
};




