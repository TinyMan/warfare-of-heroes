#pragma once
#include "ServiceLocator.h"
#include "OctopusBaby.h"
#include "Font.h"
class Label :
	public OctopusBaby
{
public:
	Label(string text = "", Font* f = nullptr);
	Label(int x, int y, int w, int h, string text = "", Font* f = nullptr);
	virtual ~Label();
	void setText(string text) { _text = text; setDirty(); }
	string getText() const { return _text; }

	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

	void update();

protected:
	void internalRender(SDL_Renderer* r, bool force = false);
private:
	string _text;
	Font* _font;
	bool _dirty = true;

};

