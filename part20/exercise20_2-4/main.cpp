//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

double* high_20_2(double* first, double* last)
{
    double h{-1};
    double* high;

    for (double* p{first}; p != last; ++p)
        if (h < *p) {
            high = p;
            h = *p;
        }
    return high;
}

//------------------------------------------------------------------------------

double* get_from_jack(int* pcount)
{
    if (pcount == nullptr) return nullptr;

    const string fname{"./jack_data"};
    ifstream ist {fname};
    if (!ist) error("невозможно открыть файл: ", fname);

    int n{0};
    int sz{10};
    int new_sz{0};
    double* p{new double[sz]{0}};
    double* q{nullptr};
    try {
        for (double d; ist >> d; ) {
            if (n == sz) {
                new_sz = sz * 2;
                q = new double[new_sz];
                copy(p, p + sz, q);
                delete[] p;
                p = q;
                q = nullptr;
                sz = new_sz;
            }
            p[n] = d;
            ++n;
        }
        if (pcount) *pcount = n;
        return p;
    }
    catch (...) {
        delete[] p;
        delete[] q;
        throw;
    }
}

//------------------------------------------------------------------------------

vector<double>* get_from_jill()
{
    unique_ptr<vector<double>> pvd{new vector<double>};

    const string fname{"./jill_data"};
    ifstream ist {fname};    // Поток для чтения из файла
    if (!ist) error("невозможно открыть файл: ", fname);

    for (double d; ist >> d; ) if (pvd) pvd->push_back(d);
    return pvd.release();
}

//------------------------------------------------------------------------------

void exercise20_2()
{
    int jack_count{0};
    double* jack_data{get_from_jack(&jack_count)};
    vector<double>* jill_data{get_from_jill()};

    double h{-1};
    double* jack_high{nullptr}; // Указатель на наибольший элемент
    double* jill_high{nullptr};

    for (int i{0}; i < jack_count; ++i)
        if (h < jack_data[i]) {
            jack_high = &jack_data[i];      // Адрес наибольшего элемента
            h = jack_data[i];               // Новый наибольший элемент
        }

    h = -1;

    for (size_t i{0}; i < jill_data->size(); ++i)
        if (h < (*jill_data)[i]) {
            jill_high = &(*jill_data)[i];   // Адрес наибольшего элемента
            h = (*jill_data)[i];
        }

    cout << "Максимум Джилл: " << *jill_high
         << "; Максимум Джека: " << *jack_high << '\n';

    delete[] jack_data;
    delete jill_data;
}

//------------------------------------------------------------------------------

template<typename Iter>
// Требует Bidirectional_iterator<Iter>
bool is_palindrome(Iter first, Iter last)
{
    auto p{last};
    --p;
    while (first!=last && first!=p) { // Мы ещё не достигли
                                      // середины слова
        if (*first != *p) return false;
        ++first;                      // Переход вперед
        --last;                       // Переход назад
        --p;
    }
    return true;
}

//------------------------------------------------------------------------------

istream& read_word(istream& is, char* buffer, int max)
{
    is.width(max);  // При выполнении следующего оператора >>
                    // будет считано не более max-1 символов
    is >> buffer;   // Читаем слово, завершающееся пробельным
                    // символом, добавляем в конец нулевой символ
    return is;
}

//------------------------------------------------------------------------------

void example18_7_1()
{
    for (string s; cin >> s; ) {
        cout << s << " is";
        if (!is_palindrome(s.begin(), s.end())) cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

void example18_7_2()
{
    constexpr int max = 128;
    for (char s[max]; read_word(cin, s, max); ) {
        cout << s << " is";
        if (!is_palindrome(s, s + strlen(s))) cout << " not";
        cout << " a palindrome\n";
    }
}

//------------------------------------------------------------------------------

void exercise20_3()
{
    //example18_7_1();
    example18_7_2();
}

//------------------------------------------------------------------------------

// Возвращает итератор, указывающий на максимальный
// элемент диапазона [first, last)
template<typename Iter>
// Требует Input_iterator<Iter>
Iter high_20_4(Iter first, Iter last)
{
    Iter high{first};
    for (Iter p{first}; p != last; ++p)
        if (*high < *p) high = p;
    return high;
}

//------------------------------------------------------------------------------

void exercise20_4()
{
    int jack_count{0};
    unique_ptr<double[]> jack_data{get_from_jack(&jack_count)};
    if (!jack_data) error("bad jack data!");

    // Указатель на наибольший элемент
    auto jack_high{high_20_4(jack_data.get(),
                             jack_data.get()+jack_count)};
    if (jack_high != jack_data.get()+jack_count)
        cout << "Максимум Джека: " << *jack_high;

    unique_ptr<vector<double>> jill_data{get_from_jill()};
    if (!jill_data) error("bad jill data!");

    auto jill_high{high_20_4(jill_data->begin(), jill_data->end())};
    if (jill_high != jill_data->end())
        cout << "; Максимум Джилл: " << *jill_high << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    //exercise20_2();
    //exercise20_3();
    exercise20_4();
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
