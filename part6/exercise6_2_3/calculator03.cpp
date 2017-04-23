//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
    char kind;                  // Разновидность лексемы
    double value;               // Для чисел: значение
    Token(char ch)              // Получает лексему из char
        :kind(ch), value(0) { }
    Token(char ch, double val)  // Получает лексему из char и double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();         // Создает объект класса Token_stream,
                            // считывающий данные из cin
    Token get();            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
private:
    bool full;              // Находится ли лексема в буфере?
    Token buffer;           // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------
// Конструктор изменяет индикатор full и
// инициализирует buffer пустым значением:
Token_stream::Token_stream()
    :full(false), buffer(0)    // Нет Token в буфере
{
}

//------------------------------------------------------------------------------
// putback()  помещает свой аргумент назад в поток лексем buffer:
void Token_stream::putback(Token t)
{
    if (full) error("буфер заполнен!");
    buffer = t;       // Копируем t в буфер
    full = true;      // Буфер заполнен
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {             // Есть готовый объект Token?
        full=false;         // Убираем его из буфера и возвращаем
        return buffer;
    }

    Token t{' '};
    char ch;
    cin >> ch;              // >> пропускает пробельные символы

    switch (ch) {
    case '=':               // Завершение выражения
    case 'x':               // Для выхода
    case '{': case '}': case '(': case ')': case '+':
    case '-': case '*': case '/': case '!':
        t = Token(ch);      // Символ представляет сам себя
        break;
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // Возвращаем цифру во входной поток
        double val;
        cin >> val;         // Считываем число с плавающей точкой
        t = Token('8',val); // '8' означает лексему число
        break;
    }
    default:
        error("неверная лексема");
    }
    return t;
}

//------------------------------------------------------------------------------

int fact_calc(int n)
{
    if (n < 0) error("отрицательный операнд!");

    for (int i = n - 1; i > 1; --i) n *= i;

    return (n == 0) ? 1 : n;
}

//------------------------------------------------------------------------------

Token_stream ts;        // Обеспечивает get() и putback()

//------------------------------------------------------------------------------

double expression();    // Объявление таким образом,
                        // что primary() может вызывать expression()

//------------------------------------------------------------------------------
// Имеем дело с числами и выражениями
double primary()
{
    double val = 0;
    Token t = ts.get(); // Получаем следующую лексему
    switch (t.kind) {
    case '(':           // Описывает '(' выражение ')'
    {
        val = expression();
        t = ts.get();
        if (t.kind != ')') error("требуется ')'");
        break;
    }
    case '{':           // Описывает '{' выражение '}'
    {
        val = expression();
        t = ts.get();
        if (t.kind != '}') error("требуется '}'");
        break;
    }
    case '8':           // Используем для представления числа
        val = t.value;  // Возвращаем значение числа
        break;
    default:
        error("требуется первичное_выражение");
    }
    return val;
}

//------------------------------------------------------------------------------
// Имеем дело с '!'
double fact()
{
    double left = primary();
    Token t = ts.get();             // Получаем следующую лексему

    while(true) {
        switch (t.kind) {
        case '!':
            left = fact_calc(left); // Вычисляем факториал
            t = ts.get();
            break;
        default:
            ts.putback(t);          // Помещаем t в поток лексем
            return left;
        }
    }
}

//------------------------------------------------------------------------------
// Имеем дело с '*' и '/'
double term()
{
    double left = fact();
    Token t = ts.get();        // Получаем следующую лексему

    while(true) {
        switch (t.kind) {
        case '*':
            left *= fact();
            t = ts.get();
            break;
        case '/':
        {
            double d = fact();
            if (d == 0) error("деление на нуль");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // Помещаем t в поток лексем
            return left;
        }
    }
}

//------------------------------------------------------------------------------
// Имеем дело с '+' и '-'
double expression()
{
    double left = term();      // Считываем и вычисляем Терм
    Token t = ts.get();        // Получаем следующую лексему

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // Вычисляем терм и суммируем
            t = ts.get();
            break;
        case '-':
            left -= term();    // Вычисляем терм и вычитаем
            t = ts.get();
            break;
        default:
            ts.putback(t);     // Конец символов: + и - нет,
            return left;       // возвращаем ответ
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    double val = 0;
    cout << "Добро пожаловать в программу калькулятор!\n"
            "Вводите выражения с числами с плавающей точкой,\n"
            "операторы +, -, *, /. Для вывода результата\n"
            "используйте символ \"=\".\nДля выхода из программы "
            "используйте символ \"x\".\n";
    while (cin) {
        Token t = ts.get();
        if (t.kind == 'x') break; // 'x' для выхода
        if (t.kind == '=')        // '=' для вывода на печать
            cout << val << '\n';
        else
            ts.putback(t);
        val = expression();
    }
}
catch (exception& e) {
    cerr << "\nОшибка: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Упс: неизвестное исключение!\n";
    keep_window_open();
    return 2;
}

//-----------------------------------------------------------------------------
