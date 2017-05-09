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
        const int& count = line.size()-1;
        for (size_t i=0; i < line.size(); ++i) {
            const char& prev = (i != 0) ? line[i-1] : 0;
            const char& next = (i == static_cast<size_t>(count))
                               ? 0 : line[i+1];
            char& ch = line[i];
            analyzer_ch(ch, prev, next);
        }
        find_replace(line);
        if (buffer.bad()) return *this;
        buffer.str(line);               // Записываем строку в поток
    }

    return *this;
}

//------------------------------------------------------------------------------

void Punct_stream::analyzer_ch(char& ch, const char& prev,
                               const char& next)
{
    if (!is_quotes(ch)) return;
    if (is_whitespace(ch)) {
        if (ch=='-' && isalpha(prev) && isalpha(next))
            return;
        else if (ch=='\'' && prev=='n' && next=='t')
            return;
        else ch = ' ';      // Преобразуем пробел
    }
    else if (!sensetive)
        ch = tolower(ch);   // Преобразуем в нижний регистр
}

//------------------------------------------------------------------------------

void Punct_stream::find_replace(string& line)
{
    buffer.str(line);
    line = "";
    string s;
    while (buffer >> s) {
        for (Word_replace& w : wr_tb)
            if (s == w.short_form)
                s = w.full_form + " ";
        line += " " + s;
    }
    if (!buffer.bad())
        buffer.clear();

}

//------------------------------------------------------------------------------

bool Punct_stream::is_whitespace(char c) const
{
    for (const char& w : white)
        if (c == w) return true;
    return false;
}

//------------------------------------------------------------------------------
// Включаем/выключаем режим "кавычек"
bool Punct_stream::is_quotes(char c)
{
    if (c == '"')
        quotes = (quotes) ? false : true;
    return quotes;
}

//------------------------------------------------------------------------------

Punct_stream::operator bool()
{
    if (buffer.good() && source.eof())  // Когда поток ввода закрыт,
        return true;                    // а строковый поток имеет данные

    return !(source.fail() || source.bad()) && source.good();
}

//------------------------------------------------------------------------------
