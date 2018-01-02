//------------------------------------------------------------------------------

#include "../exercise21_9/Order.hpp"

//------------------------------------------------------------------------------

double sum_order(double v, const Order& o)
{    
    // Вычисляет сумму всего заказа
    for (int i{0}; i < o.number_of_purchases(); ++i)
        v += o.purchase(i).unit_price * o.purchase(i).count;
    return v;  // Накапливает итог
}

//------------------------------------------------------------------------------

double sum_order_alternative(double v, const Order& ord)
{
    // Вычисляет сумму всего заказа
    for (const auto& p : ord)
        v += p.unit_price * p.count;
    return v;  // Накапливает итог
}

//------------------------------------------------------------------------------

double get_sum_from_file(const string& fname)
{
    ifstream ifs{fname};
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    if (!ifs)
        error("exercise_21_10: ", "Невозможно открыть входной файл");

    vector<Order> orders{istream_iterator<Order>{ifs},
                         istream_iterator<Order>{},
                         std::allocator<Order>{}};

    return std::accumulate(orders.begin(), orders.end(),
                           0.0, sum_order_alternative);
}

//------------------------------------------------------------------------------

void exercise_21_10()
{
    cout << get_sum_from_file("../../exercise21_9/bin/data1.txt")
          + get_sum_from_file("../../exercise21_9/bin/data2.txt")
         << '\n';

}

//------------------------------------------------------------------------------

int main()
try
{
    exercise_21_10();
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
