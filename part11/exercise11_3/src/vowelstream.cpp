//------------------------------------------------------------------------------

#include "vowelstream.hpp"

//------------------------------------------------------------------------------

Vowel_stream& Vowel_stream::operator>>(string& s)
{
    while (!(buffer >> s)) {    // Попытка прочитать данные
                                // из потока buffer
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();

        string line;
        getline(source, line);  // Считываем строку line
                                // из потока source

        // При необходимости отбрасываем гласные символы
        string tmp;
        for (char& ch : line)
            if (!sensetive && !is_vowel_symb(ch)) {
                ch = tolower(ch);   // Преобразуем в нижний регистр
                tmp += ch;
            }
            else if (!is_vowel_symb(ch))
                tmp += ch;          // Добавляем согласные в строку

        line = tmp;
        buffer.str(line);           // Записываем строку в поток
    }
    return *this;
}

//------------------------------------------------------------------------------

bool Vowel_stream::is_vowel_symb(char c) const
{
    for (const char& v : vowel)
        if (c == v) return true;
    return false;
}

//------------------------------------------------------------------------------

Vowel_stream::operator bool()
{
    if (buffer.good() && source.eof())  // Когда поток ввода закрыт,
        return true;                    // а строковый поток имеет данные

    return !(source.fail() || source.bad()) && source.good();
}

//------------------------------------------------------------------------------
