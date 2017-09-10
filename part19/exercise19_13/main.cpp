//------------------------------------------------------------------------------

#include "Tracer.hpp"

//------------------------------------------------------------------------------

Tracer gb_tr{"Obj_glob"};

//------------------------------------------------------------------------------

struct Pod {
    int i;
    char ch;
    double d;
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Pod& p)
{
    return os << "i: "     << p.i
              << "\nch: "  << p.ch
              << "\nd: "   << p.d;
}

//------------------------------------------------------------------------------

struct Struct1 {
    Tracer tr;
    //Struct1() = default;
};

//------------------------------------------------------------------------------

struct Struct2 : Struct1 {
    Tracer tr;
    Struct2(const string& str) : tr{str}  {}
    Struct2() = default;
};

//------------------------------------------------------------------------------

void f()
{
    Pod pod{};
    cout << pod << '\n';
    Struct2 struc2;
    Struct2 struc21{"Obj_a"};
}

//------------------------------------------------------------------------------

Tracer test_move()
{
    Tracer tr{"Obj_b"};
    return tr;
}

//------------------------------------------------------------------------------

void f1()
{
    Tracer mtr{"Obj_c"};
    mtr = test_move();

    Tracer mtr1{"Obj_d"};
    Tracer mctr{move(mtr1)};

    Tracer t{test_move()};
}

//------------------------------------------------------------------------------

void f2()
{
    Tracer* ptr{new Tracer{"Obj_e"}};


    Tracer loc{*ptr};
    delete ptr;


    Tracer loc1{"Obj_f"};
    loc1 = loc;

    //vector<Tracer> vtr(5);
}

//------------------------------------------------------------------------------

pair<Tracer, string> test_pair()
{
    pair<Tracer, string> p{Tracer{"Obj_g"}, ""};
    return p;
}

//------------------------------------------------------------------------------

void f3()
{
    pair<Tracer, string> p{test_pair()};
}

//------------------------------------------------------------------------------

int main()
try
{
    f1();
    f2();
    f3();
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
