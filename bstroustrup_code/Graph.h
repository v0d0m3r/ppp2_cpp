
#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include "Point.h"
#include<vector>

#include "fltk.h"
#include "std_lib_facilities.h"

#include <functional>

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

struct Color {
    enum Color_type {
        red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
        yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
        magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
        dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
        dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
    };
    enum Transparency { invisible = 0, visible=255 };

    Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
    Color(int cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Transparency vv) :c(Fl_Color()), v(vv) { }

    int as_int() const { return c; }
    char visibility() const { return v; }
    void set_visibility(Transparency vv) { v=vv; }
private:
    unsigned char v;	// 0 or 1 for now
    Fl_Color c;
};

struct Line_style {
    enum Line_style_type {
        solid=FL_SOLID,				// -------
        dash=FL_DASH,				// - - - -
        dot=FL_DOT,					// .......
        dashdot=FL_DASHDOT,			// - . - .
        dashdotdot=FL_DASHDOTDOT,	// -..-..
    };
    Line_style(Line_style_type ss) :s(ss), w(0) { }
    Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
    Line_style(int ss) :s(ss), w(0) { }

    int width() const { return w; }
    int style() const { return s; }
private:
    int s;
    int w;
};

class Font {
public:
    enum Font_type {
        helvetica=FL_HELVETICA,
        helvetica_bold=FL_HELVETICA_BOLD,
        helvetica_italic=FL_HELVETICA_ITALIC,
        helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
        courier=FL_COURIER,
        courier_bold=FL_COURIER_BOLD,
        courier_italic=FL_COURIER_ITALIC,
        courier_bold_italic=FL_COURIER_BOLD_ITALIC,
        times=FL_TIMES,
        times_bold=FL_TIMES_BOLD,
        times_italic=FL_TIMES_ITALIC,
        times_bold_italic=FL_TIMES_BOLD_ITALIC,
        symbol=FL_SYMBOL,
        screen=FL_SCREEN,
        screen_bold=FL_SCREEN_BOLD,
        zapf_dingbats=FL_ZAPF_DINGBATS
    };

    Font(Font_type ff) :f(ff) { }
    Font(int ff) :f(ff) { }

    int as_int() const { return f; }
private:
    int f;
};

template<class T> class Vector_ref {
    vector<T*> v;
    vector<T*> owned;
public:
    Vector_ref() {}

    Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
    {
            if (a) push_back(a);
            if (b) push_back(b);
            if (c) push_back(c);
            if (d) push_back(d);
    }

    ~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

    void push_back(T& s) { v.push_back(&s); }
    void push_back(T* p) { v.push_back(p); owned.push_back(p); }

    // ???void erase(???)

    T& operator[](int i) { return *v[i]; }
    const T& operator[](int i) const { return *v[i]; }
    int size() const { return v.size(); }
};

typedef double Fct(double);
typedef function<double(double)> Fct_capture ;

class Shape  {	// deals with color and style, and holds sequence of lines
protected:
    Shape() { }
    Shape(initializer_list<Point> lst);  // add() the Points to this Shape

//	Shape() : lcolor(fl_color()),
//		ls(0),
//		fcolor(Color::invisible) { }

    void add(Point p){ points.push_back(p); }
    void set_point(int i, Point p) { points[i] = p; }
public:
    void draw() const;					// deal with color and draw_lines
protected:
    virtual void draw_lines() const;	// simply draw the appropriate lines
public:
    virtual void move(int dx, int dy);	// move the shape +=dx and +=dy

    void set_color(Color col) { lcolor = col; }
    Color color() const { return lcolor; }

    void set_style(Line_style sty) { ls = sty; }
    Line_style style() const { return ls; }

    void set_fill_color(Color col) { fcolor = col; }
    Color fill_color() const { return fcolor; }

    Point point(int i) const { return points[i]; }
    int number_of_points() const { return int(points.size()); }

