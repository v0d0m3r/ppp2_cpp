//------------------------------------------------------------------------------

#include "Vector_easy.hpp"

//------------------------------------------------------------------------------

void example19_1()
{
    vector<double>* p{new vector<double>(10)};
    size_t n{0};
    for (double d; cin >> d; ) {
        if (n == p->size()) {
            vector<double>* q{new vector<double>(p->size()*2)};
            copy(p->begin(), p->end(), q->begin());
            delete p;
            p = q;
        }
        (*p)[n] = d;
        ++n;
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    Vector_easy vr(10);
    vr.resize(-77);
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
