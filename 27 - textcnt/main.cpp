#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

template<class T, int size>
class CountedSet{
public:
	CountedSet():used(0){}

	void count(T t){
		int i = 0;
		for(; i < used; i++){
			if(arr[i]==t){
				counts[i]++;
				return;
			}
		}
		if(i == size) return;
		arr[i] = t;
		counts[i] = 1;
		used++;
	}

	void print(){
		for(int i = 0; i < used; i++){
			cout << counts[i] << " x " << arr[i] << endl;
		}
	}

	int getUsed(){return used;}

private:
	T arr[size];
	int counts[size];
	int used;
};

int main(int argc, const char *argv[]) {

	CountedSet<string, 1000> wordCounter;
	CountedSet<char, 50> letterCounter;
	CountedSet<int, 100> lengthCounter;

	for(int i = 1; i < argc; i++){
		ifstream inFile(argv[i]);
		if(!inFile) exit(EXIT_FAILURE);
		const int len = 200;
		char line[len];
		while (inFile.getline(line,len)){
			int wordStart = 0;
			for(int i = 0; i < len; i++){
				if(isalpha(line[i])){
					letterCounter.count(tolower(line[i]));
				}else{
					string s(line+wordStart, i-wordStart);
					wordStart = i+1;
					if(s.length() == 0) continue;
					wordCounter.count(s);
					lengthCounter.count(s.length());
				}
			}
		}
		inFile.close();
	}
	cout << "Buchstaben: " << letterCounter.getUsed() << endl;
	letterCounter.print();
	cout << "Wortlängen: "<< lengthCounter.getUsed() << endl;
	lengthCounter.print();
	cout << "Wörter: " << wordCounter.getUsed()  << endl;
	wordCounter.print();
	return 0;
}
