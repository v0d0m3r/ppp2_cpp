//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename In, typename T>
// Требует Input_iterator<In>()
// и Equality_comparable<Value_type<T>>()
Iterator_difference_type<In> mcount(In first, In last, const T& val)
// Количество вхождений val в диапазон [first, last)
{
    Iterator_difference_type<In> cnt{0};
    while (first != last) {
        if (*first == val) ++cnt;
        ++first;
    }
    return cnt;
}

//------------------------------------------------------------------------------

template<typename In, typename Pred>
// Требует Input_iterator<In>()
// и Predicate<Pred, Value_type<In>>
Iterator_difference_type<In> mcount_if(In first, In last, Pred pred)
// Количество элементов удовлетворяющих предикату
{
    Iterator_difference_type<In> cnt{0};
    while (first != last) {
        if (pred(*first)) ++cnt;
        ++first;
    }
    return cnt;
}

//------------------------------------------------------------------------------

void exercise_21_3_4()
{
    vector<int> vi{0, 2, 3, 3, 4, 5, 3, 6, 3};
    cout << mcount(vi.begin(), vi.end(), 3) << '\n';

    list<int> li{vi.begin(), vi.end()};
    cout << mcount(li.begin(), li.end(), -1) << '\n';

    cout << mcount_if(li.begin(), li.end(),
                      [] (int a) { return a > 3; })
         << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise_21_3_4();
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
