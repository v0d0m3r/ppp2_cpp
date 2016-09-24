#ifndef POINT_H
#define POINT_H

struct Point {
    Point(int xx, int yy)
        : x(xx), y(yy){}
    int x, y;
};

inline bool operator==(Point a, Point b) { return (a.x==b.x && a.y==b.y); }
inline bool operator!=(Point a, Point b) { return !(a==b); }

#endif // POINT_H
