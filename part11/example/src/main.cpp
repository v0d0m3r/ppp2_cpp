//------------------------------------------------------------------------------

#include "punctstream.hpp"

//------------------------------------------------------------------------------

void out_int_digit()
{
    cout << 11 << "\t(decimal)\n"
         << hex << 9 << "\t(hexadecimal)\n"
         << oct << 9 << "\t(octal)\n";
    cout << "-------------------\n"
         << 1234 << '\t' << hex << 1234
         << '\t' << oct << 1234 << '\n';
    cout << showbase << dec;    // Показывает основание
                                // системы счисления
    cout << 1234 << '\t' << hex << 1234
         << '\t' << oct << 1234 << '\n';
    cout << "-------------------\n"
         << 1234 << '\t' << 0x4d2 << '\t' << 02322 << '\n';
    cout << dec << "-------------------\n";
}

//------------------------------------------------------------------------------

void input_int_digit()
{
    int a;
    int b;
    int c;
    int d;
    cin >> a >> hex >> b >> oct >> c >> d;
    cin >> dec;
    cout << dec << "-------------------\n"
         << a << '\t' << b << '\t' << c << '\t' << d << '\n';
    cout << "-------------------\n";
    cin.unsetf(ios::dec);   // Не считать десятичным (0x может означать
                            // шестнадцатиричное число)
    cin.unsetf(ios::oct);   // Не считать восьмеричным
                            // (т.е. 12 может означать денадцать)
    cin.unsetf(ios::hex);   // Не считать шестнадцатиричным
                            // (т.е. 12 может означать денадцать)
    cin >> a >> b >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
    cout << "-------------------\n";
}

//------------------------------------------------------------------------------

void out_float_digit()
{
    cout << 1234.56789 << "\t\t(по умолчанию)\n"
         << fixed << 1234.56789 << "\t(фиксированный)\n"
         << scientific << 1234.56789 << "\t(научный)\n";
    cout << "-------------------\n";
    cout << defaultfloat;
    cout << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
    cout << 1234.56789 << '\n';         // Формат "клейкий"
    cout << defaultfloat << 1234.56789  // Формат по умолчанию
         << '\t' << fixed << 1234.56789
         << '\t' << scientific << 1234.56789 << '\n';
    cout << "-------------------\n";
    cout << defaultfloat;
}

//------------------------------------------------------------------------------

void precision()
{
    cout << defaultfloat << 1234567.89  // Формат по умолчанию
         << '\t' << fixed << 1234567.89
         << '\t' << scientific << 1234567.89 << '\n';
    cout << "-------------------\n";
    cout << defaultfloat;
    cout << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
    cout << defaultfloat << setprecision(5)
         << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
    cout << defaultfloat << setprecision(8)
         << 1234.56789 << '\t'
         << fixed << 1234.56789 << '\t'
         << scientific << 1234.56789 << '\n';
}

//------------------------------------------------------------------------------

void io_field()
{
    cout << 123456 << '|'               // Поля не используются
         << setw(4) << 123456 << '|'    // Число 123456 не помещается
                                        // в поле из 4 символов
         << setw(8) << 123456 << '|'    // Ширина поля равна 8
         << 123456 << "|\n";            // Размер поля не "клейкий"
    cout << "-------------------\n";
    cout << 12345 << '|' << setw(4) << 12345 << '|'
         << setw(8) << 12345 << '|' << 12345 << "|\n";
    cout << 1234.5 << '|' << setw(4) << 1234.5 << '|'
         << setw(8) << 1234.5 << '|' << 1234.5 << "|\n";
    cout << "asdfg" << '|' << setw(4) << "asdfg" << '|'
         << setw(8) << "asdfg" << '|' << "asdfg" << "|\n";
    cout << "-------------------\n";
    cout << setw(17) << "Фамилия" << '|'
         << setw(10) << "Имя" << '|'
         << setw(12) << "Номер телефона" << '|'
         << setw(36) << "Адрес е-почты" << "|\n";
    cout << setw(15) << "Иванов" << '|'
         << setw(5) << "Иван" << '|'
         << setw(14) << "+71111111111" << '|'
         << setw(25) << "mail@mail.ru" << "|\n";
}

