#include "LogService.h"

TimePrefixBuf::TimePrefixBuf(std::string const& prefix, std::streambuf* sbuf) : _prefix(prefix), sbuf(sbuf), start_time(0)
{
	//start_time = SDL_GetTicks();
}

int TimePrefixBuf::overflow(int c)
{
	if (traits_type::eq_int_type(traits_type::eof(), c))
		return traits_type::not_eof(c);
	switch (c) {
		case '\n':
		case '\r':
		{
			stringstream sstm;
			sstm << setfill('0') << setw(10) << SDL_GetTicks() - start_time << "\t" << _prefix;
			string prefix = sstm.str();

			buffer += c;
			if (buffer.size() > 1)
				sbuf->sputn(prefix.c_str(), prefix.size());
			int rc = (int)sbuf->sputn(buffer.c_str(), buffer.length());
			buffer.clear();
			return rc;
		}
		default:
			buffer += c;
			return c;
		}
	}

LogService::LogService(string filename, bool INCONSOLE)
	: filename(filename), debug("[DEBUG]\t", cout), error("[ERROR]\t", cout), info("[INFO]\t", cout), warning("[WARNING]\t", cout), _to_file(INCONSOLE)
{	
	if (filename.empty() || !INCONSOLE)
	{
		switchDestOutput();
	}
	info.setStartTime(start_time);
	warning.setStartTime(start_time);
	debug.setStartTime(start_time);
	error.setStartTime(start_time);

	/* redirect cerr to error stream */
	oldbuf = cerr.rdbuf();
	cerr.rdbuf(error.rdbuf());

	info << "Starting log" << endl;
}


LogService::~LogService()
{
	info << "Ending log ..." << endl;
	if (logfile.is_open())
	{
		//write(INFO, "Ending log ...");  // equivalent to: info << "Ending log ..." << endl;
		logfile.close();
		cerr.rdbuf(oldbuf);
	}
}

void LogService::write(LogLevel ll, const string& str)
{
	TimePrefixOStream * stream = nullptr;
	switch (ll)
	{
	case DEBUG:
		stream = &debug;
		break;
	case INFO:
		stream = &info;
		break;
	case ERROR:
		stream = &error;
		break;
	case WARNING:
		stream = &warning;
		break;
	default:
		break;
	}
	if(stream)
		*stream << str << endl;
}

void LogService::switchDestOutput()
{
	if (_to_file)
	{
		_to_file = false;
		/* redirect all the log stream to cout */
		debug.setOstream(cout);
		info.setOstream(cout);
		error.setOstream(cout);
		warning.setOstream(cout);
	}
	else if (!filename.empty())
	{
		_to_file = true;
		/* open file */
		logfile.open(filename.c_str());

		if (logfile.is_open())
		{
			/* redirect all the log stream to the file */
			debug.setOstream(logfile);
			info.setOstream(logfile);
			error.setOstream(logfile);
			warning.setOstream(logfile);
		}
	}
}