#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int anzahlZiffern = 4;
const int maxZahl = 9999;

class Los{
public:
	Los(string kunde) : mKundenname(kunde), mLosnummer(++mAnzahl) {}

	virtual ~Los() {}

	virtual int gewinnRang(void) = 0;

protected:
	string mKundenname;
	int mLosnummer;
private:
	static int mAnzahl;
};

int Los::mAnzahl;

class ZahlenLos: public Los{
public:
	ZahlenLos(string kunde, int zahl):Los(kunde), mZahl(zahl){}

	virtual int gewinnRang(void){

		int zahl = mZahl;
		int letzteZahl = mLetzteZahl;
		int gleicheZiffern = 0;

		for(int i = 0; i < anzahlZiffern; i++){
			if(zahl%10 == letzteZahl%10) gleicheZiffern++;
			zahl /= 10;
			letzteZahl /= 10;
		}

		return gleicheZiffern;
	}

	static void Ziehung(void){
		mLetzteZahl = rand()%(maxZahl+1);
	}

protected:
		int mZahl;
		static int mLetzteZahl;
};

int ZahlenLos::mLetzteZahl;


class ZahlenLosStat: public ZahlenLos{

public:
	ZahlenLosStat(string kunde, int zahl):ZahlenLos(kunde, zahl), mGewinnRangAufrufe(0){
		for (int i = 0; i <= anzahlZiffern; ++i) {
			mGewinnAnzahl[i] = 0;
		}
	}

	virtual int gewinnRang(void){
		int gewinn = ZahlenLos::gewinnRang();
		mGewinnRangAufrufe++;
		mGewinnAnzahl[gewinn]++;
		return gewinn;
	}

	~ZahlenLosStat(){
		cout << "Kunde: " << mKundenname << "(Losnummer: " << mLosnummer << ")" << endl;
		for (int i = 0; i < anzahlZiffern; ++i) {
			cout << "Gewinn " << i << ": " << mGewinnAnzahl[i] << "x; ";
		}
		cout << endl;
	}

private:
	int mGewinnRangAufrufe;
	int mGewinnAnzahl[anzahlZiffern+1];
};

int main() {

	srand(time(nullptr));


	Los *losA = new ZahlenLosStat("Franz", 1234);
	Los *losB = new ZahlenLosStat("Xaver", 6666);

	for (int i = 0; i < 1000000; ++i) {
		ZahlenLos::Ziehung();
		losA->gewinnRang();
		losB->gewinnRang();
	}

	delete losA;
	delete losB;

	return 0;
}
