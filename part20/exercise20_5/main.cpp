//------------------------------------------------------------------------------

#include "../example20/Vector.hpp"

//------------------------------------------------------------------------------

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

void exercise20_5()
{
    vector<double> vd(1000000);
    cin >> vd;

    cout << '\n' << vd << '\n';

}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_5();
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

//------------------------------------------------------------------------------
