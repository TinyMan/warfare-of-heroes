#pragma once
#include "Event.h"
class GameObject;

/* declaring events */
namespace Events
{
	namespace GameObjectEvents
	{
		class Event : public Events::Event
		{
		public:
			Event(GameObject* go) : _object(go) {}
			virtual ~Event(){}
		protected:
			GameObject* _object;
		};
		class ActivateEvent
			: public Event
		{
		public:
			ActivateEvent(GameObject* go) : Event(go) {}
			virtual ~ActivateEvent(){}
		};
		class DeactivateEvent
			: public Event
		{
		public:
			DeactivateEvent(GameObject* go) : Event(go) {}
			virtual ~DeactivateEvent(){}
		};
		class ToDeleteEvent
			: public Event
		{
		public:
			ToDeleteEvent(GameObject* go) : Event(go) {}
			virtual ~ToDeleteEvent(){}
		};
	}
}