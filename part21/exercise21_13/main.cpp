//------------------------------------------------------------------------------

#include "Clear_punctstream.hpp"

//------------------------------------------------------------------------------

void exercise21_13()
{
    map<string, int> words{get_data_from_file()};
    cout << accumulate(words.begin(), words.end(),
                       0, Sum_pair{}) << '\n'
         << words;
}

//------------------------------------------------------------------------------

int main()
try {
    exercise21_13();
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
