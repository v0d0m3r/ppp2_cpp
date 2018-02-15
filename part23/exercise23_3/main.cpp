//------------------------------------------------------------------------------

#include "Mail_file.hpp"

//------------------------------------------------------------------------------

void example23_4()
try {
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

    // Теперь обходим мультиотображение и извлекаем темы
    // сообщений, поступивших от John Doe:
    auto pp{sender.equal_range(
                    "John Doe <jdoe@machine.example>")};
    for (auto p{pp.first}; p != pp.second; ++p) {
        string s;
        if (find_subject(p->second, s))
            cout << s << '\n';
        else
            cout << "Пропущена строка с темой!";
    }
}
catch(const Bad_mail_file& e) {
    cout << e.what() << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
    example23_4();
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
