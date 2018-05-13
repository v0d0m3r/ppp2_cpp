//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Graph.h"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Message {
    char ch[5];
};

//------------------------------------------------------------------------------

struct Node {
    char ch[3];
};

//------------------------------------------------------------------------------

// Создаем объект Message в динамической памяти
inline Message* get_input()
{
    return new Message;
}

//------------------------------------------------------------------------------

void test_fragmentation()
{
    constexpr int msg_sz = sizeof(Message);
    constexpr int node_sz = sizeof(Node);
    cout << "Message sz: " << msg_sz
         << "\nNode sz: " << node_sz << '\n';

    constexpr int count = 2;
    for (auto i = 0; i < count; ++i) {
        Message* p = get_input();
        cout << "Iteration: " << i << "\tp: " << p;
        // ...
        Node* n1 = new Node;
        cout << "\tn1: " << n1;
        //..
        delete p;
        Node* n2 = new Node;
        cout << "\tn2: " << n2 << '\n';
    }
}

//------------------------------------------------------------------------------

template <typename T, int N>
class Pool {                // Пул из N объектов типа T
public:
    Pool();                 // Создаем пул из N объектов типа T
    T* get();               // Получаем T из пула; если доступных
                            // объектов нет возвращает 0
    void free(T*);          // Возвращаем T, полученный из пула
                            // с помощью функции get()
    int aviable() const;    // Количество доступных объектов T
private:
    // Память для T[N] и данные, позволяющие определить, какие
    // объекты извлечены из пула, а какие нет (например,
    // список доступных объектов)
};

//------------------------------------------------------------------------------

/* Pseudo code
void example25_3_3()
{
    Pool<Small_buffer, 10> sb_pool;
    Pool<Status_indicator, 200> indicator_pool;

    Small_buffer* p = sb_pool.get();
    // ...
    sb_pool.free(p);
}*/

//------------------------------------------------------------------------------

template <typename N>
class Stack {               // Стек из N байтов
public:
    Stack();                // Создаем стек из N байтов
    void* get(int n);       // Выделяет n байтов из стека; если
                            // свободной памяти нет возвращает 0
    void free();            // Освобождает последнее значение,
                            // возвращенное функцией get
    int aviable() const;    // Количество доступных байтов
private:
    // Память для char[N] и данные, позволяющие определить, какие
    // объекты извлечены из стека, а какие нет (например,
    // указатель на вершину стека)
};

//------------------------------------------------------------------------------

/* Pseudo code
void example25_3_3()
{
    using Connection = Message;
    Stack<50*1024> my_free_store; // Стек с 50 кб памяти

    void* pv1 = my_free_store.get(1024);
    int* buffer = static_cast<int*>(pv1);
    void* pv2 = my_free_store.get(sizeof(Connection));
    Connection* pconn = new(pv2)Connection();
}*/

//------------------------------------------------------------------------------

void poor(Shape* p, int sz) // Плохой интерфейс
{
    for (int i=0; i < sz; ++i) p[i].draw();
}

//------------------------------------------------------------------------------

// Очень плохой код
void f25_4_2(Shape* q, vector<Circle> s0)
{
    constexpr int max = 5;
    Polygon s1[10];
    Open_polyline s2[10];
    // Инициализация
    Shape* p1 = new Rectangle{Point{0, 0}, Point{10, 20}};
    poor(&s0[0], s0.size());    // #1 (передача массива из вектора)
    poor(s1, 10);               // #2
    poor(s2, 20);               // #3
    poor(p1, 1);                // #4
    delete p1;
    p1 = 0;
    poor(p1, 1);                // #5
    poor(q, max);               // #6
}

//------------------------------------------------------------------------------

template <typename T>
class Array_ref {
public:
    Array_ref(T* p, int size) {}

    T& operator[](int n) { return p[n]; }
    const T& operator[](int n) const { return p[n]; }

    bool assign(Array_ref a)
    {
        if (sz != a.sz) return false;
        for (int i=0; i < sz; ++i) p[i] = a[i];
        return true;
    }

