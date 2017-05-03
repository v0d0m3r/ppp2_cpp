#include "point.hpp"

//------------------------------------------------------------------------------

Point::Point():x{0.00}, y{0.00}
{

}

//------------------------------------------------------------------------------

istream& operator>> (istream& is, Point& p)
{
    double x,y;
    is >> x >> y;
    if (!is) return is;
    p.x = x;
    p.y = y;
    return is;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Point& p)
{
    return os << "x = " << p.x << '\t'
              << "y = " << p.y << '\n';
}

//------------------------------------------------------------------------------

ifstream& operator>>(ifstream& ist, Point& p)
{
    double x, y;
    ist >> x >> y;
    if (!ist)
        return ist;
    p.x = x;
    p.y = y;
    return ist;
}

//------------------------------------------------------------------------------

ofstream& operator<<(ofstream& ost, const Point& p)
{
    ost << p.x << ' ' << p.y << '\n';
    return ost;
}

//------------------------------------------------------------------------------

bool operator==(const Point& a, const Point& b)
{
    return (a.x==b.x && a.y==b.y);
}

//------------------------------------------------------------------------------

bool operator!=(const Point& a, const Point& b)
{
    return !(a == b);
}

//------------------------------------------------------------------------------
