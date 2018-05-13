//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename In_iter>
In_iter middle(In_iter first, In_iter last,
               input_iterator_tag)
{
    advance(first, distance(first, last)/2);
    return first;
}

//------------------------------------------------------------------------------

template<typename Ra_iter>
Ra_iter middle(Ra_iter first, Ra_iter last,
               random_access_iterator_tag)
{
    return first + (last-first)/2;
}

//------------------------------------------------------------------------------

template<typename Iter, typename T>
Iter mbinary_search_ret_it(Iter first, Iter last, const T& val)
{
    Iter p;
    Iter not_found{last};
    while (first != last) {
        p = middle(first, last,
                   typename iterator_traits<Iter>::iterator_category());
        if (*p == val)
            return p;
        if (first == p)       // Последний элемент, с которым можно
            return not_found; // сравнивать; элемент не найден
        if (*p < val)
            first = p;
        else
            last = p;
    }
    return not_found;
}

//------------------------------------------------------------------------------

void example26_1()
{
    vector<int> vi{1, 3, 123, 0, 2, 4};
    sort(vi.begin(), vi.end());
    auto p{mbinary_search_ret_it(vi.begin(), vi.end(), 123)};
    if (p != vi.end())
        cout << "Найдено: " << *p << '\n';
    else
        cout << "Не найдено!\n";

    list<int> li{vi.begin(), vi.end()};
    auto link = mbinary_search_ret_it(li.begin(), li.end(), -1);
    if (link != li.end())
        cout << "Найдено: " << *p << '\n';
    else
        cout << "Не найдено!\n";
}

//------------------------------------------------------------------------------

template<typename Iter, typename T>
bool mbinary_search(Iter first, Iter last, const T& val)
{
    Iter p{last};
    while (first!=last) {
        p = middle(first, last,
                   typename iterator_traits<Iter>::iterator_category());
        if (*p == val) return true;
        if (first==p) return false; // Последний элемент
        if (*p < val) first = p;
        else          last = p;
    }
    return false;
}

//------------------------------------------------------------------------------

void simple_test26_3_2_2v1()
{
    vector<int> v {1, 2, 3, 5, 8, 13, 21};
    if (mbinary_search(v.begin(), v.end(), 1)  == false) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), 5)  == false) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), 8)  == false) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), 21) == false) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), -7) == true ) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), 4)  == true ) cout << "отказ";
    if (mbinary_search(v.begin(), v.end(), 22) == true ) cout << "отказ";
}

//------------------------------------------------------------------------------

void simple_test26_3_2_2v2()
{
    vector<int> v {1, 2, 3, 5, 8, 13, 21};
    for (int x : {1, 5, 8, 21, -7, 2, 44})
        if (mbinary_search(v.begin(), v.end(), x) == false)
            cout << x << ": отказ";
}

//------------------------------------------------------------------------------

struct Test {
    string label;
    int val;
    vector<int> seq;
    bool res;
};

//------------------------------------------------------------------------------

inline istream& set_failbit_ios(istream& is)
{
    is.clear(ios_base::failbit);
    return is;
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Test& t)
{
    char op_bound = '{';
    char ch1, ch2;
    string label;
    int val;
    is >> ch1 >> label >> val >> ch2;
    if (!is) return is;
    if (ch1!=op_bound || ch2!=ch1)  // Ошибка формата
        return set_failbit_ios(is);

    vector<int> seq;
    for (int i; is >> i;)
        seq.push_back(i);
    is.clear();

    int res;
    char ch3, ch4;
    char cl_bound = '}';
    is >> ch3 >> res >> ch4;
    if (!is) return is;
    if (ch3!=cl_bound || ch4!=ch3)  // Ошибка формата
        return set_failbit_ios(is);

    t.label = label;
    t.val = val;
    t.seq = move(seq);
    t.res = res;
    return is;
}

//------------------------------------------------------------------------------

int test_all(istream& is)
{
    int error_count = 0;
    for (Test t; is >> t; ) {
        bool r = mbinary_search(t.seq.begin(),
                                t.seq.end(), t.val);
        if (r != t.res) {
            cout << "отказ: тест " << t.label
                 << " mbinary_search: "
                 << t.seq.size() << " элементов, val=="
                 << t.val << " -> " << t.res << '\n';
            ++error_count;
        }
    }
    return error_count;
}

//------------------------------------------------------------------------------

void example26_3_2_2()
{
    ifstream is{ifstream("../my_tests.txt")};
    if (!is) error("file was not opened");
    int errors = test_all(is);
    cout << "Количество ошибок: " << errors << '\n';
}

//------------------------------------------------------------------------------

void make_test26_3_2_3(const string& lab, int n, int base, int spread)
    // Записывает описание теста с меткой lab в поток cout
    // Генерирует последовательность из n элементов, начиная
    // со значения base; среднее расстояние между элементами
    // имеет равномерное распределение на отрезке [0, spread]
{
    cout << "{ " << lab << "  " << n << " { ";
    vector<int> v;
    int elem = base;
    for (int i=0; i < n; ++i) {          // Создаем элементы
        elem += randint(spread);
        v.push_back(elem);
    }

    int val = base + randint(elem-base); // Искомое значение
    bool found = false;
    for (int i=0; i < n; ++i) {          // Вывод элементов
        if (v[i] == val) found = true;   // Есть ли элемент val
        cout << v[i] << "  ";
    }
    cout << "} " << found << " }\n";
}

//------------------------------------------------------------------------------

void use_make_test()
{
    int no_of_test = 10 + randint(50);          // Создаем порядка 50 тестов
    for (int i=0; i < no_of_test; ++i) {
        string lab = "rand_test_";
        make_test26_3_2_3(lab + to_string(i),
                          randint(500),         // Количество элементов
                          0,                    // base
                          randint(50));         // spread
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    //example26_1();
    //simple_test26_3_2_2v2();
    //example26_3_2_2();
    use_make_test();
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
