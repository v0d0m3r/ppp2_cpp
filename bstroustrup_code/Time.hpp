#ifndef TIME_HPP
#define TIME_HPP

//-----------------------------------------------------------------------------

#include "std_lib_facilities.h"
#include <chrono>
#include <thread>

//-----------------------------------------------------------------------------
// Простая структура получения текущего времени
struct Current_time
{
    Current_time() { update(); }

    int hour()   { return hs; }
    int minute() { return ms; }
    int second() { return ss; }

    void update();  // Обновляем текущее время

private:
    int hs{0};
    int ms{0};
    int ss{0};    
};

//-----------------------------------------------------------------------------

#endif // TIME_HPP
