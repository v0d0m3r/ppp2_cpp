//------------------------------------------------------------------------------

#include "../example20/Document.hpp"

//------------------------------------------------------------------------------

void exercise20_6()
{
    string text{"Hello, my name is\n"
                "dan, and I so happy\n"
                "and now\n"
                "i\n"
                "would like father\n"
                "do\n"
                "while ma\n"};
    istringstream is{text};
    Document d;
    is >> d;

    print(d);

    string find{"is\ndan"};
    string replace{"gi but"};

    find_replace_txt(d, find, replace);

    cout << "\nDocument after replace:\n";
    print(d);
    cout << '\n';
}

//------------------------------------------------------------------------------

int main()
try
{
    exercise20_6();
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
