#ifndef LINK_HPP
#define LINK_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Link {
    string value;
    Link* prev;
    Link* succ;
    Link(const string& s, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
};

//------------------------------------------------------------------------------

#endif // LINK_HPP
