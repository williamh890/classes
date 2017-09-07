// sample_class.cpp
// William Horn
// Sep 6, 2017
// Simple cs202 assignment

#ifndef TIME_OF_DAY_H_INCLUDED
#define TIME_OF_DAY_H_INCLUDED

#include<iostream>

class TimeOfDay {
public:
    TimeOfDay();
    TimeOfDay(unsigned int h,  unsigned int m,  unsigned int s);

    ~TimeOfDay() = default;
    TimeOfDay(const TimeOfDay & other) = default;
    TimeOfDay & operator=(const TimeOfDay & other) = default;
    TimeOfDay & operator=(TimeOfDay && other) = default;

    void getTime(unsigned int & h,unsigned int & m, unsigned int & s) const;
    void setTime(unsigned int h, unsigned int m, unsigned int s);

    TimeOfDay operator++(int dummy);
    TimeOfDay & operator++();

    TimeOfDay operator--(int dummy);
    TimeOfDay & operator--();

private:
    int _sec; // Seconds past midnight
};

std::ostream & operator<<(std::ostream & str, const TimeOfDay & t) {
    unsigned int h, m, s;
    t.getTime(h, m, s);
    return str << h << ":" << m << ":" << s;
}

TimeOfDay::TimeOfDay() {
    setTime(0, 0, 0);
}

TimeOfDay::TimeOfDay(unsigned int h, unsigned int m, unsigned int s){
    setTime(h, m, s);
}

TimeOfDay TimeOfDay::operator--(int dummy) {
    _sec--;
    return *this;
}

TimeOfDay & TimeOfDay::operator--() {
    _sec--;
    return *this;
}


TimeOfDay TimeOfDay::operator++(int dummy) {
    _sec++;
    return *this;
}

TimeOfDay & TimeOfDay::operator++() {
    _sec++;
    return *this;
}

void TimeOfDay::getTime(unsigned int & h, unsigned int & m,unsigned int & s) const {
    h = _sec / 60 * 60;
    m = _sec / 60;
    s = _sec % (60 * 60);
}


void TimeOfDay::setTime(unsigned int h, unsigned int m, unsigned int s) {
    _sec = s + 60 * m + 60 * 60 * h;
    _sec = _sec % (24 * 60 * 60);
}

#endif // End TIME_OF_DAY_H_INCLUDED
