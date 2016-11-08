#include <Graph.h>
#include <map>

//-----------------------------------------------------------------------------

namespace Graph_lib {

//-----------------------------------------------------------------------------

void Shape::set_color(Color col)
{
    lcolor = col;
}

//-----------------------------------------------------------------------------

Color Shape::color() const
{
    return lcolor;
}

//-----------------------------------------------------------------------------

void Shape::set_style(Line_style sty)
{
    ls = sty;
}

//-----------------------------------------------------------------------------

Line_style Shape::style() const
{
    return ls;
}

//-----------------------------------------------------------------------------

void Shape::set_fill_color(Color col)
{
    fcolor = col;
}

//-----------------------------------------------------------------------------

Color Shape::fill_color() const
{
    return fcolor;
}

//-----------------------------------------------------------------------------

void Shape::add(Point p)
{
    points.push_back(p);
}

void Shape::set_point(int i, Point p)
{
    points[i] = p;
}

Point Shape::point(int i) const
{
    return points[i];
}

int Shape::number_of_points() const
{
    return points.size();
}

//-----------------------------------------------------------------------------
}