    void reset(Array_ref a) { reset(a.p, a.sz); }
    void reset(T* pp, int ss) { p = pp; sz = ss; }

    int size() const { return sz; }
    // Операции копирования по умолчанию:
    // Array_ref не владеет какими-либо ресурсами
    // Array_ref имеет семантику ссылки

    template<typename Q>
    operator const Array_ref<const Q>()
    {
        // Проверка неявного преобразования элемента
        static_cast<Q>(*static_cast<T*>(nullptr));
        // Приведение класса Array_ref:
        return Array_ref<const Q>{reinterpret_cast<Q*>(p), sz};
    }
private:
    T* p;
    int sz;
};

//------------------------------------------------------------------------------

template<typename T>
auto make_ref(T* pp, int ss)
{
    return (pp) ? Array_ref<T>{pp, ss} : Array_ref<T>{nullptr, 0};
}

//------------------------------------------------------------------------------

template<typename T>
auto make_ref(vector<T>& v)
{
    return (v.size()) ? Array_ref<T>{&v[0], v.size()}
                      : Array_ref<T>{nullptr, 0};
}

//------------------------------------------------------------------------------

template<typename T, int s>
auto make_ref(T(&pp)[s])
{
    return Array_ref<T>{pp, s};
}

//------------------------------------------------------------------------------

void better25_4_3(Array_ref<Shape> a)
{
    for (int i=0; i < a.size(); ++i) a[i].draw();
}

//------------------------------------------------------------------------------

/*void f25_4_3(Shape* q, vector<Circle> s0) // Очень плохой код
{
    constexpr int max = 5;
    Polygon s1[10];
    Shape s2[20];
    // Инициализация
    Shape* p1 = new Rectangle{Point{0, 0}, Point{10, 20}};
    better25_4_3(make_ref(s0));     // Ошибка требуется Array_ref<Shape>
    better25_4_3(make_ref(s1));     // Ошибка требуется Array_ref<Shape>
    better25_4_3(make_ref(s2));     // ОК (преобразование не требуется)
    better25_4_3(make_ref(p1, 1));  // ОК: один элемент
    delete p1;
    p1 = 0;
    better25_4_3(make_ref(p1, 1));  // ОК: нет элементов
    better25_4_3(make_ref(q, max)); // ОК (если max задано корректно)
}*/

//------------------------------------------------------------------------------

void better25_4_4(const Array_ref<Shape*const> a)
{
    for (int i=0; i < a.size(); ++i)
        if (a[i])
            a[i]->draw();
}

//------------------------------------------------------------------------------

void f25_4_3(Shape* q, vector<Circle*>& s0) // Очень плохой код
{
    constexpr int max = 5;
    Polygon* s1[10];
    Shape* s2[20];
    // Инициализация
    Shape* p1 = new Rectangle{Point{0, 0}, Point{10, 20}};
    better25_4_4(make_ref(s0));     // ОК: преобразование
                                    // В Array_ref<Shape*const>
    better25_4_4(make_ref(s1));     // ОК: преобразование
                                    // В Array_ref<Shape*const>
    better25_4_4(make_ref(s2));     // ОК (преобразование не требуется)
    //better25_4_4(make_ref(p1, 1));  // ОК: один элемент
    delete p1;
    p1 = 0;
    //better25_4_4(make_ref(p1, 1));  // Ошибка
    //better25_4_4(make_ref(q, max)); // Ошибка
}

//------------------------------------------------------------------------------

void example25_5_1()
{
    for (int i; cin >> i;)
        cout << dec << i << "=="
             << hex << "0x" << i << "=="
             << bitset<8*sizeof(int)>(i) << '\n';
}

//------------------------------------------------------------------------------

void example25_5_2()
{
    constexpr int max = 10;
    for (bitset<max> b; cin >> b; ) {
        cout << b << '\n';
        for (size_t i=0; i < b.size(); ++i)
            cout << b[i];   // Обратный порядок
        cout << '\n';
    }
}

//------------------------------------------------------------------------------

