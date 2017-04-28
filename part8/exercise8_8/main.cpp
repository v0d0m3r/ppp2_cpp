//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

int print_sum(const vector<int>& price, const vector<int>& weight)
{
    if (price != weight)
        error("print_sum: ", "Не совпадает размер у векторов!");

    int sum = 0;
    int multiplication = 0;
    for (size_t i=0; i < price.size(); ++i) {
        multiplication = price[i] * weight[i];
        sum += multiplication;
    }
    return sum;
}

//------------------------------------------------------------------------------

void init(vector<int>& integer)
{
    for (size_t i=0; i<integer.size(); ++i)  integer[i]=i;
}

//------------------------------------------------------------------------------

int main()
try {
    vector<int> price(10);
    vector<int> weight(10);
    init(price);
    init(weight);

    cout << "Сумма произведений = "
         << print_sum(price, weight) << '\n';

    keep_window_open("~~");
    return 0;

}
catch (exception& e) {
    cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "Упс: неизвестное исключение!\n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------

