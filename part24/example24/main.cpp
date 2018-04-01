//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include "../../bstroustrup_code/MatrixIO11.h"
#include <functional>
using namespace Numeric_lib;

//------------------------------------------------------------------------------

void help_example24_2(int num)
{
    float x{1.0/num};
    float sum{0};
    for (int i=0; i < num; ++i) sum += x;
    cout << setprecision(15) << sum << "\n";
}

//------------------------------------------------------------------------------

void f24_2(int i, double fpd)
{
    cout << "start: \ti == " << i << "\tfpd == " << fpd << '\n';
    char c = i;      // Тип char действительно представляет
                     // очень маленькие целые числа
    cout << "c == " << int(c) << '\n';
    short s = i;     // Опасно: тип int может не поместиться
                     // в памяти для переменной типа short
    cout << "s == " << s << '\n';
    i = i + 1;       // Что будет, если число i до увеличения
                     // было максимально возможным?
    cout << "i == " << i << '\n';
    long lg = i*i;   // Опасно: long может быть не больше int
    cout << "lg == " << lg << '\n';
    float fps = fpd; // Опасно: значение double может
                     // не поместиться в типе float
    cout << "fps == " << fps << '\n';
    i = fpd;         // Усечение; например, 5.7 -> 5
    cout << "i == " << i << '\n';
    fps = i;         // Возможна потеря точности (при
                     // очень больших целочисленных значениях)
    cout << "fps == " << fps << '\n';
}

//------------------------------------------------------------------------------

void g24_2()
{
    char ch = 0;
    for (int i=0; i < 500; ++i)
        cout << int(ch++) << '\t';
    cout << '\n';
}

//------------------------------------------------------------------------------

void example24_2()
{
    auto def_precision = cout.precision();
    help_example24_2(333);
    help_example24_2(10);

    short int y = 40000;
    int i{1000000};
    cout << setprecision(def_precision)
         << y << " " << i*i << '\n';

    cout << "Размеры: " << sizeof(int)
         << '\t'         << sizeof(float) << '\n';
    int x = 2100000009;     // Большое целое число
    float f = x;
    cout << x << '\t' << f << endl;
    cout << setprecision(15) << x << '\t' << f
         << def_precision << '\n';

    float f1 = 2.8;
    int x1 = f1;
    cout << x1 << '\t' << f1 << '\n';

    g24_2();
    f24_2(2100000009, 210000000.3);
    f24_2(300, 321.34);
}

//------------------------------------------------------------------------------

void example24_2_1()
{
    cout << "Количетсво байтов в типе int: "
         << sizeof(int) << '\n';
    //cout << "" << INT_MAX << endl;
    cout << "Наибольшее число типа int: "
         << numeric_limits<int>::max() << '\n';
    cout << "Наименьшее число типа int: "
         << numeric_limits<int>::min() << '\n';

    if (numeric_limits<char>::is_signed)
        cout << "Тип char имеет знак\n";
    else
        cout << "Тип char не имеет знака\n";

    // Наименьшее положительное значение:
    char ch = numeric_limits<char>::min();
    cout << "Наименьшее значение char: "
         << ch << '\n';
    cout << "Значение int для char с наименьшим "
         << "значением: " << int(ch) << '\n';
}

//------------------------------------------------------------------------------

void f24_3_1(int a[3][5])
{

}

//------------------------------------------------------------------------------

void f24_3_2(int a[][5], int dim1)
{

}

//------------------------------------------------------------------------------

void f24_3_5(int* m, int dim1, int dim2)
{
    for (int i=0; i < dim1; ++i)
        for (int j=0; j < dim2; ++i) m[i*dim2+j] = 0;
}

//------------------------------------------------------------------------------

void example24_3()
{
    f24_3_1(nullptr);
    f24_3_2(nullptr, 2);
}

//------------------------------------------------------------------------------

