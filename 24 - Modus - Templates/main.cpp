#include <iostream>
#include <cstring>

using namespace std;

template <class T>
T modus(T arr[], int size, T def, int &rMaxC){
	T modus = arr[0];
	int maxC = 0;
	for(int i = 0; i < size; i++){
		int c = 1;
		for(int k = i+1; k < size; k++){
			if(arr[i]==arr[k]) c++;
		}
		if(c > maxC){
			maxC = c;
			modus = arr[i];
		}
	}
	rMaxC = maxC;
	return maxC ? modus : def;
}


int main(int argc, char *argv[]) {
	string *words = new string[argc - 1];
	int *lengths = new int[argc - 1];

	for (int i = 0; i < argc - 1; i++) {
		words[i] = argv[i + 1];
		lengths[i] = strlen(argv[i + 1]);
	}

	int maxC;
	cout << "Häufigstes Wort: " << modus<string>(words, argc-1, "", maxC) << " x " << maxC << endl;
	cout << "Häufigste Wortlänge: " << modus(lengths, argc-1, 0, maxC) << endl;
	return 0;
}
