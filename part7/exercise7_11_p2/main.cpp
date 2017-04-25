/*
Переработка программы
Глава: 4
Задание: 19

Грамматика для ввода:
Главный_отчет:
        Отчет_недели
    	Вывод
    	Выход
    	Главный_отчет Отчет_недели
    	Отчет_недели Вывод Отчет_недели

Вывод:
    	";"    
        "\n"

Выход:
    	"q"

Отчет_недели:
        Отчет_за_день

Отчет_за_день:
        День_недели Число

Число:
        Литерал_целое_число
*/

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Day {
public:
    string name;   // Наименование Дня
    int value;     // Значение
    Day(string n, int val):name(n),value(val){}
};

//------------------------------------------------------------------------------

class Day_table {
public:    
    void add(Day d);            // Добавляет День в хранилище
    void print(string name);    // Печатает данные Дня
    Day_table() {}
private:
    vector<Day> day_table;      // Хранилище Дней
};

//------------------------------------------------------------------------------

Day_table dt;

//------------------------------------------------------------------------------

void Day_table::add(Day d)
{
    day_table.push_back(d);
}

//------------------------------------------------------------------------------

void Day_table::print(string name)
{
    int sum = 0;
    cout << "Значения " << name << ":\n";
    for (size_t i=0; i<day_table.size(); ++i)
        if (day_table[i].name == name)
        {
            cout << day_table[i].value << '\t';
            sum += day_table[i].value;
        }
    cout << "\nсумма:" << sum << '\n';
}

//------------------------------------------------------------------------------

class Token {
public:
    char kind;          	// Разновидность лексемы
    int value;    		// Для чисел: значение
    string day;
    Token(char ch)              // Получает лексему из символа (";", q и т.д.)
        :kind(ch){ }
    Token(char ch, int val)         // Формирует лексему
        :kind(ch), value(val) { }   // число
};

//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();
    Token get();            // Получает объект Token из потока
    void putback(Token t);  // Возвращает Token обратно в поток
    void ignore(char c);    // Отбрасывает символы до
                            // символа *c* включительно
    char find(string unknown_day);  // Является ли лексема днём недели?

private:
    bool full;              // Имеется ли лексема в буфере?
    Token buffer;           // Здесь хранится лексема после
                            // вызова putback()
};

//------------------------------------------------------------------------------

// Конструктор изменяет индикатор full и инициализирует buffer пустым значением:
Token_stream::Token_stream()
    :full(false), buffer(0) // Нет Token в буфере
{
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t)
{
    if (full) error("putback: ","буфер заполнен!");
    buffer = t;     // Копируем t в буфер
    full = true;    // Буфер не пустой
}

//------------------------------------------------------------------------------

// Разновидности лексем
constexpr char number = 8;      // Число
constexpr char quit = 'q';      // Выход
constexpr char print = ';';     // Печать
constexpr char monday = 'M';    // Понедельник
constexpr char thuesday = 'T';  // Вторник
constexpr char wednesday = 'W';	// Среда
constexpr char thursday = 't';  // Четверг
constexpr char friday = 'F';    // Пятница
constexpr char saturday = 'S';  // Суббота
constexpr char sunday = 's';    // Воскресенье

//------------------------------------------------------------------------------

// Ключевые слова
// Понедельник
vector<string> mon_name; 
// Вторник
vector<string> thues_name; 
// Среда
vector<string> wed_name; 
// Четверг
vector<string> thur_name; 
// Пятница
vector<string> frid_name; 
// Суббота
vector<string> sat_name; 
// Воскресенье
vector<string> sun_name; 

//------------------------------------------------------------------------------

// Ф-ция do_names заполняет ключевые слова обозначающие День
void do_names()
{
    mon_name.push_back("Monday");
    mon_name.push_back("Mon");
    mon_name.push_back("monday");

    thues_name.push_back("Thuesday");
    thues_name.push_back("Thue");
    thues_name.push_back("thuesday");

    wed_name.push_back("Wednesday");
    wed_name.push_back("Wed");
    wed_name.push_back("wednesday");

    thur_name.push_back("Thursday");
    thur_name.push_back("Thur");
    thur_name.push_back("thursday");

    frid_name.push_back("Friday");
    frid_name.push_back("Fri");
    frid_name.push_back("friday");

    sat_name.push_back("Saturday");
    sat_name.push_back("Sat");
    sat_name.push_back("saturday");

    sun_name.push_back("Sunday");
    sun_name.push_back("Sun");
    sun_name.push_back("sunday");
}

