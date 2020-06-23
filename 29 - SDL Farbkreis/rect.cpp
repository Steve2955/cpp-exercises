#include "rect.h"
#include "lib/sdlinterf.h"

void Rect::draw() {
	sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw() {
	sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}