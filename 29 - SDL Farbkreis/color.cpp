#include "color.h"

#include <algorithm>

using namespace std;

Color::Color(){
	int n = ((next++) % 192) * 4 + 2;

	mR = max(0, min(-256 + n, 768 - n));
	mG = max(0, min(n, 512 - n));
	mB = max(0, max(-512 + n, 256 - n));
}

int Color::next;