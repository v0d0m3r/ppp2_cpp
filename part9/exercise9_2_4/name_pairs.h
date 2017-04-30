
#include "../../bstroustrup_code/std_lib_facilities.h"

namespace Registr {
class Name_pairs
{
public:
    Name_pairs() : a{0.00} { }
    class Invalid {};
    string member_names(int i) const;
    int member_ages(int i) const;
    int size_names() const { return int(names.size()); }
    void read_names();
    void read_ages();
    void my_sort();
    void clear();
private:
    string n;
    double a;
    vector<string> names;
    vector<int> ages;
    static const char eof = ';';
};
bool operator==(const Name_pairs& a, const Name_pairs& b);
bool operator!=(const Name_pairs& a, const Name_pairs& b);
ostream& operator<<(ostream& os, const Name_pairs& np);
void ignore();
}


