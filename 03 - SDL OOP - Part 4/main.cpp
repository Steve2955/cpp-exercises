#include <cstdlib>
#include <ctime>

#include "lib/sdlinterf.h"
#include "rect.h"
#include "circ.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

using namespace std;

int randRange(int min, int max){
	return min + (rand() % (max-min));
}

Drawable *randDrawable(){
	if(rand()%2) return new Circ(Color(randRange(0,255), randRange(0,255), randRange(0,255)), SDL_X_SIZE/2 , SDL_Y_SIZE/2 , 13, 13,randRange(-7,7),randRange(-7,7));
	return new Rect(Color(randRange(0,255), randRange(0,255), randRange(0,255)), SDL_X_SIZE/2 , SDL_Y_SIZE/2 , 10,10, randRange(-7,7), randRange(-7,7));
}

const int drawableCount = 1000;

int main() {
	srand((unsigned int) time(nullptr));

	sdlInit();

	Drawable *drawables[drawableCount];

	for(int i = 0; i < drawableCount; i++){
		if(i%10){
			drawables[i] = drawables[i-1]->clone();
			drawables[i]->setPos(drawables[i-1]->getX()+drawables[i-1]->getSX()*3, drawables[i-1]->getY() + drawables[i-1]->getSY()*3);
		}else{
			drawables[i] = randDrawable();
		}
	}

	int aliveCount = drawableCount;

	while(aliveCount) {
		sdlMilliSleep(10);
		for(int i = 0; i < drawableCount; i++){
			if(!drawables[i]) continue;
			if (!drawables[i]->fly(true)) {
				//drawables[i]->scale(90, 90);
				if ((drawables[i]->getW() == 0) || (drawables[i]->getH() == 0)) {
					delete drawables[i];
					drawables[i] = nullptr;
					aliveCount--;
				}
			}
		}
		sdlUpdate();
	}

	sdlExit();

	exit(EXIT_SUCCESS);
}



#pragma clang diagnostic pop