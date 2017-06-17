//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

double one(double)           { return 1; }
double slope(double x)       { return x/2; }
double square(double x)      { return x*x;}
double sloping_cos(double x) { return cos(x) + slope(x); }

//-----------------------------------------------------------------------------

void example()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 400;

    constexpr int x_orig = xmax/2;  // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;      // Диапазон {-10, 11)
    constexpr int r_max = 11;

    constexpr int n_points = 400;   // Количество точек в диапазоне

    constexpr int x_scale = 30;     // Масштабные множетели
    constexpr int y_scale = 30;

    Simple_window win{Point{100, 100}, xmax, ymax, "Function graphing"};

    Function s{one, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2{slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s3{square, r_min, r_max, orig, n_points, x_scale, y_scale};

    win.attach(s);
    win.attach(s2);
    win.attach(s3);
    win.wait_for_button();

    Text ts{Point{100, y_orig-40}, "one"};
    Text ts2{Point{100, y_orig + y_orig/2-40}, "x/2"};
    Text ts3{Point{x_orig-100, 20}, "x*x"};

    win.set_label("Function graphing: label functions");
    win.attach(ts);
    win.attach(ts2);
    win.attach(ts3);
    win.wait_for_button();

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 40;

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.set_label("Function graphing: use axis");
    win.attach(x);
    win.attach(y);
    win.wait_for_button();

    Function f4{cos, r_min, r_max, orig, 400, 30, 30};
    f4.set_color(Color::blue);
    Function f5{Fct_capture([](double x) { return cos(x) + slope(x); }),
                r_min, r_max, orig, 400, 30, 30};
    x.label.move(-160, 0);
    x.notches.set_color(Color::dark_red);
    win.set_label("Function graphing: more functions");
    win.attach(f4);
    win.attach(f5);
    win.wait_for_button();

    Function f6{log, 0.000001, r_max, orig, 200, 30, 30};
    Function f7{sin, r_min, r_max, orig, 200, 30, 30};
    f7.set_color(Color::blue);
    Function f8{cos, r_min, r_max, orig, 200, 30, 30};
    Function f9{exp, r_min, 7, orig, 200, 30, 30};
    f9.set_color(Color::yellow);

    win.set_label("log, exp, sin and cos");
    win.attach(f6);
    win.attach(f7);
    win.attach(f8);
    win.attach(f9);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

double fac(int n)          // n! Факториал
{
    double r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

//-----------------------------------------------------------------------------

double fac_recursive(int n) { return n>1 ? n*fac_recursive(n-1) : 1 ; }

//-----------------------------------------------------------------------------

double term(double x, int n)    // n-й член ряда
{
    return pow(x, n) / fac(n);
}

//-----------------------------------------------------------------------------

double expe(double x, int n)
{
    double sum = 0;
    for (int i=0; i < n; ++i) sum += term(x, i);
    return sum;
}

//-----------------------------------------------------------------------------

void approximation15_5()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 400;

    constexpr int x_orig = xmax/2;  // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;      // Диапазон {-10, 11)
    constexpr int r_max = 7;

    constexpr int n_points = 200;   // Количество точек в диапазоне

    constexpr int x_scale = 30;     // Масштабные множетели
    constexpr int y_scale = 30;

    constexpr int xlength = xmax - 40;  // Оси чуть меньше окна
    constexpr int ylength = ymax - 40;

    Simple_window win{Point{100, 100}, xmax, ymax, "Approximation"};

    Axis x{Axis::x, Point{20, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+20},
           ylength, ylength/y_scale, "one notch = 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    Function real_exp{exp, r_min, r_max, orig, n_points, x_scale, y_scale};
    real_exp.set_color(Color::blue);
    win.attach(real_exp);
    win.wait_for_button();
    for (int n=0; n < 50; ++n) {
        ostringstream ss;
        ss << "exp approximation; n==" << n;
        win.set_label(ss.str());
        // Очередное приближение:
        Function e{[n] (double x) { return expe(x, n); },
                   r_min, r_max, orig ,n_points, x_scale, y_scale};
        win.attach(e);
        win.wait_for_button();
        win.detach(e);
    }


}

//-----------------------------------------------------------------------------

struct Distribution {
    int year, young, middle, old;
};

//-----------------------------------------------------------------------------
// Предполагаемый формат: ( год : дети взрослые старики )
istream& operator>>(istream& is, Distribution& d)
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Distribution dd;

    if (is >> ch1 >> dd.year
           >> ch2 >> dd.young >> dd.middle >> dd.old
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

void fill_from_file(vector<Distribution>& dv, int base_year, int end_year)
{
    string file_name = "japanese-age-data.txt";
    ifstream ifs{file_name};
    if (!ifs) error("Не возможно открыть файл ", file_name);

    for (Distribution d; ifs >> d; ) {
        if (d.year < base_year || d.year > end_year)
            error("Год вне диапозона");
        if (d.young + d.middle + d.old != 100)
            error("Проценты не согласуются");
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

    constexpr int base_year = 1960;
    constexpr int end_year = 2040;

    constexpr double xscale = double(xlenght) / (end_year-base_year);
    constexpr double yscale = double(ylenght) / 100;

    Scale xs{xoffset, base_year, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};

    Simple_window win{Point{100, 100}, xmax, ymax, "Aging Japan"};

    Axis x{Axis::x, Point{xoffset, ymax-yoffset}, xlenght,
           (end_year-base_year)/10,
           "year  "
           "1960      1970      1980      1990      "
           "2000      2010      2020      2030      2040"};
    x.label.move(-90, 0);

    Axis y{Axis::y, Point{xoffset, ymax-yoffset}, ylenght, 10,
           "% of population"};

    Line current_year{Point{xs(2008), ys(0)}, Point{xs(2008), ys(100)}};
    current_year.set_style(Line_style::dash);

    Open_polyline children;
    Open_polyline adults;
    Open_polyline aged;

    vector<Distribution> dv;
    fill_from_file(dv, base_year, end_year);

    for (const auto& d : dv) {
        const int x = xs(d.year);
        children.add(Point{x, ys(d.young)});
        adults.add(Point{x, ys(d.middle)});
        aged.add(Point{x, ys(d.old)});
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
    win.attach(current_year);

    win.wait_for_button();
}

//-----------------------------------------------------------------------------

void task_build_graph()
{
    constexpr int xmax = 600;       // Размер окна
    constexpr int ymax = 600;

    constexpr int x_orig = xmax/2;  // Центр окна (0, 0)
    constexpr int y_orig = ymax/2;
    const Point orig{x_orig, y_orig};

    constexpr int r_min = -10;      // Диапазон {-10, 10)
    constexpr int r_max = 10;

    constexpr int n_points = 400;   // Количество точек в диапазоне

    constexpr int x_scale  = 20;     // Масштабные множетели
    constexpr int y_scale  = 20;

    constexpr int dx       = 200;    // Разница между длиной оси и окна
    constexpr int dy       = 200;
    constexpr int xlength  = xmax - dx;  // Оси меньше окна
    constexpr int ylength  = ymax - dy;

    Simple_window win{Point{100, 100}, xmax, ymax, "Graphics function"};

    Axis x{Axis::x, Point{dx/2, y_orig},
           xlength, xlength/x_scale, "one notch = 1"};
    Axis y{Axis::y, Point{x_orig, ylength+dy/2},
           ylength, ylength/y_scale, "one notch = 1"};

    x.set_color(Color::red);
    y.set_color(Color::red);

    win.attach(x);
    win.attach(y);

    Function s{one, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2{slope, r_min, r_max, orig, n_points, x_scale, y_scale};

    win.attach(s);
    win.attach(s2);

    Text ts1{Point{100, y_orig + y_orig/2-65}, "x/2"};
    win.attach(ts1);

    Function f3{cos, r_min, r_max, orig, n_points, x_scale, y_scale};
    f3.set_color(Color::blue);
    Function f4{Fct_capture([](double x) { return cos(x) + slope(x); }),
                r_min, r_max, orig, n_points, x_scale, y_scale};
    x.label.move(-120, 0);
    x.notches.set_color(Color::dark_red);\

    win.set_label("Function graphing: more functions");

    win.attach(f3);
    win.attach(f4);

    win.wait_for_button();

}

//-----------------------------------------------------------------------------

struct Person {
    Person(const string& first_name,
           const string& second_name, int age);
    Person();

    string first_name()  const {return fn;}
    string second_name() const {return sn;}
    int    age()         const {return a;}

    //void set_name(const string& name) { n = name; }
    //void set_age (int age)            { a = age;  }
private:
    string fn;
    string sn;
    int    a;
};

//-----------------------------------------------------------------------------

bool is_person(const string& first_name,
               const string& second_name, int age)
{
    static constexpr int max_age = 149; // Возраст в диапозоне [0, 150)
    static constexpr int min_age = 0;

    if (age<min_age || age>max_age) return false;

    stringstream ss{first_name + second_name};
    for (char ch=0; ss >> ch;) {
        switch (ch) {
        case ';': case ':': case '"': case '\'': case'[':
        case ']': case '*': case '&': case '^' : case '%':
        case '$': case '#': case '@': case '!':
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------

Person::Person(const string& first_name,
               const string& second_name, int age)
    : fn{first_name}, sn{second_name}, a{age}
{
    if (!is_person(first_name, second_name, age)) error("not person");
}

//-----------------------------------------------------------------------------

const Person& default_person()
{
    static Person pp{"Unnamed", "Unsonamed", 0};
    return pp;
}

//-----------------------------------------------------------------------------

Person::Person()
    : fn{default_person().first_name()},
      sn{default_person().second_name()},
      a{default_person().age()}
{}

//-----------------------------------------------------------------------------
// Предполагаемый формат: (имя возраст)
istream& operator>>(istream& is, Person& p)
{
    char ch1 = 0;
    char ch2 = 0;

    string fname;
    string sname;
    int age = 0;

    if (is >> ch1 >> fname >> sname
           >> age >> ch2) {
        if (ch1!='(' || ch2!=')') {
            is.clear(ios_base::failbit);
            return is;
        }
    }
    else
        return is;
    p = Person{fname, sname, age};
    return is;
}

//-----------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Person& p)
{
   return os << '(' << p.first_name()
             << ' ' << p.second_name() << ' ' << p.age() << ')';
}

//-----------------------------------------------------------------------------

/*void task_class_definition()
{
    Person p;
    p.name = "Goofy";
    p.age = 63;
    cout << "Персона: \n" << p.name
         << '\n'          << p.age;

}*/

//-----------------------------------------------------------------------------

void task_class_definition2()
{
    string greeting = "Введите персону в формате "
                      "\"(имя фамилия возвраст)\"\n";
    cout << greeting;
    vector<Person> vp;
    for(Person p; cin >> p;) {
        vp.push_back(p);
        cout << greeting;
    }

    for(int i=0; i < vp.size(); ++i)
        cout << "Вы ввели персону - " << vp[i] << '\n';
}

//-----------------------------------------------------------------------------

int main()
try {    
    //example();
    //approximation15_5();
    //grafical_present_data15_6();

    //task_build_graph();

    //task_class_definition();
    task_class_definition2();
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
