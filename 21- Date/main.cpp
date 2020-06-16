#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

void EingabeFehler(const char *meldung, int wert);

bool IstSchaltjahr(int jahr);

int TageImJahr(int jahr);

int TageImMonat(int monat, int jahr);

int JahrAusDatum(int datum);

int MonatAusDatum(int datum);

int TagAusDatum(int datum);

int TageBisDatum(int datum);

int liesDatum(const char *prompt);

/*class FalschesDatum:public exception{
public:
	FalschesDatum(const char *msg, int date): msg(msg), date(date){}
	void print(){
		cout << "Eingabefehler: " << msg << " (" << date << ") Korrektes Eingabeformat: ddmmyyyy" << endl;
	}
private:
	const char *msg;
	int date;
};*/

string FalschesDatum(const char *msg, int date){
	stringstream s;
	s << "Eingabefehler: " << msg << " (" << date << ") Korrektes Eingabeformat: ddmmyyyy" << endl;
	return s.str();
}

// Ist "jahr" ein Schaltjahr? (Returnwert true oder false)
bool IstSchaltjahr(int jahr) {
	// Gibt das Ergebnis der Bedingung als Returnwert zurück
	return (jahr % 400 == 0) || ((jahr % 4 == 0) && (jahr % 100 != 0));
}

// Wie viele Tage hat das Jahr "jahr"?
int TageImJahr(int jahr) {
	return IstSchaltjahr(jahr) ? 366 : 365;
}

// Liefert die Anzahl der Tage des Monats "monat" im Jahr "jahr"
int TageImMonat(int monat, int jahr) {
	static const int monatTage[12] =
			{31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (monat == 2) {
		return IstSchaltjahr(jahr) ? 29 : 28;
	} else {
		return monatTage[monat - 1];
	}
}

// Liefert das "yyyy" aus "ddmmyyyy"
int JahrAusDatum(int datum) {
	int jahr = datum % 10000;
	if (jahr < 1) {
		throw FalschesDatum("Jahr ist ungültig", jahr);
	}

	return jahr;
}

// Liefert das "mm" aus "ddmmyyyy"
int MonatAusDatum(int datum) {
	int monat = (datum / 10000) % 100;
	if ((monat < 1) || (monat > 12)) {
		throw FalschesDatum("Monat ist ungültig", monat);
	}

	return monat;
}

// Liefert das "dd" aus "ddmmyyyy"
int TagAusDatum(int datum) {
	int tag = datum / 1000000;
	int maxTag = TageImMonat(MonatAusDatum(datum), JahrAusDatum(datum));
	if ((tag < 1) || (tag > maxTag)) {
		throw FalschesDatum("Tag ist ungültig", tag);
	}

	return tag;
}

// Verwandelt "ddmmyyyy"-Zahl in "Tage seit 1.1.01": Liefert Anzahl der Tage.
int TageBisDatum(int datum) {
	if (datum <= 0) {
		throw FalschesDatum("Datum ist <= 0", datum);
	}

	int tag = TagAusDatum(datum);
	int monat = MonatAusDatum(datum);
	int jahr = JahrAusDatum(datum);

	// summiere:
	// * alle ganzen Jahre vor dem Datum
	// * alle ganzen Monate vor dem Datum
	// * die Tage im aktuellen Monat
	int tage = 0;
	for (int i = 1; i < jahr; ++i) tage += TageImJahr(i);
	for (int i = 1; i < monat; ++i) tage += TageImMonat(i, jahr);
	tage += tag;

	return tage;
}

int liesDatum(const char *prompt) {
	int eingabe;

	cout << prompt;
	cin >> eingabe;

	int tage;

	try{
		tage = TageBisDatum(eingabe);
	} catch (string &s) {
		cout << s;
		return liesDatum(prompt);
	}

	return tage;
}

int main(void) {
	int von = liesDatum("Anfangsdatum? ");
	int bis = liesDatum("Enddatum? ");
	cout << "Zeitabstand " << bis - von << " Tage." << endl;

	exit(EXIT_SUCCESS);
}