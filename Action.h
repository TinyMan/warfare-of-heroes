#pragma once
#include <iostream>
#include <string>
#include "Callback.h"
#include "Event.h"
using namespace std;

namespace Events{
	class Action :
		public Event
	{
	private:
		string _text;
		Callback _cb;

	public:		
		Action(Callback& cb, string text = "");
		virtual ~Action();

		virtual void trigger() const;

		string getText() const{ return _text; }

	};

	ostream& operator<<(ostream& o, const Action&);
}
