#pragma once
template<typename T> void lswap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template<typename T> T lmax(T a, T b) {
	return (a > b) ? a : b;
}