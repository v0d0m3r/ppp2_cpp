//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return {p.second, p.first};
}

//------------------------------------------------------------------------------

template<typename A, typename B,
         template<class,class,class...> class M, class... Args>
multimap<B,A> flip_map(const M<A,B,Args...>& src)
// Приводит ассоциативный контейнер пар A,B к парам B,A
{
    multimap<B,A> dst;
    transform(src.begin(), src.end(),     // Входная последовательность
              inserter(dst, dst.begin()), // Итератор вставки
                                          // выходного контейнера
              flip_pair<A,B>);            // Переворот пар
    return dst;
}

//------------------------------------------------------------------------------

void exercise_21_8()
{
    map<string, int> words; // Поддержка пар (слово, частота)
    for (string s; cin >> s; )
        ++words[s];
    multimap<int, string> dst{flip_map(words)};
    for (const auto& p : dst)
        cout << p.first << ": " << p.second << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise_21_8();
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
