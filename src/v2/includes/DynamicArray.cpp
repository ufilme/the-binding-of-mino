#include "DynamicArray.hpp"

template <class L>
DynamicArray<L>::DynamicArray(){
    elements = NULL;
    size = 0;
};

// Create a tmp copy of the array pointer 
// Expand the array with the size + 1
// Copy each element from the tmp to the new array

template <class L>
void DynamicArray<L>::push(L element){
    L *tmp = elements;
    elements = new L[++size];

    elements[size - 1] = element;

    for (int i = 0; i < size - 1; i++){
        elements[i] = tmp[i];
    }

    delete[] tmp;
};

// begin() and end() are used for range loops

template <class L>
L *DynamicArray<L>::begin(){
    return elements;
};

template <class L>
L *DynamicArray<L>::end(){
    return elements + size;
};

// It's necessary to initialize the template
// This cause we have a header file, so when the compiler
// use the template to create the class for a specific type
// it can't find the defined methods in the cpp file.
// Another alternative is to add an include in the header
// to this file, but since we use the template only for
// two types we can just initiazile them here 

template class DynamicArray<Entity>;
template class DynamicArray<Enemy>;