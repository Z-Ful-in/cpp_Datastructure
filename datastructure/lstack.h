#pragma once
#include<iostream>
#include "lvector.h"

template <typename T> class lstack:public lvector<T>{
public:
	void push(const T& item);
	T pop();
	T& top()const;
};

template<typename T> void lstack<T>::push(const T& item){
	lvector<T>::push_back(item);
}

template<typename T> T lstack<T>::pop(){
	return lvector<T>::remove(lvector<T>::_size - 1);
}

template<typename T> T& lstack<T>::top() const
{
	return lvector<T>::elem[lvector<T>::_size - 1];
}
