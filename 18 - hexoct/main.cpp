#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>

using namespace std;

int main(int argc, const char *argv[]) {
	if(argc!=3){
		cout << "Aufruf: " << argv[0] << " inFile outFile" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream inFile(argv[1]);

	if(!inFile){
		cout << "Datei " << argv[1] << " konnte nicht geöffnet werden (lesender Zugriff)" << endl;
		exit(EXIT_FAILURE);
	}

	ofstream outFile(argv[2]);

	if(!outFile){
		cout << "Datei " << argv[2] << " konnte nicht geöffnet werden (schreibender Zugriff)" << endl;
		exit(EXIT_FAILURE);
	}

	char line[200];
	while(inFile.getline(line,200)){
		stringstream s(line);
		int zahl;
		switch (tolower(line[strlen(line)-1])) {
			case 'h':
				s >> hex >> zahl;
				break;
			case 'o':
				s >> oct >> zahl;
				break;
			default:
				s >> zahl;
		}
		if(s.fail()){
			outFile << "Fehler bei der Konvertierung. Bitte überprüfen Sie ihre Eingabe." << endl;
			continue;
		}
		outFile << zahl << endl;
	}

	inFile.close();
	outFile.close();

	return 0;
}
