#include "Sortable.h"


Sortable::Sortable()
{
}


Sortable::~Sortable()
{
}


bool Sortable::compare(const Sortable& s1, const Sortable& s2)
{
	return s1.compare(&s2);
}
bool compare(const Sortable * s1, const Sortable * s2)
{
	return Sortable::compare(*s1, *s2);
}