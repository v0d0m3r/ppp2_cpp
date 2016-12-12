// exercise14_16
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

class Controller {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void set_level(int ll) = 0;
    virtual void show() const = 0;
};

//-----------------------------------------------------------------------------

string int_to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

//-----------------------------------------------------------------------------

class Test_Controller : public Controller {
public:
    Test_Controller() {}
    void on()               { status = true; }
    void off()              { status = false; }
    void set_level(int ll)  { l = ll; }
    void show() const
    {
        (status) ? cout << "status: on\n"
                 : cout << "status: off\n";
        cout << "level: "<< int_to_string(l);
    }
private:
    bool status = false;   // true, если on()
    int l = 0;
};

//-----------------------------------------------------------------------------

class Shape_color_controller : public Controller {
public:
    Shape_color_controller(Shape& ss) : s{ss} {}
    void on()               { status = true; }
    void off()              { status = false; }
    void set_level(int ll)  { if (status) s.set_color(ll);
                              else error("status off");}
    void show() const
    {
        (status) ? cout << "status: on\n"
                 : cout << "status: off\n";
        cout << "color: "<< int_to_string(s.color().as_int());
    }
private:
    bool status = true;   // true, если on()
    Shape& s;
};

//-----------------------------------------------------------------------------

void exercise14_16()
{
    Circle cir{Point{100, 100}, 50};
    Shape_color_controller contr{cir};
    contr.off();
    contr.set_level(Color::blue);
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_16();
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
