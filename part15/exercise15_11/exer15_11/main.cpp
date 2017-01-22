//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

struct Distribution {
    int month, london, barcelona, dubai;
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
           >> ch2 >> dd.london >> dd.barcelona >> dd.dubai
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

//-----------------------------------------------------------------------------

void exercise15_11()
{
    constexpr int xmax = 800;       // Размер окна
    constexpr int ymax = 700;
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
    constexpr double yscale = double(ylenght) / 40;

    Scale xs{xoffset, base_month, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};

    Simple_window win{Point{100, 100}, xmax, ymax, "Weather of year"};

    Axis x{Axis::x, Point{xoffset, ymax-yoffset}, xlenght,
           (end_month-base_month),
           "month   "
           "jan          feb          mar         apr         "
           "may          jun          jul           aug         "
           "sep         oct          nov         dec"};

    x.label.move(-180, 0);

    Axis y{Axis::y, Point{xoffset, ymax-yoffset}, ylenght, 4,
           "C, weather of year"};
    y.label.move(8, 0);

    Open_polyline london;
    Open_polyline barcelona;
    Open_polyline dubai;

    vector<Distribution> dv;
    fill_from_file(dv, base_month, end_month);

    for (int i=0; i < dv.size(); ++i) {
        const int x = xs(dv[i].month);
        london.add(Point{x, ys(dv[i].london)});
        barcelona.add(Point{x, ys(dv[i].barcelona)});
        dubai.add(Point{x, ys(dv[i].dubai)});
    }

    Text london_label{Point{20, london.point(0).y}, "London"};
    london.set_color(Color::red);
    london_label.set_color(Color::red);

    Text barcelona_label{Point{20, barcelona.point(0).y}, "Barcelona"};
    barcelona.set_color(Color::blue);
    barcelona_label.set_color(Color::blue);

    Text dubai_label{Point{20, dubai.point(0).y}, "Dubai"};
    dubai.set_color(Color::dark_green);
    dubai_label.set_color(Color::dark_green);

    win.attach(london);
    win.attach(barcelona);
    win.attach(dubai);

    win.attach(london_label);
    win.attach(barcelona_label);
    win.attach(dubai_label);

    win.attach(x);
    win.attach(y);


    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {

    exercise15_11();    
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~");
    return -1;
}
catch (...) {
    cout << "exiting\n";
    keep_window_open("~");
    return -2;
}

//-----------------------------------------------------------------------------
