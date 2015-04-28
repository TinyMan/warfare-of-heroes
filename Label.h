#pragma once
#include "ServiceLocator.h"
#include "OctopusBaby.h"
#include "Font.h"
class Label :
	public OctopusBaby
{
public:
	Label(string text = "", Font* f = nullptr);
	Label(int w, int h, string text = "", Font* f = nullptr, int x = 0, int y = 0);
	virtual ~Label();
	void setText(string text) { _text = text; setDirty(); }
	string getText() const { return _text; }

	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

	void update();
	void setFont(Font* f) { _font = f; }
	Font* getFont() const { return _font; }
	void setTextColor(Color c) { _text_color = c; setDirty(); }
	Color getTextColor() const { return _text_color; }
	void setTextSize(int size) { _text_size = size; setDirty(); }
	int getTextSize() const { return _text_size; }
	void setTextAlignment(Uint8 a) { _alignment = a; setDirty(); }
	Uint8 getTextAlignment() const { return _alignment; }
protected:
	void internalRender(SDL_Renderer* r, bool force = false);
	Font* _font;

private:
	string _text;
	bool _dirty = true;
	Color _text_color = Color::BLACK;
	int _text_size = 32;
	Uint8 _alignment = Alignment::LEFT | Alignment::CENTERY;
};

