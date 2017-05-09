//------------------------------------------------------------------------------

#include "punctstream.hpp"

//------------------------------------------------------------------------------

Punct_stream& Punct_stream::operator>>(string& s)
{
    while (!(buffer >> s)) {    // Попытка прочитать данные
                                // из потока buffer
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();

        string line;
        getline(source, line);  // Считываем строку line
                                // из потока source
        // При необходимости заменяем символы
        for (char& ch : line)
            if (is_whitespace(ch))
                ch = ' ';           // Преобразуем пробел
            else if (!sensetive)
                ch = tolower(ch);   // Преобразуем в нижний регистр

        buffer.str(line);           // Записываем строку в поток
    }
    return *this;
}

//------------------------------------------------------------------------------

bool Punct_stream::is_whitespace(char c) const
{
    for (const char& w : white)
        if (c == w) return true;
    return false;
}

//------------------------------------------------------------------------------

Punct_stream::operator bool()
{
    if (buffer.good() && source.eof())  // Когда поток ввода закрыт,
        return true;                    // а строковый поток имеет данные

    return !(source.fail() || source.bad()) && source.good();
}

//------------------------------------------------------------------------------