    virtual ~Shape() { }
    /*
    struct Window* attached;
    Shape(const Shape& a)
        :attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
    {
        if (a.attached)error("attempt to copy attached shape");
    }
    */
    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;
private:
    vector<Point> points;	// not used by all shapes
    Color lcolor {fl_color()};
    Line_style ls {0};
    Color fcolor {Color::invisible};

//	Shape(const Shape&);
//	Shape& operator=(const Shape&);
};

// Note that f can be either a function or a lambda.
// Solution courtesy of Jordan Harris <jordanharris1175@gmail.com>
struct Function : Shape {
    // graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
    // x coordinates are scaled by xscale and y coordinates scaled by yscale
    // the function parameters are not stored
    Function(Fct f, double r1, double r2, Point orig, int count = 100,
             double xscale = 25, double yscale = 25);
    Function(Fct_capture f, double r1, double r2, Point orig, int count = 100,
             double xscale = 25, double yscale = 25);
};

//-----------------------------------------------------------------------------

class Fnctn : Shape {
public:
    Fnctn(Fct ff, double r_min, double r_max, Point orig, int count = 100,
          double xscale = 25, double yscale = 25);
    Fnctn(Fct_capture ff, double r_min, double r_max, Point orig, int count = 100,
          double xscale = 25, double yscale = 25);

    double r_min()                  const { return r1; }
    double r_max()                  const { return r2; }

    double xscale()                 const { return xs; }
    double yscale()                 const { return ys; }

    int count_of_point()            const { return cp; }
    //Point orig()                    const { return xy; }

    void set_r_min(double r_min)          { r1 = r_min; }
    void set_r_max(double r_max)          { r2 = r_max; }

    void set_xscale(double xscale)        { xs = xscale; }
    void set_yscale(double yscale)        { ys = yscale; }

    void set_count_of_point(int count)    { cp = count; }

    void set_function(Fct* ff)            { f = ff;  }
    void set_function(Fct_capture* ff)    { fc = ff; }

protected:
    Fct*         function()         const { return f;  }
    Fct_capture* function_capture() const { return fc; }
    void set_function_flag() ;
    bool is_function()              const { return fct_flag; }
    virtual void recalculate();
private:
    bool fct_flag;
    Fct* f;
    Fct_capture* fc;
    double r1, r2;
    int cp;
    double xs, ys;
    Point xy;
};

//-----------------------------------------------------------------------------

/*struct Function : Shape {
      // the function parameters are not stored
      template <typename Fct = double(double)>
      Function(Fct f, double r1, double r2, Point xy,
               int count = 100, double xscale = 25, double yscale = 25) {
         if (r2-r1<=0) error("bad graphing range");
         if (count<=0) error("non-positive graphing count");
         double dist = (r2-r1)/count;
         double r = r1;
         for (int i = 0; i<count; ++i) {
            add(Point{xy.x+int(r*xscale), xy.y-int(f(r)*yscale)});
            r += dist;
         }
      }
   };*/

struct Fill {
    Fill() :no_fill(true), fcolor(0) { }
    Fill(Color c) :no_fill(false), fcolor(c) { }

    void set_fill_color(Color col) { fcolor = col; }
    Color fill_color() { return fcolor; }
protected:
    bool no_fill;
    Color fcolor;
};

//-----------------------------------------------------------------------------

struct Group {
    Group(){}
    void add(Shape& s)  { shapes.push_back(s); }
    void add(Shape* s)  { shapes.push_back(s); }

    int size() const { return shapes.size(); }

    Shape& operator[](int i) { return shapes[i]; }
    const Shape& operator[](int i) const { return shapes[i]; }

private:
    Vector_ref<Shape> shapes;
};

//-----------------------------------------------------------------------------

struct Line : Shape {
    Line(Point p1, Point p2) { add(p1); add(p2); }
};

struct Rectangle : Shape {

