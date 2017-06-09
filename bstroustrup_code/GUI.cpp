#include "GUI.h"
#include "std_lib_facilities.h"
#include <sstream>

using namespace Graph_lib;


void Button::attach(Window& win)
	{
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
		own = &win;
	}

int In_box::get_int()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
//	return atoi(pi.value());
	const char* p = pi.value();
	if (!isdigit(p[0])) return -999999;
	return atoi(p);
}

string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	return string(pi.value());
}

void In_box::attach(Window& win)
{
	pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
	own = &win;
}

void Out_box::put(int i)
{
	Fl_Output& po = reference_to<Fl_Output>(pw);
	std::stringstream ss;
	ss << i;
	po.value(ss.str().c_str());
}

void Out_box::put(const string& s)
{
	reference_to<Fl_Output>(pw).value(s.c_str());
}

void Out_box::attach(Window& win)
{
	pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
	own = &win;
}

/*Menu::Menu(Point xy, int w, int h, Kind kk, const string& s)
:Widget(xy,w,h,s,0), k(kk), offset(0)
{
}*/

int Menu::attach(Button& b)
{
	b.width = width;
	b.height = height;

	switch(k) {
	case horizontal:
		b.loc = Point(loc.x+offset,loc.y);
		offset+=b.width;
		break;
	case vertical:
		b.loc = Point(loc.x,loc.y+offset);
		offset+=b.height;
		break;
	}
	selection.push_back(&b);
	return int(selection.size()-1);
}

int Menu::attach(Button* p)
{
//	owned.push_back(p);
	return attach(*p);
}

//-----------------------------------------------------------------------------

Analog_clock::Analog_clock(Point xy, int rr)
    : Widget(xy, rr, rr, "", 0),
      dial{xy, rr}
{
    h.set_style(Line_style{Line_style::solid, 3});
    m.set_style(Line_style{Line_style::solid, 3});
    update();
}

//-----------------------------------------------------------------------------

void Analog_clock::attach(Window& win)
{
    win.attach(dial);
    win.attach(h);
    win.attach(m);
    win.attach(s);

    own = &win;
}

//-----------------------------------------------------------------------------
// Получаем точку соответствующую
// текущему виду часовой стрелки и ее времени
inline Point get_watch_arrow_end(Point o, int r, int common, int current)
{
    double alpha{90 - 360.0 / common * current};
    return Point{static_cast<int>(o.x + r * std::cos(alpha * M_PI / 180.0)),
                 static_cast<int>(o.y - r * std::sin(alpha * M_PI / 180.0))};
}

//-----------------------------------------------------------------------------
// Пересчет координат часовых стрелок
void Analog_clock::update()
{
    constexpr int hours{12};
    constexpr int min_or_sec{60};

    int r{dial.radius()};
    Point o{dial.center()};

    ct.update();    // Обновляем текущее время

    h.set_point(o, get_watch_arrow_end(o, r-30,
                                       hours, ct.hour()));
    m.set_point(o, get_watch_arrow_end(o, r-10,
                                       min_or_sec, ct.minute()));
    s.set_point(o, get_watch_arrow_end(o, r-5,
                                       min_or_sec, ct.second()));
}

//-----------------------------------------------------------------------------
