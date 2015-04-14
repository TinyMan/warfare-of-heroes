#pragma once
#include "Event.h"

class Modifiable
{
public:
	Modifiable();
	virtual ~Modifiable();
	
protected:
	virtual void triggerModifyEvent() = 0;

};



namespace Events
{
	class ModifyEvent
		: public Event
	{
	public:
		ModifyEvent(Modifiable* o) : _o(o) {}
		virtual ~ModifyEvent(){}
		Modifiable* getObject() const { return _o; }
	private:
		Modifiable* _o;
	};
}