void f24_5_1(int n1, int n2, int n3)
{
    Matrix<double, 1> ad1(n1);  // Одномерная с элементами double
    Matrix<int, 1>    ai1(n1);  // Одномерная с элементами int
    ad1(7) = 0;                 // Индексирование в стиле Fortran - ()
    ad1[7] = 8;                 // Индексирование в стиле C - []

    Matrix<double, 2> ad2(n1, n2);      // Двумерная
    Matrix<double, 3> ad3(n1, n2, n3);  // Трехмерная
    ad2(3,4) = 7.5;                     // Истинное многомерное
    ad3(3, 4, 5) = 9.2;                 // индексирование
    ad2[3][4] = 8.5;
}

//------------------------------------------------------------------------------

// Пример ошибок с Матрицами
/*void f24_5_1_err(int n1, int n2, int n3)
{
    Matrix<int, 0> ai0;         // Ошибка: 0-мерная матрица
    Matrix<double, 1> ad1(5);
    Matrix<int, 1> ai(5);

    Matrix<double, 1> ad11(7);
    ad1(7) = 0;                 // Исключение Matrix_error
                                // (7 - за пределами диапозона)
    ad1 = ai;                   // Ошибка: разные типы элементов
    ad1 = ad11;                 // Исключение Matrix_error
                                // (несовпадающие размерности)

    Matrix<double, 2> ad2(n1);  // Ошибка: не указана вторая размерность
    ad2(3) = 7.5;               // Ошибка: неверное количество индексов
    ad2(1, 2, 3) = 7.5;         // Ошибка: неверное количество индексов

    Matrix<double, 3> ad3(n1, n2, n3);
    Matrix<double, 3> ad33(n1, n2, n3);
    ad3 = ad33;                 // ОК: одинаковые типы элементов,
                                // одинаковые размерности
}*/

//------------------------------------------------------------------------------

void init24_5_1(Matrix<int, 2>& a)  // Инициализация каждого элемента
{                                   // характеризующим значением
    for (int i=0; i < a.dim1(); ++i)
        for (int j=0; j < a.dim2(); ++j)
            a(i, j) = 10*i+j;
}

//------------------------------------------------------------------------------

void print24_5_1(const Matrix<int, 2>& a)   // Построчный вывод матрицы
{
    for (int i=0; i < a.dim1(); ++i)
        for (int j=0; j < a.dim2(); ++j)
            cout << a(i, j) << '\t';
    cout << '\n';
}

//------------------------------------------------------------------------------

double scale24_5_2(double d, double s) { return d*s; }
void scale_in_place24_5_2(double& d, double s) { d *= s; }

//------------------------------------------------------------------------------

void some_functions(double* p, int n)
{
    double val[] = { 1.2, 2.3, 3.4, 4.5};
    Matrix<double> data{p,n};
    Matrix<double> constants{val};
}

//------------------------------------------------------------------------------

// Примеры с одномерными матрицами
/*void example24_5_2()
{
    Matrix<int,1> a1(8); // a1 - одномерная матрица целых чисел
    Matrix<int> a(8);    // Означает Matrix<int,1> a(8);

    a.size();            // Количество элементов в Matrix
    a.dim1();            // Количество элементов в первом измерении
    int* p = a.data();   // Получаем данные через указатель на массив

    int i=100, n=500;    // "Случайное" число для примера
    a(i);                // i-й элемент (в стиле Fortran) с проверкой диапазона
    a[i];                // i-й элемент (в стиле C) с проверкой диапазона
    a(1,2);              // Ошибка: а - одномерная матрица

    a.slice(i);          // Элементы с a[i] по последний
    a.slice(i, n);       // n элементов с a[i] по a[i+n-1]

    a.slice(4,4) = a.slice(0,4); // Присваиваем первую половину матрицы второй
    a.slice(4) = a.slice(0, 4);  // Присваиваем первую половину матрицы второй

    Matrix<int> a2 = a;  // Копирующая инициализация
    a = a2;              // Копирующее присваивание
    a *= 7;              // a[i]*=7 для всех i (работает также
                         // для +=, -=, /= и т.д.)
    a = 7;               // a[i]=7 для всех i
    a.apply(f);          // a[i]=f(a[i]) для каждого элемента a[i]
    a.apply(f, 7);       // a[i]=f(a[i],7) для каждого элемента a[i]
    b = apply(abs, a);   // Создаем новую матрицу, такую, что b(i)==abs(a(i))
    b = a*7;             // b[i] = a[i]*7 для каждого i
    y = apply(f, x);     // y[i] = f(x[i]) для каждого i
    x.apply(f);          // x[i] = f(x[i]) для каждого i
    b = apply(f, a, x);  // b[i] = f(a[i], x) для каждого i
    b = apply(scale24_5_2, a, 7); // b[i] = a[i]*7 для каждого i
    b.apply(scale_in_place24_5_2, 7); // b[i] *= 7 для каждого i
    Matrix<int> a3 = 
        scale_and_add(a, 8, a2); // Слитное умножение и сложение
    int r = dot_product(a3, a);  // Скалярное произведение
}*/

