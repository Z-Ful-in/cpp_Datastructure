#pragma once
template<typename T> void lswap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}