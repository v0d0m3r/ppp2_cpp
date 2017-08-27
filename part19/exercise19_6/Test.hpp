//------------------------------------------------------------------------------

#ifndef TEST_HPP
#define TEST_HPP

//------------------------------------------------------------------------------

#include "Number.hpp"

//------------------------------------------------------------------------------

template<typename T, typename N = Number<T>>
struct User_case
{
    N lvl;
    N rvl;
    N sum;
    N sub;
    N prod;
    N div;
};

//------------------------------------------------------------------------------

template<typename T>
istream& operator>>(istream& is, User_case<T>& u)
    // Предполагаемый формат:
    // ( lvl rvl : сумма разность произведение деление)
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    User_case<T> uc;

    if (is >> ch1 >> uc.lvl >> uc.rvl
           >> ch2 >> uc.sum >> uc.sub >> uc.prod >> uc.div
           >> ch3) {
        if (ch1!='(' || ch2!=':' || ch3!=')') {
            is.clear(ios_base::failbit);
            return is;
        }
    }
    else
        return is;
    u = uc;
    return is;
}

//------------------------------------------------------------------------------

template<typename T>
bool operator==(const User_case<T>& a, const User_case<T>& b)
{
    return     a.lvl  == b.lvl
            && a.rvl  == b.rvl
            && a.sum  == b.sum
            && a.sub  == b.sub
            && a.prod == b.prod
            && a.div  == b.div;
}

//------------------------------------------------------------------------------

template<typename T>
bool operator!=(const User_case<T>& a, const User_case<T>& b)
{
    return !(a == b);
}

//------------------------------------------------------------------------------

template<typename T>
void get_test_data(vector<User_case<T>>& vuc)
{
    string iname{"./test_data.txt"};
    ifstream ifs{iname};
    if (!ifs) error("Невозможно открыть файл ", iname);

    for (User_case<T> uc; ifs >> uc;) vuc.push_back(uc);
}

//------------------------------------------------------------------------------

inline void error_test(int i)
{
    error("do_test(): ошибка в " + to_string(i)
          + " наборе теста" );
}

//------------------------------------------------------------------------------

template<typename T>
void calculate(User_case<T>& calc, const Number<T>& lvl,
               const Number<T>& rvl)
{
    calc.lvl  = lvl;
    calc.rvl  = rvl;
    calc.sum  = lvl + rvl;
    calc.sub  = lvl - rvl;
    calc.prod = lvl * rvl;
    calc.div  = lvl / rvl;
}

//------------------------------------------------------------------------------

#endif // TEST_HPP

//------------------------------------------------------------------------------
