//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void print(const vector<string>& str, const vector<int>& val)
{
    for (size_t i=0; i < str.size(); ++i)
        if(i < str.size()-1)
            cout << str[i] << ": "
                 << val[i] << ',';
        else
            cout << str[i] << ": "
                 << val[i] << '\n';
}

//------------------------------------------------------------------------------

int main()
{  
    vector<string> name;
    cout << "Введите произвольное количество "
         << "имен через пробел, введите "
         << "'|'\n";

    for (string s; cin >> s;)
        if (s == "|")
            break;
        else
            name.push_back(s);


    vector<int> age(name.size());
    cout << "Введите " << name.size()
         << " возрастов через пробел\n";
    int value;
    for (size_t i=0; i<age.size(); i++) {
        cin >> value;
        age[i] = value;
    }
    vector<string> temp_n = name;
    vector<int> temp_ag = age;
    sort(name.begin(), name.end());
    for (size_t i=0; i<name.size();++i)
        for (size_t j=0; j<name.size();++j)
        {
            if (name[i] == temp_n[j])
                age[i] = temp_ag[j];
        }
    temp_ag.clear();
    temp_n.clear();
    print(name,age);

    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
/* Тест
 * Введите 5 имен через пробел
anna1 vanna2 banna3 wanga4 panga5
Введите 5 возрастов через пробел
1 2 3 4 5
anna1: 1,banna3: 2,panga5: 3,vanna2: 4,wanga4: 5
*/
