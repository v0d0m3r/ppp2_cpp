#ifndef ROMAN_INT_H
#define ROMAN_INT_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Roman_int
{
public:
    Roman_int();
    Roman_int(string rom);
    int as_int() const { return integer; }
private:
    int integer;    // Представление римского числа
};

ostream& operator<<(ostream& os, const Roman_int& r);
istream& operator>>(istream& is, Roman_int& r);

int roman_to_int(string& roman); // Преобразует входную строку
                                 // с римским выражением в целое число
string int_to_roman(int digit);
int get_digit(char ch);          // По римской цифре получает
                                 // соответствующее целое число
int get_roman(int digit);        // По целому числу получает
                                 // соответствующее римскую цифру
int get_base(int digit);
void end_of_loop(istream& is, char term, const string& message);

//------------------------------------------------------------------------------

#endif // ROMAN_INT_H
