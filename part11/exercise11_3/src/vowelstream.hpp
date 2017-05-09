#ifndef VOWELSTREAM_H
#define VOWELSTREAM_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Vowel_stream { // Аналогичен istream, но пользователь
                     // может задавать гласные символы
public:
    Vowel_stream(istream& is)
        :source{is}, sensetive{true} {}
    void vowel_symb(const string& s)    // Делает s строкой
        {   vowel = s;   }              // гласных символов
    void add_vowel(char c)              // Добавляет символ в
        {   vowel += c;   }             // набор гласных
    bool is_vowel_symb(char c) const;   // Входит ли c в набор
                                        // гласных символов?
    void case_sensitive(bool b) { sensetive = b; }
    bool is_case_sensitive()    { return sensetive; }

    Vowel_stream& operator>>(string& s);
    operator bool();
private:
    istream& source;        // Источник символов
    istringstream buffer;   // Буфер для форматирования
    string vowel;           // Гласные символы
    bool sensetive;         // Чувствителен ли поток регистру?
};

//------------------------------------------------------------------------------

#endif // VOWELSTREAM_H
