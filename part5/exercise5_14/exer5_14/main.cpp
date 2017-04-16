//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

constexpr char mon_ch = '1';
constexpr char thues_ch = '2';
constexpr char wed_ch = '3';
constexpr char thur_ch = '4';
constexpr char frid_ch = '5';
constexpr char sat_ch = '6';
constexpr char sun_ch = '7';

//-----------------------------------------------------------------------------

char check_inp_day(string unknown_day)
{
    char result_day = 0;
    if (unknown_day=="Monday" or unknown_day=="Mon" or unknown_day=="monday")
        result_day = mon_ch;
    else if (unknown_day=="Thuesday" or unknown_day=="Thue" or unknown_day=="thuesday")
        result_day = thues_ch;
    else if (unknown_day=="Wednesday" or unknown_day=="Wed" or unknown_day=="wednesday")
        result_day = wed_ch;
    else if (unknown_day=="Thursday" or unknown_day=="Thur" or unknown_day=="thursday")
        result_day = thur_ch;
    else if (unknown_day=="Friday" or unknown_day=="Fri" or unknown_day=="friday")
        result_day = frid_ch;
    else if (unknown_day=="Saturday" or unknown_day=="Sat" or unknown_day=="saturday")
        result_day = sat_ch;
    else if (unknown_day=="Sunday" or unknown_day=="Sun" or unknown_day=="sunday")
        result_day = sun_ch;
    else if (unknown_day=="|")
        result_day = 'e';
    else
        result_day = 'n';

    return result_day;
}

//-----------------------------------------------------------------------------

void print_numbers_day(vector<int> day, char day_ch)
{
    string name_day = "";
    switch (day_ch) {
        case mon_ch:
            name_day = "Monday";
            break;
        case thues_ch:
            name_day = "Thuesday";
            break;
        case wed_ch:
            name_day = "Wednesday";
            break;
        case thur_ch:
            name_day = "Thursday";
            break;
        case frid_ch:
            name_day = "Friday";
            break;
        case sat_ch:
            name_day = "Saturday";
            break;
        case sun_ch:
            name_day = "Sunday";
            break;
        default:
        break;
    }


    int sum = 0;
    cout << "Значения " << name_day << ":\n";
    for (size_t i=0; i<day.size(); ++i)
    {
        cout << day[i] << '\t';
        sum += day[i];
    }
    cout << "\nсумма:" << sum << '\n';
}

//-----------------------------------------------------------------------------

int main()
try {
    bool input_err = true;
    vector<int> monday, thuesday, wednesday, thursday,
                friday, saturday, sunday;
    int unnecessary = 0;
    char day_of_week = 0;
    string input_day = "";
    cout << "Введите пары (день недели, значение), для выхода введите \"|\":\n";
    for(int number = 0; cin>>input_day>>number;)
    {
        day_of_week = check_inp_day(input_day);
        switch (day_of_week) {
            case mon_ch:
                monday.push_back(number);
                break;
            case thues_ch:
                thuesday.push_back(number);
                break;
            case wed_ch:
                wednesday.push_back(number);
                break;
            case thur_ch:
                thursday.push_back(number);
                break;
            case frid_ch:
                friday.push_back(number);
                break;
            case sat_ch:
                saturday.push_back(number);
                break;
            case sun_ch:
                sunday.push_back(number);
                break;
            case 'e':
                input_err = false;
                break;
            default:
                unnecessary++;
                break;
        }
        if (!input_err)
            break;
    }

    print_numbers_day(monday, mon_ch);
    print_numbers_day(thuesday, thues_ch);
    print_numbers_day(wednesday, wed_ch);
    print_numbers_day(thursday, thur_ch);
    print_numbers_day(saturday, sat_ch);
    print_numbers_day(sunday, sun_ch);

    cout << "Непопавшие в последовательность числа: "
         << unnecessary << '\n';

    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open();
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    keep_window_open();
    return -2;
}

//-----------------------------------------------------------------------------
