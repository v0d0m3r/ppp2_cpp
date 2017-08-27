//------------------------------------------------------------------------------

#include <Unique_ptr.hpp>

//------------------------------------------------------------------------------

Unique_ptr<vector<int>> make_vec()
{
    Unique_ptr<vector<int>> p{new vector<int>};
    p->push_back(1);
    (*p).push_back(2);
    return p;
}

//------------------------------------------------------------------------------

int main()
try
{
    Unique_ptr<vector<int>> p{make_vec()};
    cout << p[0][0];
    return 0;
}
catch(exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
