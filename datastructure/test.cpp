#include<iostream>
#include<ctime>
#include<memory>
#include"lvector.h"
#include"tools.h"
using namespace std;
class test {
public:
	test() { cout << "a" << endl; }
	~test() { cout << "b" << endl; }
};
int main() {

	//int a[10] = {};
	//for (int i = 0; i < 10; i++)
	//	a[i] = i;
	//shared_ptr<int> p = make_shared<int>(a[0]);
	//shared_ptr<int> q(p);
	//cout << p.use_count() << endl << q.use_count();
	srand(time(0));
	lvector<int> p(10);
	for (int i = 0; i < 10; i++)
	{
		p[i] = rand()%10;
		cout << p[i] << "  ";
	}
	cout<<endl;
	p.uniquify();
	for (auto i : p) {
		cout << i << "  ";
	}
	cout << endl;
	p.print();
}
