#include <iostream>
#include <fstream>

using namespace std;

class Messw{
	friend ostream &operator<<(ostream &outFile, const Messw &w);
public:
	Messw(): size(0), data(nullptr){}
	Messw(const Messw &orig);

	~Messw(){
		delete [] data;
	}

	int operator~() const{ return size;	}

	bool operator!() const{ return (size==0); }

	double operator[](int i){
		if(i < 0 || i >= size) return 0;
		return data[i];
	}

	Messw operator+(double d) const;
	Messw operator+(const Messw &m) const;
	Messw &operator=(const Messw &m);

	operator double() const;

private:
	Messw(int size): size(size), data(new double[size]){}
	double *data;
	int size;
};

Messw::Messw(const Messw &orig) : size(orig.size), data(new double[size]){
	for (int i = 0; i < size; ++i) data[i] = orig.data[i];
}

Messw Messw::operator+(double d) const{
	Messw result(size + 1);
	for (int i = 0; i < size; i++) result.data[i] = data[i];
	result.data[size] = d;
	return result;
}

Messw Messw::operator+(const Messw &m) const{
	Messw result(size + m.size);
	for (int i = 0; i < size; ++i) result.data[i] = data[i];
	for (int i = 0; i < m.size; ++i) result.data[size + i] = m.data[i];
	return result;
}

Messw &Messw::operator=(const Messw &m){
	if (this == &m) return *this;
	if (m.size != size) {
		delete [] data;
		size = m.size;
		data = new double[size];
	}
	for (int i = 0; i < size; i++) data[i] = m.data[i];
	return *this;
}

Messw::operator double() const{
	if (size == 0) return 0;
	double sum = 0;
	for (int i = 0; i < size; i++) sum += data[i];
	return sum / size;
}

ostream &operator<<(ostream &outFile, const Messw &w){
	for(int i = 0; i < w.size; i++) outFile << w.data[i] << ' ';
	return outFile;
}

int main(int argc, char *argv[]) {
	Messw total;
	for(int i = 1; i < argc; i++){
		ifstream inFile(argv[i]);
		if(!inFile){
			cerr << "File " << argv[i] << "could not be opened";
			continue;
		}
		Messw current;
		double a;
		while(inFile >> a) current = current + a;
		if(!current){
			cout << "Keine Werte" << endl;
		}else{
			cout << current << " (Mittel: " << (double) current << "; Anzahl: "<< ~current << ")" << endl;
		}
		total = total + current;
		inFile.close();
	}
	cout << "Gesamt: " << total << endl
		<< " Erster:" << total[0] << " Letzter:"
		<< total[~total-1] << " (Mittel: " << (double) total
		<< "; Anzahl: "<< ~total << ")" << endl;
	return 0;
}
