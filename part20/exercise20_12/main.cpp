//------------------------------------------------------------------------------

#include "List.hpp"

//------------------------------------------------------------------------------

/*
https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01055_source.html
https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a00588.html
https://habrahabr.ru/post/242639/
https://habrahabr.ru/post/226229/
*/

int main()
try
{    
    List<int> lst;
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//----------------------------------------------------------------