void infinity()
{
    unsigned char max = 160;    // Очень большое
    for (signed char i=0; i < max; ++i)
        cout << int(i) << '\n';
}

//------------------------------------------------------------------------------

template<typename T>
void print(T i) { cout << i << '\t'; }

//------------------------------------------------------------------------------

void print(char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

void print(signed char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

void print(unsigned char i) { cout << int(i) << '\t'; }

//------------------------------------------------------------------------------

void example25_5_3()
{
    int si = 257;
    char c = si;
    unsigned char uc = si;
    signed char sc = si;
    print(si); print(c); print(uc); print(sc); cout << '\n';

    si = 129;
    c = si;
    uc = si;
    sc = si;
    print(si); print(c); print(uc); print(sc);
}

//------------------------------------------------------------------------------

struct PPN {                    // Номер физической страницы R6000
    unsigned int PFN    : 22;   // Номер страничного кадра
    int : 3;                    // Не используется
    unsigned int CCA    : 3;    // Алгоритм когерентности кэша
    bool nonreachable   : 1;
    bool dirty          : 1;
    bool valid          : 1;
    bool global         : 1;
};

//------------------------------------------------------------------------------

void encipher(const unsigned long* const v,
              unsigned long* const w,
              const unsigned long* const k)
{
    static_assert(sizeof(long) == 4,
                  "Неправильный размер long для TEA");

    unsigned long y = v[0];
    unsigned long z = v[1];
    unsigned long sum = 0;
    const unsigned long delta = 0x9E3779B9;

    for (unsigned long n = 32; n-- > 0;) {
        y += (z<<4 ^ z>>5) + z ^ sum + k[sum&3];
        sum += delta;
        z += (y<<4 ^ y>>5) + y ^ sum + k[sum>>11 & 3];
    }
    w[0] = y;
    w[1] = z;
}

//------------------------------------------------------------------------------

void decipher(const unsigned long* const v,
              unsigned long* const w,
              const unsigned long* const k)
{
    static_assert(sizeof(long) == 4,
                  "Неправильный размер long для TEA");
    unsigned long y = v[0];
    unsigned long z = v[1];
    unsigned long sum = 0xC6EF3720;
    const unsigned long delta = 0x9E3779B9;
    // sum = delta<<5, в целом sum = delta * n
    for (unsigned long n = 32; n-- > 0;) {
        z -= (y<<4 ^ y>>5) + y ^ sum + k[sum>>11 & 3];
        sum -= delta;
        y -= (z<<4 ^ z>>5) + z ^ sum + k[sum&3];
    }
    w[0] = y;
    w[1] = z;
}

//------------------------------------------------------------------------------

void sender()
{
    const int nchar = 2*sizeof(long);   // 64 бита
    const int kchar = 2*nchar;          // 128 бит

    string key;
    string infile;
    string outfile;
    cout << "Введите имена входного "
            "и выходного файлов и ключ:\n";
    cin >> infile >> outfile >> key;
    while (key.size() < kchar) key += '0'; // Дополнение ключа
    ifstream inf(infile.c_str());
    ofstream outf(outfile.c_str());
    if (!inf || !outf) error("Неправильное имя файла");

    const unsigned long* k =
            reinterpret_cast<const unsigned long*>(key.data());

    unsigned long outptr[2];
    char inbuf[nchar];
    unsigned long* inptr =
            reinterpret_cast<unsigned long*>(inbuf);

    int count = 0;
    while (inf.get(inbuf[count])) {
        outf << hex;    // Используется шестнадцатеричный вывод
        if (++count == nchar) {
            encipher(inptr, outptr, k);
                        // Заполнение ведущими нулями:
            outf << setw(8) << setfill('0') << outptr[0] << ' '
                 << setw(8) << setfill('0') << outptr[1] << ' ';
            count = 0;
        }
    }
    if (count) {        // Заполнение
        while (count != nchar) inbuf[count++] = '0';
        encipher(inptr, outptr, k);
        outf << outptr[0] << ' ' << outptr[1] << ' ';
    }
}

//------------------------------------------------------------------------------

void reciver()
{
    const int nchar = 2*sizeof(long);   // 64 бита
    const int kchar = 2*nchar;          // 128 бит

    string key;
    string infile;
    string outfile;
    cout << "Введите имена входного "
            "и выходного файлов и ключ:\n";
    cin >> infile >> outfile >> key;
    while (key.size() < kchar) key += '0'; // Дополнение ключа
    ifstream inf(infile.c_str());
    ofstream outf(outfile.c_str());
    if (!inf || !outf) error("Неправильное имя файла");

    const unsigned long* k =
            reinterpret_cast<const unsigned long*>(key.data());

    unsigned long inptr[2];
    char outbuf[nchar+1];
    outbuf[nchar] = 0;              // Завершающий нуль
    unsigned long* outptr =
            reinterpret_cast<unsigned long*>(outbuf);
    inf.setf(ios_base::hex,
             ios_base::basefield);  // Шестнадцатеричный ввод

    while (inf >> inptr[0] >> inptr[1]) {
        decipher(inptr, outptr, k);
        outf << outbuf;
    }
}

//------------------------------------------------------------------------------

enum class Operation { sender_b = 0, reciver_b = 1 };

//------------------------------------------------------------------------------

istream& operator >>(istream& is, Operation& op)
{
    int i;
    if (!(is >> i)) return is;
    op = static_cast<Operation>(i);
    return is;
}

//------------------------------------------------------------------------------

void sender_reciver()
{
    while (true) {
        cout << "\nInput 0 - sender or 1 - reciver\n";
        Operation op;
        cin >> op;
        if (!cin) throw runtime_error("input error!");
        switch (op) {
        case Operation::sender_b:
            sender();
            break;
        case Operation::reciver_b:
            reciver();
            break;
        default:
            cout << "Выходим\n";
            return;
        }
    }
}

//------------------------------------------------------------------------------

void task_1_2()
{
    int v = 1;
    for (int i = 0; i < sizeof(v)*8; ++i) {
        cout << v << ' ';
        v <<= 1;
    }
}

//------------------------------------------------------------------------------

void print(short unsigned int sui)
{
    cout << "sui: hex\t" << hex << sui
         <<    ";\tdec\t" << dec << sui << '\n';
}

//------------------------------------------------------------------------------

void task_3_4()
{
    static_assert(sizeof(short unsigned int) == 2,
                  "Неправильный размер int для tasks");
    short unsigned int sui = 0xffff;
    print(sui);
    sui = 0x1;
    print(sui);
    sui = 0x8000;
    print(sui);
    sui = 0xff;
    print(sui);
    sui = 0xff00;
    print(sui);
    sui = 0x5555; // 0101 0101 0101 0101
    print(sui);
    sui = 0xaaaa; // 1010 1010 1010 1010
    print(sui);
}

//------------------------------------------------------------------------------

void task_5()
{
    static_assert(sizeof(short unsigned int) == 2,
                  "Неправильный размер int для tasks");
    short unsigned int sui = 0;
    sui = ~sui;
    print(sui);
    sui &= 1;
    print(sui);
    sui = ~(sui>>1);
    sui = sui >> 1 ^ sui;
    print(sui);
    sui = 1;
    sui = sui << 1 | 1;
    sui = sui << 2 | sui;
    sui |= sui << 4;
    print(sui);
    sui = ~sui;
    print(sui);
    sui = 1;
    sui = sui << 2 | 1;
    sui |= sui << 4;
    sui |= sui << 4;
    sui |= sui << 4;
    print(sui);
    sui = 1;
    sui = (sui << 2 | 1) << 1;
    sui |= sui << 4;
    sui |= sui << 4;
    sui |= sui << 4;
    print(sui);
}

//------------------------------------------------------------------------------

int main()
try
{
    //test_fragmentation();
    //example25_5_1();
    //example25_5_2();
    //infinity();
    //example25_5_3();
    //task_1_2();
    //lambda_test();
    //task_3_4();
    //task_5_ugly;
    task_5();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "\noops!\n";
    return -2;
}

//------------------------------------------------------------------------------
