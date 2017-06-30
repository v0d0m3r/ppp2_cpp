//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Link.hpp"

//------------------------------------------------------------------------------

int main()
try {

    Link* p{new Link("dddd")};
    p->insert(new Link("sss"));

    //p = p->advance(1);
    //p = p->previous();
    print_all(p);

    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "Exiting\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
