#pragma once
#include "OctopusBaby.h"
#include "Cell.h"
#include "GridOctopus.h"

class ObstacleOctopus :
	public OctopusBaby
{
public:
	ObstacleOctopus(Cell* cell, GridOctopus * grid);
	virtual ~ObstacleOctopus();

	virtual void update() override{};

	virtual bool isDirty() { return _dirty; }
	virtual void setDirty(bool d = true) { _dirty = d; }
protected:
	virtual void internalRender(SDL_Renderer* r, bool froce = false) override;

	void drawObstacle(SDL_Renderer* r, unsigned int cell, unsigned int type);
private:
	bool _dirty = true;
	GridOctopus* _grid;
	Cell* _cell;
	static map<unsigned int, Texture> _obstacles_tex;

};