    Rectangle(Point xy, int ww, int hh) :w{ ww }, h{ hh }
    {
        if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
        add(xy);
    }
    Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
    {
        if (h<=0 || w<=0) error("Bad rectangle: first point is not top left");
        add(x);
    }
    void draw_lines() const;

//	void set_fill_color(Color col) { fcolor = col; }
//	Color fill_color() { return fcolor; }

    int height() const { return h; }
    int width() const { return w; }
private:
    int h;			// height
    int w;			// width
//	Color fcolor;	// fill color; 0 means "no fill"
};

//-----------------------------------------------------------------------------

struct Binary_tree : Shape {
    Binary_tree(Point p, int ll, int ww, const string &ss = "l");

    int levels()             const { return l;   }
    int down_level_width()   const { return dlw; }
    double node_width()      const { return nw;  }
    string kind_edges()      const { return ke;  }

    void add_text_node(const string& loc,
                       const string& lab);

    const Shape& edge(int i) const { return edges[i];     }
    int number_of_edges()    const { return edges.size(); }

    void set_color_edges(Color col);

    void draw_lines() const override;
    void move(int dx, int dy) override;
protected:
    virtual void draw_nodes() const;
    virtual void choose_kind_edges(); // Выбор вида и расчет
                                      // координат ребер
private:
    void init();
    int l;            // Количество уровней
    int dlw;          // Длина нижнего уровня
    double nw;        // Длина узла
    string ke;        // Вид линий, соединяющих узлы
    Group edges;      // Ребра, соединяющие узлы
    vector<string> lab_nodes;
};

//-----------------------------------------------------------------------------

struct Triangle_nodes_binary_tree : Binary_tree {
    using Binary_tree::Binary_tree;
    void draw_nodes() const override;
    //void draw_lines() const override;
};


//-----------------------------------------------------------------------------

class Chess_board : public Rectangle {
public:
    static constexpr int min_size = 100;
    static constexpr int item_on_line = 8;

    Chess_board(Point xy, int rr);   

    const Shape& checker(int i) const { return checkers[i];}
    int number_of_checkers()    const { return checkers.size(); }

    void draw_lines() const override;

    Color color_up_checkers()   const { return col_up; }
    void set_color_up_checkers(Color col);

    Color color_down_checkers() const { return col_down; }
    void set_color_down_checkers(Color col);

    void move(int dx, int dy) override;
    void move_checker(int i, int dx, int dy)
    { checkers[i].move(dx, dy); }
private:
    void init();
    Group checkers;  // шашки
    Color col_up{Color::blue};
    Color col_down{Color::white};
};

//-----------------------------------------------------------------------------

struct Striped_rectangle : Rectangle {
    using Rectangle::Rectangle;
    void draw_lines() const override;
};

//-----------------------------------------------------------------------------
// Exercise 13_2
struct Box : Rectangle {
    Box(Point xy, int rww, int rhh)
        : Rectangle{xy, rww, rhh}
    {
        if (rww/ew<2 || rhh/eh<2)
            error("Bad Box: не корректно заданы парамметры");
        init();
    }
    Box(Point xy, int rww, int rhh, int eww, int ehh)
        : Rectangle(xy, rww, rhh), ew{eww}, eh{ehh}
    {
        if (rww/ew<2 || rhh/eh<2)
            error("Bad Box: не корректно заданы парамметры");
        if (ew<=0 || ew>100 || eh<=0 || eh>100)
            error("Bad Box: not correct semiaxis");
        init();
    }

    void draw_lines() const;

    int major() const { return ew; }
    int minor() const { return eh; }

private:
    void init();
    // For ellipses
    int ew = 10; // major
    int eh = 15; // minor

};

//-----------------------------------------------------------------------------
// Exercise 13_6
struct Texted_box : Box {
    Texted_box(Point xy, int rww, int rhh, const string& s)
        : Box {xy, rww, rhh}, lab{s} {}
    Texted_box(Point xy, const string& s);
    void draw_lines() const;
private:
    string lab;
};

//-----------------------------------------------------------------------------

bool intersect(Point p1, Point p2, Point p3, Point p4);


