#include <iostream>
#include <cstdlib>

#define MAX_NUMBERS 100

using namespace std;

struct NumberCounter {
	int number;
	int count;
};

struct CounterContainer {
	int size;
	NumberCounter numbers[MAX_NUMBERS];
};

void printContainer(CounterContainer &c) {
	cout << "Anzahl x Wert" << endl;
	for (int i = 0; i < c.size; i++) {
		cout << c.numbers[i].count << " x " << c.numbers[i].number << endl;
	}
}

NumberCounter &findCounterInContainer(CounterContainer &c, int num) {
	int i;
	for (i = 0; i < c.size; i++) {
		if (c.numbers[i].number == num) return c.numbers[i];
		if (c.numbers[i].number > num) break;
	}

	for (int k = c.size; k > i; k--) c.numbers[k] = c.numbers[k - 1];

	c.size++;

	c.numbers[i].number = num;
	c.numbers[i].count = 0;
	return c.numbers[i];
}


int main(int argc, char *argv[]) {

	CounterContainer c;
	c.size = 0;

	for (int i = 1; i < argc; i++) {
		findCounterInContainer(c, atoi(argv[i])).count++;
	}

	printContainer(c);
	return 0;
}
