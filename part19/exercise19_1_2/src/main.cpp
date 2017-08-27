//------------------------------------------------------------------------------

#include "Exercises.hpp"

//------------------------------------------------------------------------------

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.fail()) {
        is.clear();
        char ch;
        if (is >> ch && ch==term) return;
        error("end_of_loop: " + message);
    }
}

//------------------------------------------------------------------------------

void input_digits(vector<int>& vi)
{
    constexpr char term{';'};
    cout << "Введите целые числа через пробел.\n"
            "Для завершения ввода введите " << term << '\n';

    istream& is{cin};
    is.exceptions(cin.exceptions()|ios_base::badbit);

    for (int i; cin >> i;) vi.push_back(i);

    end_of_loop(is, term, "Ошибка формата при вводе данных!");
}

//------------------------------------------------------------------------------
// Exercise 19_1
void main_test_f()
{
    vector<int> vi1;
    input_digits(vi1);

    vector<int> vi2;
    constexpr int delta{3};

    for (const auto& i : vi1)
        vi2.push_back(i + delta);

    test_f(vi1, vi2);    // Тестируем функцию
    f(vi1, vi2);
    cout << "vi1: " << vi1
         << "\nvi2: " << vi2 <<'\n';
}

//------------------------------------------------------------------------------
// Exercise 19_2
void test_fprod()
{
    vector<int> vi1;
    input_digits(vi1);

    vector<double> vi2;
    constexpr double delta{3.5};

    for (const auto& i : vi1)
        vi2.push_back(1.0 * i + delta);

    auto vrt{fprod(vi2, vi1)};
    cout << "vi1: " << vi1
         << "\nvi2: " << vi2
         << "\nvrt: " << vrt <<'\n';
}

//------------------------------------------------------------------------------

int main()
try
{    
    main_test_f();
    test_fprod();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
