#pragma once
#include<iostream>
#include"tools.h"

template <typename T>
class lvector{
protected:
	int CAPACITY = 10;
	int _size;
	T* elem = new T[CAPACITY];

	int getMax(int lo, int hi)const;
	void selectionSort(int lo, int hi);
	void bubbleSort(int lo, int hi);
	void quickSort(int lo, int hi);
	void insertSort(int lo, int hi);
	void mergeSort(int lo, int hi);

public:
	class iterator {
		lvector<T>* parent;
		int index;
	public:
		iterator(lvector<T> *item, int index): parent(item),index(index){}
		iterator& operator++();
		bool operator!=(const iterator& other);
		T operator*();
	};

	lvector();
	lvector(int n);
	lvector(int n, T item);
	lvector(const lvector<T>& vector);
	~lvector(){delete[] elem;}
	int size()const { return _size; }
	int capacity()const { return CAPACITY; }

	iterator begin() { return iterator(this, 0); }
	iterator end() { return iterator(this, _size); }

	bool ranktest(int rank) const;
	bool rangetest(int lo, int hi)const;
	bool isEmpty()const { return _size == 0; }
	bool isSorted() const { return isSorted(0, _size, [](const T& a, const T& b) ->bool {return a <= b; }); }
	template <typename F> bool isSorted(int lo, int hi, F compare) const;

	void expand(int srcsize); 
	void shrink(); 

	T& lget(int rank)const;
	T& operator[] (int rank)const;

	T push_back(T item);
	T insert(int rank, T item);
	int remove(int lo, int hi);
	T remove(int rank);
	void print() const;
	int getMax()const { return getMax(0, _size); }

	void sort(int lo, int hi);
	void sort() { sort(0, _size); }

	void deduplicate(int lo, int hi); // sorted
	void deduplicate(){ deduplicate(0, _size); }

	void uniquify(int lo, int hi); //unsorted
	void uniquify() { uniquify(0, _size); }

	int search(int lo, int hi,const T& target) const; //sorted
	int search(const T& target)const { return 0 >= _size ? -1 : search(0, _size, target); }
	int find(int lo, int hi,const T& target) const; // unsorted
	int find(const T& target)const { return 0 >= _size ? -1 : find(0, _size, target); }

	lvector<T>& operator+(const lvector<T>& other);
	bool operator==(const lvector<T>& other)const;

};


template<typename T> int lvector<T>::getMax(int lo, int hi) const {
	int max = elem[lo], record = 0;
	for (int i = lo; i < hi; i++){
		if (elem[i] > max) {
			max = elem[i];
			record = i;
		}
	}
	return record;
}
template <typename T> bool lvector<T>::ranktest(int rank) const {
	try{
		if (rank > _size || rank <= 0) {
			throw "IndexERROR!";
		}
	}
	catch (const char* errmsg){
		std::cout << errmsg << std::endl;
		return false;
	}
	return true;
}
template<typename T> bool lvector<T>::rangetest(int lo, int hi)const {
	return lo < hi;
}
template<typename T> template<typename F> bool lvector<T>::isSorted(int lo, int hi, F compare)const {
	while ((lo < --hi) && compare(elem[hi - 1], elem[hi]))
		if (lo == hi - 1)
			return true;
	return false;
}

template <typename T> void lvector<T>::expand(int srcsize) {
	if (CAPACITY < _size * 1.5) {
		CAPACITY = _size * 2;
		T* newelem = elem;
		elem = new T[CAPACITY];
		for (int i = 0; i < srcsize; i++){
			elem[i] = newelem[i];
		}
		delete[] newelem;
	}
}
template <typename T> void lvector<T>::shrink() {
	if (CAPACITY > _size * 2) {
		CAPACITY = 1.5 * _size;
		T* newelem = elem;
		elem = new T[CAPACITY];
		for (int i = 0; i < _size; i++){
			elem[i] = newelem[i];
		}
		delete[] newelem;
	}
}

template <typename T> lvector<T>::lvector(){
	_size = 0;
	elem = new T[CAPACITY];
}
template <typename T> lvector<T>::lvector(int n) {
	_size = n;
	expand(_size);
	for (int i = 0; i < n; i++) {
		elem[i] = T();
	}
}
template <typename T> lvector<T>::lvector(int n, T item) {
	_size = n;
	expand(_size);
	for (int i = 0; i < n;i++) {
		elem[i] = item;
	}
}

template <typename T> T& lvector<T>::lget(int rank)const {
	if (!ranktest(rank + 1))
		exit(0);
	return elem[rank];
}
template <typename T> T& lvector<T>::operator[](int rank)const {
	if (!ranktest(rank + 1))
		exit(0);
	return elem[rank];
}

template <typename T> lvector<T>::lvector(const lvector<T>& srcvector) {
	_size = srcvector.size();
	expand(_size);
	for (int i = 0; i < _size; i++)
		elem[i] = srcvector.lget(i);
}
template <typename T> T lvector<T>::push_back(T item) {
	_size++;
	expand(_size-1);
	elem[_size-1] = item;
	return item;
}
template <typename T> T lvector<T>::insert(int rank, T item) {
	if (!ranktest(rank)) {
		exit(0);
	}
	_size++;
	expand(_size-1);
	for (int i = _size; i >=rank; i--){
		elem[i] = elem[i - 1];
	}
	elem[rank - 1] = item;
	return item;
}
template <typename T> int lvector<T>::remove(int lo, int hi) {
	if (hi <= 0 || lo >= _size) {
		std::cout << "Boundary Error in remove" << std::endl;
		exit(0);
	}
	hi = (hi >= _size ? _size : hi);
	lo = (lo <= 0 ? 0 : lo);
	while (hi < _size) {
		elem[lo++] = elem[hi++];
	}
	_size -= hi - lo;
	shrink();
	return hi - lo;
}
template<typename T> T lvector<T>::remove(int rank) {
	if (ranktest(rank + 1)) {
		T e = elem[rank];
		remove(rank, rank + 1);
		return e;
	}
	exit(0);
}
template<typename T> void lvector<T>::print() const {
	for (int i = 0; i < _size; i++) {
		std::cout << elem[i] << "  ";
	}
}

