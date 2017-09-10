//------------------------------------------------------------------------------

#ifndef FILE_HANDLE_HPP
#define FILE_HANDLE_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class File_handle
{
    FILE* f;
public:
    File_handle(const string& name, const string& mode)
        : f{fopen(name.c_str(), mode.c_str())}
    { if (f == nullptr) error("file not opened\n"); }

    FILE* get() const { return f; }

    ~File_handle() { if (f) fclose(f); }
};

//------------------------------------------------------------------------------

#endif // FILE_HANDLE_HPP

//------------------------------------------------------------------------------
