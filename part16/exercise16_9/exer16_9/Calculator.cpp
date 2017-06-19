//------------------------------------------------------------------------------

#include "Calculator.hpp"

//------------------------------------------------------------------------------

namespace Calc_lib {

//------------------------------------------------------------------------------

double Symbol_table::get_value(const string& name)
{
    for (const auto& v : var_table)
        if (v.name == name) return v.value;
    error("get_value: неопределенная переменная: " + name);
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
    if (full && buffer.size() == max)
        error("putback: буфер заполнен!");

    buffer.push_back(t);     // Копируем t в буфер
    full = true;             // Буфер не пустой
}

//------------------------------------------------------------------------------
// Формирует лексемы из буфера
Token Token_stream::get_from_buffer()
{
    Token t = buffer.front();
    if (buffer.size() <= 1) {
        buffer.clear();
        full = false;
    }
    else
        buffer.erase(buffer.begin());

    return t;
}

//------------------------------------------------------------------------------
// Функция-член get() формирует лексемы
Token Token_stream::get()
{
    // Есть готовый объект Token?
    if (full) return get_from_buffer();;

    char ch;
    source.get(ch);        // Считывание данных с
                           // пробельными символами
    if (isspace(ch)) {
        if (ch == '\n')    // Есть возврат коретки?
            return Token(Token::print);
        source.putback(ch);
        source >> ch;      // Пропускаем пробельные
    }
    if (!source) return Token(Token::quit);
    switch (ch) {
    case Token::quit: case Token::print:
    case Token::help:
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
        source.putback(ch); // Возвращаем цифру во входной поток
        double val;
        source >> val;      // Считываем число с плавающей точкой
        return Token(Token::number, val);
    }
    default:
        if (isalpha(ch)) {
            string s = "";
            s += ch;
            while (source.get(ch) &&
                   (isalpha(ch) || isdigit(ch) || ch=='_')) s += ch;
            source.putback(ch);

            Token::Token_kind tk = recognize(s);
            if (tk == Token::none)
                return Token(Token::var, s);
            return Token(tk);
        }
        error("get: неправильная лексема");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    // Сначала проверяем буфер:
    for (const auto& t : buffer)
        if (full && c==t.kind()) {
            full = false;
            buffer.clear();
            return;
        }

    buffer.clear();
    full = false;

    // Теперь проверяем входные данные
    char ch = 0;
    while (source >> ch)
        if (ch == c) return;
}

//------------------------------------------------------------------------------

Token_stream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
}

//------------------------------------------------------------------------------

Calculator::Calculator(istream &is, ostream &ost)
    : ts{is}, os{ost}
{

}

//------------------------------------------------------------------------------
// Имеем дело с '+' и '-'
double Calculator::expression()
{
    double left = term();       // Считываем и вычисляем Терм
    Token t = ts.get();         // Получаем следующую лексему

    while (true) {
        switch (t.kind()) {
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
// Имеем дело с '*', '/', '%'
double Calculator::term()
{
    double left = primary();      // Считываем и вычисляем первичное_выражение
    Token t = ts.get();           // Получаем следующую лексему

    while(true) {
        switch (t.kind()) {
        case '*':
            left *= primary();    // Вычисляем первичное_выражение и умножаем
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("term: деление на нуль");
            left /= d;            // Вычисляем первичное_выражениеи и делим
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) error("term: деление на нуль");
            left = fmod(left, d); // x%y = x-y*int(x/y)
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);        // Кладем t в поток лексем
            return left;
        }
    }
}

//------------------------------------------------------------------------------
// Имеем дело с числами и выражениями
double Calculator::primary()
{
    Token t = ts.get();           // Получаем следующую лексему
    switch (t.kind()) {
    case '(':                     // Описание '(' выражение ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind() != ')')  error("primary: требуется ')'");
        return d;
    }
    case Token::number:                  // Используем number для представления числа
        return t.value();           // Возвращаем значение числа
    case '-':
        return - primary();       // Унарный минус
    case '+':
        return primary();         // Унарный плюс
    case Token::var:                    // Используем name для представления
                                  // имени переменной
        return st.get_value(t.name());
    case Token::ln:
        return nature_logarifm();
    default:
        error("primary: требуется первичное_выражение");
    }
}

//------------------------------------------------------------------------------
// Имеем дело с ф-цией натурального логарифма и выражениями
double Calculator::nature_logarifm()
{
    Token t = ts.get();
    if (t.kind() != '(')
        error("nature_logarifm: пропущена '('");
    double res = expression();

    t = ts.get();
    if (t.kind() != ')')
        error("nature_logarifm: пропущена ')'");
    return log(res);
}

//------------------------------------------------------------------------------
// Обрабатываем Имя = Выражение
// Объявление переменной с Именем с начальным значением, заданным Выражением
double Calculator::declaration()
{
    bool is_constant = false;
    Token t = ts.get();
    if (t.kind() == Token::constante) // Является переменная константой?
        is_constant = true;

    t = ts.get();
    if (t.kind() != Token::var)
        error("declaration: в объявлении ожидается имя переменной");

    string var_name = t.name();

    Token t2 = ts.get();
    if (t2.kind() != Calculator::result)
        error("declaration: пропущен символ \"=\" в объявлении: "
              + var_name);

    double d = expression();
    st.define_name(var_name, d, is_constant);
    return d;
}

//------------------------------------------------------------------------------
// Имеем дело с оператором присваивания и выражениями
double Calculator::assignment(const Token& t)
{
    if (!st.is_declared(t.name()))
        error("assignment: необъявленная переменная " + t.name());

    string var_name = t.name();

    Token t1 = ts.get();
    // Если у нас нет оператора присваивания,
    // то необходимо вернуть в буфер две лексемы
    // 1 - имя переменной, 2 - оператор
    if (t1.kind() != Calculator::result) {
        ts.putback(t);
        ts.putback(t1);
        return expression();
    }

    double var_val = expression();
    st.set_value(var_name, var_val); // Изменяем значение переменной
    return var_val;
}

//------------------------------------------------------------------------------

double Calculator::statement()
{
    Token t = ts.get();
    switch (t.kind()) {
    case Token::let: case Token::constante:
        ts.putback(t);
        return declaration(); // Объявление констант и переменных
    case Token::var:          // Имя переменной
        return assignment(t);
    default:
        ts.putback(t);
        return  expression(); // Обработка выражений
    }
}

//------------------------------------------------------------------------------
// Цикл вычисления инструкций
void Calculator::calculate()
{
    while (ts)
    try
    {
        os << char(Calculator::promt) << ' ';
        Token t = ts.get();
        if (!ts) return;
        while (t.kind() == Token::print) t = ts.get();   // "Съедает ';'"
        if (t.kind() == Token::quit) return;
        if (t.kind() == Token::help)                     // Подсказка
        { os << "Подсказка\n"; }
        else {
            ts.putback(t);
            os << char(Calculator::result) << ' '
               << statement() << '\n';
        }
    }
    catch (exception& e) {
        os << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

void Calculator::clean_up_mess()
{
    ts.ignore(Token::print);
}

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
