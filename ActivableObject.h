#pragma once
#include "Event.h"
class ActivableObject
{
public:

	ActivableObject()
	{
	}

	virtual ~ActivableObject()
	{
	}
	bool isActive() const { return _active; }
	void setActive(bool b = true) { _active = b; }
	bool operator<(const ActivableObject& o)
	{
		if (o.isActive() == isActive())
			return false;
		return o.isActive() && !isActive();
	}
private:
	bool _active = false;
};

namespace Events
{
	namespace ActivableObjectEvents
	{
		class ActivableObjectEvent : public Events::Event
		{
		public:
			ActivableObjectEvent(ActivableObject* o = nullptr) : _object(o) {}
			~ActivableObjectEvent() {}
			ActivableObject* getObject() const { return _object; }
		private:
			ActivableObject* _object;
		};
		class ActivateEvent
			: public ActivableObjectEvent
		{
		public:
			ActivateEvent(ActivableObject* go = nullptr) : ActivableObjectEvent(go) {}
			virtual ~ActivateEvent(){}
		};
		class DeactivateEvent
			: public ActivableObjectEvent
		{
		public:
			DeactivateEvent(ActivableObject* go = nullptr) : ActivableObjectEvent(go) {}
			virtual ~DeactivateEvent(){}
		};
	}
}