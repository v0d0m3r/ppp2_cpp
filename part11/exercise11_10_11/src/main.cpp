//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

vector<string> split(const string& s)
{
    vector<string> v;
    istringstream buffer{s};
    for (string tmp; buffer >> tmp;) v.push_back(tmp);
    return v;
}

//------------------------------------------------------------------------------

vector<string> split(const string& s, const string& w)
{
    string line = s;
    // При необходимости заменяем символы
    for (auto& c : line)
        for (const auto& white : w)
            if (c == white)
                c = ' ';

    vector<string> v;
    istringstream buf{line};
    for (string tmp; buf >> tmp;) v.push_back(tmp);
    return v;
}

//------------------------------------------------------------------------------

int main()
{
    string s = "Hello,my name is kon;Aftre;Whats-up";
    string w = ";,";
    vector<string> vs = split(s, w);
    for (const auto& tmp : vs)   cout << tmp << '\n';
    return 0;
}

//------------------------------------------------------------------------------
