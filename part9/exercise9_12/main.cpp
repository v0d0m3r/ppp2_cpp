#include "chrono.h"

//------------------------------------------------------------------------------

int main()
{
    Chrono::Date d;
    cout << d << '\n';
    d.add_month(14);
    cout << d << '\n';
    Chrono::next_sunday(d);
    cout << Chrono::next_sunday(d) << '\n';
    cout << Chrono::week_of_year(d) << '\n';
    return 0;
}

//------------------------------------------------------------------------------
