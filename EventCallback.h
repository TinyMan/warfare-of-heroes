#pragma once

#include <functional>
#include "Event.h"
using namespace std;

namespace Events
{
	/*
	same as Callback
	*/
	class EventCallback
	{
	public:

		/*
		Need to be inline because it is a template ctor
		see: http://stackoverflow.com/questions/644397/c-class-with-template-cannot-find-its-constructor
		*/
		template<typename ...Args>
		EventCallback(Args... args)
		{
			_cb = bind(args..., placeholders::_1);
		}

		/* one can give a ptr to data to forward to the callback as last argument */
		void call(Event* e = nullptr) const
		{
			_cb(e);
		}

	private:
		function<void(Event*)> _cb;

	};
}