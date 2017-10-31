// ssarray.h  INCOMPLETE
// VERSION 5
// Glenn G. Chappell
// 25 Oct 2017
//
// For CS 311 Fall 2017
// Header for class SSArray
// Stunningly Smart Array of int
// Preliminary to Assignment 5
//
// History:
// - v1:
//   - Skeleton only: header & source files, #ifndef, #include, empty
//     class definition.
// - v2:
//   - Add data members.
//   - Add member types value_type, size_type, iterator, const_iterator.
//   - Add dummy versions (at least) of all member functions, including
//     dummy return statements for non-void functions. Package compiles.
//   - Write (untested versions of) the following member functions:
//     dctor, op[], size, empty, begin, end, push_back, pop_back.
// - v3:
//   - Combine default ctor & ctor from size into a single function, and
//     write this function.
//   - Add comments, preconditions as necessary for push_back, pop_back.
// - v4:
//   - Revise class invariants to allow for _data being nullptr if _size
//     is 0.
//   - Write copy ctor & move ctor.
//   - Make move assignment and swap noexcept.
//   - Add exception-safety guarantees to all implemented functions.
//   - Move copy & move ops, resize, insert, erase, swap to source file.
// - v5:
//   - Ctor from size is explicit.
//   - Add _capacity data member.
//   - Add static data member DEFAULT_CAP and use it in setting the
//     capacity in default ctor/ctor from size.

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max


// *********************************************************************
// class SSArray - Class definition
// *********************************************************************


// class SSArray
// Stunningly Smart Array of int.
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of int, allocated with new[], owned by
//      *this, holding _capacity ints. Exception: _data may be nullptr,
//      if _capacity == 0.
class SSArray {

// ***** SSArray: types *****
public:

    // value_type: type of data items
    using value_type = int;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** SSArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    static const size_type DEFAULT_CAP;

// ***** SSArray: ctors, op=, dctor
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    explicit SSArray(size_type size=size_type(0))
        :_capacity(std::max(size, DEFAULT_CAP)),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    SSArray(const SSArray & other);

    // Move ctor
    // No-Throw Guarantee
    SSArray(SSArray && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    ~SSArray()
    {
        delete [] _data;
    }

    // Copy assignment
    SSArray & operator=(const SSArray & rhs);

    // Move assignment
    // No-Throw Guarantee
    SSArray & operator=(SSArray && rhs) noexcept;

// ***** SSArray: general public operators *****
public:

    // Operator[] - non-const & const
    // No-Throw Guarantee
    value_type & operator[](size_type index)
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index];
    }

// ***** SSArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    size_type size() const
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const
    {
        return size() == size_type(0);
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin()
    {
        return _data;
    }
    const_iterator begin() const
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end()
    {
        return begin() + size();
    }
    const_iterator end() const
    {
        return begin() + size();
    }

    // resize
    void resize(size_type newsize);

    // insert
    iterator insert(iterator pos,
                    const value_type & item);

    // erase
    iterator erase(iterator pos);

    // push_back
    // InsertEnd operation.
    // ??? Guarantee
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // RemoveEnd operation.
    // Pre:
    //     _size > 0.
    // ??? Guarantee
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    void swap(SSArray & other) noexcept;

// ***** SSArray: data members *****
private:

    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

}; // End class SSArray


#endif //#ifndef FILE_SSARRAY_H_INCLUDED

