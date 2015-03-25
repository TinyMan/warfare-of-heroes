#pragma once

using namespace std;

class Event
{
public:

	typedef enum EVENT_TYPE
	{
		NONE,
		LAND,
		GAMEOBJECT_ACTIVATE,
		GAMEOBJECT_DEACTIVATE,
		PLAYER_ACTION
	} EVENT_TYPE;

	Event(EVENT_TYPE t = NONE, void* data =nullptr );
	virtual ~Event();

	//virtual void dispatch() const;
	virtual void setData(void* data) { _data = data; }
	virtual void* getData() const { return _data; }

	virtual int getId() const { return _id; }

	EVENT_TYPE getType() const { return _type; }

protected:
	/*static EventService* getEventService()
	{
		if (_manager == nullptr)
			_manager = ServiceLocator::getEventService();
		return _manager; 
	}
	*/
private:
	EVENT_TYPE _type;

	void* _data;
	//static EventService * _manager;

	int _id;

	static int next_id;
};

