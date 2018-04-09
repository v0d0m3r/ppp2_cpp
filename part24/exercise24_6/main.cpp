//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include "../../bstroustrup_code/MatrixIO11.h"
#include <functional>
#include <complex>
using namespace Numeric_lib;

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

            const auto& a_slice{a[j].slice(j)};
            const auto& x_slice{a[i].slice(j)};

            if (a_slice.size() != x_slice.size())
                error("scale_and_add: bad args");

            Vector_m res(a_slice.size());
            for (auto k=0; k < a_slice.size(); ++k)
                res(k) += a_slice(k) * (-mult) + x_slice(k);

            a[i].slice(j) = res;
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
        const auto& a_slice{a[i].slice(i+1)};
        const auto& x_slice{x.slice(i+1)};

        if (a_slice.size() != x_slice.size())
            error("dot_product: bad args");

        double sum{0.0};
        for (auto k=0; k < a_slice.size(); ++k)
            sum += a_slice(k) * x_slice(k);

        double s = b(i) - sum;
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

            const auto& a_slice{a[i].slice(j)};
            const auto& x_slice{a[i].slice(j)};

            if (a_slice.size() != x_slice.size())
                error("scale_and_add: bad args");

            Vector_m res(a_slice.size());
            for (auto k=0; k < a_slice.size(); ++k)
                res(k) += a_slice(k) * (-mult) + x_slice(k);

            a[i].slice(j) = res;
            b(i) -= mult * b(j);    // Изменяем вектор b
        }
    }
}

//------------------------------------------------------------------------------

Vector_m no_classical_gaussian_elimination(Matrix_m a, Vector_m b)
{
    elim_with_partial_pivot(a, b);
    return back_substitution(a, b);
}

//------------------------------------------------------------------------------

Vector_m operator*(const Matrix_m& m, const Vector_m& u)
{
    const Index n = m.dim1();
    Vector_m v(n);
    for (Index i = 0; i < n; ++i) {

        const auto& m_row{m[i]};
        if (m_row.size() != u.size())
            error("dot_product: bad args");

        double sum{0.0};
        for (auto j=0; j < m_row.size(); ++j)
            sum += m_row(j) * u(j);

        v(i) = sum;
    }
    return v;
}

//------------------------------------------------------------------------------

template<class Gen>
Vector_m random_vector(Index n, Gen gen)
{
    Vector_m v(n);
    for (Index i = 0; i < n; ++i)
        v(i) = gen();
    return move(v);
}

//------------------------------------------------------------------------------

template<class Gen>
Matrix_m random_matrix(Index n, Gen gen)
{
    Matrix_m m(n, n);
    for (Index i=0; i < n; ++i)
        for (Index j=0; j < n; ++j)
            m(i, j) = gen();
    return move(m);
}

//------------------------------------------------------------------------------

void solve_random_system(Index n, double max)
{
    auto gen = bind(uniform_real_distribution<> // Генерирует целые числа
                    {0, max},                   // Отображает int в double
                    default_random_engine{});   // в диапазоне [0, max)

    Matrix_m a = random_matrix(n, gen);
    Vector_m b = random_vector(n, gen);

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

int main()
try
{
    solve_random_system(4, 10);
    solve_random_system(5, 40);
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (const Matrix_error& e) {
    cout << "error: " << e.name << '\n';
    return -2;
}
catch (...) {
    cerr << "\noops!\n";
    return -3;
}

//------------------------------------------------------------------------------
