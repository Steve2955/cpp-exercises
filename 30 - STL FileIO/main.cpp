#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

template<class T>
void scramble(vector<T> &lines){
	for(int i = lines.size(); i >= 0; i--){
		swap(lines[i], lines[rand() % (i + 1)]);
	}
}

int main(int argc, const char *argv[]) {
	if(argc != 3) exit(EXIT_FAILURE);

	srand(time(nullptr));

	ifstream inFile(argv[1]);
	if(!inFile){
		cout << "inFile could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

	ofstream outFile(argv[2]);
	if(!outFile) {
		cout << "outFile could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> lines;

	string line;
	while(getline(inFile, line)){
		lines.push_back(line);
	}

	scramble(lines);

	for(int i = 0; i < lines.size(); i++){
		outFile << lines[i] << endl;
	}

	inFile.close();
	outFile.close();
	return 0;
}
