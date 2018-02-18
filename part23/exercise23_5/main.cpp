//------------------------------------------------------------------------------

#include "../exercise23_4/Mail_file.hpp"

//------------------------------------------------------------------------------

template<typename C>
void experiment(C& sender, const Mail_file& mfile,
                const vector<string>& addr_tb, int n)
{
    for (const auto& m : mfile) {
        string s;
        if (find_from_addr(&m, s))
            sender.insert(make_pair(s, &m));
    }
    size_t sz{addr_tb.size()-1};
    for (int i{0}; i < n; ++i) {
        // Теперь обходим мультиотображение и извлекаем темы
        // сообщений
        auto pp{sender.equal_range(addr_tb[randint(sz)])};
        for (auto p{pp.first}; p != pp.second; ++p) {
            string s;
            if (find_subject(p->second, s))
                cout << s << '\n';
            else
                cout << "Пропущена строка с темой!";
        }
    }
}

//------------------------------------------------------------------------------

template<typename C>
void do_experiment(C& c, const Mail_file& mfile,
                   const vector<string>& addr_tb, int n,
                   const string& cont_name)
{
    auto begin{chrono::high_resolution_clock::now()};

    experiment(c, mfile, addr_tb, n);

    auto end{chrono::high_resolution_clock::now()};

    auto duration{chrono::duration_cast<chrono::milliseconds>(end - begin)
                .count()};
    cout << "Выполнение эксперимента с " << cont_name.c_str()
         << " при N == "    << n         << " заняло "
         << duration        << "мс\n";
}

//------------------------------------------------------------------------------

vector<string> get_addr_from_mail(const Mail_file& mfile)
{
    vector<string> addr_tb;
    for (const auto& m : mfile) {
        string s;
        if (find_from_addr(&m, s))
            addr_tb.push_back(s);
    }
    return addr_tb;
}

//------------------------------------------------------------------------------

void test(int n)
{
    string fname;
    cout << "Please, input mail file name: ";
    cin >> fname;

    Mail_file mfile{fname}; // Инициализируем mfile
                            // данными из файла

    // Заполняем вектор адресов,
    // чтобы потом использовать для поиска в отображжениях
    vector<string> addr_tb{get_addr_from_mail(mfile)};

    multimap<string, const Message*> mltmap;
    unordered_multimap<string, const Message*> un_mltmap;

    for (int i{n}; i < 1000; i+=100) {
        do_experiment(mltmap, mfile, addr_tb, i, "multimap");
        do_experiment(un_mltmap, mfile, addr_tb, i, "un_mltmap");
        mltmap.clear();
        un_mltmap.clear();
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    constexpr int start{100};
    test(start);
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
