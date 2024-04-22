#include<iostream>
#include<ctime>
#include<memory>
#include"lvector.h"
#include"tools.h"
#include"llist.h"
using namespace std;
class test {
public:
	test() { cout << "a" << endl; }
	~test() { cout << "b" << endl; }
};
int main() {
	srand(time(0));
	llist<int> p;
	for (int i = 0; i < 10; i++)
		p.insertAsLast(rand() % 10);
	p.print();
	p.uniquify();
	p.print();
}
