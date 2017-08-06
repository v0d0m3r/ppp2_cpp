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

void suspicious(vector<int>& v, int s)
{
    int* p{new int[s]};
    try {
        vector<vector<int>> v1;
        p[s-1] = v.at(s-1);

        // ....
    }
    catch (...) {
        delete[] p;
        throw;
    }
    try {
        int* q{new int[s]};
        try {
            vector<int> v2;
            q[s-1] = v2.at(s-1);

            // ....
        }
        catch (...) {
            delete[] q;
            throw;
        }
    }
    catch (...) {
        delete[] p;
        throw;
    }
    delete[] p;
    delete[] q;
}

//------------------------------------------------------------------------------

void example19_3_6()
{
    array<char, 1024> buf;
    array<double, 10> b2;

    fill(buf, 'x');
    fill(b2, 0.0);
}

//------------------------------------------------------------------------------

int main()
try
{
    vector<int> v;
    suspicious(v, 3);
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
