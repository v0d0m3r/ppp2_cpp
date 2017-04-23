//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Numb_dig_name {
public:
    Numb_dig_name();
    int number;             // число
    vector<int> dig;        // список цифр числа
    vector<string> name;    // список имен цифр
                            // согласно своему разряду
    void data_clear();      // очистка информации о числе
};

//------------------------------------------------------------------------------

Numb_dig_name::Numb_dig_name()
    :number(0)
{
}

//------------------------------------------------------------------------------

void Numb_dig_name::data_clear()
{
    number = 0;
    dig.clear();
    name.clear();
}

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
    if (full) error("putback()","буфер заполнен!");
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
    cin >> ch;    // >> пропускает пробельные символы

    switch (ch) {
    case ';':    // Завершение выражения
    case 'q':    // Для выхода
        t = Token(ch);   // Символ представляет сам себя
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        int val = 0;
        val = ch - '0';
        t = Token('8',val);
        break;
    }
    default:
        error("неверная лексема");
    }
    return t;
}

//------------------------------------------------------------------------------

Token_stream ts;        // Обеспечивает get() и putback()

//------------------------------------------------------------------------------
// ф-ция unit_name() узнает в каком падеже разряд "единиц"
string unit_name(int dig)
{
    switch (dig) {
    case 0: case 5: case 6: case 7: case 8: case 9:
        return "единиц";
    case 1:
        return "единица";
    default:
        return "единицы";
    }
}

//------------------------------------------------------------------------------
// ф-ция tens_name() узнает в каком падеже разряд "десяток"
string tens_name(int dig)
{
    switch (dig) {
    case 0: case 5: case 6: case 7: case 8: case 9:
        return "десяток";
    case 1:
        return "десятка";
    default:
        return "десятки";
    }
}

//------------------------------------------------------------------------------
// ф-ция tens_name() узнает в каком падеже разряд "сотен"
string hundred_name(int dig)
{
    switch (dig) {
    case 0: case 5: case 6: case 7: case 8: case 9:
        return "сотен";
    case 1:
        return "сотня";
    default:
        return "сотни";
    }
}

//------------------------------------------------------------------------------
// ф-ция tens_name() узнает в каком падеже разряд "тысяч"
string thousand_name(int dig)
{
    switch (dig) {
    case 5: case 6: case 7: case 8: case 9:
        return "тысяч";
    case 1:
        return "тысяча";
    default:
        return "тысячи";
    }
}

//------------------------------------------------------------------------------
// ф-ция what_is_name() узнает имя цифры по разряду
string what_is_name(int dig, int rank)
{
    string name_dig;
    switch (rank) {
    case 3:
        name_dig = thousand_name(dig);
        break;
    case 2:
        name_dig = hundred_name(dig);
        break;
    case 1:
        name_dig = tens_name(dig);
        break;
    case 0:
        name_dig = unit_name(dig);
        break;
    default:
        error("Неверное количество цифр в числе!");
    }
    return name_dig;
}

//------------------------------------------------------------------------------
// ф-ция data_processing() обрабатывает полученные цифры
Numb_dig_name data_processing(Numb_dig_name ndn)
{

    int count = ndn.dig.size()-1;   // степень десятки для
                                    // получения числа
    for(size_t i=0; i<ndn.dig.size(); ++i)
    {
        ndn.number = ndn.number+ndn.dig[i]*pow(10,count); // формула получения полного целого числа
        ndn.name.push_back(what_is_name(ndn.dig[i],count)); // определение имени цифры
        --count;
    }
    return ndn;
}

//------------------------------------------------------------------------------

Numb_dig_name result()
{
    Token t = ts.get();
    if (t.kind=='8' && t.value==0)
        error("Число не может начинаться с '0'");
    else
        ts.putback(t);

    Numb_dig_name ndn;
    for (int i=0; i<5; ++i) {
        t = ts.get();
        if (t.kind=='8' && i!=4) // цифры могут быть с индексом от 0 до 3
            ndn.dig.push_back(t.value); // получаем очередную цифру
        else if(t.kind==';' && i!=0) // ";" и не первый символ
        {
            ts.putback(t); // возвращаем лексему в поток
            break;
        }
        else
            error("Ошибка ввода!");
    }

    return data_processing(ndn); // обработка введеных цифр
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        Numb_dig_name ndn; // полные данные о числе
        cout << "Введите число (от одного до\n"
             << "четырех разрядов). Для обработки числа\n"
             << "используйте символ \";\".\nДля выхода из программы"
             << "используйте символ \"q\"\n";

        while (cin) {
            // cout << "> ";
            Token t = ts.get();
            if (t.kind == 'q') break; // 'q' для выхода
            if (t.kind == ';')        // ';' для "печати сейчас"
            {
                cout << ndn.number << " - это ";      // выводим число типа int
                for (size_t i=0; i<ndn.dig.size(); ++i)
                    cout << ndn.dig[i] << ' '        // выводим цифры и
                         << ndn.name[i] << ' ';      // значения цифр в числе
                cout << '\n';
                ndn.data_clear();   // очистка данных

                t = ts.get();
                if (t.kind == 'q') break;
                else
                    ts.putback(t);
            }
            else
                ts.putback(t);
            ndn = result();
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
