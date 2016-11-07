#ifndef GRAPH_H
#define GRAPH_H

#include "../../../bstroustrup_code/Point.h"
#include<vector>
#include "../../../bstroustrup_code/fltk.h"
#include "../../../bstroustrup_code/std_lib_facilities.h"

namespace Graph_lib {

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

class Shape {   // Работает с цветом и стилем,
                // хранит последовательность точек
public:
    void draw() const;                  // Вывод цветных линий
    virtual void move(int dx, int dy);  // Перемещение фигуры
                                        // +=dx и +=dy
    void set_color(Color col);
    Color color() const;

    void set_style(Line_style sty);
    Line_style style() const;

    void set_fill_color(Color col);
    Color fill_color() const;

    Point point(int i) const;           // Доступ только для чтения
    int number_of_points() const;

    Shape(const Shape&) = delete;       // Предотращение копрования
    Shape& operator=(const Shape&)
                        = delete;

    virtual ~Shape() {}
protected:
    Shape() {}
    Shape(initializer_list<Point> lst); // Добавление точек
    virtual void draw_lines() const;    // Вывод линий
    void add(Point p);                  // Добавление p к точкам
    void set_point(int i, Point p);     // points[i]=p;
private:
    vector<Point> points;               // Не используется всеми
                                        // фигурами
    Color lcolor{fl_color()};           // Цвет линий и символов
                                        // (значение по умолчанию)
    Line_style ls{0};
    Color fcolor{Color::invisible};     // Цвет заполнения
};

}

#endif // GRAPH_H
