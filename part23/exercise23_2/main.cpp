//------------------------------------------------------------------------------

#include "../example23/Mail_file.hpp"

//------------------------------------------------------------------------------

void subject_match_input()
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
        if (find_subject(&m, s))
            sender.insert(make_pair(s, &m));
    }

    string greeting{"Введите тему сообщения: "};
    cout << greeting;
    cin >> ws;
    for (string str; getline(cin, str); ) {
        // Теперь обходим мультиотображение и выводим
        // сообщения, с искомой темой:
        auto pp{sender.equal_range(str)};
        if (pp.first != pp.second) {
            cout << "Найдены следующие письма:\n";
            for (auto p{pp.first}; p != pp.second; ++p) {
                copy(p->second->begin(), p->second->end(),
                     ostream_iterator<string>{cout, "\n"});
                cout << "----\n";
            }
        }
        else
            cout << "Нет ниодного письма с темой: "
                 << str << '\n';
        cout << greeting;
    }
    cout << "\nЗавершение работы!\n";
}

//------------------------------------------------------------------------------

int main()
try
{
    subject_match_input();
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
