#include <cstdlib>
#include <ctime>

#include "lib/sdlinterf.h"
#include "rect.h"
#include "circ.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

using namespace std;

int randRange(int min, int max, int withZero = true){
	if(!withZero) max--;
	int randNum = min + (rand() % (max-min));
	if(!withZero && randNum >=0) randNum++;
	return randNum;
}

Drawable *randDrawable(){
	if(rand()%2) return new Circ(Color(), SDL_X_SIZE/2 , SDL_Y_SIZE/2 , randRange(10,150),randRange(10,150),randRange(-3,3, false),randRange(-3,3,false));
	return new Rect(Color(), SDL_X_SIZE/2 , SDL_Y_SIZE/2 , randRange(10,150),randRange(10,150), randRange(-3,3, false), randRange(-3,3, false));
}

const int drawableCount = 100;

int main() {
	srand((unsigned int) time(nullptr));

	sdlInit();

	Drawable *drawables[drawableCount];

	for(int i = 0; i < drawableCount; i++){
		drawables[i] = randDrawable();
	}

	int aliveCount = drawableCount;

	while(aliveCount) {
		sdlMilliSleep(10);
		for(int i = 0; i < drawableCount; i++){
			if (!drawables[i]->fly()) {
					delete drawables[i];
					drawables[i] = randDrawable();
			}
		}
		Drawable::drawAll();
		sdlUpdate();
	}

	sdlExit();

	exit(EXIT_SUCCESS);
}



#pragma clang diagnostic pop