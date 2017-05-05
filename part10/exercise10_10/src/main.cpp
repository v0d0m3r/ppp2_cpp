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
    Ввод_из_файла

Объявление:
    "let" Имя "=" Выражение

Объявление_констант:
    "const" Имя "=" Выражение

Присваивание:
    Имя "=" Выражение

Ввод_из_файла:
    "from" Имя_файла Выражение

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

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

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
    double get_value(string s); // Добавить переменную в хранилище
    void set_value(string s, double d); // Изменить значение переменной
    bool is_declared(string var); // Переменная была уже добавлена?
    // Добавление (объявление) перемменной в хранилище
    double define_name(string var, double val, bool is_constant=NULL);
    Symbol_table() {}
private:
    vector<Variable> var_table; // Хранилище переменных
};

//------------------------------------------------------------------------------

Symbol_table st;

//------------------------------------------------------------------------------

double Symbol_table::get_value(string s)
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get_value: ", "неопределенная переменная " + s);
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
            error("set_value: ", "Нельзя присвоить "
                                 "значение константы" + s);
        }
    error("set_value: ", "неопределенная переменная " + s);
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
        :kind(ch), name(n) { }     //  и 'Имя-переменная'
};

//------------------------------------------------------------------------------

const int num = 2; // Возможное количество лексем в буфере Token_stream

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();         // Создает объект класса Token_stream,
                            // считывающий данные из потока cin
    Token get(istream& ist);            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
    void ignore(char c, istream &ist);  // Отбрасывает символы до
                                        // символа *c* включительно
    string iname;

private:
    bool full;              // Имеется ли лексема в буфере?
    vector<Token> buffer;   // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------

