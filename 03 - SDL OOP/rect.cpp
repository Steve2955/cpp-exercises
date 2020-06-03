#include "rect.h"
#include "lib/sdlinterf.h"

Rect::Rect(const Rect &orig) : mRGB(orig.mRGB.getR() > 12 ? orig.mRGB.getR() - 2 : 10,
									orig.mRGB.getG() > 12 ? orig.mRGB.getG() - 2 : 10,
									orig.mRGB.getB() > 12 ? orig.mRGB.getB() - 2 : 10),
							   mX(orig.mX), mY(orig.mY),
							   mW(orig.mW > 1 ? orig.mW - 1 : 1), mH(orig.mH > 1 ? orig.mH - 1 : 1),
							   mSX(orig.mSX), mSY(orig.mSY) {
	draw();
}

void Rect::setPos(int x, int y) {
	undraw();
	mX = x;
	mY = y;
	draw();
}

void Rect::setSize(int w, int h) {
	undraw();
	mW = w;
	mH = h;
	draw();
}

void Rect::scale(int percentX, int percentY) {
	undraw();
	mW = (mW * percentX) / 100;
	mH = (mH * percentY) / 100;
	draw();
}

bool Rect::fly(bool bounce) {
	bool ret = true;

	if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mW)) ||
		((mSX < 0) && (mX < -mSX + mW))) {
		if (!bounce) return false;

		mSX = -mSX;
		ret = false;
	}
	if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mH)) ||
		((mSY < 0) && (mY < -mSY + mH))) {
		if (!bounce) return false;

		mSY = -mSY;
		ret = false;
	}

	undraw();
	mX += mSX;
	mY += mSY;
	draw();
	return ret;
}

void Rect::moveOnTop(Rect &rect) {
	undraw();
	mX = rect.mX;
	mY = rect.mY;
	draw();
}

void Rect::draw() {
	sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw() const {
	sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}