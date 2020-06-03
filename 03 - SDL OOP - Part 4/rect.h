#ifndef SDL_OOP_RECT_H
#define SDL_OOP_RECT_H

#include "drawable.h"

class Rect : public Drawable {
public:
	Rect(const Color &color, int x, int y, int w, int h,
		 int sx = 0, int sy = 0) : Drawable(color, x, y, w, h, sx, sy) {
		draw();
	}

	Rect(const Rect &orig) : Drawable(orig){
		draw();
	}

	virtual ~Rect() { undraw(); }

	virtual Rect *clone() const override {
		return new Rect(*this);
	}

	virtual void draw() override;
	virtual void undraw() override;
};


#endif