struct Open_polyline : Shape {	// open sequence of lines
    using Shape::Shape;
    void add(Point p) { Shape::add(p); }
    void draw_lines() const;
};

struct Closed_polyline : Open_polyline {	// closed sequence of lines
    using Open_polyline::Open_polyline;
    void draw_lines() const;

//	void add(Point p) { Shape::add(p); }
};

struct Striped_closed_polyline : Shape {
    using Shape::Shape;
    void add(Point p) {
        Shape::add(p);
        orect = get_out_rectangle();
    }
    void draw_lines() const override;
    void move(int dx, int dy) override;
protected:
    pair<Point, Point> get_out_rectangle() const;
    void getx_instersect(const pair<Point, Point> &line,
                         vector<int>& xs) const;
private:
    // Наименьший прямоугольник, окамляющий closed_polyline
    pair<Point, Point> orect{Point{0,0}, Point{0,0}};
};

struct Polygon : Closed_polyline {	// closed sequence of non-intersecting lines
    using Closed_polyline::Closed_polyline;
    void add(Point p);
    void draw_lines() const;
};

struct Poly : Closed_polyline {	// closed sequence of non-intersecting lines
    Poly(initializer_list<Point> lst);
    void draw_lines() const ;
private:
    void add(Point p);
};

struct Lines : Shape {	// indepentdent lines
    Lines() {}
    Lines(initializer_list<Point> lst) : Shape{lst} { if (lst.size() % 2) error("odd number of points for Lines"); }
    void draw_lines() const;
    void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

//-----------------------------------------------------------------------------
// Exercise 13_3
struct Arrow : Lines {
    Arrow(Point b, Point e);
    Arrow(Point b, Point e, int ll, int tt);

    void draw_lines() const;

    int longitudinal() const { return l; }
    int transverse()   const { return t; }
private:
    void init();
    int l = 13;   // Продольная длина усика
    int t = 5;    // Поперечная
};

//-----------------------------------------------------------------------------

struct Text : Shape {
    // the point is the bottom left of the first letter
    Text(Point x, const string& s) : lab{ s } { add(x); }

    void draw_lines() const;

    void set_label(const string& s) { lab = s; }
    string label() const { return lab; }

    void set_font(Font f) { fnt = f; }
    Font font() const { return Font(fnt); }

    void set_font_size(int s) { fnt_sz = s; }
    int font_size() const { return fnt_sz; }
private:
    string lab;	// label
    Font fnt{ fl_font() };
    int fnt_sz{ (14<fl_size()) ? fl_size() : 14 };	// at least 14 point
};

struct Axis : Shape {
    enum Orientation{ x, y, z };
    Axis(Orientation d, Point xy, int length,
         int number_of_notches = 0, string label = 0);

    void draw_lines() const override;
    void move(int dx, int dy) override;
    void set_color(Color c);

    Text label;
    Lines notches;
};

struct Circle : Shape {
    Circle(Point p, int rr)	// center and radius
    :r{ rr } {
        add(Point{ p.x - r, p.y - r });
    }

    void draw_lines() const;

    Point center() const { return { point(0).x + r, point(0).y + r }; }

    virtual void set_radius(int rr) { r=rr; }
    int radius() const { return r; }
private:
    int r;
};

struct Striped_circle : Circle {
    using Circle::Circle;
    void draw_lines() const override;
};

struct Immobile_circle : Circle {
    using Circle::Circle;
protected:
    void move(int dx, int dy) override { }
};

//-----------------------------------------------------------------------------

struct Smiley : Circle {
    const int delim1 = 6; // Знаменатель радиуса для "глаз"
    const int delim2 = 4; // Для "рта"

    Smiley(Point p, int rr);
    void set_radius(int rr) override;

    void draw_lines() const override;

