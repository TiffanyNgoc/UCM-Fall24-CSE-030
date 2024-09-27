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

// inline int time_diff(Timestamp start, Timestamp end, Unit u = mill){
    
//     if (u == mill){
//         auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        
//         return (int) diff;
//     }
//     else{
//         auto diff = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
        
//         return (int) diff;
//     }
// }


// inline TimePoint current_time(){
//     return std::chrono::high_resolution_clock::now();
// }

#endif
