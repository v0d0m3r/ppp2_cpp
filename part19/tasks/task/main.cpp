//------------------------------------------------------------------------------

#include <Task.hpp>

//------------------------------------------------------------------------------

void some_fct()
{
    S<int> si{1};    
    S<char> sc{'!'};
    S<double> sd{2.0};
    S<string> ss{"hello world!"};
    S<vector<int>> svi{vector<int>{2, 3}};

    cout << si << '\n'
         << sc << '\n'
         << sd << '\n'
         << ss << '\n'
         << svi << '\n';

    read_val(svi.get());
    cout << si << '\n'
         << sc << '\n'
         << sd << '\n'
         << ss << '\n'
         << svi << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    some_fct();
    return 0;
}
catch(exception& e) {
    cout << "Error: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
