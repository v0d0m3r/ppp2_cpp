//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename In_iter>
In_iter middle(In_iter first, In_iter last,
               std::input_iterator_tag)
{
    std::advance(first, std::distance(first, last)/2);
    return first;
}

//------------------------------------------------------------------------------

template<typename Ra_iter>
Ra_iter middle(Ra_iter first, Ra_iter last,
                std::random_access_iterator_tag)
{
    return first + (last-first)/2;
}

//------------------------------------------------------------------------------

template<typename Iter, typename T>
bool mbinary_search(Iter first, Iter last, const T& val)
{
    Iter p{last};
    while (first!=last) {
        p = middle(first, last,
                   typename iterator_traits<Iter>::iterator_category());
        if (*p == val) return true;
        if (first==p) return false; // Последний элемент
        if (*p < val) first = p;
        else          last = p;
    }
    return false;
}

//------------------------------------------------------------------------------

int main()
try
{
    vector<int> vi{1, 3, 123, 0, 2, 4};
    sort(vi.begin(), vi.end());
    bool is_find{mbinary_search(vi.begin(), vi.end(), 123)};
    if (is_find) cout << "Найдено!\n";
    else         cout << "Не найдено!\n";

    list<int> li{vi.begin(), vi.end()};
    is_find = mbinary_search(li.begin(), li.end(), -1);
    if (is_find) cout << "Найдено!\n";
    else         cout << "Не найдено!\n";


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
