#include "Graph.h"
#include <map>

namespace Graph_lib {

void Shape::draw_lines() const
{
	if (color().visibility() && 1<points.size())	// draw sole pixel?
		for (unsigned int i=1; i<points.size(); ++i)
			fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}

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

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4,
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


//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4,
                            Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

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


void Polygon::draw_lines() const
{
		if (number_of_points() < 3) error("less than 3 points in a Polygon");
		Closed_polyline::draw_lines();
}

//-----------------------------------------------------------------------------
// Exercise 13_18
Poly::Poly(initializer_list<Point> lst)
{
    for (const Point& p : lst ) {
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
}

//-----------------------------------------------------------------------------
// Exercise 13_18
void Poly::draw_lines() const
{
    if (number_of_points() < 3) error("less than 3 points in a Polygon");
    Closed_polyline::draw_lines();
}

//-----------------------------------------------------------------------------

void Open_polyline::draw_lines() const
{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
			Shape::draw_lines();
}


void Closed_polyline::draw_lines() const
{
	Open_polyline::draw_lines();

	if (color().visibility())	// draw closing line:
		fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,point(0).x,point(0).y);
}
void Shape::move(int dx, int dy)
{
	for (unsigned int i = 0; i<points.size(); ++i) {
		points[i].x+=dx;
		points[i].y+=dy;
	}
}

void Lines::draw_lines() const
{
//	if (number_of_points()%2==1) error("odd number of points in set of lines");
	if (color().visibility())
		for (int i=1; i<number_of_points(); i+=2)
			fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
}

void Text::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(),fnt_sz);
	fl_draw(lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt,osz);
}

Function::Function(Fct f, double r1, double r2, Point xy, int count,
                   double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
	if (r2-r1<=0) error("bad graphing range");
	if (count<=0) error("non-positive graphing count");
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i<count; ++i) {
		add(Point(xy.x+int(r*xscale),xy.y-int(f(r)*yscale)));
		r += dist;
	}
}

void Rectangle::draw_lines() const
{
    if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x,point(0).y,w,h);
		fl_color(color().as_int());	// reset color
    }

	if (color().visibility()) {	// edge on top of fill
		fl_color(color().as_int());
        fl_rect(point(0).x,point(0).y,w,h);
	}
}

//-----------------------------------------------------------------------------
// Exercise 13_2
// Фигура состоит из 4 отрезков и 4 эллипсов
void Box::init()
{
    const int& rww = width();
    const int& rhh = height();
    const Point& xy = point(0); // Верхняя левая точка
                                // первого эллипса
    // Вершины, определеяющие отрезки
    Point top2{xy.x, xy.y+rhh-eh};
    Point top4{xy.x+rww-ew, xy.y+rhh};
    Point top7{xy.x+rww-ew, xy.y};
    // Остальные верхние левые точки эллипсов
    add(Point{top2.x, top2.y-eh});
    add(Point{top4.x-ew, top4.y-eh-eh});
    add(Point{top7.x-ew, top7.y});
    // Добавляем вершины, определяющие отрезки
    add(Point{xy.x, xy.y+eh});
    add(top2);
    add(Point{xy.x+ew, xy.y+rhh});
    add(top4);
    add(Point{xy.x+rww, xy.y+rhh-eh});
    add(Point{xy.x+rww, xy.y+eh});
    add(top7);
    add(Point{xy.x+ew, xy.y});
}

//-----------------------------------------------------------------------------
// Exercise 13_2
void Box::draw_lines() const
{
    constexpr int left_up_count = 4; // Количество верхних
                                     // левых точек еллипсов
    constexpr int angle = 90;        // Угол увеличения
    if (color().visibility()) {	// edge on top of fill
        fl_color(color().as_int());
        for (int i=0; i < left_up_count; ++i) { // paint ellipses
            if (i==left_up_count-1)
                fl_arc(point(i).x,point(i).y,ew+ew,eh+eh,
                       0, angle);
            else
                fl_arc(point(i).x,point(i).y,ew+ew,eh+eh,
                       (i+1)*angle, (i+2)*angle);
        }
        // paint four lines
        for (int i=left_up_count+1; i<number_of_points(); i+=2)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
    }
}

