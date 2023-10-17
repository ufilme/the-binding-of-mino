

template <class L>
DynamicArray<L>::DynamicArray(){
    elements = NULL;
    size = 0;
};

template <class L>
void DynamicArray<L>::push(L element){
    L *tmp = elements;
    size++;
    elements = new L[size];

    elements[size - 1] = element;

    for (int i = 0; i < size - 1; i++){
        elements[i] = tmp[i];
    }

    delete[] tmp;
};

template <class L>
L *DynamicArray<L>::begin(){
    return elements;
};

template <class L>
L *DynamicArray<L>::end(){
    return elements + size;
};

// template class DynamicArray<Entity>;
// template class DynamicArray<Enemy>;