//------------------------------------------------------------------------------

// Поиск Дня
char Token_stream::find(string unknown_day)
{
    for (const string& s : mon_name)
        if (s == unknown_day) return monday;
    for (const string& s : thues_name)
        if (s == unknown_day) return thuesday;
    for (const string& s : wed_name)
        if (s == unknown_day) return wednesday;
    for (const string& s : thur_name)
        if (s == unknown_day) return thursday;
    for (const string& s : frid_name)
        if (s == unknown_day) return friday;
    for (const string& s : sat_name)
        if (s == unknown_day) return saturday;
    for (const string& s : sun_name)
        if (s == unknown_day) return sunday;
    error("find: ", "неправильная лексема");
}

//------------------------------------------------------------------------------

// Функция-член get() формирует лексемы
Token Token_stream::get()
{
    if (full) {     // Есть готовый объект Token?
        full=false; // Убираем его из буфера и возвращаем
        return buffer;
    }

    char ch;
    cin.get(ch);                 // Считывание данных с
                                 // пробельными символами
    if (isspace(ch)) {
        if (ch == '\n')          // Есть возврат коретки?
            return Token(print); // Да - печать результата
        cin.putback(ch);
        cin >> ch;
    }

    switch (ch) {
    case quit:                   // Для выхода
    case print:                  // Для печати
        return Token(ch);        // Символ представляет сам себя
    // Числовой литерал
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch); // Возвращаем цифру во входной поток
        int val;
        cin >> val;      // Считываем число с плавающей точкой
        return Token(number,val);
    }
    default:
        if (isalpha(ch)) {
            string s = "";
            s += ch;
            while (cin.get(ch) &&
                   isalpha(ch)) s+=ch;
            cin.putback(ch);
            return Token(find(s));
        }
        error("get: ", "неправильная лексема");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
{
    // Сначала проверяем буфер:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // Теперь проверяем входные данные
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

// Имеем дело с числом 
void add_day(string name)
{
    char ch;
    cin.get(ch);
    if (ch != ' ')
        error("week_report: ", "пропущен пробел");
    cin.putback(ch);

    Token t = ts.get();
    if (t.kind != number)
        error("week_report: ", "пропущено число!");
    dt.add(Day(name, t.value));
}

//------------------------------------------------------------------------------

// Печать отчета за всю неделю
void print_all()
{
    dt.print(mon_name[0]);
    dt.print(thues_name[0]);
    dt.print(wed_name[0]);
    dt.print(thur_name[0]);
    dt.print(frid_name[0]);
    dt.print(sat_name[0]);
    dt.print(sun_name[0]);
}

//------------------------------------------------------------------------------

// Имее дело с Днями
void week_report()
{
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case monday:
            add_day(mon_name[0]);
            t = ts.get();
            break;
        case thursday:
            add_day(thues_name[0]);
            t = ts.get();
            break;
        case wednesday:
            add_day(wed_name[0]);
            t = ts.get();
            break;
        case thuesday:
            add_day(thues_name[0]);
            t = ts.get();
            break;
        case friday:
            add_day(frid_name[0]);
            t = ts.get();
            break;
        case saturday:
            add_day(sat_name[0]);
            t = ts.get();
            break;
        case sunday:
            add_day(sun_name[0]);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            print_all();
            return;
        }
    }
}

//------------------------------------------------------------------------------

const string promt = "> ";    // Приветствие
const string result = "******* РЕЗУЛЬТАТ *******\n";

//------------------------------------------------------------------------------

// Цикл получения отчета за неделю
void big_report()
{
    while (cin)
    try
    {
        cout << promt;                          // Приветствие
        Token t = ts.get();
        while (t.kind == print) t = ts.get();   // "Съедает ';'"
        if (t.kind == quit) return;             // Выход
        ts.putback(t);
        cout << result;
        week_report();
    }
    catch (exception& e) {
        cerr << "ошибка: " << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();                        // Очистка ошибочных данных
    }
}

//------------------------------------------------------------------------------

int main()
{
    try {
        do_names();	// Доступные имена дней для ввода
        big_report();
        keep_window_open("~~");
        return 0;
    }
    catch (...) {
        cerr << "неизвестное исключение!\n";
        keep_window_open("~~");
        return 2;
    }
}

//------------------------------------------------------------------------------
