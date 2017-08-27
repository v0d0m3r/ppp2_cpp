//------------------------------------------------------------------------------

#include <../exercise19_6/Number.hpp>
#include <../exercise19_1_2/src/Exercises.hpp>

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

template<typename T>
void input_digits(vector<Number<T>>& vi)
{
    constexpr char term{';'};
    cout << "Введите целые числа через пробел.\n"
            "Для завершения ввода введите " << term << '\n';

    istream& is{cin};
    is.exceptions(cin.exceptions()|ios_base::badbit);

    for (Number<T> v; cin >> v;) vi.push_back(v);

    end_of_loop(is, term, "Ошибка формата при вводе данных!");
}

//------------------------------------------------------------------------------

// Exercise 19_2
void test_fprod()
{
    vector<Number<int>> vi1;
    input_digits(vi1);

    vector<Number<double>> vi2;
    constexpr double delta{3.5};

    for (const auto& i : vi1)
        vi2.push_back((1.0) * i + delta);

    auto vrt{fprod(vi2, vi1)};
    cout << "vi1: " << vi1
         << "\nvi2: " << vi2
         << "\nvrt: " << vrt <<'\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    test_fprod();
    return 0;
}
catch(exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
