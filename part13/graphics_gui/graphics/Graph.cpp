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

Lines::Lines(initializer_list<pair<Point, Point>> lst)
{
    for (auto p : lst) add(p.first, p.second);
}

//-----------------------------------------------------------------------------

void Closed_polyline::draw_lines()
{
    Open_polyline::draw_lines();    // Вывод открытой последовательности
    // Затем - вывод замыкающей линии
    if (2<number_of_points() && color().visiblity())
        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,
                point(0).x,
                point(0).y);
}

//-----------------------------------------------------------------------------
// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2,
                                          Point p3, Point p4,
                                          bool& parallel)
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
    if (denom == 0){
        parallel= true;
        return pair<double,double>(0,0);
    }
    parallel = false;
    return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                                ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

//-----------------------------------------------------------------------------
//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2,
                            Point p3, Point p4,
                            Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

//-----------------------------------------------------------------------------

void Polygon::add(Point p)
{
    int np = number_of_points();

    if (1<np) {	// check that thenew line isn't parallel to the previous one
        if (p==point(np-1)) error("polygon point equal to previous point");
        bool parallel;
        line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
        if (parallel)
            error("two polygon points lie in a straight line");
    }

    for (int i = 1; i<np-1; ++i) {	// check that new segment doesn't interset and old point
        Point ignore(0,0);
        if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
            error("intersect in polygon");
    }


    Closed_polyline::add(p);
}

//-----------------------------------------------------------------------------

void Polygon::draw_lines() const
{
        if (number_of_points() < 3) error("less than 3 points in a Polygon");
        Closed_polyline::draw_lines();
}

//-----------------------------------------------------------------------------

Rectangle::Rectangle(Point xy, int ww, int hh)
    : w{ww}, h{hh}
{
    if (w <= 0 && h <= 0)
        error("Ошибка: не положительная сторона!");
    add(xy);
}

//-----------------------------------------------------------------------------

Rectangle::Rectangle(Point x, Point y)
    : w{y.x-x.x}, h{y.y-x.y}
{
    if (w <= 0 && h <= 0)
        error("Ошибка: Первая точка не верхняя левая!");
    add(x);
}

//-----------------------------------------------------------------------------

void Rectangle::draw_lines() const
{
    if (fill_color().visibility()) {	// Заполнение
        fl_color(fill_color().as_int());
        fl_rectf(point(0).x,point(0).y,w,h);
    }

    if (color().visibility()) {	// Линии поверх заполнения
        fl_color(color().as_int());
        fl_rect(point(0).x,point(0).y,w,h);
    }
}

//-----------------------------------------------------------------------------

void Text::draw_lines() const
{
    fl_draw(lab.c_str(), point(0).x, point(0).y);
}

//-----------------------------------------------------------------------------

Circle::Circle(Point p, int rr)
    : r{rr}
{
    add(Point{p.x-r, p.y -r});
}

//-----------------------------------------------------------------------------

Point Circle::center() const
{
    return {point(0).x+r, point(0).y+r};
}

//-----------------------------------------------------------------------------

void Circle::draw_lines() const
{
    if (color().visiblity())
        fl_arc(point(0).x, point(0).y, r+r, r+r, 0, 360);
}

//-----------------------------------------------------------------------------

Point Ellipce::focus1() const
{
    return { center().x + int(sqrt(double(w*w - h*h))), center().y };
}

//-----------------------------------------------------------------------------

Point Ellipce::focus2() const
{
    return { center().x - int(sqrt(double(w*w - h*h))), center().y };
}

//-----------------------------------------------------------------------------

Point Ellipce::center() const
{
    return {point(0).x + w, point(0).y + h};
}

//-----------------------------------------------------------------------------

void Ellipce::draw_lines() const
{
    if (color().visiblity())
        fl_arc(point(0).x, point(0).y, w+w, h+h, 0, 360);
}

//-----------------------------------------------------------------------------

void draw_mark(Point xy, char c)
{
    constexpr int dx = 4;
    constexpr int dy = 4;
    string m{1, c}; // Строка с единственным символом
    fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
}

//-----------------------------------------------------------------------------

Marked_polyline::Marked_polyline(const string &m,
                                 initializer_list<Point> lst)
    : Open_polyline{lst}, mark{m}
{
    if (mark == "") mark = "*";
}

//-----------------------------------------------------------------------------

void Marked_polyline::draw_lines() const
{
    Open_polyline::draw_lines();
    for (int i=0; i<number_of_points(); ++i)
        draw_mark(point(i), mark[i%mark.size()]);
}

//-----------------------------------------------------------------------------

bool is_can_open(const string& s)
{
    ifstream ff(s);
    return ff;
}

//-----------------------------------------------------------------------------

Suffix::Encoding get_encoding(const string& s)
        // try to deduce type from file name using a lookup table
{
    static int x = init_suffix_map();

    string::const_iterator p = find(s.begin(),s.end(),'.');
    if (p==s.end()) return Suffix::none;	// no suffix

    string suf(p+1,s.end());
    return suffix_map[suf];
}

//-----------------------------------------------------------------------------

Image::Image(Point xy, string s, Suffix e)
    : w{0}, h{0}, fn(xy, "")
{
    add(xy);
    if (!is_can_open(s)) {
        fn.set_label("Невозможно открыть \"" + s + '"');
        p = new Bad_image(30, 20);  // "Ошибочное изображение"
        return;
    }

    if (e == Suffix::none) e = get_encoding(s);
    switch (e) {
    case Suffix::jpg:
        p = new Fl_JPEG_Image{s.c_str()};
        break;
    case Suffix::gif:
        p = new Fl_GIF_Image{s.c_str()};
        break;
    default:
        fn.set_label("Неподдерживаемый тип файла \"" + s + '"');
        p = new Bad_image(30, 20);  // "Ошибочное изображение"
        break;
    }
}

} // Graph