    int eye_radius() const { return er; }
    int mouth_radius() const { return mr; }
private:
    int er; // Радиус глаз
    int mr; // Радиус рта
};

//-----------------------------------------------------------------------------

struct Smiley_hat : Smiley {
    using Smiley::Smiley;
    void draw_lines() const override;
};

//-----------------------------------------------------------------------------

struct Frowny : Smiley {
    using Smiley::Smiley;
    void draw_lines() const override;
};

//-----------------------------------------------------------------------------

struct Frowny_hat : Frowny {
    using Frowny::Frowny;
    void draw_lines() const override;
};

//-----------------------------------------------------------------------------
// Exercise 13_8
struct Regular_hexagon : Shape {
    Regular_hexagon(Point xy, int rr);

    void draw_lines() const;

    Point center() const { return { point(0).x, point(0).y}; }

    int radius() const { return r; }
private:
    int r;
};

Point find_dot(Point center, int angle, int radius);

void find_dot_reg_poly(vector<Point>& points, Point center,
                       int count_angle, int radius, double rot);

//-----------------------------------------------------------------------------
// Exercise 13_10
struct Regular_polygon : Shape {
    Regular_polygon(Point xy, int ss, int rr);

    void draw_lines() const;

    Point center() const { return { point(0).x, point(0).y}; }

    int radius()   const { return r; }
    int sides()    const { return s; }
private:
    int r;
    int s;
};

//-----------------------------------------------------------------------------
// Exercise 14_8
struct Regular_octagon : Regular_polygon {
    Regular_octagon(Point xy, int rr)
        : Regular_polygon(xy, 8, rr)
    {}
};

//-----------------------------------------------------------------------------
// Exercise 13_19
struct Star : Shape {
    Star(Point xy, int nn, int irds, int ords);

    void draw_lines() const;

    Point center() const { return { point(0).x, point(0).y}; }

    int outer_radius()   const { return out_rds; }
    int inner_radius()   const { return in_rds; }
    int number_apex()    const { return n; }
private:
    int out_rds;
    int in_rds;
    int n;
};

//-----------------------------------------------------------------------------
// Exercise 13_14
struct Right_triangle : Shape {
    // Отрицаельные катеты означают противополжное
    // направление относительно осей
    Right_triangle(Point xy, int cc1, int cc2); // xy - вершина прямого угла

    void draw_lines() const;

    int cathetus1() const { return c1; }
    int cathetus2() const { return c2; }
    Point top()     const { return point(0); } // Вывод вершины прямого угла
private:
    int c1; // Катет 1
    int c2;
};

//-----------------------------------------------------------------------------

struct Ellipse : Shape {
    Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
    :w{ ww }, h{ hh } {
        add(Point{ p.x - ww, p.y - hh });
    }

    void draw_lines() const;

    Point center() const { return{ point(0).x + w, point(0).y + h }; }
    Point focus1() const { return{ center().x + int(sqrt(double(w*w - h*h))), center().y }; }
    Point focus2() const { return{ center().x - int(sqrt(double(w*w - h*h))), center().y }; }

    void set_major(int ww) { w=ww; }
    int major() const { return w; }
    void set_minor(int hh) { h=hh; }
    int minor() const { return h; }
private:
    int w;
    int h;
};

struct Arc : Ellipse {
    using Ellipse::Ellipse;

    void set_begin_angle(int b) { ba = b; }
    int begin_angle() const { return ba; }

    void set_end_angle(int e) { ea = e; }
    int end_angle() const { return ea; }

