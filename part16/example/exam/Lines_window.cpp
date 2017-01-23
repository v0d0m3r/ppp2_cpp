#include "Lines_window.h"

//-----------------------------------------------------------------------------

Lines_window::Lines_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title),
      next_button{Point{x_max()-150, 0}, 70, 20, "Next", cb_next},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      next_x{Point{x_max()-310, 0}, 50, 20, "next x:"},
      next_y{Point{x_max()-210, 0}, 50, 20, "next y:"},
      xy_out{Point{100, 0}, 100, 20, "current (x, y):"},
      color_menu{Point{x_max()-70, 40}, 70, 20,
                 Menu::vertical, "color"},
      c_menu_button{Point{x_max()-80, 30}, 80, 20,
                    "color_menu", cb_c_menu},
      line_style_menu{Point{x_max()-160, 40}, 70, 20,
                      Menu::vertical, "style"},
      ls_menu_button{Point{x_max()-170, 30}, 80, 20,
                     "style_menu", cb_ls_menu}
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "red", cb_red});
    color_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "blue", cb_blue});
    color_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "black", cb_black});
    attach(color_menu);
    color_menu.hide();
    attach(c_menu_button);

    line_style_menu.attach(new Button{Point{0, 0}, 0, 0,
                                      "solid", cb_solid});
    line_style_menu.attach(new Button{Point{0, 0}, 0, 0,
                                      "dot", cb_dot});
    line_style_menu.attach(new Button{Point{0, 0}, 0, 0,
                                      "dash", cb_dash});
    attach(line_style_menu);
    line_style_menu.hide();
    attach(ls_menu_button);
    attach(lines);
}

//-----------------------------------------------------------------------------

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();
    lines.add(Point{x, y});

    // Обновление текущей точки
    ostringstream ss;
    ss << '(' << x << ", " << y << ')';
    xy_out.put(ss.str());

    redraw();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_red(Address, Address pw)
{
    reference_to<Lines_window>(pw).red_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_blue(Address, Address pw)
{
    reference_to<Lines_window>(pw).blue_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_black(Address, Address pw)
{
    reference_to<Lines_window>(pw).black_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_c_menu(Address, Address pw)
{
    reference_to<Lines_window>(pw).c_menu_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_solid(Address, Address pw)
{
    reference_to<Lines_window>(pw).solid_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_dot(Address, Address pw)
{
    reference_to<Lines_window>(pw).dot_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_dash(Address, Address pw)
{
    reference_to<Lines_window>(pw).dash_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_ls_menu(Address, Address pw)
{
    reference_to<Lines_window>(pw).ls_menu_pressed();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_next(Address, Address pw)
{
    reference_to<Lines_window>(pw).next();
}

//-----------------------------------------------------------------------------

void Lines_window::cb_quit(Address, Address pw)
{
    reference_to<Lines_window>(pw).quit();
}

//-----------------------------------------------------------------------------

void Lines_window::solid_pressed()
{
    change_ls(Line_style(Line_style::solid, 1));
    hide_ls_menu();
    redraw();
}

//-----------------------------------------------------------------------------

void Lines_window::dot_pressed()
{
    change_ls(Line_style(Line_style::dot,2));
    hide_ls_menu();
    redraw();
}

//-----------------------------------------------------------------------------

void Lines_window::dash_pressed()
{
    change_ls(Line_style(Line_style::dash,2));
    hide_ls_menu();
    redraw();
}

//-----------------------------------------------------------------------------



