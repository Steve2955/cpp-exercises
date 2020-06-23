#include "drawable.h"
#include "lib/sdlinterf.h"

using namespace std;

list<Drawable *> Drawable::drawables;

void Drawable::setPos(int x, int y){
	undraw();
	mX = x;
	mY = y;
	draw();
}

void Drawable::setSize(int w, int h){
	undraw();
	mW = w;
	mH = h;
	draw();
}

void Drawable::scale(int percentX, int percentY){
	undraw();
	mW = (mW * percentX) / 100;
	mH = (mH * percentY) / 100;
	draw();
}

bool Drawable::fly(bool bounce){
	bool ret = true;
	if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mW)) ||
		((mSX < 0) && (mX < -mSX + mW))) {
		if (bounce) {
			mSX = -mSX;
			ret = false;
		}
		else {
			return false;
		}
	}
	if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mH)) ||
		((mSY < 0) && (mY < -mSY + mH))) {
		if (bounce) {
			mSY = -mSY;
			ret = false;
		}
		else {
			return false;
		}
	}

	undraw();
	mX += mSX;
	mY += mSY;
	draw();
	return ret;
}

void Drawable::drawAll() {
	for(Drawable *drawable: drawables){
		drawable->draw();
	}
}