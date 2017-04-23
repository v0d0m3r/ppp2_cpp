//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
    char kind;          // Разновидность лексемы
    string value;
    Token(char ch)
        :kind(ch), value("") { }
    Token(char ch, string val)
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
    bool full;              // Имеется ли лексема в буфере?
    Token buffer;           // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------
// Конструктор изменяет индикатор full и
// инициализирует buffer пустым значением:
Token_stream::Token_stream()
:full(false), buffer(0)     // нет Token в буфере
{
}

//------------------------------------------------------------------------------
// putback()  помещает свой аргумент назад в поток лексем buffer:
void Token_stream::putback(Token t)
{
    if (full) error("буфер заполнен!");
    buffer = t;     // Копируем t в буфер
    full = true;    // Буфер заполнен
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {     // Есть готовый объект Token?
        full=false; // Убираем его из буфера и возвращаем
        return buffer;
    }

    Token t{' '};

    string str;
    cin >> str;
    cout << "Token_stream::get(): " << str << '\n';

    if (str=="and" || str=="or" || str=="but")  // Союзы "u"
        t = Token('u', str);
    else if (str=="birds" || str=="fish" || str=="c++")
        t = Token('n', str);
    else if (str=="rules" || str=="fly" || str=="swim")
        t = Token('v', str);
    else if (str=="." || str=="q")
        t = Token(str[0]);
    else if (str=="the")
        t = Token('a', str);
    else
        error("неверная лексема");
    return t;
}

//------------------------------------------------------------------------------

Token_stream ts;         // Обеспечивает get() и putback()s

//------------------------------------------------------------------------------

string article()
{
    string str = " ";
    Token t = ts.get();
    switch (t.kind) {
    case 'a':
        str += t.value;
        break;
    default:
        error("Не артикль " + t.value);
    }
    return str;
}

//------------------------------------------------------------------------------

string noun()
{
    string str = " ";
    Token t = ts.get();
    switch (t.kind) {
    case 'n':
        str += t.value;
        break;
    default:
        error("Не существительное");
    }
    return str;
}

//------------------------------------------------------------------------------

string verb()
{
    string str = " ";
    Token t = ts.get();
    switch (t.kind) {
    case 'v':
        str += t.value;
        break;
    default:
        error("Не глагол");
    }
    return str;
}

//------------------------------------------------------------------------------

string sentence()
{
    string left = article();
    left += noun();
    left += verb();
    Token t = ts.get();
    while(true) {
        switch(t.kind) {
        case 'u':
            left = left + " " + t.value;
            cout << "left: " << left << '\n';
            left += sentence();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        string val = "";
        cout << "Добро пожаловать в программу части речи!\n"
                "Для вывода результата\n"
                "используйте символ \".\".\nДля выхода из программы "
                "используйте символ \"q\"\n";
        while (cin) {
            Token t = ts.get();
            cout << "t.kind: " << t.kind << '\n'
                 << "t.value: " << t.value << '\n';
            if (t.kind == 'q') break; // 'q' for quit
            if (t.kind == '.')        // '.' for "print now"
            {
                if (val != "")
                    cout << "> " << "yes" << '\n';
            }
            else
                ts.putback(t);
            val = sentence();
        }
        keep_window_open();
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
