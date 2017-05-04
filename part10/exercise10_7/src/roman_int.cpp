//------------------------------------------------------------------------------

#include "roman_int.hpp"

//------------------------------------------------------------------------------

Roman_int::Roman_int():integer{0}
{
}

//------------------------------------------------------------------------------

Roman_int::Roman_int(string rom)
    : integer{roman_to_int(rom)}
{
}

//------------------------------------------------------------------------------

constexpr char terminator = '|';

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Roman_int& r)
{
    string s;
    for (char ch; is.get(ch); ) {
        if (!isalpha(ch)) { // Считали не букву
            is.unget();
            //is.clear(ios_base::failbit); // Поток сделали ошибочным
            break;
        }
        s += ch;
    }
    end_of_loop(is, terminator, "Неправильное завершение ввода");
    r = Roman_int{s};
    return is;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Roman_int& r)
{
    return os << int_to_roman(r.as_int());
}

//------------------------------------------------------------------------------

int roman_to_int(string &roman)
{
    constexpr int max_duplic = 3;   // Максимальное число повторений
                                    // одной римской цифры в числе
    vector<int> digits;
    // Переводим каждую римскую цифру в int
    for (size_t i=0; i < roman.size(); ++i)
        digits.push_back(get_digit(roman[i]));

    int duplicates = 0;
    int result = 0;
    int difference = 0;
    int product = 0;
    int dig_count = digits.size() - 1;
    for (size_t i=0; i < digits.size(); ++i) {
        if (i != static_cast<size_t>(dig_count)) {
            if (digits[i] < digits[i+1]) {  // Цифра слева меньше цифры справа
                product = digits[i] * 10;
                if (product < digits[i+1])  // 10*цифра_слева меньше цифры справа
                    error("roman_to_int: ", "Неправильная запись римского числа!");
                difference = digits[i+1] - digits[i];
                result += difference;
                i = i + 1;
            }
            else
                result += digits[i];
        }
        else
            result += digits[i];

        if (i != 0) // Проверяем на повтор цифр в числе
            (digits[i] == digits[i-1]) ? ++duplicates
                                       : duplicates=0;
        if (duplicates == max_duplic)
            error("roman_to_int: ", "Более трех одинаковых цифр подряд!");
    }
    return result;
}

//------------------------------------------------------------------------------

const int max_digit = 4000;

//------------------------------------------------------------------------------

string int_to_roman(int digit)
{
    /*
      В класической системе римских цифр число стоящее справа
   (то есть из которого вычитается) должно быть не больше чем,
   то что слева умноженное на десять. То есть то же число 99
   надо переводить буквально XC(90 = 100 - 10) + IX (9 = 10 - 1) = XCIX.
   То есть 49 нельзя записывать как IL, только как LXIX.
   Есть ещё одно правило. Нельзя делать повторения четырёх цифр подряд
   (исключение составляет цифра четыре, которую изображают в часах как
   IIII для лучшего восприятия), то есть число 40 нельзя записывать как XXXX,
   а только как LX. Из всех этих правил вытекает, что максимальное число,
   которое можно записать римскими цифрами есть MMMCMXCIX = 3999.
       */
    string  tmp;
    int base = 0;
    if (digit<0 || digit>max_digit)
        return ("err");
    while (digit > 0)  {
        base = get_base(digit);
        if (digit >= 9*base) {
            tmp += get_roman(base);
            tmp += get_roman(base*10);
            digit -= 9*base;
        }
        else if (digit >= 5*base) {
            tmp += get_roman(5*base) ;
            digit -= 5*base ;
        }
        else if (digit >= 4*base) {
            tmp += get_roman(base);
            tmp += get_roman(5*base);
            digit -= 4*base;
        }
        while (digit >= base) {
            tmp += get_roman(base);
            digit -= base;
        }
    }
    return tmp;
}

//------------------------------------------------------------------------------

enum Roman_digit {
    roman_i = 1, roman_v = 5, roman_x = 10, roman_l = 50,
    roman_c = 100, roman_d = 500, roman_m = 1000
};

//------------------------------------------------------------------------------
// get_base() находит нижнюю границу интервала (между цифрами),
// которому принадлежит входное число
int get_base(int digit)
{
    if (digit>=roman_i && digit<roman_x)
        return roman_i;
    else if (digit>=roman_x && digit<roman_c)
        return roman_x;
    else if (digit>=roman_c && digit<roman_m)
        return roman_c;
    else if (digit>=roman_m && digit<max_digit)
        return roman_m;
    error("get_base: ","Неизвестный случай!");
}

//------------------------------------------------------------------------------

vector <char> ch_roman_tb {
    'I', 'V', 'X', 'L',
    'C', 'D', 'M'
};
vector <int> roman_digit {
    1, 5, 10, 50, 100, 500, 1000
};

//------------------------------------------------------------------------------

int get_roman(int digit)
{
    if (ch_roman_tb.size() != roman_digit.size())
        error("get_digit: ",
              "Не совпадают размеры roman_digit и ch_roman_tb");
    for (size_t i=0; i < ch_roman_tb.size(); ++i)
        if (digit == roman_digit[i])
            return ch_roman_tb[i];
    error("get_roman: ", "неправильное представление числа");
}

//------------------------------------------------------------------------------

int get_digit(char ch)
{
    if (ch_roman_tb.size() != roman_digit.size())
        error("get_digit: ",
              "Не совпадают размеры roman_digit и ch_roman_tb");
    for (size_t i=0; i < ch_roman_tb.size(); ++i)
        if (ch == ch_roman_tb[i])
            return roman_digit[i];
    error("get_digit: ", "неправильное представление римского числа");
}

//------------------------------------------------------------------------------

void end_of_loop(istream& is, char term, const string& message)
{
    if (is.eof()) {         // Конец ввода
        is.clear();
        return;
    }
    if (is.fail()) {        // Некорректное состояние
        is.clear();
        char c;
        if (is >> c && c==term) return; // Является ли введеный символ
                                        // символом завершения ввода
        error("end_of_loop: ", message);
    }
}

//------------------------------------------------------------------------------
