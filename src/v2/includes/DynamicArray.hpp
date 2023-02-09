#include "Entity.hpp"

/**
 * @brief Implementation of the Data Structure
 * Define an array with variable size
 * 
 * @tparam the type of data stored in the array
*/
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
        void push(L *element);
        void remove_element(L element);
        void reset();
        L *begin();
        L *end();
};