//------------------------------------------------------------------------------

// Примеры с двумерными матрицами
void example24_5_3()
{
    /*Matrix<int, 2> a(3,4);
    int s = a.size();       // Количество элементов всей матрицы
    int d1 = a.dim1();      // Количество элементов в строке
    int d2 = a.dim2();      // Количество элементов в столбце
    int* p = a.data();      // Указатель на данные
    a(i, j);                // Элемент (i, j) (в тиле Fortran) с проверкой диапазона
    a[i];                   // i-ая строка (в стиле C) с проверкой диапазона
    a[i][j];                // Элемент (i, j) (в стиле C)
    a.slice(i);             // Строки от a[i] до последней
    a.slice(i, n);          // Строки от a[i] до по a[i+n-1]

    Matrix<int> a2 = a;     // Копирующая инициализация
    a = a2;                 // Копирующее присваивание
    a *= 7;                 // Масштабирование (а также +=, -=, /= и т.д.)
    a.apply(f);             // a(i, j) = f(a(i, j)) для каждого a(i, j)
    a.apply(f, 7);          // a(i, j) = f(a(i, j), 7) для каждого a(i, j)
    b = apply(f, a);        // Новая матрица с b(i,j)=f(a(i, j))
    b = apply(f, a, 7);     // Новая матрица с b(i,j)=f(a(i, j), 7)
    a.swap_rows(1, 2);      // Перестановка строк a[1] <-> a[2]    
    */
    enum Piece { none, pawn, knight, queen, king, bishop, rook};
    Matrix<Piece, 2> board(8,8);    // Шахматная доска

    const int white_start_row = 0;
    const int black_start_row = 7;

    Matrix<Piece> start_row 
        = (rook, knight, bishop, queen, king, bishop, knight, rook);

    Matrix<Piece> clear_row(8);     // 8 элементов со значением по умолчанию
    board[white_start_row] = start_row; // Расстановка белых фигур
    for (int i=1; i < 7; ++i)
        board[i] = clear_row;           // Очистка середины доски
    board[black_start_row] = start_row; // Расстановка черных фигур

    cout << board;
}

//------------------------------------------------------------------------------

using Matrix_m = Matrix<double,2>;
using Vector_m = Matrix<double>;

//------------------------------------------------------------------------------

void classical_elimination(Matrix_m& a, Vector_m& b)
{
    const Index n = a.dim1();

    // Проходим от первого столбца до предпоследнего,
    // обнуляя элементы, стоящие ниже диагонали:
    for (Index j = 0; j < n-1; ++j) {
        const double pivot = a(j, j);
        if (pivot == 0)
            error("Решения нет, нулевой опорный элемент");

        // Обнуляем элементы, стоящие ниже диагонали в строке i
        for (Index i=j+1; i < n; ++i) {
            const double mult = a(i, j) / pivot;
            a[i].slice(j) = scale_and_add(a[j].slice(j),
                                -mult, a[i].slice(j));
            b(i) -= mult * b(j);    // Изменяем вектор b
        }
    }
}

