#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 3) exit(EXIT_FAILURE);

	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);

	if(!inFile) exit(EXIT_FAILURE);
	if(!outFile) exit(EXIT_FAILURE);

	char c;

	while(inFile.get(c)) outFile.put(tolower(c));

	outFile.close();
	if (!outFile) exit(EXIT_FAILURE);

	inFile.clear();
	inFile.seekg(0);


	char line[200];
	while(inFile.getline(line,200)){
		for(int i = (200 - strlen(line))/2; i > 0; i--) cout << ' ';
		cout << line << endl;
	}

	return 0;
}
