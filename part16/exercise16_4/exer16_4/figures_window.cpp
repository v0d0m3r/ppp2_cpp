#include "figures_window.h"

//-----------------------------------------------------------------------------

Figures_window::Figures_window(Point xy, int w, int hh, const string &title)
    : Window(xy, w, hh, title), h{hh},
      cir{Point{0,0}, int(h*percent/2)},
      sq{ Point{0,0}, int(h*percent), int(h*percent)},
      rt{ Point{0,0}, int(h*percent), int(h*percent)},
      rh{ Point{int(h*percent/2)-1, int(h*percent/2)-16}, int(h*percent/2)},
      current{&cir},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      next_x{Point{x_max()-310, 0}, 50, 20, "next x:"},
      next_y{Point{x_max()-210, 0}, 50, 20, "next y:"},
      figure_menu{Point{x_max()-70, 40}, 70, 20,
                  Menu::vertical, "figure"}

{
    attach(quit_button);
    attach(next_x);
    attach(next_y);

    figure_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "circle", cb_circle});
    figure_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "square", cb_square});
    figure_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "triangle", cb_triangle});
    figure_menu.attach(new Button{Point{0, 0}, 0, 0,
                                 "hexagon", cb_hexagon});
    attach(figure_menu);
}

//-----------------------------------------------------------------------------
// Связывает/разъединяет фигуры с окном
void Figures_window::set_attached(Shape& s)
{
    detach(*current);   // Освобождаем предыдущую фигуру
    attach(s);          // Связываем новую фигуру
    current = &s;       // Запоминаем новую фигуру
}

//-----------------------------------------------------------------------------

void Figures_window::circle_pressed()
{
    int x = next_x.get_int() - cir.point(0).x;
    int y = next_y.get_int() - cir.point(0).y;
    cir.move(x, y);
    set_attached(cir);
    redraw();
}

//-----------------------------------------------------------------------------

void Figures_window::square_pressed()
{
    int x = next_x.get_int() - sq.point(0).x;
    int y = next_y.get_int() - sq.point(0).y;
    sq.move(x, y);
    set_attached(sq);
    redraw();
}

//-----------------------------------------------------------------------------

void Figures_window::triangle_pressed()
{
    int x = next_x.get_int() - rt.point(0).x;
    int y = next_y.get_int() - rt.point(0).y;
    rt.move(x, y);
    set_attached(rt);
    redraw();
}

//-----------------------------------------------------------------------------

void Figures_window::hexagon_pressed()
{
    int x = next_x.get_int() - (rh.point(0).x - h*percent/2 + 1);
    int y = next_y.get_int() - (rh.point(0).y - h*percent/2 + 16);
    rh.move(x, y);
    set_attached(rh);
    redraw();
}

//-----------------------------------------------------------------------------

void Figures_window::cb_circle(Address, Address pw)
{
    reference_to<Figures_window>(pw).circle_pressed();
}

//-----------------------------------------------------------------------------

void Figures_window::cb_square(Address, Address pw)
{
    reference_to<Figures_window>(pw).square_pressed();
}

//-----------------------------------------------------------------------------

void Figures_window::cb_triangle(Address, Address pw)
{
    reference_to<Figures_window>(pw).triangle_pressed();
}

//-----------------------------------------------------------------------------

void Figures_window::cb_hexagon(Address, Address pw)
{
    reference_to<Figures_window>(pw).hexagon_pressed();
}

//-----------------------------------------------------------------------------

void Figures_window::cb_quit(Address, Address pw)
{
    reference_to<Figures_window>(pw).quit();
}

//-----------------------------------------------------------------------------