//------------------------------------------------------------------------------

Vector_m back_substitution(const Matrix_m& a, const Vector_m& b)
{
    const Index n = a.dim1();
    Vector_m x(n);

    for (Index i = n-1; i >= 0; --i) {
        double s = b(i) - dot_product(a[i].slice(i+1),
                                        x.slice(i+1));
        if (double m = a(i,i))
            x(i) = s / m;
        else
           error("Решения нет, нулевой опорный элемент");
    }
    return x;
}

//------------------------------------------------------------------------------

Vector_m classical_gaussian_elimination(Matrix_m a, Vector_m b)
{
    classical_elimination(a, b);
    return back_substitution(a, b);
}

//------------------------------------------------------------------------------

void elim_with_partial_pivot(Matrix_m& a, Vector_m& b)
{
    const Index n = a.dim1();
    for (Index j = 0; j < n; ++j) {
        Index pivot_row = j;

        // Поиск подходящего опорного элемента
        for (Index k = j+1; k < n; ++k)
            if (abs(a(k,j)) > abs(a(pivot_row, j)))
                pivot_row = k;

        // Обмен строк для лучшего опорного представления
        if (pivot_row != j) {
            a.swap_rows(j, pivot_row);
            std::swap(b(j), b(pivot_row));
        }
        // Исключение:
        for (Index i=j+1; i < n; ++i) {
            const double pivot = a(j, j);
            if (pivot == 0) 
                error("Решения нет, нулевой опорный элемент");            
            const double mult = a(i, j) / pivot;
            a[i].slice(j) = scale_and_add(a[j].slice(j),
                                -mult, a[i].slice(j));
            b(i) -= mult * b(j);    // Изменяем вектор b
        }
    }    
}

//------------------------------------------------------------------------------

Vector_m operator*(const Matrix_m& m, const Vector_m& u)
{
    const Index n = m.dim1();
    Vector_m v(n);
    for (Index i = 0; i < n; ++i)
        v(i) = dot_product(m[i], u);
    return v;
}

//------------------------------------------------------------------------------

Vector_m random_vector(Index n)
{
    Vector_m v(n);
    default_random_engine ran{};    // Генерирует целые числа
    uniform_real_distribution<>     // Отображает int в double
        unreal{0, numeric_limits<int>::max()};
                                    // в диапазоне [0, max)
    for (Index i = 0; i < n; ++i)
        v(i) = unreal(ran);
    return v;
}

//------------------------------------------------------------------------------

Matrix_m random_matrix(Index n)
{
    return Matrix_m(n, n);
}

//------------------------------------------------------------------------------

void solve_random_system(Index n)
{
    Matrix_m a = random_matrix(n);
    Vector_m b = random_vector(n);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    try {
        Vector_m x = classical_gaussian_elimination(a, b);
        cout << "Решение методом Гаусса: x = " << x << endl;
        Vector_m v = a * x;
        cout << "a * x = " << v << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

//------------------------------------------------------------------------------

void example24_7()
{
    auto gen = bind(normal_distribution<double>{15, 4.0},
                  default_random_engine{});
    vector<int> hist(2*15);
    for (int i=0; i < 500; ++i)             // Генерация гистограммы
        ++hist[int(round(gen()))];          // из 500 значений
    for (int i=0; i != hist.size(); ++i) {  // Вывод гистограммы
        cout << i << '\t';
        for (int j = 0; j != hist[i]; ++j)
            cout << '*';
        cout << '\n';
    }
    for (auto i : hist)
        cout << i << '\t';
    cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    //example24_2();
    //example24_2_1();
    //f24_5_1(1,2,3);
    //f24_5_1_err(1, 2, 3);
    example24_7();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (const Matrix_error& e) {
    cout << "\nerror: " << e.name << '\n';
    return -2;
}
catch (...) {
    cerr << "\noops!\n";
    return -3;
}

//------------------------------------------------------------------------------
