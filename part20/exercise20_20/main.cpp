//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

using namespace chrono;

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
    int ran{0};
    Iterator<C<E, Args...>> f;
    Iterator<C<E, Args...>> l;
    for (int i{0}; i < n; ++i) {
        f = c.begin();
        l = c.end();
        ran = randint(n);
        while (f!=l && ran > *f) // Проходим по последовательности
            ++f;                  // в поисках места вставки
        /*if (f==l) c.push_back(ran);  // Должно быть эффективнее для вектора
        else */     c.insert(f, ran);
    }
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
void do_experiment(C<E, Args...>& c, int n, const string& cont_name)
{
    auto begin{chrono::high_resolution_clock::now()};

    experiment(c, n);

    auto end{chrono::high_resolution_clock::now()};

    auto duration{chrono::duration_cast<chrono::milliseconds>(end - begin).count()};
    cout << "Выполнение эксперимента с " << cont_name.c_str()
         << " при N == " << n << " заняло " << duration
         << "мс\n";
}

//------------------------------------------------------------------------------

void prepare_for_experiment(int n)
{
    vector<int> v;
    string title1{"vector"};
    list<int> l;
    string title2{"list"};
    for (int i{n}; i < 1000000000; i+=100000) {
        do_experiment(v, i, title1);
        do_experiment(l, i, title2);
        v.clear();
        l.clear();
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    constexpr int start{100000};
    prepare_for_experiment(start);
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
