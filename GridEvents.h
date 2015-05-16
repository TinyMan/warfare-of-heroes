#pragma once
#include "Event.h"

namespace Events
{
	namespace GridEvents
	{
		class GridEvent : public Events::Event
		{
		public:
			GridEvent(){}
			virtual ~GridEvent(){}
		};
		class CellClick : public GridEvent
		{
		public:
			CellClick(unsigned int c) : cell(c){}
			virtual ~CellClick() {}
			unsigned int cell;
		};
	}

}