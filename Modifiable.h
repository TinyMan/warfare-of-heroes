#pragma once
class Modifiable
{
public:
	Modifiable();
	virtual ~Modifiable();
	virtual bool isDirty() = 0;

	virtual void setDirty(bool b = true) = 0;
};

