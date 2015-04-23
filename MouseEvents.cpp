#include "MouseEvents.h"


Uint32 Events::MouseEvents::ClickEvent::_last_click = 0;
const Uint32 Events::MouseEvents::ClickEvent::_time_between_clicks = 50; // milliseconds