#include "OctopusBaby.h"


OctopusBaby::OctopusBaby()
{
}


OctopusBaby::~OctopusBaby()
{
}

void OctopusBaby::setZIndex(int z)
{
	if (z != _z_index)
	{		
		_z_index = z;
		setSorted(false);
	}
}
bool OctopusBaby::operator<(const OctopusBaby& o) const
{
	return isAbove(o);
}
bool OctopusBaby::compare(const Sortable* s) const
{
	return isAbove(*(const OctopusBaby*)s);
}
