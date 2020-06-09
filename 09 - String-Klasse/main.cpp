#include <iostream>
#include <cstring>

using namespace std;

class String {

	friend ostream &operator<<(ostream &outFile, const String &a);

public:
	String(int len = 0): s(new char[len+1]){
		s[0] = '\0';
	};

	String(const String &orig) : s(new char[strlen(orig.s) + 1]) {
		strcpy(s, orig.s);
	}

	String(const char *str) : s(new char[strlen(str) + 1]) {
		strcpy(s, str);
	}

	~String(){
		delete [] s;
	}

	String operator+(const String &b) const {
		String result(strlen(s) + strlen(b.s));
		strcpy(result.s, s);
		strcat(result.s, b.s);
		return result;
	}

	bool operator==(const String &b) const {
		return strcmp(s, b.s) == 0;
	}

	bool operator<(const String &b) const {
		return (strcmp(s, b.s) < 0);
	}

	bool operator!() const {
		return (s[0] == '\0');
	}

	String &operator=(const String &b) {
		if (this != &b) {
			delete[] s;
			s = new char[strlen(b.s) + 1];
			strcpy(s, b.s);
		}
		return *this;
	}

	String &operator+=(const String &b) {
		char *news = new char[strlen(s) + strlen(b.s) + 1];
		strcpy(news, s);
		strcat(news, b.s);
		delete[] s;
		s = news;
		return *this;
	}

	char &operator[](const int i){
		if(i < 0 || i >= strlen(s)){
			static char x{'\0'};
			return x;
		}
		return s[i];
	}

	char *getS(){ return s; }

private:
	char *s;
};

ostream &operator<<(ostream &outFile, const String &a)
{
	outFile << a.s;
	return outFile;
}

int main() {
	String nix;
	String a = "Äpfel";
	String aa = a;
	String b = "Birnen";
	String bb;
	String k = "Kompott";
	String ab = "ÄpfelBirnen";
	String res;

	bb = b;
	res = aa + String("") + bb;

	cout << "Ist 'nix' leer? " << (!nix ? "Ja!" : "Nein???") << endl;
	cout << "'" << bb << "' sind " << (!bb ? "auch" : "nicht") << " leer." << endl;
	cout << "'" << a << "' und '" << b << "' sind " <<
		 ((a == b) ? "gleich" : "verschieden") << "." << endl;
	cout << "'" << bb << "' sind " << (bb < k ? "kleiner" : "größer") <<
		 " als '" << k << "'" << endl;
	cout << "'" << k << "' ist " << (k < b ? "kleiner" : "größer") <<
		 " als '" << b << "'" << endl;
	cout << "'" << aa << "' plus '" << bb << "' sind '" << res << "'." << endl;
	cout << "Sind es wirklich 'ÄpfelBirnen'? " <<
		 ((ab == res) ? "Ja!" : "Nein???") << endl;

	// ab hier auskommentieren, solange du noch kein += hast
	a += bb;
	a += k;
	cout << "Und jetzt gibt es '" << a << "'." << endl;

	// ab hier auskommentieren, solange Index- und Typumwandlungsoperator fehlen
	cout << "'" << res << "[5]' ist ein '" << res[5] << "'." << endl;
	res[5] = 'H';
	cout << "Und jetzt machen wir ein 'H' daraus: '" << res << "'." << endl;
	cout << "Ausgabe als C++ string: '" << res << "'." << endl;
	cout << "Wird '" << b << "[6]' richtig abgefangen? ";
	b[6] = 'x';
	cout << ((b == bb) ?  "Ja!" : "Nein???") << endl;

	return 0;
}
