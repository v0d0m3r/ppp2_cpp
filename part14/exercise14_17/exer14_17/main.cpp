//-----------------------------------------------------------------------------
// exercise14_17
//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------
// Имена прямых потомков exception
const vector<string> exception_labels = {
    "logic_error", "bad_typeid",   "runtime_error",
    "bad_cast",    "bad_weak_ptr", "bad_function_call",
    "bad_alloc",   "bad_exception"
};

//-----------------------------------------------------------------------------
// Номера элементов ..._labels имеющие потомков
enum kind_exception {
    logic = 1, runtime = 3, badalloc = 7, syst = 3
};

//-----------------------------------------------------------------------------
// Имена прямых потомков logic_error
const vector<string> logic_labels = {
    "invalid_argument", "domain_error",
    "length_error",     "out_of_range",
    "future_error"
};

//-----------------------------------------------------------------------------
// Имена прямых потомков runtime_error
const vector<string> runtime_labels = {
    "range_error",      "overflow_error",
    "underflow_error",  "system_error"
};

//-----------------------------------------------------------------------------
// Создание текстовых ячеек и связывание их с окном
void init_items(Point start, Point d, const vector<string>& labels,
                Vector_ref<Texted_box>& vr)
{
    for (int i=0; i < labels.size(); ++i)
        if (i == 0)
            vr.push_back(new Texted_box{start,labels[i]});
        else
            vr.push_back(new Texted_box {
                                Point{
                                 vr[vr.size()-1].point(0).x + d.x,
                                 vr[vr.size()-1].point(0).y + d.y
                             },
                             labels[i]
                         });
}

//-----------------------------------------------------------------------------

void init_exception_items(Simple_window& win,
                          Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20; // Начальная высота
    const int hy = 6 * height0;         // Шаг по ОУ
    const int dx = win.x_max() * 1.00 / exception_labels.size();
    const int dy = 0;
    init_items(Point{10, height0 + hy}, Point{dx, dy},
               exception_labels, vr);
    for (int i=0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_logic_items(Simple_window& win,
                      Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 6 * height0;
    const int dx = 0;
    const int dy = hy/4;
    init_items(Point{40, height0 + hy + hy/3}, Point{dx, dy},
               logic_labels, vr);
    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_runtime_items(Simple_window& win,
                        Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 6 * height0;
    const int dx = 0;
    const int dy = hy/4;
    init_items(Point{350, height0 + hy + hy/3}, Point{dx, dy},
               runtime_labels, vr);

    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_badalloc_items(Simple_window& win,
                         Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 6 * height0;
    static const vector<string> badalloc_labels = {
        "bad_array_new_length"
    };
    const int dx = 0;
    const int dy = hy/4;
    init_items(Point{930, height0 + hy + hy/3}, Point{dx, dy},
               badalloc_labels, vr);

    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void init_system_items(Simple_window& win,
                       Vector_ref<Texted_box>& vr)
{
    const int height0 = win.y_max()/20;
    const int hy = 6 * height0;
    static const vector<string> system_labels = {
        "ios_base::failure"
    };
    const int dx = 0;
    const int dy = hy/4;
    init_items(Point{380, height0 + hy + hy + hy/3}, Point{dx, dy},
               system_labels, vr);

    for (int i =0; i < vr.size(); ++i)
        win.attach(vr[i]);
}

//-----------------------------------------------------------------------------

void go_to_exception(const Vector_ref<Texted_box>& vr,
                     Vector_ref<Arrow>& arrows)
{
    Point b{0, 0};
    Point e{vr[0].point(0).x,
            vr[0].point(0).y + vr[0].height()};
    int dx = vr[0].width() / vr.size();
    for (int i=1; i < vr.size(); ++i) {
        b = Point{vr[i].point(0).x + vr[i].width()/2,
                  vr[i].point(0).y};
        e = Point{e.x + dx,e.y};
        arrows.push_back(new Arrow(b, e));

    }
}

//-----------------------------------------------------------------------------

void go_to_item(kind_exception ke,
                const Vector_ref<Texted_box>& from,
                const Vector_ref<Texted_box>& to,
                Vector_ref<Arrow>& arrows, Lines& lines)

{
    for (int i=0; i < from.size(); ++i)
        lines.add(Point{
                      from[i].point(0).x,
                      from[i].point(0).y+from[i].height()/2,
                  },
                  Point{
                      to[ke].point(0).x,
                      from[i].point(0).y+from[i].height()/2
                  });
    arrows.push_back(new Arrow(
                         Point{
                             lines.point(lines.number_of_points()-1).x,
                             lines.point(lines.number_of_points()-1).y
                         },
                         Point{
                             to[ke].point(0).x,
                             to[ke].point(0).y+to[ke].height()
                         }));
}

//-----------------------------------------------------------------------------

void exercise14_17()
{
    Simple_window win{Point {0, 0}, 1200, 800, "exercise 14_17"};

    const int width0 = 175;
    Point start{win.x_max()/2-width0,win.y_max()/10};


    Vector_ref<Texted_box> ei;  // Потомки exception
    ei.push_back(new Texted_box {start,350, 30,
                                        "                    "
                                        "               exception"});
    init_exception_items(win, ei);

    Vector_ref<Texted_box> li;  // Потомки logic_error
    init_logic_items(win, li);

    Vector_ref<Texted_box> ri;  // Потомки runtime_error
    init_runtime_items(win, ri);

    Vector_ref<Texted_box> bi;  // Потомки bad_alloc
    init_badalloc_items(win, bi);

    Vector_ref<Texted_box> si;  // Потомки bad_alloc
    init_system_items(win, si);

    Vector_ref<Arrow> arrows;   // Стрелки от потомков к родителям
    go_to_exception(ei, arrows);

    Lines lines;                // Линии для общих родителей
    go_to_item(badalloc, bi, ei, arrows, lines);
    go_to_item(logic,    li, ei, arrows, lines);
    go_to_item(runtime,  ri, ei, arrows, lines);
    go_to_item(syst,     si, ri, arrows, lines);

    for(int i=0; i < arrows.size(); ++i)
        win.attach(arrows[i]);
    win.attach(lines);
    win.wait_for_button();
}

//-----------------------------------------------------------------------------

int main()
try {
    exercise14_17();
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
