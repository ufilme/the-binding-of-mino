#include "Entity.hpp"

template <class L>
class DynamicArray{
    protected:
        L *elements;
        int size;
    public:
        DynamicArray();
        void push(L element);
        L *begin();
        L *end();
};

#include "DynamicArray.tpp"