#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <stdio.h>
#include <fcntl.h>
#include <stdexcept>
#include <ctime>
#include <iostream>
#include "fstream"

struct Point
{
    Point();
    double x;
    double y;
};

std::istream& operator>> (std::istream& is, Point& p);
std::ostream& operator<< (std::ostream& os, const Point& p);
std::ifstream& operator>>(std::ifstream& ist, Point& p);
std::ofstream& operator<<(std::ofstream& ost, const Point& p);
bool operator==(const Point& p1, const Point& p2);
bool operator!=(const Point& p1, const Point& p2);


#endif // POINT_H
