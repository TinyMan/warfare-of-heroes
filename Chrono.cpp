#include "Chrono.h"


Chrono::Chrono()
	: Button(300, 100)
{
	setText("xxx's turn\nTime left: xx sec");
	setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	// TODO: set callback etc
}


Chrono::~Chrono()
{
}
