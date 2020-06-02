#include <cstdlib>
#include <ctime>

#include "lib/sdlinterf.h"
#include "rect.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

using namespace std;

inline int randPM(int n) {
	return ((rand() % n) + 1) - ((rand() % 2) * (n + 1));
}

int main() {
	srand((unsigned int) time(nullptr));

	sdlInit();

	Rect r(Color(255, 255, 255), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 10, 25, 5, 2);

	for (;;) {
		sdlMilliSleep(1);
		if (!r.fly(true)) {
			r.scale(90, 90);
			if ((r.getW() == 0) || (r.getH() == 0)) {
				r.setPos(SDL_X_SIZE / 2, SDL_Y_SIZE / 2);
				r.setSize(rand() % 30 + 1, rand() % 30 + 1);
				r.setSpeed(randPM(10), randPM(10));
			}
		}
		sdlUpdate();
	}

	sdlExit();

	exit(EXIT_SUCCESS);
}



#pragma clang diagnostic pop