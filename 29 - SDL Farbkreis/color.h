#ifndef SDL_OOP_COLOR_H
#define SDL_OOP_COLOR_H

class Color {
public:

	Color();

	Color(int r, int g, int b) : mR(r), mG(g), mB(b) {}

	int getR() const { return mR; }

	int getG() const { return mG; }

	int getB() const { return mB; }

private:
	static int next;
	int mR, mG, mB;
};


#endif //SDL_OOP_COLOR_H
