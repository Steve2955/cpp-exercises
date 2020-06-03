#include "circ.h"
#include "lib/sdlinterf.h"

void Circ::draw() {
	sdlDrawCirc(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Circ::undraw() {
	sdlDrawCirc(mX, mY, mW, mH, 0, 0, 0);
}