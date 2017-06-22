//------------------------------------------------------------------------------

#include "Func_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//------------------------------------------------------------------------------

Func_window::Func_window(Graph_lib::Point xy, int w, int h,
                         const string &title, Graph_lib::Funct &ff)
    : Window(xy, w, h, title),
      f{ff},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      r_min_in_box{Point{60, 0}, 50, 20, "r_min:"},
      r_max_in_box{Point{60, 30}, 50, 20, "r_max:"},
      count_in_box{Point{60, 60}, 50, 20, "count:"},
      xscale_in_box{Point{60, 90}, 50, 20, "xscale:"},
      yscale_in_box{Point{60, 120}, 50, 20, "yscale:"},
      func_menu{Point{130, 0}, 70, 20,
                Menu::vertical, "func"},
      menu_button{Point{130, 0}, 80, 20,
                  "func menu", cb_menu}
{
    attach(f);
    attach(quit_button);

    attach(r_min_in_box);
    attach(r_max_in_box);
    attach(count_in_box);
    attach(xscale_in_box);
    attach(yscale_in_box);

    load_func_menu();
    attach(func_menu);
    func_menu.hide();

    attach(menu_button);
}

//------------------------------------------------------------------------------

void Func_window::load_func_menu()
{
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "sin", cb_sin});
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "cos", cb_cos});
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "exp", cb_exp});
}

//------------------------------------------------------------------------------

void Func_window::recalculate(Fct ff)
{
    f.set_function(ff);
    istringstream is{r_min_in_box.get_string()};
    double value;
    is >> value;
    if (!is) error("Неправильный ввод r_min");

    f.set_r_min(value);

    is.str(r_max_in_box.get_string());
    is.clear();
    is >> value;
    if (!is) error("Неправильный ввод r_max");

    f.set_r_max(value);

    f.set_count_of_points(count_in_box.get_int());
    f.set_xscale(xscale_in_box.get_int());
    f.set_yscale(xscale_in_box.get_int());

    redraw();
}

//------------------------------------------------------------------------------

void Func_window::cb_sin(Address, Address pw)
{
    reference_to<Func_window>(pw).sin_pressed();
}

//------------------------------------------------------------------------------

void Func_window::cb_cos(Address, Address pw)
{
    reference_to<Func_window>(pw).cos_pressed();
}

//------------------------------------------------------------------------------

void Func_window::cb_exp(Address, Address pw)
{
    reference_to<Func_window>(pw).exp_pressed();
}

//------------------------------------------------------------------------------

void Func_window::cb_menu(Address, Address pw)
{
    reference_to<Func_window>(pw).menu_pressed();
}

//------------------------------------------------------------------------------

void Func_window::cb_quit(Address, Address pw)
{
    reference_to<Func_window>(pw).quit();
}

//------------------------------------------------------------------------------
