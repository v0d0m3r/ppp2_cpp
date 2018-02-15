//------------------------------------------------------------------------------

#include "Mail_file.hpp"

//------------------------------------------------------------------------------

void addr_match_input()
{
    string fname;
    cout << "Please, input file name: ";
    cin >> fname;

    Mail_file mfile{fname}; // Инициализируем mfile
                            // данными из файла

    // Сначала собираем сообщения, поступившие от каждого
    // отправителя, в объекте класса multimap:
    multimap<string, const Message*> sender;

    for (const auto& m : mfile) {
        string s;
        if (find_from_addr(&m, s))
            sender.insert(make_pair(s, &m));
    }

    string greeting{"Введите адрес отправителя: "};
    cout << greeting;
    cin >> ws;
    for (string str; getline(cin, str); ) {
        // Теперь обходим мультиотображение и извлекаем темы
        // сообщений, поступивших от John Doe:
        auto pp{sender.equal_range(str)};
        if (pp.first != pp.second) {
            cout << "Найдены следующие темы:\n";
            for (auto p{pp.first}; p != pp.second; ++p) {
                string s;
                if (find_subject(p->second, s))
                    cout << s << '\n';
            }
        }
        else
            cout << "Нет ниодного отправителя: "
                 << str << '\n';
        cout << greeting;
    }
    cout << "\nЗавершение работы!\n";
}

//------------------------------------------------------------------------------

int main()
try
{
    addr_match_input();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
