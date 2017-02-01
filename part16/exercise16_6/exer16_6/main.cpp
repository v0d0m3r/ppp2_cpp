#include <chrono>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <list>
#include <forward_list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <regex>
#include <random>
#include <stdexcept>

using namespace std;
using namespace std::chrono;

int getUTCoffset()
{
    time_t currtime;
    struct tm * timeinfo;
    time ( &currtime );
    timeinfo = gmtime ( &currtime );
    time_t utc = mktime( timeinfo );
    timeinfo = localtime ( &currtime );
    time_t local = mktime( timeinfo );

    // Get offset in hours from UTC
    double offsetFromUTC = difftime(utc, local) / 3600;

    // Adjust for DST
    if (timeinfo->tm_isdst)
        offsetFromUTC -= 1;
    return static_cast<int>(offsetFromUTC);
}

int main()
{
    system_clock::time_point now = system_clock::now();
    system_clock::duration tp = now.time_since_epoch();

    int offsetFromUTC = getUTCoffset();

    hours h = duration_cast<hours>(tp);
    cout << "current hour " << ( (h.count() - offsetFromUTC) % 24 ) % 24 << endl;

    minutes m = duration_cast<minutes>(tp);
    cout << "current hour " << m.count()  % 60 << endl;

    seconds s = duration_cast<seconds>(tp);
    cout << "seconds " << s.count() % 60;
}

/*Стрелочные часы, а не аналоговые...

В сутках 24*60*60 секунд, обход окружности дает угол в 360 градусов, т.е 1 сек - угол в -360/24/60/60. градуса это у тебя будет часовая стрелка.
Ну итд.

Добавлено через 49 минут
Вот пример секундной стрелки
C++
Выделить код

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22



#include <cmath>
#include <Math.hpp>
#include <DateUtils.hpp>

float alpha;
int r=50,x,y;
TPoint O(100,100);
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
Image1->Canvas->Brush->Color=clBtnFace;
Image1->Canvas->FillRect(Image1->ClientRect);

alpha=90-360/60.*SecondOf(Time());

x= O.x+ r*std::cos(DegToRad(alpha));
y= O.y+ -r*std::sin(DegToRad(alpha));

Image1->Canvas->MoveTo(O.x,O.y);
Image1->Canvas->LineTo(x,y);
}
//---------------------------------------------------------------------------
*/
