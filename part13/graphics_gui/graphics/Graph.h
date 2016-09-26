#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include "Point.h"
#include<vector>
//#include<string>
//#include<cmath>
#include "fltk.h"
#include "std_lib_facilities.h"

//-----------------------------------------------------------------------------

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

struct Line : Shape {           // Класс Line - это класс Shape,
                                // определенный двумя точками
    // Создание объекта Line из двух точек Point
    Line(Point p1, Point p2) { add(p1); add(p2); }
};

//-----------------------------------------------------------------------------

struct Lines : Shape {  // Связанные друг с другом линии
    Lines() {}          // Пустой набор линий
    Lines(initializer_list<Point> lst); // Инициализация списком точек
    void draw_lines() const;
    void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

//-----------------------------------------------------------------------------

struct Color {
    enum Color_type {
        red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
        yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
        magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
        dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
        dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
    };

    enum Transparency { invisible = 0, visible = 255 };

    Color(Color_type cc) : c{Fl_Color(cc)}, v{visible} {}
    Color(Color_type cc, Transparency vv)
        : c{Fl_Color(cc)}, v{vv} {}
    Color(int cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Transparency vv) : c{Fl_Color()}, v{vv} {} // Цвет по
                                                     // умолчанию
    int as_int() const { return c; }

    char visiblity() const { return v; }
    void set_visiblity(Transparency vv) { v = vv; }

private:
    char v;     // Видимый или невидимый
    Fl_Color c;
};

//-----------------------------------------------------------------------------

struct Line_style {
    enum Line_style_type {
        solid      = FL_SOLID,      // -------
        dash       = FL_DASH,		// - - - -
        dot        = FL_DOT,		// .......
        dashdot    = FL_DASHDOT,	// - . - .
        dashdotdot = FL_DASHDOTDOT,	// -..-..
    };
    Line_style(Line_style_type ss) : s{ss}, w{0} {}
    Line_style(Line_style_type ss, int ww) : s{ss}, w{ww} {}
    Line_style(int ss) : s{ss}, w{0} {}

    int width() const { return w; }
    int style() const { return s; }
private:
    int s;
    int w;
};

//-----------------------------------------------------------------------------

struct Open_polyline : Shape {  // Открытая последовательность линий
    using Shape::Shape;         // Использует конструктор Shape
    void add(Point p) { Shape::add(p); }
};


//-----------------------------------------------------------------------------

struct Closed_polyline
        : Open_polyline { // Замкнутая последовательность линий
    using Open_polyline::Open_polyline; // Использует конструкторы
                                        // Open_polyline
    void draw_lines() const;
};

//-----------------------------------------------------------------------------

struct Polygon : Closed_polyline {
    using Closed_polyline::Closed_polyline;

    void add(Point p);
    void draw_lines() const;
};

//-----------------------------------------------------------------------------

struct Rectangle : Shape {
    Rectangle(Point xy, int ww, int hh);
    Rectangle(Point x, Point y);
    void draw_lines() const;

    int height() const { return h; }
    int weight() const { return w; }
private:
    int h;  // Высота
    int w;  // Длина
};

//-----------------------------------------------------------------------------

struct Text : Shape {
    // Точка в левом нижнем углу первой буквы
    Text(Point x, const string& s)
        :lab{s}
    { add(x); }

    void draw_lines() const;
    void set_label(const string& s) { lab = s; }
    string label() const { return lab; }

    void set_font(Font f) { fnt = f; }
    Font font() const { return fnt; }

    void set_font_size(int s) { fnt_sz = s; }
    int font_size() { fnt_sz; }
private:
    string lab; // Текст
    Font fnt{fl_font()};
    int fnt_sz{(fl_size()<14) ? 14 : fl_size()};
};

//-----------------------------------------------------------------------------

struct Circle : Shape {
    Circle(Point p, int rr); // Центр и радиус

    void draw_lines() const;
    Point center() const;
    int radius() const { return r; }
    void set_radius(int rr)
    {   // Поддержка центра
        set_point(0, Point{center().x - rr, center().y-rr});
        r = rr;
    }
private:
    int r;
};

//-----------------------------------------------------------------------------

struct Ellipce : Shape {
    // Центр, минимальное и максимальное расстояние до центра
    Ellipce(Point p, int ww, int hh);

    void draw_lines() const;

    Point center() const;
    Point focus1() const;
    Point focus2() const;

    void set_major(int ww)
    {   // Поддержка центра
        set_point(0, Point{center().x-ww, center().y-h});
        w = ww;
    }
    int major() const { return w; }
    void set_minor(int hh)
    {   // Поддержка центра
        set_point(0, Point{center().x-w, center().y-hh});
        h = hh;
    }
    int minor() const { return h; }

private:
    int w;
    int h;
};

//-----------------------------------------------------------------------------

struct Marked_polyline : Open_polyline {
    Marked_polyline(const string& m) : mark{m}
    { if (mark == "") mark = "*"; }
    Marked_polyline(const string &m,
                    initializer_list<Point> lst);
    void draw_lines() const;
private:
    string mark;
};

//-----------------------------------------------------------------------------

}


#endif
