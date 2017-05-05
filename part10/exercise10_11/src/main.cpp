//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------
// Маркер определяет конец ввода
const string end_of_loop = "Ввода нет";

//------------------------------------------------------------------------------
// Пропускает все НЕцифры
void skip_to_int(istream& ist)
{
    if (ist.fail()) { // Ввели не целое число
        ist.clear();
        for (char ch; ist >> ch;) {
            if (isdigit(ch) || ch == '-') {
                ist.unget();
                return;
            }
        }
    }
    error(end_of_loop); // Ввода нет
}

//------------------------------------------------------------------------------
// Получение числа из потока ввода
int get_int(istream& ist)
{
    int n = 0;
    while (true) {
        if (ist >> n) return n;
        skip_to_int(ist);
    }
}

//------------------------------------------------------------------------------
// sum_reading() расчитывает
// сумму считанных целых чисел
int sum_reading(const vector<int>& digit_tb)
{
    int sum = 0;
    for (const int& i : digit_tb)
        sum += i;
    return sum;
}

//------------------------------------------------------------------------------
// Цикл ввода данных из файла
void fill_from_file()
{
    vector<int> digit_tb;
    try
    {
        const string path = "./";
        cout << "Введите имя файла для ввода: \n";
        string iname;
        cin >> iname;
        if (!cin) error("sum_from_file(): "
                        "Неправильное имя файла");
        ifstream ifs{path + iname};
        if (!ifs) error("sum_from_file(): "
                        "Невозможно открыть входной файл");
        ifs.exceptions(ifs.exceptions()|ios_base::badbit);
        int n = 0;
        while (true) {
            n = get_int(ifs);
            digit_tb.push_back(n);  // Заполняем таблицу чисел
        }
    }
    catch (exception& e) {
        if (e.what() != end_of_loop) {           
            cout << "ошибка: " << e.what() << '\n';
            return;
        }
        // Если мы здесь, значит конец
        // ввода и выводим сумму чисел
        cout << "Сумма чисел из файла = "
             << sum_reading(digit_tb) << '\n';
    }
    catch(...) {
        cout << "Неизвестная ошибка!\n";
    }
}

//------------------------------------------------------------------------------

int main()
{
    fill_from_file();
    keep_window_open("~~");
    return 0;
}
