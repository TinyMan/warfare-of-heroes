#include "logservice.h"


LogService::LogService(string filename, bool d) : filename(filename)
{
	
	if (!d)
	{
		logfile.open(filename.c_str());
		oldbuf = cerr.rdbuf();
		cerr.rdbuf(logfile.rdbuf());
		logfile << setfill('0');
	}
	cerr << setfill('0');


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
		cerr.rdbuf(oldbuf);
	}
}

void LogService::write(LogLevel ll, const string& str)
{
	cerr << setw(10)<< SDL_GetTicks() - start_time << "\t[";
	switch (ll)
	{
	case LogService::DEBUG:
		cerr << "DEBUG";
		break;
	case LogService::INFO:
		cerr << "INFO";
		break;
	case LogService::ERROR:
		cerr << "ERROR";
		break;
	case LogService::WARNING:
		cerr << "WARNING";
		break;
	default:
		break;
	}
	cerr << "]\t" << str << endl;
}