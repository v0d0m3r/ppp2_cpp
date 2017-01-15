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
    string mark;
};

//-----------------------------------------------------------------------------

void ignore_symb(istream& is, char ignore)
{
    char ch = 0;
    while(is >> ch)
        if (ch == ignore) return;
}

//-----------------------------------------------------------------------------

istream& read_distribution(istream& is, Distribution& d)
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
// Предполагаемый формат: ( d: рост количество_людей )
// ( m: str1 str2 ... str# )
istream& operator>>(istream& is, Distribution& d)
{
    char ch1 = 0;
    char ch2 = 0;

    constexpr char data = 'd';
    constexpr char mark = 'm';

    if (is >> ch1 >> ch2) {
        if (ch1 != '(') {
            is.clear(ios_base::failbit);
            return is;
        }
        switch (ch2) {
        case data:
            return read_distribution(is, d);
        case mark:
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

void exercise15_8()
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
    constexpr int end_growth = 195;

    constexpr double xscale = double(xlenght) / (end_growth-base_growth);
    constexpr double yscale = double(ylenght) / 50;

    Scale xs{xoffset, base_growth, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise15_8();
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
