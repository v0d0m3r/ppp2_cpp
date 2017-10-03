//------------------------------------------------------------------------------

#include "../example20/Vector.hpp"

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

template<typename C>
    // Требует Container<C>()
istream& operator>>(istream& is, C& c)
{
    C temp;
    for (Value_type<C> var; is >> var;) temp.push_back(var);
    c = move(temp);
    return is;
}

//------------------------------------------------------------------------------

template<typename C>
    // Требует Container<C>()
void print(C& c)
{
    for (auto p : c) cout << p << ' ';
}

//------------------------------------------------------------------------------

void exercise20_5()
{
    vector<double> vd(1000000);
    cin >> vd;

    print(vd);
    cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_5();
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
