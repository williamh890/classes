// sample_class.cpp
// William Horn
// Sep 6, 2017
// Simple cs202 assignment

class TimeOfDay {
    TimeOfDay();
    TimeOfDay(unsigned int h,  unsigned int m,  unsigned int s);

    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};


TimeOfDay::TimeOfDay() {
    hour = 0;
    minute = 0;
    second = 0;
}

TimeOfDay::TimeOfDay(unsigned int m,
