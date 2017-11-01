// kssarray.h
// William Horn
// 25 Oct 2017
//
// For CS 311 Fall 2017
// Header for class TSSArray
// Templated Stunningly Smart Array
// Assignment 5

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max
#include <algorithm>
// For std::copy
// For std::rotate
#include <iterator>
// For std::distance
#include <iostream> // For std::cout, std::endl

#define DEFAULT_CAP 10

// *********************************************************************
// class TSSArray - Class definition
// *********************************************************************


// class TSSArray
// Template Stunningly Smart Array
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _capacity ints. Exception: _data may be nullptr,
//      if _capacity == 0.
template<typename T>
class TSSArray {

// ***** TSSArray: types *****
public:

    // value_type: type of data items
    using value_type = T;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** TSSArray: internal-use functions *****
private:

    // getOverAllocAmount
    // Exception Neutral
    // No-Throw Guarantee
    size_type getOverAllocAmount() noexcept {
        return (size_type) 2;
    }

    // capacityResize
    // Exception Neutral
    // Strong Guarantee
    void capacityResize(size_type newCap);

// ***** TSSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Exception Neutral
    // Strong Guarantee
    explicit TSSArray(size_type size=size_type(0))
        :_capacity(std::max(size * getOverAllocAmount(), (size_type)DEFAULT_CAP)),
         _size(size),
         _data(new value_type[_capacity]) {}

    // Copy ctor
    // Exception Neutral
    // Strong Guarantee
    TSSArray(const TSSArray & other);

    // Move ctor
    // Exception Neutral
    // No-Throw Guarantee
    TSSArray(TSSArray && other) noexcept;

    // Dctor
    // Exception Neutral
    // No-Throw Guarantee
    ~TSSArray() noexcept {
        delete[] _data;
    }

    // Copy assignment
    // Exception Neutral
    // Strong Guarantee
    TSSArray & operator=(const TSSArray & rhs);

    // Move assignment
    // Exception Neutral
    // No-Throw Guarantee
    TSSArray & operator=(TSSArray && rhs) noexcept;

// ***** TSSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // Exception Neutral
    // No-Throw Guarantee
    value_type & operator[](size_type index) noexcept {
        return _data[index];
    }
    const value_type & operator[](size_type index) const noexcept {
        return _data[index];
    }

// ***** TSSArray: general public functions *****
public:

    // size
    // Exception Neutral
    // No-Throw Guarantee
    size_type size() const noexcept {
        return _size;
    }

    // empty
    // Exception Neutral
    // No-Throw Guarantee
    bool empty() const noexcept {
        return size() == size_type(0);
    }

    // begin - non-const & const
    // Exception Neutral
    // No-Throw Guarantee
    iterator begin() noexcept {
        return _data;
    }
    const_iterator begin() const noexcept {
        return _data;
    }

    // end - non-const & const
    // Exception Neutral
    // No-Throw Guarantee
    iterator end() noexcept {
        return begin() + size();
    }
    const_iterator end() const noexcept {
        return begin() + size();
    }

    // resize
    // Exception Neutral
    // Strong Guarantee
    void resize(size_type newsize);

    // insert
    // Exception Neutral
    // Strong Guarantee
    iterator insert(iterator pos,
                    const value_type & item);

    // erase
    // Exception Neutral
    // No-Throw Guarantee
    iterator erase(iterator pos) noexcept;

    // push_back
    // InsertEnd operation.
    // Exception Neutral
    // Strong Guarantee
    void push_back(const value_type & item) {
        insert(end(), item);
    }

    // pop_back
    // RemoveEnd operation.
    // Pre:
    //     _size > 0.
    // Exception Neutral
    // No-Throw Guarantee
    void pop_back() noexcept {
        erase(end()-1);
    }

    // swap
    // Exception Neutral
    // No-Throw Guarantee
    void swap(TSSArray & other) noexcept;

// ***** TSSArray: data members *****
private:

    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

}; // End class TSSArray


// Copy ctor
template<typename T>
TSSArray<T>::TSSArray(const TSSArray<T> & other)
    :_capacity(other._capacity),
     _size(other._size),
     _data(new value_type[_capacity]) {


    try {
        std::copy(other.begin(), other.end(), begin());
     }
    catch(...) {
        delete [] _data;
        throw;
    }

}


// Move ctor
template<typename T>
TSSArray<T>::TSSArray(TSSArray<T> && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data) {
    // 'Destroy' other
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(const TSSArray<T> & other) {
    // Self assignment
    if (this != &other) {
        // Reallocate if different sizes
        if (other._capacity != _capacity) {
            delete[] _data;
            _size = 0;
            _data = nullptr;

            _data = new value_type[other._capacity];
            _size = other._size;
            _capacity = other._capacity;
        }

        std::copy(other._data, other._data + other._size, _data);
    }

    return *this;
}


// Move assignment
template<typename T>
TSSArray<T> & TSSArray<T>::operator=(TSSArray<T> && other) noexcept {

    if (this != &other) {
        this->swap(other);
    }

    return *this;
}


// capacityResize
template<typename T>
void TSSArray<T>::capacityResize(size_type newCap) {
    // Check if a resize is needed
    if (newCap <= _capacity) {
        return;
    }

    // Do the resize
    newCap *= getOverAllocAmount();
    auto newLoc = new value_type[newCap];

    try {
        std::copy(begin(), end(), newLoc);
    }
    catch(...) {
        delete [] newLoc;
        throw;
    }

    // Copy was successful
    delete[] _data;

    _data = newLoc;
    _capacity = newCap;
}


// resize
template<typename T>
void TSSArray<T>::resize(size_type newSize) {
    if (newSize > _capacity) {
        capacityResize(newSize * getOverAllocAmount());
    }

    _size = newSize;
}


// insert
template<typename T>
typename TSSArray<T>::iterator
TSSArray<T>::insert(TSSArray<T>::iterator pos,
                    const value_type & item) {
    // Check if need to resize array
    if (_size + 1 > _capacity) {
        auto posIndex = std::distance(begin(), pos);
        capacityResize(_capacity + 1);
        pos = begin() + posIndex;
    }

    // Move the data
    for (auto iter = end() - 1; iter != (pos - 1); --iter) {
        std::swap(*(iter + 1), *iter);
    }

    // Add the item
    *pos = item;
    ++_size;

    return pos;
}


// erase
template<typename T>
typename TSSArray<T>::iterator
TSSArray<T>::erase(TSSArray<T>::iterator pos) noexcept {
    // Move the data down
    for (auto iter = pos; iter != end(); ++iter) {
        std::swap(*iter, *(iter + 1));
    }

    --_size;

    return pos;  // DUMMY
}


// swap
template<typename T>
void TSSArray<T>::swap(TSSArray<T> & other) noexcept {
    using std::swap;

    swap(_data , other._data);
    swap(_capacity , other._capacity);
    swap(_size , other._size);
}


#endif //#ifndef FILE_SSARRAY_H_INCLUDED