//-----------------------------------------------------------------------------
// Exercise 13_3
Arrow::Arrow(Point b, Point e)
{
    set_fill_color(color());
    add(b, e);
    if (l<=0 || t<=0) error("Bad arrow: non-positive side");
    init();
}

//-----------------------------------------------------------------------------
// Exercise 13_3
Arrow::Arrow(Point b, Point e, int ll, int tt)
    : l{ll}, t{tt}
{
    set_fill_color(color());
    add(b, e);
    if (l<=0 || t<=0) error("Bad arrow: non-positive side");
    init();
}

//-----------------------------------------------------------------------------

void Arrow::init()
{
    const Point& b = point(0);
    const Point& e = point(1);
    // Нахождение координат вектора be
    double vect_x = e.x - b.x;
    double vect_y = e.y - b.y;
    double lenght = sqrt(pow(vect_x, 2) + pow(vect_y, 2));  // Длина вектора
    double unit_x = vect_x / lenght;    // x, единичного вектора
    double unit_y = vect_y / lenght;    // y, единичного вектора
    // Находим точку O, через которую пойдет
    // одна из сторон "усика"
    double opoint_x = e.x - l * unit_x;
    double opoint_y = e.y - l * unit_y;
    // Находим вектор нормали,
    // умноженный на поперечную длину "усика"
    double normal_x = t * unit_y;
    double normal_y = t *(-unit_x);
    // Искомые точки "усиков"
    Point a{int(opoint_x + normal_x), int(opoint_y + normal_y)};
    Point c{int(opoint_x - normal_x), int(opoint_y - normal_y)};
    add(a, c); // Формируем отрезки стрелы
    add(c, e);
    add(e, a);
}

void Arrow::draw_lines() const
{
    // Заполняем цветом усик
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=2; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }
    Lines::draw_lines();
}

//-----------------------------------------------------------------------------
// Exercise 13_8
Regular_hexagon::Regular_hexagon(Point xy, int rr)
    : r{rr}
{
    if (r<=0) error("Regular_hexagon: non-positive radius");
    add(xy);
    vector<Point> points;
    find_dot_reg_poly(points, xy, 6, r, 0.00);
    for (int i=0; i < points.size(); ++i)
        add(points[i]);
}

//-----------------------------------------------------------------------------
// Exercise 13_8
void Regular_hexagon::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=1; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }
    if (color().visibility()) {
        for (int i=2; i<number_of_points(); ++i)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);

        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,point(1).x,point(1).y);
    }
}

//-----------------------------------------------------------------------------
// Exercise 13_8
void find_dot_reg_poly(vector<Point>& points, Point center,
                       int count_angle, int radius, double rot)
{
    const double delta_angle = 360.00 / count_angle;
    double angle = rot; // Угол пересечения вершины
                        // и описываемой окружности
    for (int i=0; i < count_angle; ++i) {
        points.push_back(find_dot(center, angle, radius));
        angle += delta_angle; // Увеличиваем угол на величину
                              // угла правильного многоугольника
    }
}

//-----------------------------------------------------------------------------
// Exercise 13_8
Point find_dot(Point center, int angle, int radius)
{
    return Point{
        center.x + radius * cos(angle * M_PI/180.0),
        center.y + radius * sin(angle * M_PI/180.0)
    };
}

//-----------------------------------------------------------------------------
// Exercise 13_10
Regular_polygon::Regular_polygon(Point xy, int ss, int rr)
    : r{rr}, s{ss}
{
    if (r<=0) error("Regular_polygon: non-positive radius");
    if (s<=2) error("Regular_polygon: non-correct polygon");
    add(xy);
    vector<Point> points;
    find_dot_reg_poly(points, xy, s, r, 0.00);
    for (int i=0; i < points.size(); ++i)
        add(points[i]);
}

//-----------------------------------------------------------------------------
// Exercise 13_10
void Regular_polygon::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=1; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }
    if (color().visibility()) {
        for (int i=2; i<number_of_points(); ++i)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);

        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,point(1).x,point(1).y);
    }
}

