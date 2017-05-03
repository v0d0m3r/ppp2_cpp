#ifndef POINT_H
#define POINT_H

#include "../../../bstroustrup_code/std_lib_facilities.h"

struct Point
{
    Point();
    double x;
    double y;
};

istream& operator>> (istream& is, Point& p);
ostream& operator<< (ostream& os, const Point& p);
ifstream& operator>>(ifstream& ist, Point& p);
ofstream& operator<<(ofstream& ost, const Point& p);
bool operator==(const Point& p1, const Point& p2);
bool operator!=(const Point& p1, const Point& p2);

#endif // POINT_H
