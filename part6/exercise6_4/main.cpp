//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Name_value {
public:
    Name_value()
        : name(""),scores(0) {} // Создает объект класса Name_value,
                                // считывающий данные из cin
    string name;                // Имя
    int scores;
};

//------------------------------------------------------------------------------

int main()
{
    vector<Name_value> all_name_value;
    cout << "Введите пожалуйста имя и количество баллов\n";
    for (Name_value nv; cin>>nv.name>>nv.scores; )
    {
        if (nv.name!="NoName" && nv.scores!=0)
        {
            for (size_t i=0; i<all_name_value.size(); i++){
                if (nv.name == all_name_value[i].name)
                {
                    cout << "Вы ввели " << nv.name
                         << " повторно\n";
                    nv.name = "";
                }
            }
            if (nv.name != "")
                all_name_value.push_back(nv);
        }
        else
        {
            for (size_t i=0; i<all_name_value.size();i++)
                cout << all_name_value[i].name << "\t" << all_name_value[i].scores << '\n';

            cout << "Введите пожалуйста Имя, чтобы узнать сколько баллов пренадлежит ему\n";
            string input_name;
            int found = 0;
            cin >> input_name;
            for (size_t i=0; i<all_name_value.size(); i++){
                if (input_name == all_name_value[i].name)
                    found = i;
            }
            if (found == 0)
                cout << "Не найден элемент с именем " << input_name << '\n';
            else
                cout << all_name_value[found].name << "\t"
                     << all_name_value[found].scores << '\n';

            cout << "Введите пожалуйста баллы, чтобы узнать кто получил их\n";
            int input_score;
            vector<int> found_names;
            cin >> input_score;
            for (size_t i=0; i<all_name_value.size(); i++){
                if (input_score == all_name_value[i].scores)
                    found_names.push_back(i);
            }
            if (found_names.size() == 0)
                cout << "Не найден элемент с баллами " << input_score << '\n';
            else
            {
                for (size_t i=0; i<found_names.size(); i++)
                    cout << all_name_value[found_names[i]].name << "\t"
                         << all_name_value[found_names[i]].scores << '\n';
            }

            all_name_value.clear();
            found_names.clear();
            cout << "Введите пожалуйста имя и количество баллов\n";
        }
    }
}

//------------------------------------------------------------------------------
