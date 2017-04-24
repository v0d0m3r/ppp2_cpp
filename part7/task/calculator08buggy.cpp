//------------------------------------------------------------------------------
/*
    calculator08buggy.cpp

    Helpful comments removed.

    We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/
//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token 
{
public:
    char kind;
    double value;
    string name;
    Token(char ch)      // Получает лексему из символа (+, -, * и т.д.)
        :kind(ch), value(0) { }
    Token(char ch, double val)     // Формирует лексему парой "8" и число
        :kind(ch), value(val) { }
    Token(char ch, string n)       // Формирует лексему kind
        :kind(ch), name(n) { }     // и 'Имя-переменная'
};

//------------------------------------------------------------------------------

class Token_stream
{	
public:
    Token_stream() :full(0), buffer(0) { }  // Инициализируем буфер и
                                            // и индикацию пустым значением
    Token get();	// Получение очередной лексемы
                        // Помещает лексему обратно в поток
    void putback(Token t) { buffer=t; full=true; }
    void ignore(char);  // Пропускает входные данные
                        // до заданного символа
private:
    bool full;          // Индикатор буфера
    Token buffer;       // Буфер с одной лексемой
};

//------------------------------------------------------------------------------

const char let = 'L';		 // Представляет лексему
                                 // ключевое слово объявления
const string decley = "let";
const char quit = 'Q';
const string quit_name = "exit";
const char print = ';';
const char number = '8';	 // Лексема - число
const char name = 'a';		 // Лексема - имя переменной(типа Variable)

const char sqrt_kind = 'S';	 // Лексема - корень квадратный
const string sqrt_name = "sqrt";
const char pow_kind = 'P';	 // Лексема - возведение в квадрат
const string pow_name = "pow";

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full)	// Буфер пуст?
    { full=false; return buffer; } // Да - возвращаем лексему
    // Нет - пытаемся считать следующую лексему
    char ch;
    cin >> ch;
    switch (ch) {
    case '(': case ')':
    case '+': case '-':
    case '*': case '/':
    case '%':
    case '=':
    case print:
    case ',':
        return Token(ch); // Символ представляет сам себя
    case '.':             // Числа с плавающей точкой
                          // могут начинаться с "."
    // Числовой литерал
    case '0': case '1': case '2': case '3':	case '4':
    case '5': case '6': case '7': case '8':	case '9':
    {
        cin.putback(ch);	// Возвращаем число в поток
        double val;
        cin >> val;		// Считываем число полностью
        return Token(number,val);
    }
    default:
        if (isalpha(ch)) {
            string s;
            s += ch;
            while(cin.get(ch) &&
                  (isalpha(ch) || isdigit(ch))) s+=ch;
            cin.putback(ch);
            if (s == decley)
                return Token(let);	 // Ключевое слово "let"
            else if (s == sqrt_name)
                return Token(sqrt_kind); // Ключевое слово "sqrt"
            else if (s == pow_name)
                return Token(pow_kind);  // Ключевое слово "pow"
            else if (s == quit_name)
                return Token(quit);      // Ключевое слово "exit"
            return Token(name,s);	 // Имя переменной
        }
        string bad_token = "";
        bad_token += ch;
        error("get: ", "неправильная лексема: "+bad_token);
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    // Символ конца отбрасывания в буфере?
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // Проверяем входные данные
    char ch;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

class Variable {
public:
    string name;	// Имя
    double value;	// Значение
    Variable(string n, double v) :name(n), value(v) { }
};

//------------------------------------------------------------------------------

vector<Variable> var_table;	// Список переменных

//------------------------------------------------------------------------------

// Ф-ция get_value() получает значение переменной по её имени
double get_value(string s)
{
    for (size_t i = 0; i<var_table.size(); ++i)
        if (var_table[i].name == s) return var_table[i].value;
    error("get_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
{
    for (size_t i = 0; i<var_table.size(); ++i)
        if (var_table[i].name == s) {
            var_table[i].value = d;
            return;
        }
    error("set_value: ", "неопределенная переменная: " + s);
}

//------------------------------------------------------------------------------

// Ф-ция is_declared() проверяет была ли раньше объявлена переменная
bool is_declared(string s)
{
    for (size_t i = 0; i<var_table.size(); ++i)
        if (var_table[i].name == s) return true;
    return false;
}

//------------------------------------------------------------------------------

void define_name(string var, double val)
{
    if(is_declared(var))
        error("define_name: ", "повторное объявление переменной: "+var);
    var_table.push_back(Variable(var,val));
}


//------------------------------------------------------------------------------

Token_stream ts; // Поток лексем

//------------------------------------------------------------------------------

double expression();

//------------------------------------------------------------------------------

double sqrt_calc()
{
    Token t = ts.get();
    if (t.kind != '(') error("sqrt_calc: ", "требуется '('");

    double d = expression();
    t = ts.get();
    if (t.kind != ')') error("sqrt_calc: ", "требуется ')'");

    if (d >= 0)
        return sqrt(d);
    error("sqrt_calc: ", "нет корня из отрицательного числа!");
}

//------------------------------------------------------------------------------

double pow_calc()
{
    Token t = ts.get();
    if (t.kind != '(') error("pow_calc: ", "требуется '('");

    double d = expression(); // Получение первого аргумента
    t = ts.get();
    if (t.kind != ',') error("pow_calc: ", "требуется ','");

    int i = narrow_cast<int>(expression()); // Получение второго аргумента
    t = ts.get();
    if (t.kind != ')') error("pow_calc: ", "требуется ')'");
    return pow(d,i);
}

//------------------------------------------------------------------------------

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("primary: ", "требуется ')'");
        return d;
    }
    case '-':
        return - primary(); 		// Унарный минус
    case number:
        return t.value;			// Число
    case name:
        return get_value(t.name); 	// Имя переменной
                                        // Корень квадратный
    case sqrt_kind:
        return sqrt_calc();
                                        // Возведение в квадрат
    case pow_kind:
        return pow_calc();
    default:
        error("primary: ", "требуется первичное_выражение");
    }
}

//------------------------------------------------------------------------------

// Работает с *, /
double term()
{
    double left = primary();
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("term: ", "деление на нуль");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// Работает с +, -
double expression()
{
    double left = term();
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// Ф-ция declaration() объявлет переменные
double declaration()
{
    Token t = ts.get();
    if (t.kind != name) error("declaration: ", "в объявлении ожидается "
                                               "имя переменной");
    string var_name = t.name;
    if (is_declared(var_name)) error("declaration: ", var_name+" второе объявление");
    Token t2 = ts.get();
    if (t2.kind != '=') error("declaration: ", "пропущен символ = "
                                               "в объявлении " + var_name);
    double d = expression();
    define_name(var_name,d);
    return d;
}

//------------------------------------------------------------------------------

// Ф-ция statement() работает с объявлениями и выражениями
double statement()
{
    Token t = ts.get();
    switch(t.kind) {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------

void calculate()
{
    while(true) try {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t=ts.get();
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << endl;
    }
    catch(runtime_error& e) {
        cerr << "\nошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
{
    try {
        define_name("k", 1000);

        calculate();
        return 0;
    }
    catch (...) {
        cerr << "Неизвестное исключение\n";
        keep_window_open("~~");
        return 2;
    }
}

//------------------------------------------------------------------------------
