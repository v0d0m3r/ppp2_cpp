//------------------------------------------------------------------------------

#ifndef TABLE_FILE_HPP
#define TABLE_FILE_HPP

//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename Target, typename Source>
Target m_to(const Source& arg)
{
    stringstream interpreter;
    Target result;
    if (       !(interpreter << arg)    // Запись arg в поток
            || !(interpreter >> result) // Чтение result из потока
            || !(interpreter >> std::ws).eof())
        throw runtime_error{"сбой в m_to<>()"};
    return result;
}

//------------------------------------------------------------------------------

/*struct Table_file {
    string name;                 // Имя файла
    string head;                 // Заголовок
    vector<string> rows;         // Строки по порядку
    Table_file(const string& n); // Чтение файла n в строки
    Table_file begin() const { return rows.begin(); }
    Table_file end()   const { return rows.end(); }
};*/

//------------------------------------------------------------------------------

#endif // TABLE_FILE_HPP

//------------------------------------------------------------------------------
