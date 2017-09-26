//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Vector.hpp"

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
    if (last < first) return nullptr;
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

template<typename Iterator>
Iterator get_right_elem(Iterator first, Iterator last, size_t counter)
// Возвращает Iterator, указывающий на counter-ый
// элемент с конца или nullptr, в случае сбоя
{
    if (first==nullptr || last==nullptr) return nullptr;
    if (last < first) return nullptr;
    while (counter && first!=last) {
        --last;
        --counter;
    }
    if (counter) return nullptr;
    return last;
}

//------------------------------------------------------------------------------

template<typename Iterator>  // Требует Input_iterator<Iterator>
Iterator high(Iterator first, Iterator last)
// Возвращает итератор, указывающий на максимальный
// элемент диапазона [first, last)
{
    if (first == last) error("contaner is empty!");
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

int main()
try
{
    /*const char* pch{nullptr};
    string str{pch};


    test_copy();*/
    Vector<string> str;
    str.push_front("strrt");
    str.push_front("12");
    str.push_back("2222");

    for (int i{0}; i < str.size(); ++i) cout << str[i] << '\n';

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
