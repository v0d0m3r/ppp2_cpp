//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Elem_variant {
public:
    char operation;       // операция перестановка или сочетание
    int element;          // элементы перестановок/сочетаний
    int variant;          // варианты перестановок/сочетаний
    Elem_variant(char ch, int elem, int var)     // формирует лексему парой "8" и число
        :operation(ch), element(elem), variant(var) { }
};

//------------------------------------------------------------------------------

class Token {
public:
    char kind;          // разновидность лексемы
    int value;          // для чисел: значение
    Token(char ch)      // получает лексему из символа (';', q)
        :kind(ch), value(0) { }
    Token(char ch, int val)     // формирует лексему парой "8" и число
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();         // Создает объект класса Token_stream,
                            // считывающий данные из потока cin
    Token get();            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
private:
    bool full;              // имеется ли лексема в буфере?
    Token buffer;           // здесь хранится лексема после
                            // выхода putback()
};

//------------------------------------------------------------------------------

Token_stream::Token_stream()
    :full(false), buffer(0)     // нет Token в буфере
{
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t)
{
    if (full) error("буфер заполнен!");
    buffer = t;     // копируем t в буфер
    full = true;    // буфер заполнен
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {
        full=false;
        return buffer;
    }

    Token t{' '};

    char ch;
    cin >> ch;

    switch (ch) {
    case 'c': case 'C':
        t = Token('c');
        break;
    case 'P': case 'p':
        t = Token('p');
        break;
    case ';':
    case 'q':
    case ',': case '(': case ')':
        t = Token(ch);
        break;
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        int val;
        cin >> val;
        t = Token('8',val);
        break;
    }
    default:
        error("неверная лексема");
    }
    return t;
}

//------------------------------------------------------------------------------

Token_stream ts;

//------------------------------------------------------------------------------
// ф-ция half_expression() считывает и обрабатывает половину выражения до ','
pair<char, int> half_expression()
{
    Token t = ts.get();
    cout << "***** " <<t.kind << " *****\n";
    if(t.kind!='p' && t.kind!='c') // у нас есть перестановка
                                   // или сочетание?
        error("Выражение должно начинаться с 'P' или 'C'!");

    char operation = t.kind;

    t = ts.get();
    if (t.kind!='(')
        error("отсутствует '('");

    t = ts.get();
    if (t.kind!='8')
        error("отсутствует первый аргумент");
    return pair<char, int>(operation, t.value);
}

//------------------------------------------------------------------------------

Elem_variant parser()
{
    constexpr int max_fact = 12;
    auto left = half_expression(); // получаем количество

    Elem_variant ev{' ', 0, 0};

    Token t = ts.get();
    switch(t.kind) {
    case ',':
    {
        t = ts.get();
        if (t.kind!='8')
            error("отсутствует второй аргумент!");

        int right = t.value; // получаем количество вариантов
        if (left.second < right)
            error("Количество элементов перестановки"
                  " меньше требуемых вариантов перестановок!");
        if (left.second > max_fact)
            error("Слишком большое число элементов!");

        t = ts.get();
        if (t.kind!=')')
            error("пропущена ')'");

        t = ts.get();
        if (t.kind!=';')
            error("пропущена ';'");
        ts.putback(t);

        ev = Elem_variant(left.first,left.second,right); // возвращаем обработанные данные
        break;
    }
    default:
        error("отсутствует ','");
    }
    return ev;
}

//------------------------------------------------------------------------------
// расчет факториала
int factorial(int n)
{
    int i = 0;
    for (i = n - 1; i > 1; i--)
        n *= i;

    return (n == 0) ? 1 : n;
}

//------------------------------------------------------------------------------
// вычисление перестановок
int permutation(Elem_variant ev)
{
    int res = 0;
    int expression1 = 0;
    int expression2 = 0;

    expression1 = factorial(ev.element);
    expression2 = factorial(ev.element - ev.variant);
    res = expression1 / expression2;
    return res;
}

//------------------------------------------------------------------------------
// вычисление сочетаний
int combination(Elem_variant ev)
{
    int res = 0;
    int expression1 = 0;
    int expression2 = 0;

    expression2 = factorial(ev.variant);
    expression1 = permutation(ev);
    res = expression1 / expression2;
    return res;
}

//------------------------------------------------------------------------------

// получание результата
int result()
{
    Elem_variant ev = parser(); // обработка данных

    int res = 0;
    switch (ev.operation) {
    case 'p':
        res = permutation(ev); // расчет перестановок
        break;
    case 'c':
        res = combination(ev); // расчет сочетаний
        break;
    default:
        error("Невероятная ошибка!");
    }
    return res;
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        int val = 0; // полные данные о числе
        cout << "Введите P(a,b); для подсчета количества перестановок\n"
                "или C(a,b); для подсчета количества сочетаний\n"
                "где a и b целые числа до 12"
                "\nДля выхода из программы "
                "используйте символ \"q\"\n";

        while (cin) {
            Token t = ts.get();
            if (t.kind == 'q') break; // 'q' для выхода
            if (t.kind == ';')        // ';' для "печати сейчас"
            {
                cout << "= " << val << '\n';
                t = ts.get();
                if (t.kind == 'q') break;
                else
                    ts.putback(t);
            }
            else
                ts.putback(t);
            val = result();
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
}

//-----------------------------------------------------------------------------
