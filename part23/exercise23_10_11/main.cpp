//------------------------------------------------------------------------------

#include "Table_file.hpp"

//------------------------------------------------------------------------------

map<string, Row> exercise23_10()
{
    string fname;
    cout << "Please, input file name: ";
    cin >> fname;

    Table_file tfile{fname}; // Инициализируем table file
                             // данными из файла
    regex grade{R"(^\d+)"};
    regex row{R"(^([\w ]+)(\s+\d+)(\s+\d+)(\s+\d+)$)"};

    map<string, Row> data_tb;
    pair<string, Row> tail;
    for (auto p{tfile.begin()}; p != tfile.end(); ++p) {
        smatch matches;
        if (!regex_match(*p, matches, row))
            error("неверная строка ");

        Row curr_row{m_to<int>(matches[2]),
                     m_to<int>(matches[3]),
                     m_to<int>(matches[4])};

        string grade_str = matches[1];
        if (regex_search(grade_str, matches, grade))
            grade_str = matches[0];

        if (*p == tfile.tail()) {
            tail = make_pair(grade_str, curr_row);
            break;
        }
        data_tb[grade_str] += curr_row;
    }
    cout << tfile.head() << '\n';
    for (const auto& t : data_tb)
        cout << t.first << "\t\t\t" << t.second << '\n';
    cout << tail.first << "\t\t" << tail.second << '\n';
    return data_tb;
}

//------------------------------------------------------------------------------

void exercise23_11_10()
{
    map<string, Row> data_tb{exercise23_10()};    
    bool up  {false};
    bool down{false};

    auto p{data_tb.begin()};
    ++p;
    auto prev{data_tb.begin()};

    if      (p->second.total > prev->second.total) up   = true;
    else if (p->second.total < prev->second.total) down = true;
    else {
        cout << "sequence do not increase and decrease\n";
        return;
    }
    while (p != data_tb.end()) {
        ++prev;
        ++p;
        if      (up   && p->second.total > prev->second.total) continue;
        else if (down && p->second.total < prev->second.total) continue;
        else {
            cout << "sequence is not increasing and decreasing\n";
            return;
        }
    }
    if      (up  ) cout << "sequence is increasing\n";
    else if (down) cout << "sequence is decreasing\n";
    else           cout << "impossible\n";
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise23_11_10();
    return 0;
}
catch (const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
