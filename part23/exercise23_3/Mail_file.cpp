//------------------------------------------------------------------------------

#include "Mail_file.hpp"

//------------------------------------------------------------------------------

Mail_file::Mail_file(const string& n)
    // Открывает файл с именем n
    // Считывает строки из файла в n
    // Находит в lines сообщения и помещает их в m;
    // для простоты полагаем, что каждое сообщение
    // заканчивается строкой "----"
{
    ifstream in{n}; // Открываем файл
    if (!in) throw Bad_mail_file{"Не удалось открыть файл: " + n};

    string marker{"----"};
    string s;
    if (!getline(in, s) || s==marker)
        throw Bad_mail_file{"Некоректное начало файла!"};
    lines.push_back(s);

    while (getline(in, s)) {            // Создаем вектор строк
        if (s==marker && lines.back()==marker)
            throw Bad_mail_file{"Два marker подряд!"};
        lines.push_back(s);
    }

    auto first{lines.begin()};          // Создаем вектор сообщений

    for (auto p{lines.begin()}; p != lines.end(); ++p)
        if (*p == marker) {             // Конец сообщения
            m.push_back(Message{first, p});
            first = p+1;                // Строка "----" не является
                                        // частью сообщения
        }

    if (m.begin() == m.end())
        throw Bad_mail_file{"Нет писем!"};
}

//------------------------------------------------------------------------------

enum {
    addr=1, subj = 2
};

bool find_from_addr(const Message* m, string& s)
{
    if (m == nullptr)
        throw runtime_error{"Bad message"};

    regex address{R"(From: (.*))"};

    for (const auto& x : *m) {
        smatch matches;
        if (regex_match(x, matches, address)) {
            s = matches[addr];
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

bool find_subject(const Message* m, string& s)
{
    if (m == nullptr)
        throw runtime_error{"Bad message"};

    regex subject{R"(Subject: (FW: |Re: )?(.*))"};

    for (const auto& x : *m) {
        smatch matches;
        if (regex_match(x, matches, subject)) {
            s = matches[subj];
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------
