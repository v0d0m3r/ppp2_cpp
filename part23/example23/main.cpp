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
    Mail_file mfile{"my-mail-file.txt"}; // Инициализируем mfile
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
    for (auto p{pp.first}; p != pp.second; ++p)
        cout << find_subject(p->second) << '\n';
}
catch(const Bad_mail_file& e) {
    cout << e.what() << '\n';
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
