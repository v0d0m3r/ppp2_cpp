//------------------------------------------------------------------------------

#include "Mail_file.hpp"

//------------------------------------------------------------------------------

using mstring = basic_string<char>;

//------------------------------------------------------------------------------

template<typename T> string m_to_string(const T& t)
{
    ostringstream os;
    os << t;
    return os.str();
}

//------------------------------------------------------------------------------

struct bad_from_string : std::bad_cast
    // Класс для сообщений об ошибках при преобразовании строки
{
    // перекрывает what() из bad_cast
    const char* what() const noexcept override
    {
        return "некорректное преобразование из string";
    }
};

//------------------------------------------------------------------------------

template<typename T> T m_from_string(const string& s)
{
    istringstream is{s};
    T t;
    if (!(is>>t)) throw bad_from_string{};
    return t;
}

//------------------------------------------------------------------------------

void do_something(const string& s)
try
{
    int i{m_from_string<int>(s)};
    // ...
}
catch (const bad_from_string& e) {
    error("неверная строка ввода", s);
}

//------------------------------------------------------------------------------

template<typename Target, typename Source>
Target m_to(const Source& arg)
{
    stringstream interpreter;
    Target result;
    if (       !(interpreter << arg)    // Запись arg в поток
            || !(interpreter >> result) // Чтение result из потока
            || !(interpreter >> std::ws).eof())
        throw runtime_error{"сбой в to<>()"};
    return result;
}

//------------------------------------------------------------------------------

void example23_2()
{
    string s1{to_string(12.33)};
    string s2{to_string(1+5*6-99/7)};
    cout << "s1 == "   << s1 << "; "
         << "s2 == " << s2 << '\n';
    double d{m_from_string<double>("12.333")};
}

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

void example23_7()
{
    ifstream in{"./file"};                   // Входной файл
    if (!in) cerr << "Нет файла\n";

    regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"};  // Шаблон индекса
    // cout << "шаблон: " << pat << '\n';

    int lineno{0};
    for (string line; getline(in, line); ) { // Чтение строки
        ++lineno;
        smatch matches;
        if (regex_search(line, matches, pat)) {
            // Полное соответствие
            cout << lineno << ": " << matches[0] << '\n';
            if (1<matches.size() && matches[1].matched)
                // Подшаблон
                cout << "\t: " << matches[1] << '\n';
        }
    }
}

//------------------------------------------------------------------------------

// Получает из входного потока шаблон и набор строк;
// проверяет шаблон и ищет строки, содержащие его
void example23_8_7()
{
    regex pattern;

    string pat;
    cout << "введите шаблон: ";
    getline(cin, pat);          // Считываем шаблон

    try {
        pattern = pat;          // Проверка шаблона
        cout << "шаблон: " << pat << '\n';
    }
    catch (bad_exception) {
        cout << "Не корректное выражение: " << pat << '\n';
        exit(1);
    }

    cout << "введите строки:\n";
    int lineno{0};

    for (string line; getline(cin, line); ) {
        ++lineno;
        smatch matches;
        if (regex_search(line, matches, pattern)) {
            cout << "строка " << lineno << ": " << line << '\n';
            for (size_t i{0}; i < matches.size(); ++i)
                cout << "\tmatches[" << i << "]: "
                     << matches[i] << '\n';
        }
        else
            cout << "не соответсвует\n";
    }
}

//------------------------------------------------------------------------------

void example23_9()
{
    ifstream in{"table.txt"};   // Входной файл
    if (!in) error("Нет входного файла\n");

    string line;                // Входной буфер
    int lineno{0};

    regex header{R"(^[\w ]+(    [\w ]+)*$)"};
    regex row{R"(^[\w ]+(   \d+)(   \d+)(   \d+)$)"};

    if (getline(in, line)) {    // Проверка заголовка
        smatch matches;
        if (!regex_match(line, matches, header))
            error("нет заголовка");
    }

    // Итог по столбцам
    int boys{0};
    int girls{0};

    while (getline(in, line)) { // Проверка данных
        ++lineno;
        smatch matches;
        if (!regex_match(line, matches, row))
            error("неверная строка", to_string(lineno));

        if (in.eof()) cout << "Конец файла";

        // Проверка строки
        int curr_boy   = m_to<int>(matches[2]);
        int curr_girl  = m_to<int>(matches[3]);
        int curr_total = m_to<int>(matches[4]);

        if (curr_boy+curr_girl != curr_total)
            error("Неверная сумма в строке\n");

        if (matches[1] == "Alle klasser") { // Последняя строка
            if (curr_boy != boys)
                error("Количество мальчиков не сходится\n");
            if (curr_girl != girls)
                error("Количество девочек не сходится\n");
            if (!(in >> ws).eof())
                error("Символы после последней строки");
            return;
        }
        // Обновление итоговых значений
        boys  += curr_boy;
        girls += curr_girl;
    }
    error("Нет итоговой строки");
}

//------------------------------------------------------------------------------

int main()
try
{
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
