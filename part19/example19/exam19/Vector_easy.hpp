//------------------------------------------------------------------------------

#ifndef VECTOR_EASY_HPP
#define VECTOR_EASY_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Vector_easy
{
    int sz;         // Размер
    double* elem;   // Указатель на первый элемент (типа double)
    int space;      // Количество элементов плюс "свободное
                    // место"/"слоты" для новых элементов
                    // (текущий выделенный размер)
public:
    explicit Vector_easy(int s); // Конструктор: размещает в памяти s чисел
                                 // типа double, направляет на них указатель
                                 // elem и сохраняет s в члене sz
    Vector_easy(initializer_list<double> lst);
    Vector_easy(const Vector_easy& a);  // Копирующий конструктор
    Vector_easy(Vector_easy&& a);       // Перемещающий конструктор
    ~Vector_easy()                                // Деструктор
    { delete[] elem; }                            // Освобождаем память
    int size() const { return sz; }               // Текущий размер

    double& operator[](int n) { return elem[n]; } // Оператор индексирования
    double operator[](int n) const                // Оператор индексирования
    { return elem[n]; }                           // для константного вектора

    Vector_easy& operator=(const Vector_easy& a); // Копирующее присваивание
    Vector_easy& operator=(Vector_easy&& a);      // Перемещающее присваивание

    void reserve(int newalloc);
    int capacity() const { return space; }

    void resize(int newsize);
    void push_back(double d);

};

//------------------------------------------------------------------------------

#endif // VECTOR_EASY_HPP

//------------------------------------------------------------------------------
