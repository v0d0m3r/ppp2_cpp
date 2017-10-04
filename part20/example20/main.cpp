//------------------------------------------------------------------------------

#include "Vector.hpp"
#include "Document.hpp"

//------------------------------------------------------------------------------

double* get_from_jack(int* count){}  // Джек записывает числа
                                    // типа double в массив,
                                    // возвращая их количество
                                    // в *count

//------------------------------------------------------------------------------

vector<double>* get_from_jill(){}    // Джилл заполняет вектор

//------------------------------------------------------------------------------

void fct()
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
         << "; Максимум Джека: " << *jack_high;

    delete[] jack_data;
    delete jill_data;
}

//------------------------------------------------------------------------------

vector<double> get_from_jill1()
{

}

//------------------------------------------------------------------------------

void fct1()
{

    vector<double> jill_data{get_from_jill1()};

    double h{-1};

    double* jill_high{nullptr};

    for (size_t i{0}; i < jill_data.size(); ++i)
        if (h < jill_data[i]) {
            jill_high = &jill_data[i];   // Адрес наибольшего элемента
            h = jill_data[i];
        }

    cout << "Максимум Джилл: " << *jill_high;
}

//------------------------------------------------------------------------------

double* high(double* first, double* last)
{
    if (first==nullptr || last==nullptr) return nullptr;   
    double h{-1};
    double* high{nullptr};

    for (double* p{first}; p != last; ++p)
        if (h < *p) {
            high = p;
            h = *p;
        }
    return high;
}

//------------------------------------------------------------------------------

void fct3()
{
    int jack_count{0};
    double* jack_data{get_from_jack(&jack_count)};
    vector<double>* jill_data{get_from_jill()};

    // Указатель на наибольший элемент
    double* jack_high{high(jack_data, jack_data+jack_count)};
    vector<double>& v{*jill_data};
    double* jill_high{high(&v[0], &v[0]+v.size())};

    if (jill_high && jack_high)
        cout << "Максимум Джилл: " << *jill_high
             << "; Максимум Джека: " << *jack_high;

    delete[] jack_data;
    delete jill_data;
}

//------------------------------------------------------------------------------

void copy(int* f1, int* e1, int* f2)
{
    if (f1==nullptr || e1==nullptr || f2==nullptr)
        throw invalid_argument{"bad copy!"};

    while (f1 != e1) {
        *f2 = *f1;
        ++f1;
        ++f2;
    }
}

//------------------------------------------------------------------------------

void test_copy()
{
    constexpr size_t sz{7};
    int* f1{new int[sz]};
    int* e1{&f1[sz]};
    for (size_t i{0}; i < sz; ++i) f1[i] = i;

    int* f2{new int[e1-f1]};
    copy(f1, e1, f2);
    for (size_t i{0}; i < sz; ++i) cout << f2[i] << '\n';

    delete[] f1;
    delete[] f2;
}

//------------------------------------------------------------------------------

template<typename Iter>
// Требует Bidirectional_iterator<Iter>
Iter get_right_elem(Iter first, Iter last, size_t counter)
// Возвращает Iterator, указывающий на counter-ый
// элемент с конца
{
    auto p{last};
    while (counter && first!=p) {
        --p;
        --counter;
    }
    if (counter) return last;
    return p;
}

//------------------------------------------------------------------------------

template<typename Iterator>  // Требует Input_iterator<Iterator>
Iterator high(Iterator first, Iterator last)
// Возвращает итератор, указывающий на максимальный
// элемент диапазона [first, last)
{ 
    Iterator high{first};
    for (Iterator p{first}; p != last; ++p)
        if (*high < *p) high = p;
    return high;
}

//------------------------------------------------------------------------------

void fct_20_3_1()
{
    int jack_count{0};
    unique_ptr<double> jack_data{get_from_jack(&jack_count)};
    unique_ptr<vector<double>> jill_data{get_from_jill()};

    // Указатель на наибольший элемент
    double* jack_high{high(jack_data.get(), jack_data.get()+jack_count)};
    vector<double>& v{*jill_data};
    double* jill_high{high(&v[0], &v[0]+v.size())};

    if (jill_high && jack_high)
        cout << "Максимум Джилл: " << *jill_high
             << "; Максимум Джека: " << *jack_high;
}

//------------------------------------------------------------------------------

void fct_20_4_2()
{
    list<int> lst;
    for (int x; cin >> x;) lst.push_front(x);

    list<int>::iterator p = high(lst.begin(), lst.end());
    if (p == lst.end()) // Мы достигли конца последовательности?
        cout << "Список пуст\n";
    else
        cout << "Наибольшее значение равно " << *p << '\n';
}

//------------------------------------------------------------------------------

void func_help_20_7(char* ac, size_t ac_sz, const vector<char>& vc,
                    const list<char>& lc, const string& str)
{
    if (ac == nullptr) return;

    const char* hello{"Hello"};
    const char* howdy{"Howdy"};

    cout << "ac size is: " << ac_sz << '\n';
    bool is_equal{true};
    for (size_t i{0}; i < ac_sz; ++i)
        if (ac[i] != hello[i] || i >= strlen(hello)) {
            is_equal = false;
            break;
        }
    cout << "ac";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << "hello\n";

    is_equal = true;
    for (size_t i{0}; i < ac_sz; ++i)
        if (ac[i] != howdy[i]) {
            is_equal = false;
            break;
        }
    cout << "ac";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << "howdy\n";

    char ac_copy[ac_sz];
    for (size_t i{0}; i < ac_sz; ++i)
        ac_copy[i] = ac[i];

    cout << "vc size is: " << vc.size() << '\n';
    is_equal = true;
    for (size_t i{0}; i < vc.size(); ++i)
        if (vc[i] != hello[i] || i >= strlen(hello)) {
            is_equal = false;
            break;
        }

    cout << "vc";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << "hello\n";

    is_equal = true;
    for (size_t i{0}; i < vc.size(); ++i)
        if (vc[i] != howdy[i] || i >= strlen(howdy)) {
            is_equal = false;
            break;
        }
    cout << "vc";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << "howdy\n";
    vector<char> vc_copy{vc};

    cout << "lc size is: " << lc.size() << '\n';
    is_equal = true;
    auto p{lc.begin()};
    for (size_t i{0}; i < strlen(hello); ++i) {
        if (p==lc.end() || *p != hello[i]) {
            is_equal = false;
            break;
        }
        ++p;
    }

    cout << "lc";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << hello << '\n';

    is_equal = true;
    for (size_t i{0}; i < strlen(hello); ++i) {
        if (p==lc.end() || *p != howdy[i]) {
            is_equal = false;
            break;
        }
        ++p;
    }

    cout << "lc";
    if (is_equal) cout << " == ";
    else          cout << " != ";
    cout << howdy << '\n';
    list<char> lc_copy{lc};

    cout << "str size is: " << str.size() << '\n';
    cout << "str";
    if (str == hello) cout << " == ";
    else              cout << " != ";
    cout << hello << '\n';
    string str_copy{str};
}

//------------------------------------------------------------------------------

void fct_20_7()
{
    char ac[]{'H', 'e', 'l', 'l', 'o'};
    vector<char> vc{'H', 'e', 'l', 'l', 'o'};
    list<char> lc{'H', 'e', 'l', 'l', 'o'};
    string str{'H', 'e', 'l', 'l', 'o'};

    func_help_20_7(ac, sizeof(ac), vc, lc, str);
}

//------------------------------------------------------------------------------

int main()
try
{
    fct_20_7();
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
