//------------------------------------------------------------------------------

#ifndef MAIL_FILE_HPP
#define MAIL_FILE_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"
#include <map>
#include <regex>

//------------------------------------------------------------------------------

using Line_iter = vector<string>::const_iterator;

class Message {     // Объект класса Message указывает
                    // на первую и последнюю строки сообщения
    Line_iter first;
    Line_iter last;

public:
    Message(Line_iter p1, Line_iter p2) : first{p1}, last{p2} {}
    Line_iter begin() const { return first; }
    Line_iter end()   const { return last; }
};

//------------------------------------------------------------------------------

struct Bad_mail_file : std::runtime_error
    // Класс для сообщений об ошибках при преобразовании строки
{
    Bad_mail_file(const string& msg)
        : runtime_error{"Bad Mail_file: " + msg} {}
};

//------------------------------------------------------------------------------

using Mess_iter = vector<Message>::const_iterator;

struct Mail_file {  // Mail_file хранит все строки из файла
                    // и упрощает доступ к сообщениям
    string name;                // Имя файла
    vector<string> lines;       // Строки по порядку
    vector<Message> m;          // Сообщение по порядку
    Mail_file(const string& n); // Чтение файла n в строки
    Mess_iter begin() const { return m.begin(); }
    Mess_iter end()   const { return m.end(); }
};

//------------------------------------------------------------------------------

// Ищет отправителя в объекте класса Message; возвращает значение true,
// если он найден; если найден, помещает отправителя в строку s
bool find_from_addr(const Message* m, string& s);

// Возвращает тему сообщения; если её нет, возвращает "":
string find_subject(const Message* m);

//------------------------------------------------------------------------------

inline int is_prefix(const string& s, const string& p)
    // Является ли строка p первой части строки s?
{
    int n = p.size();
    if (string(s, 0, n) == p) return n;
    return 0;
}

//------------------------------------------------------------------------------

#endif // MAIL_FILE_HPP

//------------------------------------------------------------------------------
