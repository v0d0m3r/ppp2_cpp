#include "point.h"

//------------------------------------------------------------------------------

Point::Point():x{0.00}, y{0.00}
{

}

//------------------------------------------------------------------------------

std::istream& operator>> (std::istream& is, Point& p)
{
    double x,y;
    is >> x >> y;
    if (!is) return is;
    p.x = x;
    p.y = y;
    return is;
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    return os << "x = " << p.x << '\t'
              << "y = " << p.y << '\n';
}

//------------------------------------------------------------------------------

std::ifstream& operator>>(std::ifstream& ist, Point& p)
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

std::ofstream& operator<<(std::ofstream& ost, const Point& p)
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
