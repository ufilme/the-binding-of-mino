#include "DynamicArray.hpp"
#include <iostream>
using namespace std;

template <class L>
DynamicArray<L>::DynamicArray(){
    elements = NULL;
    size = 0;
};

template <class L>
L DynamicArray<L>::operator[](int i){
    return elements[i];
}

template <class L>
int DynamicArray<L>::get_size(){
    return size;
}

/**
 * @brief Add an element to the data structure
 * Create a tmp copy of the array pointer
 * Expand the array with the size + 1 
 * Copy each element from the tmp to the new array
 * 
 * @tparam L type of element
 * @param element element to add to the data structure
 */
template <class L>
void DynamicArray<L>::push(L element){
    L *tmp = elements;
    elements = new L[++size];

    elements[size - 1] = element;

    for (int i = 0; i < size - 1; i++)
        elements[i] = tmp[i];
    delete[] tmp;
};

/**
 * @brief Remove an element from the data structure
 * Create a tmp copy of the array pointer
 * Compact the array with the size - 1 
 * Copy each element from the tmp to the new array
 * excluding the element to remove
 *  
 * @tparam L type of element
 * @param element element to remove
 */
template <class L>
void DynamicArray<L>::remove_element(L element){
    if (size <= 1){
        this->reset();
    }
    else{
        L *tmp = elements;
        elements = new L[--size];
    
        int j = 0;
        for (int i = 0; i < size + 1; i++){
            if (tmp[i] != element)
                elements[j++] = tmp[i];
        }
    
        delete[] tmp;
    }
};

template <class L>
void DynamicArray<L>::reset(){
    delete[] elements;
    size = 0;
    elements = NULL;
}

// begin() and end() are used for range loops

template <class L>
L *DynamicArray<L>::begin(){
    return elements;
};

template <class L>
L *DynamicArray<L>::end(){
    return elements + size;
};

/**
 * @brief It's necessary to initialize the template
 * This cause we have a header file, so when the compiler
 * use the template to create the class for a specific type
 * it can't find the defined methods in the cpp file.
 * Another alternative is to add an include in the header
 * to this file, but since we use the template only a few
 * types we can just initiazile them here 
 * 
*/
template class DynamicArray<Entity>;
template class DynamicArray<Enemy>;
template class DynamicArray<Bullet>;
template class DynamicArray<Artifact>;
template class DynamicArray<int>;