//------------------------------------------------------------------------------

void binary_file()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname, ios_base::binary};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);
    // Открытие потока ostream для бинарной записи файла
    cout << "Введите имя файла для вывода\n";
    string oname;
    cin >> oname;
    oname = path + oname;
    ofstream ofs{oname,ios_base::binary};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);

    vector<int> v;
    // Чтение из бинарного файла
    for (int x; ifs.read(as_bytes(x), sizeof(int));) {  // Чтение
        v.push_back(x);                                 // байтов
        cout << x << '\n';
    }

    // ... работа с вектором v ...

    // Запись в бинарный файл
    for (int x : v)
        ofs.write(as_bytes(x), sizeof(int));
}

//------------------------------------------------------------------------------

void seek_in_files()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода/вывода\n";
    string fname;
    cin >> fname;
    fname = path + fname;
    fstream fs {fname};
    if (!fs) error("Невозможно открыть файл: ", fname);
    fs.seekg(5);    // Перенести позицию чтения (g означает "get")
                    // на 5 ячеек вперед
    char ch;
    fs >> ch;       // Считать и увеличить позицию чтения
    cout << "Шестой символ - это " << ch
         << '(' << static_cast<int>(ch) << ")\n";
    fs.seekp(1);    // Перенести позицию запис (p означает "put")
                    // на одну ячейку вперед
    fs << 'y';      // Записать и увеличить позицию записи
}

//------------------------------------------------------------------------------
// По возможности преобразует символы из строки s
// в число с плавающей точкой
double str_to_double(string& s)
{
    istringstream is{s};  // Создаем поток ввода из строки s
    double d;
    is >> d;
    if (!is) error("Ошибка формата типа double: ", s);
    return d;
}

//------------------------------------------------------------------------------

void input_on_str()
{
    string name;
    getline(cin, name);
    cout << name << '\n';

    string first_name;
    string second_name;
    stringstream ss{name};
    ss >> first_name;
    ss >> second_name;
    cout << "first_name: " << first_name << '\n';
    cout << "second_name: " << second_name << '\n';

    string command;
    getline(cin, command);
    ss.str(command);
    ss.seekg(0);
    vector<string> words;
    for (string s; ss >> s;)
        words.push_back(s);

    for (const string& s : words)
        cout << s << '\n';
}

//------------------------------------------------------------------------------

void work_with_ps()
{
    const string path = "./";
    // Открытие потока istream для бинарного чтения файла
    cout << "Введите имя файла для ввода\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    ifstream ifs {iname};
    if (!ifs) error("Невозможно открыть входной файл: ", iname);

    Punct_stream ps(ifs);
    //Punct_stream ps(cin);
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");  // \" в строке
                                                // означает "
    ps.case_sensitive(false);
    vector<string> vs;
    for (string word; ps >> word;)
        vs.push_back(word);         // Ввод слов
    sort(vs.begin(), vs.end());     // Сортировка в лексикографическом
                                    // порядке    
    for (int i=0; i <vs.size(); ++i)
        if (i==0 || vs[i]!=vs[i-1]) cout << vs[i] << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
    /* Функции к пунктам главы 11
    out_int_digit();    // Вывод целых чисел
    input_int_digit();  // Ввод целых чисел
    out_float_digit();  // Вывод чисел с плавающей точкой
    precision();        // Вывод чисел с плавающей точкой
                        // с заданной точностью
    io_field();         // Работа с полями i/o stream
    binary_file();      // Работа с бинарными файлами
    seek_in_files();    // Позициониравание в файле
    double d1 = str_to_double("12.4");
    input_on_str(); */
    work_with_ps();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}

//------------------------------------------------------------------------------
