// ssarray.cpp  INCOMPLETE
// VERSION 5
// Glenn G. Chappell
// 25 Oct 2017
//
// For CS 311 Fall 2017
// Source for class SSArray
// Stunningly Smart Array of int
// Preliminary to Assignment 5
//
// See ssarray.h for history.

#include "ssarray.h"  // For class SSArray definition
#include <algorithm>
using std::copy;


// *********************************************************************
// class SSArray - Static data member definitions
// *********************************************************************


const SSArray::size_type SSArray::DEFAULT_CAP = SSArray::size_type(16);


// *********************************************************************
// class SSArray - Member function definitions
// *********************************************************************


// Copy ctor
SSArray::SSArray(const SSArray & other)
    :_capacity(other._capacity),
        // _capacity must be declared before _data
     _size(other._size),
     _data(new value_type[_capacity])
{
    copy(other.begin(), other.end(), begin());
}


// Move ctor
SSArray::SSArray(SSArray && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data)
{
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment
SSArray & SSArray::operator=(const SSArray & rhs)
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// Move assignment
SSArray & SSArray::operator=(SSArray && rhs) noexcept
{
    // TODO: WRITE THIS!!!
    return *this; // DUMMY
}


// resize
void SSArray::resize(size_type newsize)
{
    // TODO: WRITE THIS!!!
}


// insert
SSArray::iterator SSArray::insert(SSArray::iterator pos,
                const value_type & item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
SSArray::iterator SSArray::erase(SSArray::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// swap
void SSArray::swap(SSArray & other) noexcept
{
    // TODO: WRITE THIS!!!
}

