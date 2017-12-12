//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
    // Требует Element<E> и Container<C, Args>()
ostream& operator <<(ostream& os, const C<E, Args...>& c)
{
    for (const auto& e : c)
        os << e << ' ';
    return os;
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
    // Требует Element<E> и Container<C, Args>()
void experiment(C<E, Args...>& c, int n)
{
    int ran{randint(n)};
    auto f{c.begin()};
    auto l{c.end()};

    c.insert(f, ran);

    for (int i{1}; i < n; ++i) {
        f = c.begin();
        l = c.end();
        ran = randint(n);
        while (f!=l && ran > *f) ++f;
        c.insert(f, ran);
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    vector<int> v;
    experiment(v, 3);
    cout << v << '\n';

    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
