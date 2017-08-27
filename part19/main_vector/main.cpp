//------------------------------------------------------------------------------

#include <Vector.hpp>

//------------------------------------------------------------------------------

Vector_base<string, Allocator<string>> call_vect_base()
{
    Vector_base<string, Allocator<string>> vbs1{Allocator<string>(), 5, 10};
    return vbs1;
}

//------------------------------------------------------------------------------

void test_vector_base()
{
    Vector_base<string, Allocator<string>> vbs;
    Vector_base<string, Allocator<string>> vbs1{Allocator<string>(), 5, 10};

    Vector_base<string, Allocator<string>> vbs2{Allocator<string>(), 4};
    //Vector_base<string, Allocator<string>> cp_vbs{vbs1};

    vbs = vbs1;
    vbs1 = vbs2;
    Vector_base<string, Allocator<string>> vbs_move{move(vbs)};
    vbs1 = call_vect_base();
    Vector_base<string, Allocator<string>> vbs3{Allocator<string>(), 4};
}

//------------------------------------------------------------------------------

Vector<string> call_vect()
{
    Vector<string> vbs1{"s", "mother"};
    return vbs1;
}

//------------------------------------------------------------------------------

void test_vector()
{
    Vector<string> vbs;
    Vector<string> vbs1{"s", "mother"};
    Vector<string> vbs4(1);
    vbs4 = call_vect();

    Vector<string> cp_vbs{vbs1};
    vbs = vbs1;

    int n = 0;
}

//------------------------------------------------------------------------------

int main()
try
{
    test_vector();
    //test_vector_base();

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
