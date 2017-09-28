//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename Iter1, typename Iter2>
// Требуется Input_iterator<Iter1>, Output_iterator<Iter2>
Iter2 m_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
    auto out_it{f2};
    for (auto p{f1}; p != e1; ++p) {
        *out_it = *p;
        ++out_it;
    }
    return out_it;
}

//------------------------------------------------------------------------------

template<typename Iter>
// Требуется Input_iterator<Iter1>, Input_iterator<Iter2>
void print(Iter first, Iter last)
{
    for (auto p{first}; p != last; ++p) cout << *p << '\n';
}

//------------------------------------------------------------------------------

template<typename Iter>
// Требуется Input_iterator<Iter>
void print(Iter first, Iter last, const string& greeting,
                                  const string& ending)
{
    cout << greeting << '\n';
    print(first, last);
    cout << ending << '\n';
}

//------------------------------------------------------------------------------

void tasks()
{
    constexpr size_t sz{10};
    int ai[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vi{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> li{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int ai1[sz];
    for (size_t i{0}; i < sz; ++i) ai1[i] = ai[i];

    print(ai1, ai1 + sz, "ai1 start", "ai1 end");

    auto vi1{vi};
    print(vi1.begin(), vi1.end(), "vi1 start", "vi1 end");
    auto li1{li};
    print(li1.begin(), li1.end(), "li1 start", "li1 end");

    for (auto p{ai}; p != ai + sz; ++p) *p += 2;
    for (auto& i : vi) i += 3;
    for (auto& i : li) i += 5;

    print(ai, ai + sz, "ai start", "ai end");
    print(vi.begin(), vi.end(), "vi start", "vi end");
    print(li.begin(), li.end(), "li start", "li end");

    copy(ai, ai + sz, vi.begin());
    print(vi.begin(), vi.end(), "vi start", "vi end");
    copy(li.begin(), li.end(), ai);
    print(ai, ai + sz, "ai start", "ai end");

    auto vi_iter{std::find(vi.begin(), vi.end(), 3)};
    if (vi_iter == vi.end())
        cout << "vi not found: 3\n";
    else {
        int index{0};
        for (auto p{vi.begin()}; p != vi_iter; ++p)
            ++index;
        cout << "found pos: " << index << '\n';
    }


    auto li_iter{std::find(li.begin(), li.end(), 10)};
    if (li_iter == li.end())
        cout << "li not found: 27\n";
    else {
        int index{0};
        for (auto p{li.begin()}; p != li_iter; ++p)
            ++index;
        cout << "found pos: " << index << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    tasks();
    return 0;
}
catch(exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
