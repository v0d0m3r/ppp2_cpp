//------------------------------------------------------------------------------

#include "List.hpp"

//------------------------------------------------------------------------------

/*
https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01055_source.html
https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a00588.html
https://habrahabr.ru/post/242639/
https://habrahabr.ru/post/226229/
*/

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.eof()) {         // Конец ввода
        is.clear();
        return;
    }
    if (is.fail()) {        // Некорректное состояние
        is.clear();
        char c;
        if (is >> c && c==term) return; // Является ли введеный символ
                                        // символом завершения ввода
        error("end_of_loop: ", message);
    }
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
    // Требует Element<E> и Container<C, Args>()
istream& operator>>(istream& is, C<E, Args...>& c)
{
    C<E, Args...> temp;
    for (Value_type<C<E, Args...>> var; is >> var;) temp.push_back(var);
    c = move(temp);
    return is;
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
    // Требует Element<E> и Container<C, Args>()
ostream& operator <<(ostream& os, const C<E, Args...>& c)
{
    for (const auto& e : c) os << e << ' ';
    return os;
}

//------------------------------------------------------------------------------

int main()
try
{    
    List<int> lst(5);
    cout << lst.front();

    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//----------------------------------------------------------------
