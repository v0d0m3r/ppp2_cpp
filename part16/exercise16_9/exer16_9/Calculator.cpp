//------------------------------------------------------------------------------

#include "Calculator.hpp"

//------------------------------------------------------------------------------

namespace Calc_lib {

//------------------------------------------------------------------------------

double Symbol_table::get_value(const string& name)
{
    for (const auto& v : var_table)
        if (v.name == name) return v.value;
    error("get_value: ", "неопределенная переменная: " + name);
}

//------------------------------------------------------------------------------

void Symbol_table::set_value(const string& name, double val)
{
    for (auto& v : var_table)
        if (v.name==name && !v.is_const) {
            v.value = val;
            return;
        }
        else if (v.name==name && v.is_const) {
            error("set_value: нельзя изменять константу");
        }
    error("set_value: неопределенная переменная: " + name);
}

//------------------------------------------------------------------------------
// true, если переменная объявлена
bool Symbol_table::is_declared(const string& name)
{
    for (const auto& v : var_table)
        if (v.name == name) return true;
    return false;
}

//------------------------------------------------------------------------------
// Определение переменной
double Symbol_table::define_name(const string& name, double val,
                                 bool is_constant)
{
    if (is_declared(name))
        error("define_name: " + name + " повторное объявление");

    var_table.push_back(Variable(name, val, is_constant));
    return val;
}

//------------------------------------------------------------------------------

Token::Token_kind Recognize::operator() (const string& str) const
{
    for (size_t i=0; i < keywords.size(); ++i)
        if (keywords[i] == str)
            switch (i) {
            case Keyword_kind::let:
                return Token::let;
            case Keyword_kind::constante:
                return Token::constante;
            case Keyword_kind::help:
                return Token::help;
            case Keyword_kind::ln:
                return Token::ln;
            default:
                error("Ошибка распознавания ключевых слов!");
            }
    return Token::none;
}

//------------------------------------------------------------------------------

void Token_stream::putback(const Token& t)
{
    if (full && buffer.size() == num)
        error("putback: буфер заполнен!");

    buffer.push_back(t);     // Копируем t в буфер
    full = true;             // Буфер не пустой
}

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
    source.get(ch); // Считывание данных с
                    // пробельными символами
    if (isspace(ch)) {
        if (ch == '\n')          // Есть возврат коретки?
            return Token(Token::print); // Да - печать результата
        source.putback(ch);
        source >> ch;
    }

    switch (ch) {
    case Token::quit:      // Для выхода
        return Token(Token::quit);
    case Token::print:     // Для печати
        return Token(Token::print);
    case '(': case ')':
    case '+': case '-':
    case '*': case '/':
    case '%': case '=':
        return Token(ch);   // Символ представляет сам себя
    case '.':               // Число с плавающей точкой может
                            // начинаться с точки
    // Числовой литерал
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        source.putback(ch);    // Возвращаем цифру во входной поток
        double val;
        source >> val;         // Считываем число с плавающей точкой
        return Token(number,val);
    }
    default:
        if (isalpha(ch)) {

            string s = "";
            s += ch;
            while (source.get(ch) &&
                   (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;
            source.putback(ch);

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

Calculator::Calculator()
{

}

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
