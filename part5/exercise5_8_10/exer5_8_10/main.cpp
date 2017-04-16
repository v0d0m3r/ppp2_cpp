//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

int main()
try {
    cout << "Введите колличество суммируемых значений\n";

    int count;
    cin >> count;
    if (count<1 || !cin)
        error("Некорректное колличество суммируемых значений");

    cout << "Введите несколько целых чисел "
            "(| для окончания ввода):\n";

    vector<double> v1;
    for (double digit; cin >> digit;) v1.push_back(digit);

    double sum = 0;
    string summand;
    int number = (count > int(v1.size())) ? v1.size() : count;
    for (int i=0; i < number; ++i) {
            sum += v1[i];
            summand += to_string(v1[i]) + " ";
    }
    cout << "Сумма первых " << number
         << " чисел (" << summand << "\b) равна "
         << sum << '\n';

    cout << "Вектор действительных чисел, содержащий "
         << number-1 << " разностей между соседними "
                        "величинами:\n";

    vector<double> v2;
    for (int i=1; i < number; ++i)
        v2.push_back(v1[i] - v1[i-1]);
    for (size_t i=0; i < v2.size(); ++i)
        cout << v2[i] << '\t';

    cout << '\n';
    if (count < int(v1.size()))
        error("Вы пытаетесь проссумировать больше чисел!");

    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open();
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    keep_window_open();
    return -2;
}

//-----------------------------------------------------------------------------