//-----------------------------------------------------------------------------

void find_dot_star(vector<Point>& points, Point cntr, int R, int r, int n)
{
    int a=0;
    for (int i=1; i < n*2+2; ++i) {
        if (!(i%2)) // Четно?
            points.push_back(Point{cntr.x+r/2*cos(a*M_PI/180),
                                   cntr.y-r/2*sin(a*M_PI/180)});
        else
            points.push_back(Point{cntr.x+R*cos(a*M_PI/180),
                                   cntr.y-R*sin(a*M_PI/180)});
        a=a+180/n;
    }
}

//-----------------------------------------------------------------------------
// Exercise 13_19
Star::Star(Point xy, int nn, int irds, int ords)
    :n{nn}, in_rds{irds}, out_rds{ords}
{
    if (in_rds<=0 || out_rds<=0)
        error("Regular_polygon: non-positive radius");
    if (n<=2) error("Regular_polygon: non-correct polygon");
    add(xy);
    vector<Point> points;
    find_dot_star(points, xy, out_rds, in_rds, n);
    for (int i=0; i < points.size(); ++i)
        add(points[i]);
}

//-----------------------------------------------------------------------------
// Exercise 13_10
void Star::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=1; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }
    if (color().visibility()) {
        for (int i=2; i<number_of_points(); ++i)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);

        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,point(1).x,point(1).y);
    }
}

//-----------------------------------------------------------------------------
// Exercise 13_14
Right_triangle::Right_triangle(Point xy, int cc1, int cc2)
    : c1{cc1}, c2{cc2}
{
    if (c1==0 || c2==0)
        error("Катет не может иметь нулевую длину");
    add(xy);
    add(Point{xy.x + c1, xy.y});
    add({xy.x, xy.y + c2});
}

//-----------------------------------------------------------------------------

void Right_triangle::draw_lines() const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=0; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }

    if (color().visibility()) {
        for (int i=1; i<number_of_points(); ++i)
            fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);

        fl_line(point(number_of_points()-1).x,
                point(number_of_points()-1).y,point(0).x,point(0).y);
    }
}

//-----------------------------------------------------------------------------

Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
	:label(Point(0,0),lab)
{
	if (length<0) error("bad axis length");
	switch (d){
	case Axis::x:
		{	Shape::add(xy);	// axis line
			Shape::add(Point(xy.x+length,xy.y));	// axis line
			if (1<n) {
				int dist = length/n;
				int x = xy.x+dist;
				for (int i = 0; i<n; ++i) {
					notches.add(Point(x,xy.y),Point(x,xy.y-5));
				x += dist;
			}
		}
		// label under the line
		label.move(length/3,xy.y+20);
		break;
	}
	case Axis::y:
		{	Shape::add(xy);	// a y-axis goes up
			Shape::add(Point(xy.x,xy.y-length));
			if (1<n) {
			int dist = length/n;
			int y = xy.y-dist;
			for (int i = 0; i<n; ++i) {
				notches.add(Point(xy.x,y),Point(xy.x+5,y));
				y -= dist;
			}
		}
		// label at top
		label.move(xy.x-10,xy.y-length-10);
		break;
	}
	case Axis::z:
		error("z axis not implemented");
	}
}

void Axis::draw_lines() const
{
	Shape::draw_lines();	// the line
	notches.draw();	// the notches may have a different color from the line
	label.draw();	// the label may have a different color from the line
}


void Axis::set_color(Color c)
{
	Shape::set_color(c);
	notches.set_color(c);
	label.set_color(c);
}

void Axis::move(int dx, int dy)
{
	Shape::move(dx,dy);
	notches.move(dx,dy);
	label.move(dx,dy);
}

void Circle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
	}
}

