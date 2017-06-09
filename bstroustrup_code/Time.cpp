#include "Time.hpp"

//-----------------------------------------------------------------------------

using namespace std;
using namespace std::chrono;

//-----------------------------------------------------------------------------
// Получаем разницу локального времени и utc
int get_utc_offset()
{
    char delim = ',';
    time_t t = time(nullptr);

    ostringstream os;
    os << put_time(gmtime(&t), "%I") << delim;
    os << put_time(localtime(&t), "%I");

    int local_hour = 0, utc_hour = 0;

    istringstream is{os.str()};
    is >> utc_hour >> delim >> local_hour;
    if (!is) return -1;

    return local_hour - utc_hour;
}

//-----------------------------------------------------------------------------

void Current_time::update()
{
    system_clock::time_point now = system_clock::now();
    system_clock::duration tp = now.time_since_epoch();

    hours hh = duration_cast<hours>(tp);
    hs = ((hh.count()) % 24) % 24 + get_utc_offset();

    minutes m = duration_cast<minutes>(tp);
    ms = m.count()  % 60;

    seconds s = duration_cast<seconds>(tp);
    ss = s.count() % 60;
}

//-----------------------------------------------------------------------------
