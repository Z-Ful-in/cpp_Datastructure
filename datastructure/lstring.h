#pragma once
#include "lvector.h"
#include<iostream>
class lstring : public lvector<char> {
public:
	lstring() :lvector<char>() {}
	lstring(const char* str) : lvector<char>(lstrlen(str)) {
		for (int i = 0; i < _size; i++)
			elem[i] = str[i];
	}
	lstring(int n, char item) : lvector<char>(n, item) {}
	lstring(const lstring& other) : lvector<char>(other) {}

	int length()const { return _size; }

	friend std::ostream& operator<<(std::ostream& os, lstring s);
	friend std::istream& operator>>(std::istream& in, lstring s);

	friend lstring& operator+(const char* str, const lstring& obj); //const char * + lstring
	friend bool operator ==(const char* str, const lstring& obj); //const char* == lstring
	lstring& operator+(const lstring& other); // lstring + lstring, or lstring + const char *str
	lstring& operator=(const lstring& other); // lstring = lstring, or lstring = const char *
	bool operator ==(const lstring& other); // lstring == lstring, or lstring == const char *
};


std::ostream& operator<<(std::ostream& os, lstring s) {
	for (char i : s)
		os << i;
	return os;
}

std::istream& operator>>(std::istream& in, lstring s) {
	for (char i : s)
		in >> i;
	return in;
}

lstring& operator+(const char* str, const lstring& obj)
{
	lstring* res = new lstring();
	for (int i = 0; i < lstrlen(str); i++)
		res->push_back(str[i]);
	for (int i = 0; i < obj.length(); i++)
		res->push_back(obj[i]);
	return *res;
}

bool operator==(const char* str, const lstring& obj){
	if (lstrlen(str) != obj.length())return false;
	for (int i = 0; i < obj.length(); i++)
		if (str[i] != obj[i])
			return false;
	return true;
}

lstring& lstring::operator+(const lstring& other) {
	lstring* res = new lstring();
	for (int i = 0; i < _size; i++)
		res->push_back(elem[i]);
	for (int i = 0; i < other.length(); i++)
		res->push_back(other[i]);
	return *res;
}

lstring& lstring::operator=(const lstring& other) {
	_size = other.length();
	if (_size >= CAPACITY) expand(_size);
	else if (_size < CAPACITY) shrink();
	for (int i = 0; i < _size; i++)
		elem[i] = other[i];
	return *this;
}


bool lstring::operator==(const lstring& other) {
	if (_size != other.length())
		return false;
	for (int i = 0; i < _size; i++)
		if (elem[i] != other[i])
			return false;
	return true;
}