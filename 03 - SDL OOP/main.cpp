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

int randRange(int min, int max){
	return min + (rand() % (max-min));
}

const int rectCount = 100;

int main() {
	srand((unsigned int) time(nullptr));

	sdlInit();

	Rect *rects[rectCount];

	rects[0] = new Rect(Color(255, 255, 0), SDL_X_SIZE / 2 , SDL_Y_SIZE / 2 , SDL_X_SIZE/5, SDL_Y_SIZE/5);

	sdlUpdate();
	sdlMilliSleep(1000);

	for(int i = 1; i < rectCount-1; i++){
		rects[i] = new Rect(*rects[i-1]);
		rects[i]->setPos(
				randRange(SDL_X_SIZE/5, SDL_X_SIZE - SDL_X_SIZE/5),
				randRange(SDL_Y_SIZE/5, SDL_Y_SIZE - SDL_Y_SIZE/5));
		sdlUpdate();
		sdlMilliSleep(5);
	}

	sdlMilliSleep(1000);

	rects[rectCount-1] = new Rect(*rects[rectCount-2]);
	rects[rectCount-1]->setPos(SDL_X_SIZE/4,SDL_Y_SIZE/2);

	sdlMilliSleep(1000);

	for(int i = rectCount-2; i > 0; i--){
		rects[i]->moveOnTop(*rects[rectCount-1]);
		sdlUpdate();
		sdlMilliSleep(5);
	}

	sdlMilliSleep(1000);

	rects[0]->setPos(SDL_X_SIZE/4*3,SDL_Y_SIZE/2);

	sdlMilliSleep(1000);

	for(int i = 1; i < rectCount; i++){
		rects[i]->moveOnTop(*rects[0]);
		sdlUpdate();
		sdlMilliSleep(5);
	}

	int aliveCount = rectCount;

	/*while(aliveCount) {
		sdlMilliSleep(5);
		for(int i = 0; i < rectCount; i++){
			if(!rects[i]) continue;
			if (!rects[i]->fly(true)) {
				rects[i]->scale(90, 90);
				if ((rects[i]->getW() == 0) || (rects[i]->getH() == 0)) {
					delete rects[i];
					rects[i] = nullptr;
					aliveCount--;
				}
			}
		}
		sdlUpdate();
	}*/

	sdlMilliSleep(5000);

	sdlExit();

	exit(EXIT_SUCCESS);
}



#pragma clang diagnostic pop