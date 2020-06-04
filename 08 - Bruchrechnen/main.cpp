#include <cstring>
#include <iostream>

using namespace std;

class Frac {
	friend ostream &operator<<(ostream &outFile, const Frac &f);
public:
	Frac(int c = 0, int d = 1) : c(c), d(d) {
		kurzen();
	}

	Frac(const char *s) {
		char *div = strchr(s, '/');
		if (!div) {
			c = atoi(s);
			d = 1;
		} else {
			*div = '\0';
			c = atoi(s);
			d = atoi(++div);
		}
	}

	Frac operator+(const Frac &f) const {
		return Frac(c * f.d + f.c * d, d * f.d);
	}

	Frac operator-(const Frac &f) const {
		return Frac(c * f.d - f.c * d, d * f.d);
	}

	Frac operator*(const Frac &f) const {
		return Frac(c * f.c,d * f.d);
	}

	Frac operator/(const Frac &f) const {
		return Frac(c * f.d,d * f.c);
	}

	void print() {
		cout << c << '/' << d << endl;
	}

private:
	int c;
	int d;

	void kurzen();
};

int ggt(int a, int b){

	for(a = abs(a), b = abs(b); b; b%=(a-=(b=(a+=b)-b)));

	return a;
};

void Frac::kurzen() {
	if(d == 0) {
		cout << "Teilen durch 0" << endl;
		exit(EXIT_FAILURE);
	}

	if(d < 0){
		c = -c;
		d = -d;
	}

	int div = ggt(c,d);
	c/=div;
	d/=div;
}

ostream &operator<<(ostream &outFile, const Frac &f){
	if (f.d == 1) outFile << f.c;
	else outFile << f.c << '/' << f.d;
	return outFile;
}

int main(int argc, const char *argv[]) {

	int i;

	if (argc % 2 != 0) {
		cout << argv[0] << ": Die Anzahl der Eingaben stimmt nicht!" << endl;
		exit(EXIT_FAILURE);
	}

	Frac result(argv[1]);

	for (i = 2; i < argc; i += 2) {
		Frac input(argv[i + 1]);
		switch (argv[i][0]) {
			case '+':
				result = result + input;
				break;
			case '-':
				result = result - input;
				break;
			case 'x':
				result = result * input;
				break;
			case '/':
				result = result / input;
				break;
			default:
				cout << argv[0] << ":" << argv[i][0] << "Kein Rechenzeichen?" << endl;
				exit(EXIT_FAILURE);
		}
	}

	cout << "Ergebnis: ";
	result.print();

	exit(EXIT_SUCCESS);
}