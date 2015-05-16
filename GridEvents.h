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
		class CellEvent : public GridEvent
		{
		public:
			CellEvent(unsigned int c) : cellNumber(c){}
			CellEvent(Cell* c) : cellPtr(c){}
			virtual ~CellEvent() {}
			unsigned int cellNumber = 9999;
			Cell* cellPtr = nullptr;
		};
		class CellClick : public CellEvent
		{
		public:
			template<typename T>
			CellClick(Uint8 _button, T c) : CellEvent(c), button(_button){}
			virtual ~CellClick() {}
			Uint8 button;
		};
		class CellHover : public CellEvent
		{
		public:
			template<typename T>
			CellHover(T c) : CellEvent(c){}
			~CellHover(){}
		};
	}

}