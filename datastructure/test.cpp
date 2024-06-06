#include<iostream>
#include<ctime>
#include"lvector.hpp"
#include"tools.h"
#include"llist.hpp"
#include "lbintree.hpp"
#include "lstring.hpp"
#include"lBST.hpp"
using namespace std;
class test {
public:
	test() { cout << "a" << endl; }
	~test() { cout << "b" << endl; }
};
int main() {
	srand(time(0));
	lvector<int> p(20);
	int index = 0;
	while(index < p.size())
		p[index++] = rand() % 100;
	p.print();
	cout << endl;
	BST<int> test(p);
	test.print();
	test.remove(5);
	//test.print();
	//cout << endl;
	test.print();
}
