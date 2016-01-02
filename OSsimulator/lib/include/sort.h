#ifndef SORT_H
#define SORT_H


template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right );


template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right );



#include "../src/sort.cpp"

#endif
