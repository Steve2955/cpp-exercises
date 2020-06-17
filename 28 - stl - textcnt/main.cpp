#include <iostream>
#include <cctype>
#include <fstream>
#include <map>

using namespace std;

template<class T>
class CountedSet{
public:
	CountedSet():arr(){}

	void count(T t){
		arr[t]++;
	}

	void print(){
		for (auto it = arr.begin(); it!=arr.end(); ++it){
			cout << it->second << " x " << it->first << endl;
		}
	}

	int getUsed(){return arr.size();}

private:
	map<T, int> arr;
};

template<class T>
class CountedMap: private map<T, int>{
public:

	void count(T t){
		(*this)[t]++;
	}

	void print(){
		for (auto it = this->begin(); it!=this->end(); it++){
			cout << it->second << " x " << it->first << endl;
		}
	}

	int getUsed(){return this->size();}

};

int main(int argc, const char *argv[]) {

	CountedSet<string> wordCounter;
	CountedMap<char> letterCounter;
	CountedSet<int> lengthCounter;

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
