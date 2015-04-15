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
		setDirty();
	}
}
bool OctopusBaby::operator<(const OctopusBaby& o) const
{
	return isAbove(o);
}
bool compareZindex(const OctopusBaby* o, const OctopusBaby *b)
{
	return o->isAbove(*b);
}
