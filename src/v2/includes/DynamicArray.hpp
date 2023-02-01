#include "Entity.hpp"

template <class L>
class DynamicArray{
    protected:
        L *elements;
        int size;
    public:
        DynamicArray();
        L operator[](int i);
        int get_size();
        void push(L element);
        void remove_element(L *element);
        void reset();
        L *begin();
        L *end();
};