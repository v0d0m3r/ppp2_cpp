//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

enum class Category {
    start, space, alpha, digit, xdigit,
    upper, lower, alnum, cntrl,
    punct, print, graph, finish
};

//-----------------------------------------------------------------------------

Category get_category(const char& ch, const Category& current)
{
    static const pair<string, string> err_msg{"get_category: ",
                                              "неизвестная категория"};
    switch (current) {
    case Category::start:
        if (isprint(ch)) return Category::print;
        else if (iscntrl(ch)) return Category::cntrl;
        else error(err_msg.first, err_msg.second);
    case Category::cntrl: case Category::space:
    case Category::punct: case Category::digit:
    case Category::upper: case Category::lower:
        return Category::finish;
    case Category::print:
        if (isgraph(ch)) return Category::graph;
        else if (isspace(ch)) return Category::space;
        else error(err_msg.first, err_msg.second);
    case Category::graph:
        if (isalnum(ch)) return Category::alnum;
        else if (ispunct(ch)) return Category::punct;
        else error(err_msg.first, err_msg.second);
    case Category::alnum:
        if (isxdigit(ch)) return Category::xdigit;
        else if (isalpha(ch)) return Category::alpha;
        else error(err_msg.first, err_msg.second);
    case Category::xdigit:
        if (isdigit(ch)) return Category::digit;
        else if (isalpha(ch)) return Category::alpha;
        else error(err_msg.first, err_msg.second);
    case Category::alpha:
        if (isupper(ch)) return Category::upper;
        else if (islower(ch)) return Category::lower;
        else error(err_msg.first, err_msg.second);
    default:
        error(err_msg.first, err_msg.second);
    }
}

//------------------------------------------------------------------------------

void all_categories(const char& ch, vector<int>& count_category_tb)
{
    Category category = get_category(ch, Category::start);
    while (category != Category::finish) {
        ++count_category_tb[int(category)];
        category = get_category(ch, category);
    }
}

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, const string& message)
{
    if (ist.eof()) {
        ist.clear();
        return;
    }
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------
// Создает поток для файла с именем iname
void fill_from_stream(istream& ist, vector<int>& count_category_tb)
{
    for (string line; getline(ist, line);)
        for (const auto& ch : line)
            all_categories(ch, count_category_tb);

    end_of_loop(ist, "Неправильное завершение ввода");
}

//------------------------------------------------------------------------------

void fill_on_stream(ostream& ost, const vector<int>& count_category_tb,
                    vector<string>& name_category_tb)
{    
    for (int i = int(Category::space); i < int(Category::finish); ++i)
        ost << name_category_tb[i] << ": "
            << count_category_tb[i] << '\n';
}

//-----------------------------------------------------------------------------

void symb_analyzer()
{
    const string path = "./";
    cout << "Введите имя файла для ввода:\n";
    string iname;
    cin >> iname;
    iname = path + iname;
    cout << "Введите имя файла для вывода\n";
    string oname;
    cin >> oname;
    oname = path + oname;

    ifstream ifs{iname};
    if (!ifs)   error("Невозможно открыть входной файл");
    ifs.exceptions(ifs.exceptions()|ios_base::badbit);

    vector<string> name_category_tb {
        "start", "space", "alpha", "digit", "xdigit",
        "upper", "lower", "alnum", "cntrl",
        "punct", "print", "graph", "finish"
    };
    vector<int> count_category_tb(name_category_tb.size(), 0);
    fill_from_stream(ifs, count_category_tb);

    ofstream ofs{oname};
    if (!ofs) error("Невозможно открыть выходной файл: ", iname);
    fill_on_stream(ofs, count_category_tb,
                   name_category_tb);
}

//-----------------------------------------------------------------------------

int main()
try {
    symb_analyzer();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "неизвестное исключение\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
