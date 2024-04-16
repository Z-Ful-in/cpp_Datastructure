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
	llist<int> p(10, 1);
	p.print();
}