    void draw_lines() const;
private:
    int ba = 0;
    int ea = 360;
};

/*
struct Mark : Text {
    static const int dw = 4;
    static const int dh = 4;
    Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
};
*/

struct Marked_polyline : Open_polyline {
    Marked_polyline(const string& m) :mark(m) { }
    void draw_lines() const;
private:
    string mark;
};

struct Marks : Marked_polyline {
    Marks(const string& m) :Marked_polyline(m)
    { set_color(Color(Color::invisible)); }
};

struct Mark : Marks {
    Mark(Point xy, char c) : Marks(string(1,c)) {add(xy); }
};

/*

struct Marks : Shape {
    Marks(char m) : mark(string(1,m)) { }
    void add(Point p) { Shape::add(p); }
    void draw_lines() const;
private:
    string mark;
};
*/

struct Bad_image : Fl_Image {
    Bad_image(int h, int w) : Fl_Image(h,w,0) { }
    void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
    enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
    Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
    ~Image() { delete p; }
    void draw_lines() const;
    void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
    void move(int dx,int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
private:
    int w,h,cx,cy; // define "masking box" within image relative to position (cx,cy)
    Fl_Image* p;
    Text fn;
};

//-----------------------------------------------------------------------------
// nw() находит верхнюю левую точку
inline Point nw(const Rectangle& r)
{
    return r.point(0);
}

//-----------------------------------------------------------------------------

inline Point nw(const Ellipse& el)
{
    return nw(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point nw(const Circle& cir)
{
    return nw(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point n(const Rectangle& r)
{
    return Point{nw(r).x, nw(r).y+r.height()/2};
}

//-----------------------------------------------------------------------------

inline Point n(const Ellipse& el)
{
    return n(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point n(const Circle& cir)
{
    return n(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point s(const Rectangle& r)
{
    return Point{n(r).x+r.width(), n(r).y};
}

//-----------------------------------------------------------------------------

inline Point s(const Ellipse& el)
{
    return s(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point s(const Circle& cir)
{
    return s(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point e(const Rectangle& r)
{
    return Point{nw(r).x+r.width()/2, nw(r).y+r.height()};
}

//-----------------------------------------------------------------------------

inline Point e(const Ellipse& el)
{
    return e(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point e(const Circle& cir)
{
    return e(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point e(const Texted_box& tb)
{
    return e(Rectangle{tb.point(0), tb.width(), tb.height()});
}

//-----------------------------------------------------------------------------

inline Point w(const Rectangle& r)
{
    return Point{e(r).x, nw(r).y};
}

//-----------------------------------------------------------------------------

inline Point w(const Ellipse& el)
{
    return w(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point w(const Circle& cir)
{
    return w(Rectangle{cir.point(0), 2*cir.radius(),
                       2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point w(const Texted_box& tb)
{
    return w(Rectangle{tb.point(0), tb.width(), tb.height()});
}

//-----------------------------------------------------------------------------

inline Point center(const Rectangle& r)
{
    return Point{w(r).x, s(r).y};
}

//-----------------------------------------------------------------------------

inline Point center(const Ellipse& ell)
{
    return ell.center();
}

//-----------------------------------------------------------------------------

inline Point center(const Circle& cir)
{
    return cir.center();
}

//-----------------------------------------------------------------------------

inline Point center(const Texted_box& tb)
{
    return center(Rectangle{tb.point(0), tb.width(), tb.height()});
}

//-----------------------------------------------------------------------------

inline Point ne(const Rectangle& r)
{
    return Point{n(r).x, e(r).y};
}

//-----------------------------------------------------------------------------

inline Point ne(const Ellipse& el)
{
    return ne(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point ne(const Circle& cir)
{
    return ne(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point se(const Rectangle& r)
{
    return Point{s(r).x, e(r).y};
}

//-----------------------------------------------------------------------------

inline Point se(const Ellipse& el)
{
    return se(Rectangle{el.point(0), 2*el.major(), 2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point se(const Circle& cir)
{
    return se(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

inline Point sw(const Rectangle& r)
{
    return Point{s(r).x, w(r).y};
}

//-----------------------------------------------------------------------------

inline Point sw(const Ellipse& el)
{
    return sw(Rectangle{el.point(0), 2*el.major(),
                        2*el.minor()});
}

//-----------------------------------------------------------------------------

inline Point sw(const Circle& cir)
{
    return sw(Rectangle{cir.point(0), 2*cir.radius(),
                        2*cir.radius()});
}

//-----------------------------------------------------------------------------

}
#endif
