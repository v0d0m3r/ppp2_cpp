//------------------------------------------------------------------------------

#include "Order.hpp"

//------------------------------------------------------------------------------

template<typename In>
// Требует Input_iterator<In>()
void fill_to_file(In first, In last, const string& fname)
{
    ofstream ofs{fname};
    if (!ofs)
        error("exercise_21_9: ", "Невозможно открыть выходной файл");
    std::copy(first, last,
              ostream_iterator<Value_type<In>>{ofs, "\n"});
}

//------------------------------------------------------------------------------

template<typename In, typename In2, typename Pred>
// Требует Input_iterator<In>(), Input_iterator<In2>()
// и Predicate<Pred, Value_type<In>>
void fill_to_file(In first, In last, In2 first2, In2 last2,
                  Pred pred, const string& fname)
{
    ofstream ofs{fname};
    if (!ofs)
        error("exercise_21_9: ", "Невозможно открыть выходной файл");
    merge(first, last, first2, last2,
          ostream_iterator<Value_type<In>>{ofs, "\n"}, pred);
}

//------------------------------------------------------------------------------

void exercise_21_9()
{
    vector<Order> orders;
    const string fname{"./data1.txt"};
    fill_from_file(orders, Cmp_by_name{}, fname);
    fill_to_file(orders.begin(), orders.end(), fname);

    const string fname2{"./data2.txt"};
    list<Order> lst_orders;
    fill_from_file(lst_orders, Cmp_by_addr{}, fname2);
    fill_to_file(lst_orders.begin(), lst_orders.end(), fname2);

    const string fname3{"./dest.txt"};
    fill_to_file(orders.begin(), orders.end(),
                 lst_orders.begin(), lst_orders.end(),
                 Cmp_by_name{}, fname3);
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise_21_9();
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
