//------------------------------------------------------------------------------

#include "name_pairs.h"

//------------------------------------------------------------------------------

namespace Registr {

//------------------------------------------------------------------------------

string Name_pairs::member_names(int i) const
{
    if (i<0 || static_cast<size_t>(i)>=names.size())
        throw runtime_error("member_names: "
                            "Нет имени с индексом: " + i);
    return names[i];
}

//------------------------------------------------------------------------------

int Name_pairs::member_ages(int i) const
{
    if (i<0 || static_cast<size_t>(i)>=ages.size())
        throw runtime_error("member_ages: "
                            "Нет возвраста с индексом: " + i);
    return ages[i];
}

//------------------------------------------------------------------------------

void Name_pairs::read_names()
{
    cout << "Введите Имена через пробел\n";
    char ch;
    char buffer = 0;
    // Считывает входные данные:
    // буквы для постоения имен, пробельные символы
    while(cin.get(ch) &&
          (isalpha(ch) || isspace(ch))) {
        switch (ch) {
        case eof: case '\n': // Конец ввода
            if (n != "")
                names.push_back(n);
            n.clear();
            return;
        case ' ':           // Разделитель слов
            if (buffer==' ') { break; }
            buffer = ch;    // Хранит предыдущий символ
            names.push_back(n);
            n.clear();
            break;
        default:
            n+=ch; buffer=ch;
        }
    }
    throw runtime_error("read_names: "
                        "Неправильно введено Имя!");
}

//------------------------------------------------------------------------------

void Name_pairs::read_ages()
{
    cout << "Введите Возвраст (количество"
         <<   " лет) через пробел\n";
    for (size_t i=0; i<names.size(); ++i) {
        cin >> a;
        if (!cin || a<0 || a>120)
            throw runtime_error("read_ages: "
                                "Не верный возраст");
        ages.push_back(a);
    }
    a = 0.00;
    ignore();
}

//------------------------------------------------------------------------------

void Name_pairs::clear()
{
    names.clear();
    ages.clear();
}

//------------------------------------------------------------------------------

void Name_pairs::my_sort()
{
    vector<string> temp_n = names;
    vector<int> temp_ag = ages;
    sort(names.begin(), names.end());
    for (size_t i=0; i<names.size(); ++i)
      for (size_t j=0; j<names.size(); ++j)
      {
        if (names[i] == temp_n[j])
          ages[i] = temp_ag[j];
      }
}

//------------------------------------------------------------------------------

void ignore()
{
    char ch = 0;
    while (cin.get(ch))
        if (ch == '\n') return;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Name_pairs& np)
{
    int count = np.size_names();
    for (int i=0; i<count; ++i)
        os << np.member_names(i) << " - "
             << np.member_ages(i) << '\n';
    return os;
}

//------------------------------------------------------------------------------

bool operator==(const Name_pairs& a, const Name_pairs& b)
{
    if (a.size_names() != b.size_names())
        return false;
    const int& count = a.size_names();
    for (int i = 0; i < count; ++i)
        if ( a.member_names(i) != b.member_names(i)
             || a.member_ages(i) != b.member_ages(i))
            return false;
    return true;
}

//------------------------------------------------------------------------------

bool operator!=(const Name_pairs& a, const Name_pairs& b)
{
    return !(a==b);
}

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
