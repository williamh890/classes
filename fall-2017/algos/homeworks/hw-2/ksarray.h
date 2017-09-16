// ksarray.h
// William Horn
// Sep 15, 2017
// CS 311 - Kinda Smart Array

#ifndef KSARRAY_DEFINED
#define KSARRAY_DEFINED

#include<cstddef>


template<typename T>
class KSArray {

public:
    using value_type = T;

    explicit KSArray(std::size_t initSize = 10);


    ~KSArray();
    KSArray(const KSArray & other);
    KSArray(KSArray && other);
    const KSArray & operator=(const KSArray & other);
    KSArray & operator=(KSArray && other);

    T operator[](std::size_t index);
    const T operator[](std::size_t index) const;

    std::size_t size() const;

    T * begin();
    const T * begin() const;

    T * end();
    const T * end() const;

    bool operator==(const KSArray & other) const;
    bool operator!=(const KSArray & other) const;
    bool operator<=(const KSArray & other) const;
    bool operator>=(const KSArray & other) const;
    bool operator>(const KSArray & other) const;
    bool operator<(const KSArray & other) const;

private:
    T * _array;
    std::size_t _size;
};


template<typename T>
KSArray<T>::KSArray(std::size_t initSize) : _size(initSize), _array(new T[_size]) {}


template<typename T>
KSArray<T>::~KSArray() {
    delete [] _array;
}


template<typename T>
KSArray<T>::KSArray(const KSArray & other) : _size(other._size) {
    T * arrCopy = new T[_size];


}


template<typename T>
KSArray<T>::KSArray(KSArray && other) {}


template<typename T>
const KSArray<T> & KSArray<T>::operator=(const KSArray & other) {}


template<typename T>
KSArray<T> & KSArray<T>::operator=(KSArray && other) {}


template<typename T>
T KSArray<T>::operator[](std::size_t index) {}


template<typename T>
const T KSArray<T>::operator[](std::size_t index) const {}


template<typename T>
std::size_t KSArray<T>::size() const { return 0; }


template<typename T>
T * KSArray<T>::begin() {}


template<typename T>
const T * KSArray<T>::begin() const {}


template<typename T>
T * KSArray<T>::end() {}


template<typename T>
const T * KSArray<T>::end() const {}


template<typename T>
bool KSArray<T>::operator==(const KSArray & other) const { return true; }


template<typename T>
bool KSArray<T>::operator!=(const KSArray & other) const { return true; }


template<typename T>
bool KSArray<T>::operator<=(const KSArray & other) const { return false; }


template<typename T>
bool KSArray<T>::operator>=(const KSArray & other) const { return true; }


template<typename T>
bool KSArray<T>::operator>(const KSArray & other) const { return true; }


template<typename T>
bool KSArray<T>::operator<(const KSArray & other) const { return true; }



#endif // KSARRAY_DEFINED
