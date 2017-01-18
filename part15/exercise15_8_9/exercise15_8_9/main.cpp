//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

struct Distribution {
    int growth, number_of_human;
};

//-----------------------------------------------------------------------------

struct Label {
    vector<string> marks;
};

//-----------------------------------------------------------------------------

void ignore_symb(istream& is, char ignore)
{
    char ch = 0;
    while(is >> ch)
        if (ch == ignore) return;
}

//-----------------------------------------------------------------------------

istream& get_distribution(istream& is, Distribution& d)
{
    char ch1 = 0;
    char ch2 = 0;

    Distribution dd;
    if (is >> ch1 >> dd.growth >> dd.number_of_human
           >> ch2) {
        if (ch1!=':' || ch2!=')' ) {
            is.clear(ios_base::failbit);
            return is;
        }
    }
    else
        return is;

    d = dd;
    return is;
}

//-----------------------------------------------------------------------------
// Формат: ( d: : рост количество_людей )
istream& operator>>(istream& is, Distribution& d)
{
    char ch1 = 0;
    char ch2 = 0;

    constexpr char data = 'd';
    constexpr char lab  = 'l';

    if (is >> ch1 >> ch2) {
        if (ch1 != '(') {
            is.clear(ios_base::failbit);
            return is;
        }
        switch (ch2) {
        case data:
            return get_distribution(is, d);
        case lab:
            ignore_symb(is, ')');
            break;
        default:
            is.clear(ios_base::failbit);
            break;
        }
    }
    return is;
}

//-----------------------------------------------------------------------------

istream& get_label(istream& is, Label& l)
{
    char ch = ')';
    char ch2 = 0;
    Label ll;

    if (is >> ch2 && ch2 != ':') {
        is.clear(ios_base::failbit);
        return is;
    }

    for(string str; is >> str;)
        if (str[str.size()-1] != ch) ll.marks.push_back(str);
        else {
            if (str == ")") break;
            ll.marks.push_back("");
            for (int i = 0; i < str.size()-1; ++i)
                ll.marks[ll.marks.size()-1] += str[i];
            break;
        }

    if (!is) return is;
    l = ll;
    return is;
}

//-----------------------------------------------------------------------------
// Формат:
// ( l : str1 str2 ... str# )
istream& operator>>(istream& is, Label& l)
{
    char ch1 = 0;
    char ch2 = 0;

    constexpr char data = 'd';
    constexpr char lab =  'l';

    if (is >> ch1 >> ch2) {
        if (ch1 != '(') {
            is.clear(ios_base::failbit);
            return is;
        }
        switch (ch2) {
        case data:
            ignore_symb(is, ')');
            break;
        case lab:
            return get_label(is, l);
        default:
            is.clear(ios_base::failbit);
            break;
        }
    }
    return is;
}

//-----------------------------------------------------------------------------

class Scale {
public:
    Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s}
    {}
    int operator() (int v) const
    { return cbase + (v-vbase)*scale; }
private:
    int cbase;
    int vbase;
    double scale;
};

//-----------------------------------------------------------------------------

void fill_from_file(const string& fname, vector<Distribution>& dv,
                    int base_growth, int end_growth)
{
    ifstream ifs{fname};
    if (!ifs) error("Не возможно открыть файл ", fname);

    for (Distribution d; ifs >> d; ) {
        if (d.growth < base_growth || d.growth > end_growth)
            error("Рост вне диапозона");
        dv.push_back(d);
    }
}

//-----------------------------------------------------------------------------

void fill_from_file(const string& fname, Label& l)
{
    ifstream ifs{fname};
    if (!ifs) error("Не возможно открыть файл ", fname);

    for (Label lab; ifs >> lab; )
        for (int i = 0; i < lab.marks.size(); ++i)
            l.marks.push_back(lab.marks[i]);
}

//-----------------------------------------------------------------------------

void exercise15_8_9()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 400;
                                    // Расстояния:
    constexpr int xoffset = 100;    //  от левого края до оси у
    constexpr int yoffset = 60;     //  от нижнего края до оси х

    constexpr int xspace = 40;      // Пространство за осями
    constexpr int yspace = 40;
                                    // Длины осей
    constexpr int xlenght = xmax - xoffset - xspace;
    constexpr int ylenght = ymax - yoffset - yspace;

    constexpr int base_growth = 170;
    constexpr int end_growth  = 195;

    constexpr int max_count_peolple = 25;
    constexpr int h_growth = 5;     // Шаг по оси x

    constexpr double xscale = double(xlenght) / (end_growth-base_growth);
    constexpr double yscale = double(ylenght) / max_count_peolple;

    Scale xs{xoffset, base_growth, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};

    const string fname = "dist.txt";
    Label l;
    fill_from_file(fname, l);
    string mark = "growth  ";
    string space = "        "
                   "         ";
    for (int i = 0; i < l.marks.size(); ++i)
        if (i == 0) mark += l.marks[i];
        else        mark += space + l.marks[i];

    Simple_window win{Point{100, 100}, xmax, ymax, "exercise15_8_9"};

    Axis x{Axis::x, Point{xoffset, ymax-yoffset}, xlenght,
           (end_growth-base_growth)/h_growth, mark};
    x.label.move(-115, 0);

    Axis y{Axis::y, Point{xoffset, ymax-yoffset}, ylenght, 0,
           "count people"};
    y.label.move(-20, 0);

    vector<Distribution> dv;
    fill_from_file(fname, dv, base_growth, end_growth);

    Open_polyline growth_of_people;
    for (int i=0; i < dv.size(); ++i)
        growth_of_people.add(Point{xs(dv[i].growth), ys(dv[i].number_of_human)});

    win.attach(growth_of_people);

    win.attach(x);
    win.attach(y);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise15_8_9();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "exiting\n";
    keep_window_open("~");
    return -2;
}

//-----------------------------------------------------------------------------
