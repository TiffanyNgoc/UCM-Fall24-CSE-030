//
// A small library for timing our programs
//

#ifndef TIME_SUPPORT_H
#define TIME_SUPPORT_H

#include <chrono>

typedef enum {
    sec,
    mill
} Unit;

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

class Timestamp{
    TimePoint t;

public:
    Timestamp(){
        t = std::chrono::high_resolution_clock::now();
    }

    int operator-(const Timestamp& rhs){
        return std::chrono::duration_cast<std::chrono::milliseconds>(t-rhs.t).count();
    }
};
#endif
