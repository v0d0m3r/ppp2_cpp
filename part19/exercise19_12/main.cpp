//------------------------------------------------------------------------------

#include <File_handle.hpp>

//------------------------------------------------------------------------------

void f(const string& s)
{
    File_handle fh{s,"w"};
    cout << "Enter a string you would like to write into the file: ";
    string in;
    getline(cin,in);
    fwrite(in.c_str(),sizeof(char),in.size(),fh.get());
}

//------------------------------------------------------------------------------

int main()
try
{
    f("./chapter19_ex12_out.txt");
    return 0;
}
catch (exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
