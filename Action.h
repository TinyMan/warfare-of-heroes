#pragma once
#include <iostream>
#include <string>
#include "Callback.h"
#include "Event.h"
using namespace std;
class Action :
	public Event
{
private:
	string _text;
	Callback _cb;

public:
	enum ACTION_TYPE
	{
		CAST,
		MOVE,
		FINISH
	};
	Action(Callback& cb, string text = "", void* data=nullptr);
	virtual ~Action();

	virtual void trigger() const;

	string getText() const{ return _text; }

};

ostream& operator<<(ostream& o, const Action&);