// Конструктор изменяет индикатор full и инициализирует buffer пустым значением:
Token_stream::Token_stream()
:full(false)     // нет Token в буфере
{
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t)
{
    if (full && buffer.size()==num) error("putback(): ","буфер заполнен!");
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
const char from_file = 'f'; // Ввод из файла
const char to_file = 'o';   // Вывод в файл

//------------------------------------------------------------------------------

// Ключевые слова
const string declkey = "let";           // Объявление
const string decl_const = "const";      // Константа
const string decl_help = "help";        // Подсказка
const string decl_ln = "ln";            // Натуральный логарифм
const string decl_from_file = "from";   // Ввод из файла
const string decl_to_file = "to";       // Ввод из файла

//------------------------------------------------------------------------------

// Функция-член get() формирует лексемы
Token Token_stream::get(istream &ist)
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
    ist.get(ch);    // Считывание данных с
                    // пробельными символами
    if (isspace(ch)) {
        if (ch == '\n') // Есть возврат коретки?
            return Token(print); // Да - печать результата
        ist.putback(ch);
        ist >> ch;
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
            ist.putback(ch); // Возвращаем цифру во входной поток
            double val;
            ist >> val;      // Считываем число с плавающей точкой
            return Token(number,val);
        }
    default:
        if (isalpha(ch)) {
            string s = "";
            s += ch;
            while (ist.get(ch) &&
                (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;
            ist.putback(ch);
            if (s == declkey)
                return Token(let);          // Для объявления
            if (s == decl_const)
                return Token(constante);    // Для констант
            if (s == decl_help)
                return Token(help);         // Для подсказок
            if (s == decl_ln)
                return Token(ln);           // Для натурального
                                            // логарифма
            if(s == decl_from_file)
                return Token(from_file);
            if(s == decl_to_file)
                return Token(to_file);
            return Token(name, s);          // Для переменной
        }
        // Конец ввода?
        if (ist.eof()) return Token(print);
        error("get(): ", "непрвильная лексема");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c, istream& ist)
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
    for (char ch; ist >> ch;)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // Обеспечивает get() и putback()

//------------------------------------------------------------------------------

void clean_up_mess(istream& ist)
{
    ts.ignore(print, ist);
}

//------------------------------------------------------------------------------

double expression(istream &ist);

//------------------------------------------------------------------------------

// Имеем дело с ф-цией натурального логарифма и выражениями
double nature_logarifm(istream &ist)
{
    Token t = ts.get(ist);
    if (t.kind != '(')
        error("nature_logarifm: ", "Пропущена '('");
    double res = expression(ist);

    t = ts.get(ist);
    if (t.kind != ')')
        error("nature_logarifm: ", "Пропущена ')'");
    return log(res);
}

//------------------------------------------------------------------------------

// Имеем дело с числами и выражениями
double primary(istream& ist)
{
    Token t = ts.get(ist);             // Получаем следующую лексему
    switch (t.kind) {
    case '(':
        {
            double d = expression(ist);
            t = ts.get(ist);
            if (t.kind != ')')  error("primary(): ", "требуется ')'");
            return d;
        }
    case number:                     // Используем number для представления числа
        return t.value;              // Возвращаем значение числа
    case '-':
        return - primary(ist);       // Унарный минус
    case '+':
        return primary(ist);         // Унарный плюс
    case name:                       // Используем name для представления
        return st.get_value(t.name); // имени переменной
    case ln:
        return nature_logarifm(ist);
    default:
        error("primary(): ", "требуется первичное_выражение");
    }
}

//------------------------------------------------------------------------------

// Имеем дело с '*', '/', '%'
double term(istream& ist)
{
    double left = primary(ist);     // Считываем и вычисляем первичное_выражение
    Token t = ts.get(ist);          // Получаем следующую лексему

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary(ist);   // Вычисляем первичное_выражение и умножаем
            t = ts.get(ist);
            break;
        case '/':
            {
                double d = primary(ist);
                if (d == 0) error("term: ","деление на нуль");
                left /= d;          // Вычисляем первичное_выражениеи и делим
                t = ts.get(ist);
                break;
            }
        case '%':
            {
                double d = primary(ist);
                if (d == 0) error("term: ","деление на нуль");
                left = fmod(left, d); // x%y = x-y*int(x/y)
                t = ts.get(ist);
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
double expression(istream& ist)
{
    double left = term(ist);    // Считываем и вычисляем Терм
    Token t = ts.get(ist);      // Получаем следующую лексему

    while(true) {
        switch(t.kind) {
        case '+':
            left += term(ist);  // Вычисляем терм и суммируем
            t = ts.get(ist);
            break;
        case '-':
            left -= term(ist);  // Вычисляем терм и вычитаем
            t = ts.get(ist);
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
double declaration(istream& ist)
{
    bool is_constant = false;
    Token t = ts.get(ist);
    if (t.kind == constante) // Является переменная константой?
        is_constant = true;

    t = ts.get(ist);
    if (t.kind != name)
        error("declaration: ", "в объявлении "
                               "ожидается имя переменной");
    string var_name = t.name;

    Token t2 = ts.get(ist);
    if (t2.kind != '=')
        error("declaration: ", "пропущен символ = "
                               "в объявлении " + var_name);

    double d = expression(ist);
    st.define_name(var_name, d, is_constant);
    return d;
}

//------------------------------------------------------------------------------

// Имеем дело с оператором присваивания и выражениями
double assignment(Token t, istream& ist)
{
    if (!st.is_declared(t.name))
        error("assignment: ", "необъявленная переменная "+t.name);
    string var_name = t.name;

    Token t1 = ts.get(ist);
    // Если у нас нет оператора присваивания,
    // то необходимо вернуть в буфер две лексемы
    // 1 - имя переменной, 2 - оператор
    if (t1.kind != '=') {
        ts.putback(t);
        ts.putback(t1);
        return expression(ist);
    }

    double var_val = expression(ist);
    st.set_value(var_name,var_val); // Изменяем значение переменной
    return var_val;
}

//------------------------------------------------------------------------------

double statement(istream& ist)
{
    Token t = ts.get(ist);
    switch (t.kind) {
    case let: case constante:
        ts.putback(t);
        return declaration(ist); // Объявление констант и переменных
    case name:                   // Имя переменной
        return assignment(t, ist);
    default:
        ts.putback(t);
        return  expression(ist); // Обработка выражений
    }
}

//------------------------------------------------------------------------------

const string promt = "> ";    // приветствие
const string result = "= ";   // используется для указания на то,
                              // что далее следует результат
const string path = "./";

//------------------------------------------------------------------------------
// Цикл вычисления инструкций
void calculate(istream& ist, ostream& ost, bool is_ifstream)
{
    for(char end_loop; ist >> end_loop;)
    try {
        ist.unget();        
        Token t = ts.get(ist);
        while (t.kind == print) t = ts.get(ist); // "Съедает ';'"
        switch (t.kind) {
        case quit: case from_file: case to_file:
            ts.putback(t);
            return;
        case help:
            ost << "help\n";
            break;
        default:
            ts.putback(t);
            ost << result << statement(ist) << '\n';
        }
        if (!is_ifstream) cout << promt;
    }
    catch (exception& e) {
        ost << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess(ist);
        if (!is_ifstream) cout << promt;
    }
}

//------------------------------------------------------------------------------

// true, когда выводим в консоль символ promt
bool is_promt(Token& t, istream& ist)
{
    t = ts.get(ist);
    if (t.kind==quit || t.kind==from_file) {
        ts.putback(t);
        return false;
    }
    ts.putback(t);
    return true;
}

//------------------------------------------------------------------------------

void get_file_name(istream& ist,string& fname)
{
    Token t = ts.get(ist);
    if (t.kind != name)
        error("from_file: ", "в объявлении "
                             "ожидается имя переменной");
    fname = path + t.name;
}

//------------------------------------------------------------------------------
// Определение потока для вывода
void what_is_ostream(istream& ist, bool is_ifstream)
{
    // Выполняем, пока есть данные для ввода
    for (char end_loop; ist >> end_loop;) {
        ist.unget();
        Token t = ts.get(ist);
        switch (t.kind) {
        case quit: case from_file:
            ts.putback(t);
            return;
        case to_file:
        {
            string oname;
            get_file_name(ist, oname);
            ofstream ofs{oname, ios_base::app};
            if (!ofs)
                error("what_is_ostream: ", "Не могу открыть: " + oname);
            calculate(ist, ofs, is_ifstream);  // Вывод с помощью  файлового
                                               // потока
            if (!is_promt(t, ist)) return;
            break;
        }
        default:
            ts.putback(t);
            calculate(ist, cout, is_ifstream); // Вывод с помощью консольного
                                               // потока
            if (!is_promt(t, ist)) return;
        }
        if (!is_ifstream) cout << promt;       // Не выводим символ promt,
                                               // когда лексемы: quit и from_file
    }
}

//------------------------------------------------------------------------------
// Определение потока для ввода
void what_is_istream()
{
    bool promt_is = true;   // true, когда выводим
                            // в консоль символ promt
    while (cin)
    try {
        if (promt_is) cout << promt;
        Token t = ts.get(cin);
        switch (t.kind) {
        case quit:          // Выходим
            return;
        case from_file:     // Получена лексема "ввод_из_файла"
        {
            string iname;
            get_file_name(cin, iname);
            ifstream ifs{iname};
            if (!ifs)
                error("from_file: ", "Не могу открыть: " + iname);
            what_is_ostream(ifs, true);     // Ввод с помощью  файлового
                                            // потока
            promt_is = is_promt(t, ifs);
            break;
        }
        default:
            ts.putback(t);
            what_is_ostream(cin, false);    // Ввод с помощью консольного
                                            // потока
            promt_is = is_promt(t, cin);
            break;
        }
    }
    catch (exception& e) {
        cout << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess(cin);
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    // Предопределенные имена
    st.define_name("pi", 3.1415926535,true);
    st.define_name("e", 2.7182818284);

    what_is_istream();
    keep_window_open("~~");
    return 0;
}
catch (...) {
    cerr << "Упс: неизвестное исключение!\n";
    keep_window_open("~~");
    return 2;
}

//-----------------------------------------------------------------------------
