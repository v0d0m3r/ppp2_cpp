//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

vector<int> get_vector_from_list(list<double>& ld)
{
    vector<int> vi;
    vi.resize(ld.size());
    copy(ld.begin(), ld.end(), vi.begin());
    return vi;
}

//------------------------------------------------------------------------------

void exercise20_11()
{
    list<double> ld{44.0, 0.1, 2.3, 3.3, 1};
    vector<int> vi{get_vector_from_list(ld)};

    sort(vi.begin(), vi.end());
    for (auto i : vi) cout << i << ' ';
    cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_11();
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
