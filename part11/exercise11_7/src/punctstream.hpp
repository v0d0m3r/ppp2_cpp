#ifndef PUNCTSTREAM_H
#define PUNCTSTREAM_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

struct Word_replace {   // Хранит слова для замены
    string short_form;  // Сокращенная форма слова (найти)
    string full_form;   // Полная форма слова (заменить)
};

//------------------------------------------------------------------------------

class Punct_stream { // Аналогичен istream, но пользователь
                     // может задавать пробельные символы
public:
    Punct_stream(istream& is)
        :source{is}, sensetive{true},
          quotes{false} {}
    void whitespace(const string& s)    // Делает s строкой
        {   white = s;   }              // пробельных символов
    void add_white(char c)              // Добавляет символ в
        {   white += c;   }             // набор пробельных
    bool is_whitespace(char c) const;   // Входит ли c в набор
                                        // пробельных символов?
    // Делает w списком слов для замены
    void wordreplace(const vector<Word_replace>& w)
        {    wr_tb = w;   }
    // Добавляет слова в список для замены
    void add_wordreplace(const Word_replace& w)
        {   wr_tb.push_back(w);   }
    void find_replace(string& line);    // Находит и заменяет слова
                                        // из списка
    void analyzer_ch(char& ch, const char& prev,
                     const char& next);

    void case_sensitive(bool b) { sensetive = b; }
    bool is_case_sensitive()    { return sensetive; }
    bool is_quotes(char c);

    Punct_stream& operator>>(string& s);
    operator bool();
private:
    istream& source;            // Источник символов
    istringstream buffer;       // Буфер для форматирования
    string white;               // Пробельные символы
    bool sensetive;             // Чувствителен ли поток регистру?
    bool quotes;                // Чувствителен ли поток к пробельным
                                // символам
    vector<Word_replace> wr_tb; // Список слов для замены
};

//------------------------------------------------------------------------------

#endif // PUNCTSTREAM_H
