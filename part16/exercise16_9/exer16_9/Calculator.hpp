#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

namespace Calc_lib {

//------------------------------------------------------------------------------

struct Variable {
    Variable(const string& n, double v,
             bool c = false)
        :name{n}, value{v}, is_const{c}  { }

    string name;    // Имя переменной
    double value;   // Значение переменной
    bool is_const;  // Является ли переменная
                    // константой?
};

//------------------------------------------------------------------------------

struct Symbol_table {
    Symbol_table() {}

    // Получить значение переменной
    double get_value(const string& name);

    // Изменить значение переменной
    void set_value(const string& name, double val);

    // true, если переменная объявлена
    bool is_declared(const string &name);

    // Объявление перемменной
    double define_name(const string &name, double val,
                       bool is_constant = false);
private:
    vector<Variable> var_table;         // Хранилище переменных
};

//------------------------------------------------------------------------------

struct Token {
    enum Token_kind {
        number    = 8,    // Число
        quit      = 'q',  // Выход
        print     = ';',  // Печать
        var       = 'a',  // Переменная
        let       = 'L',  // Объявление
        constante = 'C',  // Константа
        help      = 'h',  // Подсказка
        ln        = 'l',  // Натуральный логарифм
        none      = 'n'
    };
    // Формирует лексему: парой "8" и число
    Token(Token_kind kk, double vv = 0)
        : k{narrow_cast<char>(kk)}, v{vv} { }
    // Формирует лексему kind и имя переменной
    Token(Token_kind kk, const string& nn)
        : k{narrow_cast<char>(kk)}, v{0}, n{nn} {}
    // Получает лексему из символа (+, -, * и т.д.)
    Token(char kk)
        : k{kk}, v{0} {}

    char kind() const { return k; }
    void set_kind(Token_kind kk) { k =  kk; }

    double value() const { return v; }
    void set_value(double vv) { v =  vv; }

    string name() const { return n; }
    void set_name(const string& nn) { n =  nn; }

private:
    char k;     // Разновидность лексемы
    double v;   // Значение
    string n;   // Имя переменной
};

//------------------------------------------------------------------------------
// Распознает тип лексемы из строки
class Recognize {
public:
    enum Keyword_kind {
        let, constante, help, ln
    };

    Recognize() {}

    Token::Token_kind operator() (const string& str) const;

private:
    const vector<string> keywords = {
        "let",   // Объявление
        "const", // Константа
        "help",  // Подсказка
        "ln",    // Натуральный логарифм
    };
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream(istream& is)
        : source{is} {}

    Token get();                  // Получает объект Token из потока
    void putback(const Token& t); // Возвращает Token обратно в поток
    void ignore(char c);          // Отбрасывает символы до
                                  // символа *c* включительно

    static constexpr int max{2};  // Максимальный размер лексем
                                  // в буфере
    operator bool();

private:
    istream& source;
    bool full{false};             // true, если буфер занят
    vector<Token> buffer;         // Здесь хранится лексема после
                                  // вызова putback()
    Recognize recognize;

    Token get_from_buffer();

};

//------------------------------------------------------------------------------

class Calculator
{
public:
    enum Facilities { promt = '>', result = '=' };

    Calculator(istream& is, ostream& ost);

    void calculate();

private:
    Token_stream ts;
    ostream& os;
    Symbol_table st;

    double expression();
    double primary();
    double term();
    double nature_logarifm();
    double declaration();
    double assignment(const Token& t);
    double statement();
    void clean_up_mess();
};

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif // CALCULATOR_HPP
