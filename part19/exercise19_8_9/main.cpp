//------------------------------------------------------------------------------

#include <Vector_easy.hpp>

//------------------------------------------------------------------------------

int main()
try
{
    Vector_easy<int> vi(10);
    vi.reserve(20);

    Vector_easy<string> vi1{"s"};
    vi1.push_back("mother");

    for (int i=0; i < vi1.size(); ++i)
        cout << vi1[i] << '\n';


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
