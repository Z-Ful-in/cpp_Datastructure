#pragma once
template<typename T> void lswap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template<typename T> T lmax(T a, T b) {
	return (a > b) ? a : b;
}

int lstrlen(const char* str) {
	int res = 0;
	while (*str != '\0') {
		res++;
		str++;
	}
	return res;
}