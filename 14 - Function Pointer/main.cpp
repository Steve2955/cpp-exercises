#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Array{
	friend ostream &operator<<(ostream &outFile, const Array &a);
public:

	Array(int size): data(new double[size]), size(size), used(0){}

	~Array(){
		delete [] data;
	}

	virtual bool append(double d){
		if(used == size) return false;
		data[used++] = d;
		return true;
	}

	virtual void apply(double (*func)(double)){
		for(int i = 0; i < used; i++) data[i] = func(data[i]);
	}

	static int cmp(const void *p1, const void *p2){
		double d1 = *((const double *) p1);
		double d2 = *((const double *) p2);
		return (int) (d1-d2);
	}

	void sort(){
		qsort(data, used, sizeof(double), cmp);
	}

protected:
	double *data;
	unsigned int size;
	unsigned int used;
};

class MinMaxArray:public Array{
public:
	MinMaxArray(int size):Array(size), min(HUGE_VAL), max(-HUGE_VAL){}

	bool append(double d){
		if(!Array::append(d)) return false;
		if(d < min) min = d;
		if(d > max) max = d;
		return true;
	}

	void apply(double(*func)(double)){
		Array::apply(func);
		min = func(min);
		max = func(max);
	}

	double getMin(){return min;}
	double getMax(){return max;}

private:
	double min;
	double max;
};


ostream &operator<<(ostream &outFile, const Array &a){
	for(int i = 0; i < a.used; i++) outFile << a.data[i];
	return outFile << endl;
}


double sqr(double d){
	return d*d;
}


int main(int argc, char *argv[]) {
	MinMaxArray arr(argc - 1);
	for(int i = 1; i < argc; i++){
		switch (argv[i][0]) {
			case 'x':
				return 0;
			case 'w':
				arr.apply(sqrt);
				break;
			case 'q':
				arr.apply(sqr);
				break;
			case 'l':
				arr.apply(log);
				break;
			case 'e':
				arr.apply(exp);
				break;
			case 's':
				arr.sort();
				break;
			default:
				arr.append(atof(argv[i]));
		}
	}
	cout << arr;
	cout << "Min: " << arr.getMin() << " Max: " << arr.getMax();
	return 0;
}
