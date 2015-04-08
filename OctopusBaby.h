#pragma once

/* 
everything that is displayed shoudl be an octopus baby (button, player, ...)
*/
class OctopusBaby
{
public:
	OctopusBaby();
	virtual ~OctopusBaby();

	virtual void update() = 0;
	virtual void render() = 0;

	bool isAbove(const OctopusBaby& ob) { return _z_index < ob._z_index; }
private:
	int _z_index;
};

