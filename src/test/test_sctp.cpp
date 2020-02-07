#include<iostream>
#include<vector>
#include<sctp.h>
#include<string.h>
#include<chunk.h>
using namespace std;


class A;
class B;

class A {
public:
	A(){
		cout << "A:A()" << endl;

	}
	A(int a){
		cout << "A:A(int a)" << endl;

	}
	virtual ~A(){
		cout << "A:~A" << endl;
	}
	virtual void test(){
		cout << "A:test" << endl;
	}
	virtual void pure() = 0;

};
class B: public A {
public:
	B() : A(){

		cout << "B:B" << endl;

	}
	~B(){
		cout << "B:~B" << endl;

	}
	void test(){
		A::test();
		cout << "B:test" << endl;
	}
	void pure(){
		cout << "B:pure" << endl;

	}
};
void test(int** test_v){
	int* a = new int[10];
	*test_v = a;
}
int main(){
	A* b;
	b = new B();
	int* data = new int[10];
	int* data2 = new int[10];
	for(int i = 0; i<10; i++) data[i] = i;
	for(int i = 0; i<10; i++) data2[i] = 0;
	memcpy(&data2[5], &data[5], sizeof(int)*5);
	cout << "===========" << endl;
	for(int i = 0; i<10; i++) cout << data[i] << endl;
	cout << "===========" << endl;
	for(int i = 0; i<10; i++) cout << data2[i] << endl;
	cout << "===========" << endl;


	b->test();
	b->pure();
	cout << "test" << endl;
	sctp::ChunkType ct = sctp::_UNKNOWN_CHUNK_;
	cout << ct << endl;
	delete b;

	vector<int> test_vec;

	test_vec.push_back(20);
	test_vec.push_back(30);
	test_vec.push_back(40);
	vector<int>::iterator iter = test_vec.begin();
	//test_vec.erase(test_vec.begin() + 1);

	cout << *iter << endl;

}



