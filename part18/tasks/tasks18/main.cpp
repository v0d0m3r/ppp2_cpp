//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

int ga[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

//------------------------------------------------------------------------------

void f(int ai[], int n)
{
    constexpr int sz = 10;
    int la[sz];
    copy(ga, ga+sz, la);
    for (int i=0; i < sz; ++i)
        cout << "la[i]: " << la[i] << '\n';

    int* p = new int[n];
    copy(ai, ai+n, p);
    for (int i=0; i < n; ++i)
        cout << "p[i]: " << p[i] << '\n';
    delete[] p;
}

//------------------------------------------------------------------------------

double fact(int n)
{
    double res{1.0};
    if (n <= res) return res;

    while (n != 1) {
        res *= n;
        --n;
    }
    return res;
}

//------------------------------------------------------------------------------

void task_array()
{
    constexpr int n = 10;
    f(ga, n);
    int aa[n];
    for (int i=0; i < n; ++i) aa[i] = fact(i);
    f(aa, n);
}

//------------------------------------------------------------------------------

vector<int> gv{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

//------------------------------------------------------------------------------

void f(vector<int> vi)
{
    vector<int> lv(vi.size());
    lv = gv;
    for (auto i : lv) cout << "lv[i]: " << i << '\n';
    vector<int> lv2{vi};
    for (auto i : lv2) cout << "lv2[i]: " << i << '\n';
}

//------------------------------------------------------------------------------

void task_vector()
{
    constexpr int n = 10;
    f(gv);
    vector<int> vv;
    for (int i=0; i < n; ++i) vv.push_back(fact(i));
    f(vv);
}

//------------------------------------------------------------------------------

int main()
try
{
    //task_array();
    task_vector();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
}

//------------------------------------------------------------------------------
