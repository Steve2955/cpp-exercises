#include <iostream>
#include <string>

using namespace std;

template <class T1, class T2>
class Pair{
public:
	Pair(){}
	Pair(T1 t1, T2 t2):a(t1), b(t2){}

	T1 getA(){ return a;}
	T2 getB(){ return b;}

	bool operator==(const Pair &p){
		return a == p.a;
	}

	bool operator<(const Pair &p){
		return a < p.a;
	}

private:
	T1 a;
	T2 b;
};

template <class T>
class Array{
public:
	Array(int size):arr(new T[size]), used(0), max(size){}

	~Array(){
		delete [] arr;
	}

	bool add(T t){
		if(used < max)arr[used++] = t;
		return used == max;
	}

	T* smallest(){
		T *min = nullptr;
		for(int i = 0; i<used; i++) {
			if(!min || arr[i] < *min) min = arr+i;
		}
		return min;
	}

	T* next(T t){
		T *min = nullptr;
		for(int i = 0; i<used; i++) {
			if ((!min || (arr[i] < *min)) && (t < arr[i])) {
				min = arr+i;
			}
		}
		return min;
	}

private:
	int max;
	int used;
	T *arr;
};

int main(int argc, const char *argv[]) {
	Array<Pair<string,int>> arr(argc-1);

	for(int i = 1; i < argc; i++){
		arr.add(Pair<string,int>(argv[i],i));
	}

	Pair<string, int> *min = arr.smallest();

	for(Pair<string, int> *p = min; p; p = arr.next(*p)){
		cout << p->getB() << ": " << p->getA() << endl;
	}

	return 0;
}
