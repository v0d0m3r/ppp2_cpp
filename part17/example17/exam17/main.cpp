//------------------------------------------------------------------------------

#include "Vector_easy.hpp"
#include "Link.hpp"

//------------------------------------------------------------------------------

struct A {
    A()  { cout << "constructor A\n"; }
    virtual ~A() { cout << "destructor A\n"; }
};

//------------------------------------------------------------------------------

struct B : A {
    B()  { cout << "constructor B\n"; }
    ~B() { cout << "destructor B\n"; }
};

//------------------------------------------------------------------------------

struct D {
    A a;
    B b;

    D()  { cout << "constructor D\n"; }
    ~D() { cout << "destructor D\n"; }
};

//------------------------------------------------------------------------------

void sizes(char ch, int i, int* pi, double d, double* pd,
           bool b, bool* pb, vector<int> vi, vector<int>* pvi)
{
    cout << "размер типа char равен " << sizeof(char) << ' '
         << sizeof(ch) << '\n';
    cout << "размер типа int равен " << sizeof(int) << ' '
         << sizeof(i) << '\n';
    cout << "размер типа int* равен " << sizeof(int*) << ' '
         << sizeof(pi) << '\n';

    cout << "размер типа bool равен " << sizeof(bool) << ' '
         << sizeof(b) << '\n';
    cout << "размер типа bool* равен " << sizeof(bool*) << ' '
         << sizeof(pb) << '\n';

    cout << "размер типа double равен " << sizeof(double) << ' '
         << sizeof(d) << '\n';
    cout << "размер типа double* равен " << sizeof(double*) << ' '
         << sizeof(pd) << '\n';

    cout << "размер типа vector<int> равен " << sizeof(vector<int>) << ' '
         << sizeof(vi) << '\n';
    cout << "размер типа vector<int>* равен " << sizeof(vector<int>*) << ' '
         << sizeof(pvi) << '\n';
}

//------------------------------------------------------------------------------

void example17_3()
{
    int x{17};
    const int* pi{&x};

    double e{2.71828};
    double* pd{&e};

    cout << "pi==" << pi << "; содержимое pi==" << *pi << '\n';
    cout << "pd==" << pd << "; содержимое pd==" << *pd << '\n';

    int& rpi = *pi;

    char ch{'\n'};
    bool b{true};
    bool* pb = &b;

    vector<int> vi(1000);
    vector<int>* pvi{&vi};

    //sizes(ch, x, pi, e, pd, b, pb, vi, pvi);
}

//------------------------------------------------------------------------------

void example17_5()
{
    D d;
    A* a = new B;
    delete a;
}

//------------------------------------------------------------------------------

void example17_9()
{

}

//------------------------------------------------------------------------------

int main()
{

    //example17_3();
    example17_9();
    return  0;
}

//------------------------------------------------------------------------------
