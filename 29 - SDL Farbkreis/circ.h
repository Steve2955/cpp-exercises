#ifndef SDL_OOP_CIRC_H
#define SDL_OOP_CIRC_H

#include "drawable.h"

class Circ : public Drawable {
public:
	Circ(const Color &color, int x, int y, int w, int h,
		 int sx = 0, int sy = 0) : Drawable(color, x, y, w, h, sx, sy) {
		draw();
	}

	Circ(const Circ &orig) : Drawable(orig){
		draw();
	}

	virtual ~Circ() { undraw(); }

	virtual Circ *clone() const override {
		return new Circ(*this);
	}

	virtual void draw() override;
	virtual void undraw() override;
};


#endif
