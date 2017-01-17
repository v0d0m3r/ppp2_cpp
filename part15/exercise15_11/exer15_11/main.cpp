//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

struct Distribution {
    int month, london, paris, dubai;
};

//-----------------------------------------------------------------------------

vector<string> month_tb = {
    "", "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

//-----------------------------------------------------------------------------
// Формат:
// ( месяц : Лондон_темпер Париж_темпер Дубай_темпер )
istream& operator>>(istream& is, Distribution& d)
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Distribution dd;

    if (is >> ch1 >> dd.month
           >> ch2 >> dd.london >> dd.paris >> dd.dubai
           >> ch3) {
        if (ch1!='(' || ch2!=':' || ch3!=')') {
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

void fill_from_file(vector<Distribution>& dv, int base_month, int end_month)
{
    string file_name = "tempetature.txt";
    ifstream ifs{file_name};
    if (!ifs) error("Не возможно открыть файл ", file_name);

    for (Distribution d; ifs >> d; ) {
        if (d.month < base_month || d.month > end_month)
            error("Год вне диапозона");
        dv.push_back(d);
    }
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

void grafical_present_data15_6()
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

    constexpr int base_month = 1;
    constexpr int end_month = 12;

    constexpr double xscale = double(xlenght) / (end_month-base_month);
    constexpr double yscale = double(ylenght) / 100;

    Scale xs{xoffset, base_month, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};

    Simple_window win{Point{100, 100}, xmax, ymax, "Aging Japan"};

    Axis x{Axis::x, Point{xoffset, ymax-yoffset}, xlenght,
           (end_month-base_month)/10,
           "month  "
           "1960      1970      1980      1990      "
           "2000      2010      2020      2030      2040"};
    x.label.move(-90, 0);

    Axis y{Axis::y, Point{xoffset, ymax-yoffset}, ylenght, 10,
           "C"};

    Open_polyline children;
    Open_polyline adults;
    Open_polyline aged;

    vector<Distribution> dv;
    fill_from_file(dv, base_month, end_month);

    for (int i=0; i < dv.size(); ++i) {
        const int x = xs(dv[i].month);
        children.add(Point{x, ys(dv[i].london)});
        adults.add(Point{x, ys(dv[i].paris)});
        aged.add(Point{x, ys(dv[i].dubai)});
    }

    Text children_label{Point{20, children.point(0).y}, "age 0-14"};
    children.set_color(Color::red);
    children_label.set_color(Color::red);

    Text adults_label{Point{20, adults.point(0).y}, "age 15-64"};
    adults.set_color(Color::blue);
    adults_label.set_color(Color::blue);

    Text aged_label{Point{20, aged.point(0).y}, "age 65+"};
    aged.set_color(Color::dark_green);
    aged_label.set_color(Color::dark_green);

    win.attach(children);
    win.attach(adults);
    win.attach(aged);

    win.attach(children_label);
    win.attach(adults_label);
    win.attach(aged_label);

    win.attach(x);
    win.attach(y);


    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {

    grafical_present_data15_6();

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
