#ifndef VECTOR_EASY_H
#define VECTOR_EASY_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Vector_easy
{
    int sz;             // Размер
    double* elem;       // Указатель на первый элемент (типа double)
public:
    Vector_easy(int s); // Конструктор: размещает в памяти s чисел
                        // типа double, направляет на них указатель
                        // elem и сохраняет s в члене sz
    ~Vector_easy()      // Деструктор
    { delete[] elem; }  // Освобождаем память
    int size() const { return sz; } // Текущий размер

    double get(int n) const { return elem[n]; } // Чтение
    void set(int n, double v) { elem[n] = v; }  // Запись

};

//------------------------------------------------------------------------------

#endif // VECTOR_EASY_H