template<typename T> void lvector<T>::selectionSort(int lo, int hi) {
	if(rangetest){
		while (--hi > lo) {
			lswap(elem[getMax(lo, hi + 1)], elem[hi]);
		}
	}
}
template<typename T> void lvector<T>::insertSort(int lo, int hi) {
	if(rangetest(lo,hi)){
		for (int i = lo + 1; i < hi; i++){
			for (int j = lo; j < i; j++){
				if (elem[j] > elem[i]) {
					int temp = elem[i];
					for (int k = i; k > j; k--){
						elem[k] = elem[k - 1];
					}
					elem[j] = temp;
					break;
				}
			}
		}
	}
}
template<typename T> void lvector<T>::quickSort(int lo, int hi) {
	if (lo >= hi - 1)return;
	T number = elem[lo];
	int startindex = 0, endindex = hi - lo;
	T* temp = new T[hi - lo];
;	for (int i = lo + 1; i < hi; i++) {
		if (elem[i] <= number) {
			temp[startindex++] = elem[i];
		}
		else {
			temp[--endindex] = elem[i];
		}
	}
	temp[startindex] = number;
	for (int i = lo; i < hi; i++)
	{
		elem[i] = temp[i - lo];
	}
	delete[] temp;
	quickSort(lo, startindex + lo);
	quickSort(endindex + lo, hi);
}
template<typename T> void lvector<T>::bubbleSort(int lo, int hi) {
	while (lo < --hi) {
		for (int i = lo; i < hi; i++){
			if (elem[i] > elem[i + 1]) {
				lswap(elem[i], elem[i + 1]);
			}
		}
	}
}
template<typename T> void lvector<T>::mergeSort(int lo, int hi) {
	if (lo == hi-1)	return; // recursion base
	mergeSort(lo, (lo + hi) / 2);
	mergeSort((lo + hi) / 2, hi);

	T* temp0 = elem + lo;
	T* temp2 = elem + (int)((hi + lo) / 2);
	T* temp1 = new T[(int)(hi - lo) / 2];
	for (int i = 0; i < (hi - lo) / 2; temp1[i] = temp0[i++]);
	int p = 0, q = 0;
	for (int i = lo; i < hi; i++) {
		if ((q == ceil((double)(hi - lo) / 2))  ||( (p < (int)(hi - lo) / 2) && (temp1[p] < temp2[q]))) {
			elem[i] = temp1[p++];
		}
		else {
			elem[i] = temp2[q++];
		}
	}
	delete[] temp1;
	return;
}
template<typename T> void lvector<T>::sort(int lo, int hi) {
	quickSort(lo, hi);
}

template<typename T> int lvector<T>::search(int lo, int hi, const T& target) const {
	if (lo == hi)return -1;
	int index = (lo + hi) / 2;
	if (elem[index] == target)return index;
	else if (elem[index] > target)search(lo, index, target);
	else if (elem[index] < target)search(index + 1, hi, target);
}
template<typename T> int lvector<T>::find(int lo, int hi, const T& target) const {
	while ((lo < hi--) && (elem[hi] != target));
	return hi;
}

template<typename T> void lvector<T>::deduplicate(int lo, int hi) { //sorted
	if (!rangetest(lo, hi)) {
		std::cout << "Boundary Error in deduplicate" << std::endl;
		exit(0);
	}
	if (!isSorted()) {
		std::cout << "Unsorted Error in deduplicate" << std::endl;
		exit(0);
	}
	int slowindex = lo, fastindex = lo + 1;
	for (; fastindex < hi; fastindex++) {
		if (elem[slowindex] == elem[fastindex])
			continue;
		elem[++slowindex] = elem[fastindex];
	}
	_size = slowindex + 1;
	shrink();
}
template<typename T> void lvector<T>::uniquify(int lo, int hi) { //unsorted
	if (!rangetest(lo, hi)) {
		std::cout << "Boundary Error in uniquify! " << std::endl;
		exit(0);
	}
	if (isSorted()) {
		std::cout << "Recommend function \"deduplicated\" for sorted vector!" << std::endl;
	}
	int start = lo;
	while (start < hi) {
		int slowindex = start, fastindex = start;
		while (fastindex++ < hi) {
			if (elem[start] != elem[fastindex]){
				elem[++slowindex] = elem[fastindex];
			}
		}
		hi = slowindex;
		start++;
	}
	_size = hi - lo;
	shrink();
}


template<typename T> //The return value is a type, we add typename to emphasize this.
typename lvector<T>::iterator& lvector<T>::iterator::operator++() {
    index++;
    return *this;
}
template<typename T> bool lvector<T>::iterator::operator!=(const iterator& other) {
	return index < other.index;
}
template<typename T> T lvector<T>::iterator::operator*() {
	return parent->elem[index];
}

template<typename T> lvector<T>& lvector<T>::operator+(const lvector<T>& other) {
	lvector<T>* res = new lvector<T>();
	for (int i = 0; i < _size; i++)
		res->push_back(elem[i]);
	for (int j = 0; j < other.size(); j++)
		res->push_back(other[j]);
	return *res;
}
template<typename T> bool lvector<T>::operator==(const lvector<T>& other)const {
	if (_size != other.size()) return false;
	for (int i = 0; i < _size; i++)
		if (elem[i] != other[i])
			return false;
	return true;
}
