#include"lvector.h"

template<typename T>
lvector<T>::lvector(int n)
{
	size = n;
	elem = new T[n];
}

template<typename T>
lvector<T>::lvector(int n, T item)
{
	size = n;
	elem = new T[n];
	for (int i = 0; i < n; i++) {
		elem[i] = item;
	}
}