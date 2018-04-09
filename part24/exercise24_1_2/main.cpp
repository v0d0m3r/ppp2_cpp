//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include "../../bstroustrup_code/MatrixIO11.h"
#include <functional>
#include <complex>
using namespace Numeric_lib;

//------------------------------------------------------------------------------

/* Нельзя писать функции в стиле функции triple_m для использования в функциях
 * apply(), так как при передачи аргумента по ссылке можем изменить,
 * текущую матрицу, когда не хотели этого. В данной версии apply() копирует
 * аргумент по значению, следовательно мы не изменим исходную матрицу. Но
 * если мы захотим, можем изменить на передачу по ссылке, тогда мы будем
 * изменять исходную матрицу.*/
template<class T> T triple_m(T& t) { t *= 3; return t; }
template<class T> T triple(const T& t) { return t*3; }
template<class T> void triple_change(T& i) { i *= 3; }

//------------------------------------------------------------------------------

void exercise24_1()
{
    Matrix<int> m(5);
    for (Index i=0; i < m.size(); ++i) m(i) = i;
    cout << "start m:\t"  << m << '\n';

    m.apply(triple_change<int>);
    cout << "m.apply:\nafter triple:\t" << m << '\n';

    m.apply(triple_m<int>);
    cout << "after triple_m:\t" << m << '\n';

    auto b = Numeric_lib::apply(triple<int>, m);
    cout << "after apply()\n"
            "after triple_change:\nb:\t\t"
         << b << '\n'
         << "m:\t\t" << m << '\n';

    auto c = Numeric_lib::apply(triple_m<int>, m);
    cout << "after apply()\n"
            "after triple_m:\nc:\t\t" << c << '\n'
         << "m:\t\t" << m << '\n';
}

//------------------------------------------------------------------------------

template<class T> struct Triple_change {
    void operator()(T& c) { c *= 3; }
};

//------------------------------------------------------------------------------

template<class T> struct Triple {
    T operator()(const T& c) { return c * 3; }
};

//------------------------------------------------------------------------------

template<class T> struct Triple_m {
    T operator()(T& c) { c *= 3; return c * 3; }
};

//------------------------------------------------------------------------------

void exercise24_2()
{
    Matrix<int> m(5);
    for (Index i=0; i < m.size(); ++i) m(i) = i;
    cout << "start m:\t"  << m << '\n';

    m.apply(Triple_change<int>{});
    cout << "m.apply:\nafter triple:\t" << m << '\n';

    m.apply(Triple_m<int>{});
    cout << "after triple_m:\t" << m << '\n';

    auto b = Numeric_lib::apply(Triple<int>{}, m);
    cout << "after apply()\n"
            "after triple_change:\nb:\t\t"
         << b << '\n'
         << "m:\t\t" << m << '\n';

    auto c = Numeric_lib::apply(Triple_m<int>{}, m);
    cout << "after apply()\n"
            "after triple_m:\nc:\t\t" << c << '\n'
         << "m:\t\t" << m << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise24_2();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (const Matrix_error& e) {
    cout << "\nerror: " << e.name << '\n';
    return -2;
}
catch (...) {
    cerr << "\noops!\n";
    return -3;
}

//------------------------------------------------------------------------------
