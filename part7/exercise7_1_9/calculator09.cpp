/*

Простой калькулятор

Версия 09, март 2016 год

Эта программа реализует основные выражения калькулятора.

Ввод осуществляется из потока cin; вывод - в поток cout.

Грамматика для ввода:

Вычисление:
    Инструкция
    Вывод
    Выход
    Вычисление Инструкция
    Инструкция Вывод Инструкция

Вывод:
    ";"
    "\n"

Выход:
    "q"

Инструкция:
    Выражение
    Объявление
    Объявление_констант
    Присваивание 

Объявление:
    "let" Имя "=" Выражение

Объявление_констант:
    "const" Имя "=" Выражение

Присваивание:
    Имя "=" Выражение

Выражение:
    Терм
    Выражение "+" Терм
    Выражение "-" Терм

Терм:
    Первичное_выражение
    Терм "*" Первичное_выражение
    Терм "/" Первичное_выражение
    Терм "%" Первичное_выражение

Первичное_выражение:
    Число
    "(" Выражение ")"
    "+" Первичное_выражение
    "-" Первичное_выражение
    Имя
    Натуральный_логарифм    

Натуральный_логарифм:
    "ln" "(" Выражение ")" 

Имя:
    литерал_буквы
    литерал_буквы литерал_целое_число

Число:
    Литерал_с_плавающей_точкой

Ввод из потока cin через Token_stream с именем ts.
*/

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Variable {
public:
    string name;    // Имя переменной
    double value;   // Значение переменной
    bool is_const;  // Является ли переменная
                    // константой?
    Variable(string n, double val)
        :name(n), value(val), is_const(false)  { }
    Variable(string n, double val, bool is_c)
        :name(n), value(val), is_const(is_c)  { }
};

//------------------------------------------------------------------------------

class Symbol_table {
public:    
    double get_value(string s);         // Добавить переменную в хранилище
    void set_value(string s, double d); // Изменить значение переменной
    bool is_declared(string var);       // Переменная была уже добавлена?
    // Добавление (объявление) перемменной в хранилище
    double define_name(string var, double val, bool is_constant=NULL);
    Symbol_table() {}
private:
    vector<Variable> var_table;         // Хранилище переменных
};

//------------------------------------------------------------------------------

Symbol_table st;

//------------------------------------------------------------------------------

double Symbol_table::get_value(string s)
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

