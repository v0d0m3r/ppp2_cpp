#include "Graph.h"
#include <map>
#include <QLine>

namespace Graph_lib {

//-----------------------------------------------------------------------------

void Shape::draw_lines() const
{
    if (color().visibility() && 1<points.size())	// draw sole pixel?
        for (unsigned int i=1; i<points.size(); ++i)
            fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}

//-----------------------------------------------------------------------------

void Shape::draw() const
{
    Fl_Color oldc = fl_color();
    // there is no good portable way of retrieving the current style
    fl_color(lcolor.as_int());
    fl_line_style(ls.style(),ls.width());
    draw_lines();
    fl_color(oldc);	// reset color (to pevious) and style (to default)
    fl_line_style(0);
}

//-----------------------------------------------------------------------------

void Shape::move(int dx, int dy)
{
    for (unsigned int i = 0; i<points.size(); ++i) {
        points[i].x+=dx;
        points[i].y+=dy;
    }
}

//-----------------------------------------------------------------------------

void Lines::draw_lines() const
{
    if (color().visibility())
        for (int i=1; i < number_of_points(); i += 2)
            fl_line(point(i-1).x, point(i-1).y,
                    point(i).x, point(i).y);
}

//-----------------------------------------------------------------------------

void Lines::Lines(initializer_list<pair<Point, Point>> lst)
{
    for (auto p : lst) add(p.first, p.second);
}

//-----------------------------------------------------------------------------

} // Graph
