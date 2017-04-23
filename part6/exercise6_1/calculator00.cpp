//-----------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

class Token {
public:
    char kind;		// Разновидность лексемы
    double value;	// Для чисел: значение
    Token(char ch)	// Получает лексему из символа (+, -, * и т.д.)
        :kind(ch), value(0) { }
    Token(char ch, double val)      // Формирует лексему парой "8" и число
        :kind(ch), value(val) { }
};

//-----------------------------------------------------------------------------

Token get_token();
vector<Token> tok;
double search_number(char inp_symb);
char lastsymb = 'x';

//-----------------------------------------------------------------------------

double expression();
double term();
double primary();

//-----------------------------------------------------------------------------

int main()
{
    try {
        cout << "Введите выражение (разрешены +, -, * и /): ";
        while (cin)
            cout << '=' << expression() << '\n';
    }
    catch (exception& e) {
        cerr << "\nОшибка: " << e.what() << '\n';
        keep_window_open();
        return 1;
    }
    catch (...) {
        cerr << "Неизвестное исключение!\n";
        keep_window_open();
        return 2;
    }
    return 0;
}

//-----------------------------------------------------------------------------
// Чтение лексемы из cin
Token get_token()
{
    Token t{' '};

    char ch;
    cin >> ch;              // Оператор >> пропускает пробельные символы
    switch (ch) {
    case '(': case ')': case '+': case '-': case '*': case '/':
        t = Token(ch);      // Символ представляет сам себя
        break;
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);    // Возвращение цифры в cin
        double val;
        cin >> val;         // Чтение числа типа double
        t = Token('8',val); // '8' представляет лексему число
        break;
    }
    default:
        error("неправильный символ");
    }
    return t;
}

//-----------------------------------------------------------------------------

double search_number(char inp_symb)
{
    int integ_part = 0;         // Целая часть
    int fract_part = 0;         // Дробная часть
    double good_fract = 0;
    int comma_count = 1;        // На сколько позиций двигать запятую
    bool comma_flag = false;    // Флаг точки
    constexpr int factor = 10;  // Множитель
    double result = 0;

    for (bool i=false; !i;) {
        switch (inp_symb) {
        case '0':
            if (!comma_flag)
                integ_part = integ_part*factor+0;
            else
                fract_part = fract_part*factor+0;
            break;
        case '1':
            if (!comma_flag)
                integ_part = integ_part*factor+1;
            else
                fract_part = fract_part*factor+1;
            break;
        case '2':
            if (!comma_flag)
                integ_part = integ_part*factor+2;
            else
                fract_part = fract_part*factor+2;
            break;
        case '3':
            if (!comma_flag)
                integ_part = integ_part*factor+3;
            else
                fract_part = fract_part*factor+3;
            break;
        case '4':
            if (!comma_flag)
                integ_part = integ_part*factor+4;
            else
                fract_part = fract_part*factor+4;
            break;
        case '5':
            if (!comma_flag)
                integ_part = integ_part*factor+5;
            else
                fract_part = fract_part*factor+5;
            break;
        case '6':
            if (!comma_flag)
                integ_part = integ_part*factor+6;
            else
                fract_part = fract_part*factor+6;
            break;
        case '7':
            if (!comma_flag)
                integ_part = integ_part*factor+7;
            else
                fract_part = fract_part*factor+7;
            break;
        case '8':
            if (!comma_flag)
                integ_part = integ_part*factor+8;
            else
                fract_part = fract_part*factor+8;
            break;
        case '9':
            if (!comma_flag)
                integ_part = integ_part*factor+9;
            else
                fract_part = fract_part*factor+9;
            break;
        case '.':
            if (comma_flag) {
                i=true;
                lastsymb = inp_symb;
                error("вы ввели лишнюю точку");
            }
            else
                comma_flag=true;
            break;
        default:
            i=true;
            lastsymb = inp_symb;

            good_fract = fract_part;
            while (good_fract >= 1) {
                comma_count *= factor;
                good_fract /= double(factor);
            }
            good_fract = fract_part*1.0/comma_count;
            result = integ_part + good_fract;
            break;
        }
        if (!i){
            cin>>inp_symb;
        }
    }
    return result;
}

//-----------------------------------------------------------------------------

double expression()
{
    double left = term();   // Считываем и вычисляем Терм
    Token t = get_token();  // Получаем следующую лексему
    for (;;) {
        switch (t.kind) {
        case '+':
            left += term(); // Вычисляем терм и суммируем
            t = get_token();
            break;
        case '-':
            left -= term(); // Вычисляем терм и вычитаем
            t = get_token();
            break;
        default:
            return left;    // Конец символов, + и - нет
        }                   // Возвращаем ответ
    }
}

//-----------------------------------------------------------------------------

double term()
{
    double left = primary();    // Считываем и вычисляем
                                // первичное_выражение
    Token t = get_token();      // Получаем следующую лексему
    for (;;) {
        switch (t.kind) {
        case '*':
            left *= primary();  // Вычисляем первичное_выражение и умножаем
            t = get_token();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)	error("деление на нуль");
            left /= d;          // Вычисляем первичное_выражениеи и делим
            t = get_token();
            break;
        }
        default:
            return left;        // Конец символов, * и / нет
        }                       // Возвращаем ответ
    }
}

//-----------------------------------------------------------------------------

double primary()
{
    Token t = get_token();  // Получаем следующую лексему
    double value = 0;
    switch (t.kind) {
    case '(':
    {
        value = expression();
        t = get_token();
        if (t.kind != ')') error("требуется \')\'");
        break;
    }
    case '8':               // Используем восьмерку для представления числа
        value = t.value;
        break;
    default:
        error("требуется первичное_выражение");
    }
    return value;
}

//-----------------------------------------------------------------------------