void Symbol_table::set_value(string s, double d)
{
    for (Variable& v : var_table)
        if (v.name==s && !v.is_const) {
            v.value = d;
            return;
        }
        else if (v.name==s && v.is_const) {
            error("set_value: ", "нельзя присвоить "
                                 "значение константы: " + s);
        }
    error("set_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

// Ф-ция is_declared() проверяет: есть ли переменная var в var_table?
bool Symbol_table::is_declared(string var)
{
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

//------------------------------------------------------------------------------

// Ф-ция define_name() добавляет пару (var, val) в var_table
double Symbol_table::define_name(string var, double val, bool is_constant)
{
    if (is_declared(var))
        error("define_name: ", var + " повторное объявление");
    var_table.push_back(Variable(var, val, is_constant));
    return val;
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
        :kind(ch), name(n) { }     // и 'Имя-переменная'
};

//------------------------------------------------------------------------------

const int num = 2; // Возможное количество лексем в буфере Token_stream

//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();         // Создает объект класса Token_stream,
                            // считывающий данные из потока cin
    Token get();            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
    void ignore(char c);    // Отбрасывает символы до
                            // символа *c* включительно

private:
    bool full;              // Имеется ли лексема в буфере?
    vector<Token> buffer;   // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------

// Конструктор изменяет индикатор full и инициализирует buffer пустым значением:
Token_stream::Token_stream()
    :full(false)     // Нет Token в буфере
{
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t)
{
    if (full && buffer.size()==num)
        error("putback: ","буфер заполнен!");
    buffer.push_back(t);     // Копируем t в буфер
    full = true;             // Буфер не пустой
}

//------------------------------------------------------------------------------

// Разновидности лексем
const char number = 8;      // Число
const char quit = 'q';      // Выход
const char print = ';';     // Печать
const char name = 'a';      // Переменная
const char let = 'L';       // Объявление
const char constante = 'C'; // Константа
const char help = 'h';      // Подсказка
const char ln = 'l';        // Натуральный логарифм

//------------------------------------------------------------------------------

// Ключевые слова
const string declkey = "let";       // Объявление
const string decl_const = "const";  // Константа
const string decl_help = "help";    // Подсказка
const string decl_ln = "ln";        // Натуральный логарифм

//------------------------------------------------------------------------------

// Функция-член get() формирует лексемы
Token Token_stream::get()
{
    if (full) {     // Есть готовый объект Token?
        // Используем FIFO
        Token t = buffer[0];
        if (buffer.size() <= 1) // В буфере остался 1 элемент?
        { buffer.clear(); full=false; }
        else
        { buffer.erase(buffer.begin());} // Удаляем [0] элемент
        return t;
    }

    char ch;
    cin.get(ch);    // Считывание данных с
                    // пробельными символами
    if (isspace(ch)) {
        if (ch == '\n')          // Есть возврат коретки?
            return Token(print); // Да - печать результата
        cin.putback(ch);
        cin >> ch;
    }

    switch (ch) {
    case quit:      // Для выхода
    case print:     // Для печати
    case '(': case ')':
    case '+': case '-':
    case '*': case '/':
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
                   (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;
            cin.putback(ch);
            if (s == declkey)
                return Token(let);          // Для объявления
            if (s == decl_const)
                return Token(constante);    // Для констант
            if (s == decl_help)
                return Token(help);         // Для подсказок
            if (s == decl_ln)
                return Token(ln);           // Для натурального
                                            // логарифма
            return Token(name, s);          // Для переменной
            
        }
        error("get: ", "неправильная лексема");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    // Сначала проверяем буфер:
    for (size_t i=0; i<buffer.size(); ++i) {
        if (full && c==buffer[i].kind) {
            full = false;
            buffer.clear();
            return;
        }
    }

    buffer.clear();
    full = false;

    // Теперь проверяем входные данные
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // Обеспечивает get() и putback() 

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

double expression(); // Объявление здесь, так как она вызывается в primary()

//------------------------------------------------------------------------------

// Имеем дело с ф-цией натурального логарифма и выражениями
double nature_logarifm()
{
    Token t = ts.get();
    if (t.kind != '(')
        error("nature_logarifm: ", "пропущена '('");
    double res = expression();

    t = ts.get();
    if (t.kind != ')')
        error("nature_logarifm: ", "пропущена ')'");
    return log(res);
}

//------------------------------------------------------------------------------

// Имеем дело с числами и выражениями
double primary()
{
    Token t = ts.get();           // Получаем следующую лексему
    switch (t.kind) {
    case '(':                     // Описание '(' выражение ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')  error("primary: ", "требуется ')'");
        return d;
    }
    case number:                  // Используем number для представления числа
        return t.value;           // Возвращаем значение числа
    case '-':
        return - primary();       // Унарный минус
    case '+':
        return primary();         // Унарный плюс
    case name:                    // Используем name для представления
                                  // имени переменной
        return st.get_value(t.name);
    case ln:
        return nature_logarifm();
    default:
        error("primary: ", "требуется первичное_выражение");
    }
}

//------------------------------------------------------------------------------

// Имеем дело с '*', '/', '%' 
double term()
{
    double left = primary();        // Считываем и вычисляем первичное_выражение
    Token t = ts.get();             // Получаем следующую лексему

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();      // Вычисляем первичное_выражение и умножаем
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("term: ","деление на нуль");
            left /= d;              // Вычисляем первичное_выражениеи и делим
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) error("term: ","деление на нуль");
            left = fmod(left, d); // x%y = x-y*int(x/y)
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
double expression()
{
    double left = term();       // Считываем и вычисляем Терм
    Token t = ts.get();         // Получаем следующую лексему

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();     // Вычисляем терм и суммируем
            t = ts.get();
            break;
        case '-':
            left -= term();     // Вычисляем терм и вычитаем
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

// Обрабатываем Имя = Выражение
// Объявление переменной с Именем с начальным значением, заданным Выражением
double declaration()
{
    bool is_constant = false;
    Token t = ts.get();
    if (t.kind == constante) // Является переменная константой?
        is_constant = true;

    t = ts.get();
    if (t.kind != name)
        error("declaration: ", "в объявлении ожидается имя переменной");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("declaration: ", "пропущен символ \"=\" в объявлении: "
                                + var_name);

    double d = expression();
    st.define_name(var_name, d, is_constant);
    return d;
}

//------------------------------------------------------------------------------

// Имеем дело с оператором присваивания и выражениями
double assignment(Token t)
{
    if (!st.is_declared(t.name))
        error("assignment: ", "необъявленная переменная " + t.name);
    string var_name = t.name;

    Token t1 = ts.get();
    // Если у нас нет оператора присваивания,
    // то необходимо вернуть в буфер две лексемы
    // 1 - имя переменной, 2 - оператор
    if (t1.kind != '=') {
        ts.putback(t);
        ts.putback(t1);
        return expression();
    }

    double var_val = expression();
    st.set_value(var_name,var_val); // Изменяем значение переменной
    return var_val;
}

//------------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let: case constante:
        ts.putback(t);
        return declaration(); // Объявление констант и переменных
    case name:                // Имя переменной
        return assignment(t);
    default:
        ts.putback(t);
        return  expression(); // Обработка выражений
    }
}

//------------------------------------------------------------------------------

const string promt = "> ";  // Приветствие
const string result = "= "; // Используется для указания на то,
                            // Что далее следует результат

//------------------------------------------------------------------------------

// Цикл вычисления инструкций
void calculate()
{
    while (cin)
    try
    {
        cout << promt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();   // "Съедает ';'"
        if (t.kind == quit) return;
        if (t.kind == help)                     // Подсказка
        { cout << "Подсказка\n";}
        else {
            ts.putback(t);
            cout << result << statement() << '\n';
        }
    }
    catch (exception& e) {
        cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();
    }
    
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        // Предопределенные имена
        st.define_name("pi", 3.1415926535,true);
        st.define_name("e", 2.7182818284);

        calculate();
        keep_window_open("~~");
        return 0;
    }
    catch (...) {
        cerr << "Упс: неизвестное исключение!\n";
        keep_window_open("~~");
        return 2;
    }
}

//-----------------------------------------------------------------------------
