#include "Callback.h"

void Callback::call(void* d) const
{
	_cb(d);
}