#include "logservice.h"


LogService::LogService(string filename) : filename(filename)
{
	logfile.open(filename.c_str());
	logfile << setfill('0');
	start_time = SDL_GetTicks();
	if (logfile.is_open())
	{
		write(DEBUG, "Beginning log ...");
	}
}


LogService::~LogService()
{
	if (logfile.is_open())
	{
		write(DEBUG, "Ending log ...");
		logfile.close();
	}
}

void LogService::write(LogLevel ll, const string& str)
{
	logfile << setw(10)<< SDL_GetTicks() - start_time << "\t[";
	switch (ll)
	{
	case LogService::DEBUG:
		logfile << "DEBUG";
		break;
	case LogService::INFO:
		logfile << "INFO";
		break;
	case LogService::ERROR:
		logfile << "ERROR";
		break;
	case LogService::WARNING:
		logfile << "WARNING";
		break;
	default:
		break;
	}
	logfile << "]\t" << str << endl;
}