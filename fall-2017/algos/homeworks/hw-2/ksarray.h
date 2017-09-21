// ksarray.h
// William Horn
// Sep 15, 2017
// CS 311 - Kinda Smart Array

#ifndef KSARRAY_DEFINED
#define KSARRAY_DEFINED

#include<cstddef> // size_t
#include<iostream> // cout
#include<utility> //exchange
#include<sstream>


template<typename T>
class KSArray {

public:
    using size_type = std::size_t;
    using value_type = T;

    explicit KSArray(size_type initSize = 10);

    ~KSArray();
    KSArray<value_type>(const KSArray<value_type> & other);
    KSArray(KSArray<value_type> && other) noexcept;
    KSArray & operator=(const KSArray<value_type> & other);
    KSArray<value_type> & operator=(KSArray<value_type> && other) noexcept;

    value_type& operator[](size_type index);
    const value_type& operator[](size_type index) const;

    size_type size() const {
        return _size;
    }

    value_type * begin();
    const value_type * begin() const;

    value_type * end();
    const value_type * end() const;

    bool operator==(const KSArray<value_type> & other) const;
    bool operator!=(const KSArray<value_type> & other) const;
    bool operator<=(const KSArray<value_type> & other) const;
    bool operator>=(const KSArray<value_type> & other) const;
    bool operator>(const KSArray<value_type> & other) const;
    bool operator<(const KSArray<value_type> & other) const;

private:
    value_type * _array;
    size_type _size;
};


template<typename value_type>
KSArray<value_type>::KSArray(size_type initSize) : _size(initSize), _array(new value_type[initSize]) {}


template<typename value_type>
KSArray<value_type>::~KSArray() {
    delete [] _array;
}


template<typename value_type>
KSArray<value_type>::KSArray(const KSArray<value_type> & other) : _size(other._size), _array(new value_type[other._size]) {
    std::copy(other._array, other._array + other._size, _array);
}


template<typename value_type>
KSArray<value_type>::KSArray(KSArray<value_type> && other) noexcept {
    _array = std::exchange(other._array, nullptr);
    _size = std::exchange(other._size, 0);
}


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


template<typename value_type>
KSArray<value_type> & KSArray<value_type>::operator=(KSArray<value_type> && other) noexcept{

    if(this != &other) {
        delete[] _array;
        _array = std::exchange(other._array, nullptr);
        _size = std::exchange(other._size, 0);
    }

    return *this;
}


template<typename value_type>
value_type& KSArray<value_type>::operator[](size_type index) {
    return _array[index];
}


template<typename value_type>
const value_type& KSArray<value_type>::operator[](size_type index) const {
    return _array[index];
}


template<typename value_type>
value_type * KSArray<value_type>::begin() {return _array;}


template<typename value_type>
const value_type * KSArray<value_type>::begin() const {return _array;}


template<typename value_type>
value_type * KSArray<value_type>::end() {return _array + _size;}


template<typename value_type>
const value_type * KSArray<value_type>::end() const {return _array + _size;}


template<typename value_type>
bool KSArray<value_type>::operator==(const KSArray<value_type> & other) const {
    bool areEq = true;

    if (_size != other._size) areEq = false;

    for(auto i = 0; i < _size; ++i) {
        if (_array[i] != other._array[i]) {
            areEq = false;
            break;
        }
    }

    return areEq;
}


template<typename value_type>
bool KSArray<value_type>::operator!=(const KSArray<value_type> & other) const {
    return !(*this == other);
}


template<typename value_type>
bool KSArray<value_type>::operator<=(const KSArray<value_type> & other) const {
    return *this < other || *this == other;
}


template<typename value_type>
bool KSArray<value_type>::operator>=(const KSArray<value_type> & other) const {
    return !(*this < other);
}


template<typename value_type>
bool KSArray<value_type>::operator>(const KSArray<value_type> & other) const {
    return !(*this < other) && !(*this == other);
}


template<typename value_type>
bool KSArray<value_type>::operator<(const KSArray<value_type> & other) const {
    bool isLessThan = false;

    auto len = (_size < other._size) ? _size :  other._size;

    for(auto i = 0; i < len; ++i) {
        if (_array[i] > other._array[i]) {
            break;
        }
        if (_array[i] == other._array[i]) continue;

        else if (_array[i] < other._array[i]) {
            isLessThan = true;
            break;
        }
    }

    return isLessThan;
}


#endif // KSARRAY_DEFINED
