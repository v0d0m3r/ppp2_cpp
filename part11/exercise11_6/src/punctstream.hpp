#ifndef PUNCTSTREAM_H
#define PUNCTSTREAM_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Punct_stream { // Аналогичен istream, но пользователь
                     // может задавать пробельные символы
public:
    Punct_stream(istream& is)
        :source{is}, sensetive{true}, quotes{false} {}
    void whitespace(const string& s)    // Делает s строкой
        {   white = s;   }              // пробельных символов
    void add_white(char c)              // Добавляет символ в
        {   white += c;   }             // набор пробельных
    bool is_whitespace(char c) const;   // Входит ли c в набор
                                        // пробельных символов?
    void case_sensitive(bool b) { sensetive = b; }
    bool is_case_sensitive()    { return sensetive; }
    bool is_quotes(char c);

    Punct_stream& operator>>(string& s);
    operator bool();
private:
    istream& source;        // Источник символов
    istringstream buffer;   // Буфер для форматирования
    string white;           // Пробельные символы
    bool sensetive;         // Чувствителен ли поток регистру?
    bool quotes;            // Чувствителен ли поток к пробельным
                            // символам
};

//------------------------------------------------------------------------------

#endif // PUNCTSTREAM_H
