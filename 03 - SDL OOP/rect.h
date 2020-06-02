#ifndef SDL_OOP_RECT_H
#define SDL_OOP_RECT_H

#include "color.h"

class Rect {
public:
	Rect(const Color &color, int x, int y, int w, int h,
		 int sx = 0, int sy = 0) : mRGB(color), mX(x), mY(y), mW(w), mH(h), mSX(sx), mSY(sy) {
		draw();
	}

	~Rect() { undraw(); }

	Color getColor() const { return mRGB; }

	int getX() const { return mX; }

	int getY() const { return mY; }

	int getW() const { return mW; }

	int getH() const { return mH; }

	int getSX() const { return mSX; }

	int getSY() const { return mSY; }

	void setColor(const Color &color) {
		mRGB = color;
		draw();
	}

	void setSpeed(int sx, int sy) {
		mSX = sx;
		mSY = sy;
	}

	void setPos(int x, int y);

	void setSize(int w, int h);

	bool fly(bool bounce = false);

	void scale(int percentX, int percentY);

	void draw();

	void undraw() const;

private:
	Color mRGB;
	int mX, mY;
	int mW, mH;
	int mSX, mSY;
};


#endif
