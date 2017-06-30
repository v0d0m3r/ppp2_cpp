//------------------------------------------------------------------------------

#include "Vector_easy.hpp"
#include "Link_first.hpp"

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
    int* pi{&x};

    double e{2.71828};
    double* pd{&e};

    cout << "pi==" << pi << "; содержимое pi==" << *pi << '\n';
    cout << "pd==" << pd << "; содержимое pd==" << *pd << '\n';



    char ch{'\n'};
    bool b{true};
    bool* pb = &b;

    vector<int> vi(1000);
    vector<int>* pvi{&vi};

    sizes(ch, x, pi, e, pd, b, pb, vi, pvi);
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
    Link_first* norse_gods{new Link_first{"Thor"}};
    norse_gods = insert(norse_gods, new Link_first{"Odin"});
    norse_gods = insert(norse_gods, new Link_first{"Zeus"});
    norse_gods = insert(norse_gods, new Link_first{"Freia"});

    Link_first* greek_gods{new Link_first{"Hera"}};
    greek_gods  = insert(greek_gods, new Link_first{"Athena"});
    greek_gods  = insert(greek_gods, new Link_first{"Mars"});
    greek_gods  = insert(greek_gods, new Link_first{"Poseidon"});

    Link_first* p = find(greek_gods, "Mars");
    if (p) p->value = "Ares";

    p = find(norse_gods, "Zeus");
    if (p) {
        if (p == norse_gods) norse_gods = p->succ;
        erase(p);
        greek_gods = insert(greek_gods, p);
    }

    print_all(norse_gods);
    cout << '\n';

    print_all(greek_gods);
    cout << '\n';
}

//------------------------------------------------------------------------------

void print_array10(ostream& os, int* a)
{
    if (a == nullptr) return;
    constexpr int sz{10};
    for (int i=0; i < sz; ++i)
        os << a[i] << " ";
}

//------------------------------------------------------------------------------

void print_array11(ostream& os, int* a)
{
    if (a == nullptr) return;
    constexpr int sz{11};

    for (int i=0; i < sz; ++i)
        os << a[i] << " ";
}

//------------------------------------------------------------------------------

void print_array(ostream& os, int* a, int n)
{
    if (n < 0) error("print_array: bad n");
    if (a == nullptr) error("print_array: invalid pointer");
    for (int i=0; i < n; ++i)
        os << a[i] << " ";
}

//------------------------------------------------------------------------------

void init_array10(int* a, int base)
{
    if (a == nullptr) return;

    constexpr int sz{10};
    for (int i=0; i < sz; ++i)
        a[i] = base + i;
}

//------------------------------------------------------------------------------

void init_array11(int* a, int base)
{
    if (a == nullptr) return;

    constexpr int sz{11};
    for (int i=0; i < sz; ++i)
        a[i] = base + i;
}

//------------------------------------------------------------------------------

void init_array(int* a, int n, int base)
{
    if (a == nullptr) error("init_array: invalid pointer");
    if (n < 0)        error("init_array: bad n");

    for (int i=0; i < n; ++i)
        a[i] = base + i;
}

//------------------------------------------------------------------------------

void print_vector(ostream& os, const vector<int>& vr)
{
    for (const auto& i : vr)
        os << i << " ";
}

//------------------------------------------------------------------------------

void init_vector(vector<int>& vr, int base)
{
    for (size_t i=0; i < vr.size(); ++i)
        vr[i] = base + i;
}

//------------------------------------------------------------------------------

void tasks_part1()
{
    int sz{10};
    constexpr int base{100};

    int* array10{new int[sz]};

    init_array10(array10, base);

    print_array10(cout, array10);
    cout << '\n';

    sz = 11;

    int* array11{new int[sz]};

    init_array11(array11, base);

    print_array11(cout, array11);
    cout << '\n';

    sz = 20;

    int* array20{new int[sz]};

    init_array(array20, sz, base);

    print_array(cout, array20, sz);
    cout << '\n';

    delete[] array10;
    delete[] array11;
    delete[] array20;

    vector<int> vr10(10);
    init_vector(vr10, base);
    print_vector(cout, vr10);
    cout << '\n';

    vector<int> vr11(11);
    init_vector(vr11, base);
    print_vector(cout, vr11);
    cout << '\n';

    vector<int> vr20(20);
    init_vector(vr20, base);
    print_vector(cout, vr20);
    cout << '\n';
}

//------------------------------------------------------------------------------

void copy_array(int* src, int* dest, int n)
{
    if (src==nullptr || dest==nullptr)
        error("copy_array: invalid pointer");

    for (int i=0; i < n; ++i) dest[i] = src[i];
}

//------------------------------------------------------------------------------

void copy_vector(const vector<int>& src, vector<int>& dest)
{
    if (src.size() != dest.size())
        error("copy_vector: bad vectors");

    for (size_t i=0; i < src.size(); ++i)
        dest[i] = src[i];
}

//------------------------------------------------------------------------------

void tasks_part2()
{
    int* p1{new int(7)};
    cout << "p1 == " << p1
         << ", *p1 == " << *p1 << '\n';

    int* p2 = new int[*p1] {1, 2, 4, 8, 16, 32, 64};
    cout << "p2 == " << p2 << '\n';
    print_array(cout, p2, *p1);
    cout << '\n';

    int* p3{p2};
    p2 = p1;
    p2 = p3;

    cout << "p1 == " << p1 << ", *p1 == " << *p1 << '\n';
    cout << "p2 == " << p2 << ", *p2 == " << *p2 << '\n';

    delete p1;
    delete[] p2;

    constexpr int sz = 10;
    p1 = new int[sz] {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    p2 = new int[sz] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    print_array(cout, p2, sz);
    cout << '\n';

    copy_array(p1, p2, sz);
    print_array(cout, p2, sz);
    cout << '\n';

    delete[] p1;
    delete[] p2;

    vector<int> vr1 = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    vector<int> vr2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    copy_vector(vr1, vr2);
    print_vector(cout, vr2);
    cout << '\n';
}

//------------------------------------------------------------------------------
// Exercise 8
void read_string()
{
    string str;
    for (char ch; cin>>ch && ch!='!';) str.push_back(ch);
    for (auto ch : str) cout << ch << '\n';
}

//------------------------------------------------------------------------------
// Exercise 9
void exercise9()
{
    int i{0};
    int* pi{&i};

    int i2{0};
    int* pi2{&i2};

    (pi2 > pi) ? cout << "Стэк растет вверх!\n":
                 cout << "Стэк растет вниз!\n";

    int* pi3{new int(0)};
    int* pi4{new int(0)};
    (pi4 > pi3) ? cout << "Адресация в куче растет вверх!\n":
                  cout << "Адресация в куче растет вниз!\n";

    delete pi3;
    delete pi4;
}

//------------------------------------------------------------------------------

int main()
try
{
    // usage_tolower();
    // usage_mstrdup();
    // usage_findx();
    // read_char_array();
    exercise9();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------
