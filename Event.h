#pragma once
#include <string>
using namespace std;

namespace Events
{
	class Event
	{
	public:
		virtual ~Event();
		void dispatch();
	};

}
