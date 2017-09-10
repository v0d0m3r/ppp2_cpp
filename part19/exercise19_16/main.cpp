//------------------------------------------------------------------------------

#include "Vector_small.hpp"

//------------------------------------------------------------------------------

void test_copy()
{
    Vector_small<int> vs1(3);
    Vector_small<int> vs2;
    vs2->push_back(2);
    vs2->push_back(4);

    vs1 = vs2;
    cout << vs1[0] << '\n';
}

//------------------------------------------------------------------------------

Vector_small<int> foo()
{
    Vector_small<int> vs2;
    vs2->push_back(2);
    vs2->push_back(4);

    return vs2;
}

//------------------------------------------------------------------------------

void test_move_oper()
{
    Vector_small<int> vs1(3);
    vs1 = foo();
}

//------------------------------------------------------------------------------

int main()
try
{
    test_copy();
    test_move_oper();
    return 0;
}
catch(exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
