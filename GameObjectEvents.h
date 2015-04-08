#pragma once
#include "Event.h"
class GameObject;

/* declaring events */
namespace Events
{
	namespace GameObjectEvents
	{
		class GameObjectEvent : public Events::Event
		{
		public:
			GameObjectEvent(GameObject* go) : _object(go) {}
			virtual ~GameObjectEvent(){}
		protected:
			GameObject* _object;
		};
		class ActivateEvent
			: public GameObjectEvent
		{
		public:
			ActivateEvent(GameObject* go) : GameObjectEvent(go) {}
			virtual ~ActivateEvent(){}
		};
		class DeactivateEvent
			: public GameObjectEvent
		{
		public:
			DeactivateEvent(GameObject* go) : GameObjectEvent(go) {}
			virtual ~DeactivateEvent(){}
		};
		class ToDeleteEvent
			: public GameObjectEvent
		{
		public:
			ToDeleteEvent(GameObject* go) : GameObjectEvent(go) {}
			virtual ~ToDeleteEvent(){}
		};
	}
}