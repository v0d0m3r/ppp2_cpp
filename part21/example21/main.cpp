//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include <unordered_map>

//------------------------------------------------------------------------------

template<typename In, typename T>
// Требует Input_iterator<In>()
// и Equality_comparable<Value_type<T>>()
using Find = In (In first, In last, const T& val);

//------------------------------------------------------------------------------

template<typename In, typename T>
// Требует Input_iterator<In>()
// и Equality_comparable<Value_type<T>>()
In find1(In first, In last, const T& val)
// Находит первый элемент в [first, last), равный val
{
    while (first!=last && *first!=val) ++first;
    return first;
}

//------------------------------------------------------------------------------

template<typename In, typename T>
// Требует Input_iterator<In>()
// и Equality_comparable<Value_type<T>>()
In find2(In first, In last, const T& val)
// Находит первый элемент в [first, last), равный val
{
    for (In p{first}; p != last; ++p )
        if (*p == val) return p;
    return last;
}

//------------------------------------------------------------------------------

void example21_2(vector<int>& v, int x)
{
    auto p{find(v.begin(), v.end(), x)};
    if (p != v.end()) {
        // Мы нашли x в v
    }
    else {
        // В v нет элемента, равного x
    }
    // ...
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
// Требует Element<E> и Container<C, Args>()
void experiment_find(C<E, Args...>& c, int n,
                     Find<Iterator<C<E, Args...>>, Value_type<C<E, Args...>>> f)
{
    auto p{f(c.begin(), c.end(), -1)};
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
void do_experiment_find(C<E, Args...>& c, int n, const string& cont_name,
                        Find<Iterator<C<E, Args...>>, Value_type<C<E, Args...>>> f)
{
    auto begin{chrono::high_resolution_clock::now()};

    experiment_find(c, n, f);

    auto end{chrono::high_resolution_clock::now()};

    auto duration{chrono::duration_cast<chrono::milliseconds>(end - begin).count()};
    cout << "Выполнение эксперимента с " << cont_name.c_str()
         << " при N == " << n << " заняло " << duration
         << "мс\n";
}

//------------------------------------------------------------------------------

template<class E, template<class, class...> class C, class... Args>
// Требует Element<E> и Container<C, Args>()
void make_contaner(C<E, Args...>& c, int n)
{
    for (int i{0}; i < n; ++i) c.push_back(randint(n));
}

//------------------------------------------------------------------------------

void check_find()
{
    constexpr int size{260000000};
    vector<int> v;
    string title1{"find1"};
    string title2{"find2"};
    make_contaner(v, size);

    do_experiment_find(v, size, title1, find1);
    do_experiment_find(v, size, title2, find2);
}

//------------------------------------------------------------------------------

template<typename In, typename Pred>
// Требует Input_iterator<In>()
// и Equality_comparable<Value_type<T>>()
In find_if(In first, In last, Pred pred)
{
    while (first!=last && !pred(*first)) ++first;
    return first;
}

//------------------------------------------------------------------------------

bool odd(int x) { return x%2; }

//------------------------------------------------------------------------------

void example21_3(vector<int>& v)
{
    auto p{std::find_if(v.begin(), v.end(), odd)};
    if (p != v.end()) { /* Мы нашли значение, превышающее x*/ }
    // ...
}

//------------------------------------------------------------------------------

class Larger_than {
    int v;
public:
    Larger_than(int vv) : v{vv} {}                  // Аргумент
    bool operator() (int x) const { return x>v; }   // Сравнение
};

//------------------------------------------------------------------------------
/*
class F {   // Абстрактный пример функционального объекта
    S s;    // Состояние
public:
    F(const S& ss) : s{ss}
    {
        // Начальное состояние
    }

    T operator() (const S& ss) const
    {
        // Делает что-то с аргументом ss
        // Возвращает значение типа T (T зачастую
        // представляет собой void, bool, или S)
    }

    // Получение состояния:
    const S& state() const { return s; }
    // Сброс состояния
    void reset(const S& ss) { s = ss; }
};
*/
//------------------------------------------------------------------------------

struct Record {
    string name;    // Для простоты - стандартная строка
    char addr[24];  // Стиль C для согласованности
                    // c базами данных
    // ...
};

//------------------------------------------------------------------------------

struct Cmp_by_name {
    bool operator() (const Record& a, const Record& b) const
        { return a.name < b.name; }
};

//------------------------------------------------------------------------------

struct Cmp_by_addr {
    bool operator() (const Record& a, const Record& b) const
        { return strncmp(a.addr, b.addr, 24) < 0; }
};

//------------------------------------------------------------------------------

// Use lambda like functional object
void example21_4_3(list<double>& v, int x)
{
    auto p{std::find_if(v.begin(), v.end(),
                        [](double a) { return a > 31; })};
    if (p != v.end()) { /* Найдено значение > 31 */ }

    auto q{std::find_if(v.begin(), v.end(),
                        [&](double a) { return a > x; })};
    if (q != v.end()) { /* Найдено значение > x */ }
}

//------------------------------------------------------------------------------

template<typename In, typename T>
// Требует Input_iterator<In>() и Number<T>
T accumulate(In first, In last, T init)
{
    while (first != last) {
        init = init + *first;
        ++first;
    }
    return init;
}

//------------------------------------------------------------------------------

template<typename In, typename T, typename Bin_op>
// Требует Input_iterator<In>() и Number<T>
// Binary_operator<Bin_op, Value_type<In>, T>()
T accumulate(In first, In last, T init, Bin_op op)
{
    while (first != last) {
        init = op(init, *first);
        ++first;
    }
    return init;
}

//------------------------------------------------------------------------------

struct Record1 {
    Record1(double up, int u) : unit_price{up}, units{u} {}
    double unit_price;
    int units; // Количество проданных единиц
    // ...
};

//------------------------------------------------------------------------------

double price(double v, const Record1& r)
{
    return v + r.unit_price * r.units;  // Вычисляет стоимость
                                        // и накапливает итог
}

//------------------------------------------------------------------------------

void example21_5_2()
{
    vector<Record1> vr{
        {2.5, 3}, {100.26, 2},
        {24, 5},  {12.2342, 12}
    };
    double total{std::accumulate(vr.begin(), vr.end(), 1.0, price)};
    cout << "total == " << total << '\n';
}

//------------------------------------------------------------------------------

template<typename In, typename In2, typename T>
// Требует Input_iterator<In>() и Input_iterator<In2>()
// и Number<T>
T inner_product(In first, In last, In2 first2, T init)
{
    while (first != last) {
        init = init + (*first) * (*first2); // Умножение пар
        ++first;
        ++first2;
    }
    return init;
}

//------------------------------------------------------------------------------

// Вычисление индекса Доу-Джонса
void example21_5_3()
{
    vector<double> dow_price {  // Цена акции каждой компании
        81.86, 34.69, 54.45,
        // ...
    };

    list<double> dow_weight {   // Вес каждой компании в индексе
        5.8549, 2.4808, 3.8940,
        // ...
    };

    double dji_index{
        std::inner_product(dow_price.begin(), dow_price.end(),
                           dow_weight.begin(), 0.0)
    };
    cout << "dji_index == " << dji_index << '\n';
}

//------------------------------------------------------------------------------

template<typename In, typename In2, typename T,
         typename Bin_op, typename Bin_op2>
// Требует Input_iterator<In>(), Input_iterator<In2>(),
// Number<T>,
// Binary_operator<Bin_op, Value_type<In>, T>(),
// Binary_operator<Bin_op2, Value_type<In2>, T>()
T inner_product(In first, In last, In2 first2, T init,
                Bin_op op, Bin_op2 op2)
{
    while (first != last) {
        init = op(init, op2(*first, *first2)); // Умножение пар
        ++first;
        ++first2;
    }
    return init;
}

//------------------------------------------------------------------------------

void example21_6_1()
{
    map<string, int> words; // Поддержка пар (слово, частота)
    for (string s; cin >> s; )
        ++words[s];

    for (const auto& p : words)
        cout << p.first << ": " << p.second << '\n';
}

//------------------------------------------------------------------------------

double weighted_value(const pair<string, double>& a,
                      const pair<string, double>& b)
{
    return a.second * b.second;
}

//------------------------------------------------------------------------------

void example21_6_3()
{
    map<string, double> dow_price { // Индекс Джоу-Джонса
            // (аббревиатура, цена)
        {"MMM", 81.86},
        {"AA", 34.69},
        {"MO", 54.45},
        {"MS", 42.21},
        {"FB", 23.23},
        // ...
    };

    map<string, double> dow_weight { // (аббревиатура, вес)
        {"MMM", 5.8549},
        {"AA", 2.4808 },
        {"MO", 3.8940},
        {"MS", 4.2121},
        {"FB", 3.2321},
        // ...
    };

    map<string, string> dow_name {  // (аббревиатура, название)
        {"MMM", "3M co."},
        {"AA", "Alcoa Inc."},
        {"MO", "Altria Group Inc."},
        {"MS", "Microsoft Inc."},
        {"FB", "Facebook Inc."},
        // ...
    };

    double alcoa_price{dow_price["AA"]};  // Считываем значения
                                          // из отображения
    // Находим запись в отображении
    if (dow_price.find("INTC") != dow_price.end())
        cout << "Intel найден\n";

    // Вывод цен акций каждой компании в индексе Доу-Джонса
    for (const auto& p : dow_price) {
        const string& symbol = p.first; // Аббревиатура
        cout << symbol << '\t'
             << p.second << '\t'
             << dow_name[symbol] << '\n';
    }

    double dji_index {
        std::inner_product(
        dow_price.begin(), dow_price.end(), // Цены всех компаний
        dow_weight.begin(),                 // Их веса
        0.0,                                // Начальное значение
        plus<double>(),                     // Обычное сложение
        weighted_value)                     // Перемножение значений
    };
    cout << "dji_index == " << dji_index << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    //check_find();
    example21_5_2();
    example21_5_3();
    example21_6_3();
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
