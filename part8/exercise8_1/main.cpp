//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

const char number = 8;  // t.kind==number означает, что t - число
const char quit = 'q';  // t.kind==quit означает, что
                        // t лексема выхода
const char print = ';'; // t.kind==print означает, что
                        // t лексема печати
const string promt = "> ";    // приветствие
const string result = "= ";   // используется для указания на то,
                              // что далее следует результат
const char name = 'a';        // Лексема Имя
const char let = 'L';         // Лексема let
const string declkey = "let"; // Ключевое слово let

//------------------------------------------------------------------------------

class Variable {
public:
    string name;
    double value;
    Variable(string n, double val)
        :name(n), value(val) { }
};

//------------------------------------------------------------------------------

vector<Variable> var_table;

//------------------------------------------------------------------------------

double get_value(string s)
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
{
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

class Token {
public:
    char kind;          // Разновидность лексемы
    double value;       // Для чисел: значение
    string name;
    Token(char ch)      // Получает лексему из символа (+, -, * и т.д.)
        :kind(ch), value(0) { }
    Token(char ch, double val)     // Формирует лексему парой "8" и число
        :kind(ch), value(val) { }
    Token(char ch, string n)       // Формирует лексему kind
        :kind(ch), name(n) { }     //  и 'Имя-переменная'
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();         // Создает объект класса Token_stream,
                            // считывающий данные из потока cin
    Token_stream(istream& i);
    Token get();            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
    void ignore(char c);    // Отбрасывает символы до
                            // символа *c* включительно
    istream& ist;

private:
    bool full;              // Имеется ли лексема в буфере?
    Token buffer;           // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------

// Конструктор изменяет индикатор full и инициализирует buffer пустым значением:
Token_stream::Token_stream()
    : ist{cin}, full{false}, buffer{0}     // нет Token в буфере
{
}

//------------------------------------------------------------------------------

Token_stream::Token_stream(istream& i)
    : ist{i}, full{false}, buffer{0}
{
}

//------------------------------------------------------------------------------

// Функция-член putback()  помещает свой аргумент назад в поток лексем buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback: ","буфер заполнен!");
    buffer = t;     // Копируем t в буфер
    full = true;    // Буфер заполнен
}

//------------------------------------------------------------------------------

// Функция-член get() осуществляет чтение символов из cin и составление Token
Token Token_stream::get()
{
    if (full) {     // Есть готовый объект Token?
        full=false; // Убираем его из буфера и возвращаем
        return buffer;
    }

    char ch;
    cin >> ch;      // Оператор ">>" пропускает пробельные символы

    switch (ch) {
    case quit:      // для выхода
    case print:     // для печати
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token(ch);   // Символ представляет сам себя
    case '.':               // Число с плавающей точкой может
                            // начинаться с точки
                            // Числовой литерал
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // Возвращаем цифру во входной поток
        double val;
        cin >> val;         // Считываем число с плавающей точкой
        return Token(number,val);
    }
    default:
        if (isalpha(ch)) {

            string s = "";
            s += ch;
            while (cin.get(ch) &&
                   (isalpha(ch) || isdigit(ch))) s+=ch;
            cin.putback(ch);
            if (s == declkey)
                return Token(let); // Ключевое слово let
            return Token(name, s);

        }
        error("get: ", "неправильная лексема");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    // Сначала проверяем буфер:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // Теперь проверяем входные данные
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

void clean_up_mess(Token_stream& ts)
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

double expression(Token_stream& ts);

//------------------------------------------------------------------------------

// Имеем дело с числами и выражениями
double primary(Token_stream& ts)
{
    Token t = ts.get();             // Получаем следующую лексему
    switch (t.kind) {
    case '(':
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')')  error("primary()", "требуется ')'");
        return d;
    }
    case number:                  // Используем number для представления числа
        return t.value;           // Возвращаем значение числа
    case '-':
        return - primary(ts);     // Унарный минус
    case '+':
        return primary(ts);       // Унарный плюс
    case name:                    // Используем name для представления
        return get_value(t.name); // имени переменной
    default:
        error("primary: ", "требуется первичное_выражение");
    }
}

//------------------------------------------------------------------------------

// Имеем дело с '*', '/', '%'
double term(Token_stream& ts)
{
    double left = primary(ts);      // Считываем и вычисляем первичное_выражение
    Token t = ts.get();             // Получаем следующую лексему

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary(ts);    // Вычисляем первичное_выражение и умножаем
            t = ts.get();
            break;
        case '/':
        {
            double d = primary(ts);
            if (d == 0) error("term: ", "деление на нуль");
            left /= d;              // Вычисляем первичное_выражениеи и делим
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary(ts);
            if (d == 0) error("term:","деление на нуль");
            left = fmod(left, d);   // x%y = x-y*int(x/y)
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);          // Ложим t в поток лексем
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// Имеем дело с '+' и '-'
double expression(Token_stream& ts)
{
    double left = term(ts);     // Считываем и вычисляем Терм
    Token t = ts.get();         // Получаем следующую лексему

    while(true) {
        switch(t.kind) {
        case '+':
            left += term(ts);   // Вычисляем терм и суммируем
            t = ts.get();
            break;
        case '-':
            left -= term(ts);   // Вычисляем терм и вычитаем
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;        // Конец символов: + и - нет,
                                // возвращаем ответ
        }
    }
}

//------------------------------------------------------------------------------

// Ф-ция is_declared() проверяет: есть ли переменная var в var_tables?
bool is_declared(string var)
{
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

//------------------------------------------------------------------------------

// Ф-ция define_name() добавляет пару (var, val) в var_table
double define_name(string var, double val)
{
    if (is_declared(var))
        error("define_name: ", var +
              " повторное объявление");
    var_table.push_back(Variable(var, val));
    return val;
}

//------------------------------------------------------------------------------

// Обрабатываем Имя = Выражение
// Объявление переменной с Именем с начальным значением, заданным Выражением
double declaration(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != name)
        error("declaration: ", "в объявлении ожидается имя переменной");
    string var_name = t.name;
    if (is_declared(var_name))
        error("declaration: ", name + string(" второе объявление"));
    Token t2 = ts.get();
    if (t2.kind != '=')
        error("declaration: ", "пропущен символ = "
                               "в объявлении " + var_name);

    double d = expression(ts);
    define_name(var_name, d);
    return d;
}

//------------------------------------------------------------------------------

double statement(Token_stream& ts)
{    
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration(ts);
    default:
        ts.putback(t);
        return  expression(ts);
    }
}

//------------------------------------------------------------------------------

// Цикл вычисления выражения
void calculate()
{
    Token_stream ts;
    while (cin)
    try
    {
        cout << promt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();   // "Съедает ';'"
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement(ts) << '\n';
    }
    catch (exception& e) {
        cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess(ts);
    }

}

//------------------------------------------------------------------------------

int main()
try
{
    // Предопределенные имена
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    calculate();
    return 0;
}
catch (...) {
    cerr << "Упс: неизвестное исключение!\n";
    keep_window_open("~~");
    return 2;
}

//-----------------------------------------------------------------------------
