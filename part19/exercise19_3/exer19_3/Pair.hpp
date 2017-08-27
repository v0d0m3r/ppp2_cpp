//------------------------------------------------------------------------------

#ifndef PAIR_HPP
#define PAIR_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T, typename U>
struct Pair {    
    explicit Pair(T f = T{}, U s = U{}) : first{f}, second{s} {}
    T first;
    U second;
};

//------------------------------------------------------------------------------

template<typename T, typename U, typename Y>
struct Tuple : Pair<T, U> {
    explicit Tuple(T f = T{}, U s = U{}, Y t = Y{})
        : Pair<T, U>{f, s}, third{t} {}
    Y third;
};

//------------------------------------------------------------------------------

#endif // PAIR_HPP

//------------------------------------------------------------------------------
