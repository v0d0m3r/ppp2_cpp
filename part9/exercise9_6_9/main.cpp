// Глава №9, задание №6-9
//------------------------------------------------------------------------------

#include "library.h"

//------------------------------------------------------------------------------

void add_book(Library& library)
{
    cout << "**** ДОБАВЛЕНИЕ КНИГИ ****\n"
            "Введите ISBN:\n";
    string isbn;
    cin >> isbn;
    cout << "Введите название:\n";
    string title;
    cin >> title;
    cout << "Введите фамилию автора:\n";
    string soname_auth;
    cin >> soname_auth;
    cout << "Выбирите жанр:\n"
            "0 - фантастика;\n"
            "1 - проза;\n"
            "2 - переодическое издание;\n"
            "3 - биография;\n"
            "4 - детская литература.\n";
    int genre = -1;
    cin >> genre;
    switch (Genre(genre)) {
    case Genre::fan: case Genre::pros:
    case Genre::period: case Genre::biogr:
    case Genre::kid:
        break;
    default:
        error("main.cpp: add_book: ",
               "Несуществующий жанр!");
        break;
    }
    bool issue = false;
    Chrono::Date date;
    Book book{isbn, title,
                soname_auth, date, Genre(genre), issue};
    library.add_book(book);
}

//------------------------------------------------------------------------------

void add_client(Library& library)
{
    cout << "**** ДОБАВЛЕНИЕ КЛИЕНТА ****\n"
            "Введите имя пользователя:\n";
    string uname;
    cin >> uname;
    cout << "Введите номер карты:\n";
    int ncard = 0;
    cin >> ncard;    
    double memb_fee = 100;
    bool paid = false;
    Patron patron{uname, ncard,
                 memb_fee, paid};
    library.add_patron(patron);
}

//------------------------------------------------------------------------------

void buy_memb_fee(Library& library)
{
    cout << "**** УПЛАТА ВЗНОСА ****\n"
            "Введите номер "
            "карты пользователя:\n";
    int ncard;
    cin >> ncard;
    library.set_patron_paid(true, ncard);
}

//------------------------------------------------------------------------------

void give_book(Library& library)
{
    cout << "**** ВЫДАЧА КНИГИ ****\n"
            "Введите номер "
            "карты пользователя:\n";
    int ncard;
    cin >> ncard;
    cout << "Введите название книги:\n";
    string title;
    cin >> title;
    library.take_book(ncard, title);
}

//------------------------------------------------------------------------------

void print_debtors(Library& library)
{
    const vector<string>& debtors = library.get_debtors();
    cout << "Должники:\n";
    for (const string& s : debtors)
        cout << s << '\n';
}

//------------------------------------------------------------------------------

void set_memb_fee(Library& library)
{
    cout << "**** ДОБАВЛЕНИЕ КЛИЕНТА ****\n"
         << "Введите размер членского взноса:\n";
    double memb_fee = 0;
    cin >> memb_fee;
    library.set_memb_fee(memb_fee);
}

//------------------------------------------------------------------------------

void menu_lib()
{
    int menu_item = 0;
    Library library;
    while (true)
    try {
        cout << "Для работы с библиотекой "
             "введите номер пункта из меню:\n"
             "1 - добавить новую книгу;\n"
             "2 - добавить нового клиента;\n"
             "3 - уплатить членский взнос;\n"
             "4 - выдать новую книгу;\n"
             "5 - вывод должников;\n"
             "6 - вывод всех книг библиотеки;\n"
             "7 - изменить членские взносы;\n"
             "8 - выход.\n";
        cin >> menu_item;
        if (!cin)
            error("menu_lib: ", "Неправильный ввод пункта меню!");
        switch (menu_item) {
        case 1:
            add_book(library);
            break;
        case 2:
            add_client(library);
            break;
        case 3:
            buy_memb_fee(library);
            break;
        case 4:
            give_book(library);
            break;
        case 5:
            print_debtors(library);
            break;
        case 6:
            cout << "Книги, зарегистрированные в библиотеки:\n";
            library.print_inf_books();            
            break;
        case 7:
            set_memb_fee(library);
            break;
        case 8:
            return;
        default:
            error("menu_lib: ",
                  "Несуществующий пункт меню!");
        }
    }
    catch (exception& e) {
        cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        keep_window_open("~~");
    }
}

//------------------------------------------------------------------------------

int main()
{
    menu_lib();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

/* Тесты!
// КНИГИ!!!!!-----------------------------------
Book1
isbn - 1-1-1-a
title - The c programming language
soname - Babuin
Book2
isbn - 1-1-1-b
title - Ferrum
soname - Ugrin
Book3
isbn - 1-1-1-c
title - Evlampii
soname - Syrkov
Book4
isbn - 123-1-1-f
title - Frends
soname - Ivlev

// Клиенты!!!!!-----------------------------------
Patron1
username - vod
ncard - 123
username - java
ncard - 2
*/

































