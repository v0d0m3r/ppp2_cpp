//------------------------------------------------------------------------------

#include "Slist.hpp"

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

template<class E, template<class, class...> class C, class... Args>
void print_contaner(const C<E, Args...>& c)
{
    for (auto& e : c) cout << e << ' ';
}

//------------------------------------------------------------------------------

void test_constructors()
{
    Slist<int> lst1(5);
    cout << lst1.front() << '\n';

    Slist<int> lst2{4, 3};
    cout << lst2.front() << '\n';

    Slist<int> lst3 = lst1;
    cout << lst3.front() << '\n';

    Slist<int> lst4 = lst2;
    for (const auto& v : lst4)
        cout << v << '\n';

    Slist<int> lst5{Slist<int>{}};

    Slist<string> lst6{"Hello", "way"};
    Slist<string> lst7{"mana", "wana"};

    lst6 = lst7;
    auto i{lst7.begin()};
    *i = "fakel";
    for (const auto& v : lst6)
        cout << v.c_str() << '\n';

    for (const auto& v : lst7)
        cout << v.c_str() << '\n';

    Slist<int> l{0, 2};
    Slist<int> l2{move(l)};
    cout << "l2: " << l2 << '\n';
    Slist<int> l3{32, 32 ,12 , 32};
    l3 = l;
    l3 = lst5;    
}

//------------------------------------------------------------------------------

void test_erase()
{
    Slist<string> lst{"Hello", "may", "way"};
    auto p{lst.begin()};

    p = lst.erase(p);

    for (const auto& v : lst)
        cout << v.c_str() << '\n';
    if (p != lst.end())
        cout << "succ: " << (*p).c_str() << '\n';

    Slist<string> lst1{"Hello"};
    auto p1{lst1.begin()};

    p1 = lst1.erase(p1);

    for (const auto& v : lst1)
        cout << v.c_str() << '\n';
    if (p1 != lst1.end())
        cout << "succ: " << (*p1).c_str() << '\n';
}

//------------------------------------------------------------------------------

void test_push_back()
{
    Slist<string> lst;
    lst.push_back("str1");
    lst.push_back("str2");
    lst.push_back("str3");

    for (const auto& v : lst)
        cout << v.c_str() << '\n';
}

//------------------------------------------------------------------------------

void test_push_front()
{
    Slist<string> lst;
    lst.push_front("str1");
    lst.push_front("str2");
    lst.push_front("str3");

    for (const auto& v : lst)
        cout << v.c_str() << '\n';
}

//------------------------------------------------------------------------------

template<typename Iterator>  // Требует Input_iterator<Iterator>
Iterator high(Iterator first, Iterator last)
// Возвращает итератор, указывающий на максимальный
// элемент диапазона [first, last)
{
    Iterator high{first};
    for (Iterator p{first}; p != last; ++p)
        if (*high < *p) high = p;
    return high;
}

//------------------------------------------------------------------------------

void test_case1()
{
    Slist<int> lst;
    for (int x; cin >> x;) lst.push_front(x);
    Slist<int>::iterator p{high(lst.begin(), lst.end())};
    if (p != lst.end())
        cout << "Наибольшее значение равно: " << *p << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    test_constructors();
    test_erase();
    test_push_back();
    test_push_front();
    test_case1();
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
