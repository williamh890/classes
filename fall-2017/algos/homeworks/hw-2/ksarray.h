// ksarray.h
// William Horn
// Sep 15, 2017
// CS 311 - Kinda Smart Array

#ifndef KSARRAY_DEFINED
#define KSARRAY_DEFINED

#include<cstddef> // size_t
#include<iostream> // cout
#include<utility> //exchange

// **********************************************************************
// class KSArray - Class Definition
// **********************************************************************

// class KsArray
// Array to hold generic types, not resizable
// keeps track of size and a pointer to the data
// Invariants:
//     size >= 0
//     array with size number of elements of type T
template<typename T>
class KSArray {

public:
    using size_type = std::size_t;
    using value_type = T;

   // ********* Ctors, dctor, op= *********

    // Ctor
    // Allocatets an array of size passed, defaults to 10
    // Pre: None
    // Post: array will be a valid pointer
    //       size == initSize
    explicit KSArray(size_type initSize = 10);

    // Dtor
    // Frees up allocated memory
    // Pre: None
    // Post: array will be deallocated
    ~KSArray();

    // Copy Ctor
    // Makes a copy of a KSArray object
    // Pre: None
    // Post: _size == other._size
    //       All values in other will be copied
    //       into the newly constructed object
    KSArray(const KSArray & other);

    // Move Ctor
    // Move a KSArray object
    // Pre: None
    // Post: other._array == nullptr
    //       _array will be the old value of other._array
    //       _size == other._size
    KSArray(KSArray && other) noexcept;

    // Op= (copy)
    // Pre: None
    // Post: other._size == _size
    //       all objects in other._array will be copied into
    //       _array
    KSArray & operator=(const KSArray & other);

    // Op= (move)
    // Pre: None
    // Post: other._size == 0
    //       other._array == nullptr
    //       _array == other._array's old value
    KSArray & operator=(KSArray && other) noexcept;

    // Op[] (non const)
    // Pre: value must be < _size
    // Post: returns address of value at _array[index]
    value_type& operator[](size_type index);

    // Op[] (const)
    // Pre: value must be < _size
    // Post: returns const ref to value at _array[index]
    const value_type& operator[](size_type index) const;

    // size
    // return the number of elements in the array
    // Pre: None
    // Post: returns value of _size
    size_type size() const {
        return _size;
    }

    // begin (non const)
    // get pointer to start of _array
    // Pre: None
    // Post: returns valid pointer
    value_type * begin();

    // begin (const)
    // get pointer to start of _array
    // Pre: None
    // Post: returns valid pointer
    const value_type * begin() const;

    // end (non const)
    // gets pointer to end of _array
    // Pre: None
    // Post: returns valid pointer    const value_type * begin() const;
    value_type * end();

    // end (const)
    // gets a const pointer to end of _array
    // Pre: None
    // Post: returns valid pointer
    const value_type * end() const;

private:
    // ********* Private Member Functions ************

    // mswap
    // Calls swap on members of KSArray
    // Pre: None
    // Post: _size and _array will be swapped between *this and other
    void mswap(KSArray & other) noexcept;

    // *******  Data Members ************

    value_type * _array; // Pointer to array data
    size_type _size;     // The size of the array

};


// (see definition for docs)
template<typename value_type>
void KSArray<value_type>::mswap(KSArray<value_type> & other) noexcept {
    using std::swap;

    swap(_array, other._array);
    swap(_size, other._size);
}


// (see definition for docs)
template<typename value_type>
KSArray<value_type>::KSArray(size_type initSize) : _size(initSize), _array(new value_type[initSize]) {}


// (see definition for docs)
template<typename value_type>
KSArray<value_type>::~KSArray() {
    delete [] _array;
}


// (see definition for docs)
template<typename value_type>
KSArray<value_type>::KSArray(const KSArray<value_type> & other) : _size(other._size), _array(new value_type[other._size]) {
    std::copy(other._array, other._array + other._size, _array);
}


// (see definition for docs)
template<typename value_type>
KSArray<value_type>::KSArray(KSArray<value_type> && other) noexcept
    : _array(other._array), _size(other._size)
{
    other._array = nullptr;
    other._size = 0;
}


// (see definition for docs)
template<typename value_type>
KSArray<value_type> & KSArray<value_type>::operator=(const KSArray<value_type> & other) {
    // Self assignment
    if (this != &other) {
        // Reallocate if different sizes
        if (other._size != _size) {
            delete[] _array;
            _size = 0;
            _array = nullptr;
            _array = new value_type[other._size];
            _size = other._size;
        }

        // Copy data
        std::copy(other._array, other._array + other._size, _array);
    }

    return *this;
}


// (see definition for docs)
template<typename value_type>
KSArray<value_type> & KSArray<value_type>::operator=(KSArray<value_type> && other) noexcept{

    if(this != &other) {
       mswap(other);
    }

    return *this;
}


// (see definition for docs)
template<typename value_type>
value_type& KSArray<value_type>::operator[](size_type index) {
    return _array[index];
}


// (see definition for docs)
template<typename value_type>
const value_type& KSArray<value_type>::operator[](size_type index) const {
    return _array[index];
}


// (see definition for docs)
template<typename value_type>
value_type * KSArray<value_type>::begin() {return _array;}


// (see definition for docs)
template<typename value_type>
const value_type * KSArray<value_type>::begin() const {return _array;}


// (see definition for docs)
template<typename value_type>
value_type * KSArray<value_type>::end() {return _array + _size;}


// (see definition for docs)
template<typename value_type>
const value_type * KSArray<value_type>::end() const {return _array + _size;}


// (see definition for docs)
template<typename value_type>
bool operator==(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    bool areEq = true;

    if (lhs.size() != rhs.size()) areEq = false;

    for(auto i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            areEq = false;
            break;
        }
    }

    return areEq;
}


// (see definition for docs)
template<typename value_type>
bool operator!=(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    return !(lhs == rhs);
}


// (see definition for docs)
template<typename value_type>
bool operator<=(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    return !(lhs > rhs);
}


// (see definition for docs)
template<typename value_type>
bool operator>=(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    return !(lhs < rhs);
}


// (see definition for docs)
template<typename value_type>
bool operator>(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}


// (see definition for docs)
template<typename value_type>
bool operator<(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs) {
    bool isShorter;
    std::size_t len;

    if (lhs.size() < rhs.size()) {
        isShorter = true;
        len = lhs.size();
    }
    else {
        isShorter = false;
        len = rhs.size();
    }

    for(auto i = 0; i < len; ++i) {
        if (lhs[i] == rhs[i]) continue;

        else if (lhs[i] < rhs[i]) {
            return true;
        }
    }

    return isShorter;

}


#endif // KSARRAY_DEFINED