void Smiley::draw_lines() const
{
    Circle::draw_lines();
    Point pp{0,0};
    pp.x = point(0).x + radius()/2.0 - radius() / 6.0;
    pp.y = point(0).y + radius()/2.0;
    int pp_r = radius() / 6.0;
    if (fill_color().visibility()) {	// fill
        fl_color(fill_color().as_int());
        fl_pie(pp.x, pp.y, pp_r+pp_r-1,pp_r+pp_r-1,0,360);
        fl_color(color().as_int());	// reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(pp.x, pp.y, pp_r+pp_r,pp_r+pp_r,0,360);
    }

    Point pp2{0,0};
    pp2.x = point(0).x + 1.5*radius() - radius() / 6.0;
    pp2.y = point(0).y + radius()/2.0;
    int pp2_r = radius() / 6.0;

    if (fill_color().visibility()) {	// fill
        fl_color(fill_color().as_int());
        fl_pie(pp2.x,pp2.y,pp2_r+pp2_r-1,pp2_r+pp2_r-1,0,180);
        fl_color(color().as_int());	// reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(pp2.x,pp2.y,pp2_r+pp2_r,pp2_r+pp2_r,0,180);
    }
}

void Ellipse::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,w+w-1,h+h-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
        fl_arc(point(0).x,point(0).y,w+w,h+h,0,360);
	}
}

void Arc::draw_lines() const
{
    if (fill_color().visibility()) {	// fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x,point(0).y,major()+major()-1,minor()+minor()-1,ba,ea);
        fl_color(color().as_int());	// reset color
    }
    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, major()+major(),
               minor()+minor(),ba,ea);
    }
}

void draw_mark(Point xy, char c)
{
	static const int dx = 4;
	static const int dy = 4;
	string m(1,c);
	fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

void Marked_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
	for (int i=0; i<number_of_points(); ++i)
		draw_mark(point(i),mark[i%mark.size()]);
}

//-----------------------------------------------------------------------------
// Exercise 13_6
void Texted_box::draw_lines() const
{
    Box::draw_lines();
    fl_draw(lab.c_str(),point(0).x+10,point(0).y+20);
}
//-----------------------------------------------------------------------------
/*
void Marks::draw_lines() const
{
	for (int i=0; i<number_of_points(); ++i)
		fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
}
*/


std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
	suffix_map["jpg"] = Suffix::jpg;
	suffix_map["JPG"] = Suffix::jpg;
	suffix_map["jpeg"] = Suffix::jpg;
	suffix_map["JPEG"] = Suffix::jpg;
	suffix_map["gif"] = Suffix::gif;
	suffix_map["GIF"] = Suffix::gif;
	suffix_map["bmp"] = Suffix::bmp;
	suffix_map["BMP"] = Suffix::bmp;
	return 0;
}

Suffix::Encoding get_encoding(const string& s)
		// try to deduce type from file name using a lookup table
{
	static int x = init_suffix_map();

	string::const_iterator p = find(s.begin(),s.end(),'.');
	if (p==s.end()) return Suffix::none;	// no suffix

	string suf(p+1,s.end());
	return suffix_map[suf];
}

bool can_open(const string& s)
            // check if a file named s exists and can be opened for reading
{
	ifstream ff(s.c_str());
	if (!ff) return false;
	return true;
}


// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, string s, Suffix::Encoding e)
	:w(0), h(0), fn(xy,"")
{
	add(xy);

	if (!can_open(s)) {
		fn.set_label("cannot open \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
		return;
	}

	if (e == Suffix::none) e = get_encoding(s);

	switch(e) {
	case Suffix::jpg:
		p = new Fl_JPEG_Image(s.c_str());
		break;
	case Suffix::gif:
		//Fl_GIF_Image fl_gf(s.c_str());
		p = new Fl_GIF_Image(s.c_str());
		break;
//	case Suffix::bmp:
//		p = new Fl_BMP_Image(s.c_str());
//		break;
	default:	// Unsupported image encoding
		fn.set_label("unsupported file type \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
	}
}

void Image::draw_lines() const
{
	if (fn.label()!="") fn.draw_lines();

	if (w&&h)
		p->draw(point(0).x,point(0).y,w,h,cx,cy);
	else
		p->draw(point(0).x,point(0).y);
}

} // Graph
