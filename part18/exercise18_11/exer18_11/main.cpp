//------------------------------------------------------------------------------

#include "Skip_list.hpp"

//------------------------------------------------------------------------------

void test_skip_list()
{
    Skip_list all_gods(4);

    all_gods.insert(9, "Thor");
    all_gods.insert(5, "Odin");
    all_gods.insert(7, "Jupiter");
    all_gods.insert(8, "Neptune");
    all_gods.insert(3, "Poseidon");
    cout << all_gods
         << "sizeof(Skip_list): " << sizeof(Skip_list)
         << "\nall_gods: size: " << all_gods.size()
         << "; level: " << all_gods.level()
         << "; max_level: " << all_gods.max_level()
         << "\nfind(5): " << all_gods.find(5) <<'\n';

    all_gods.erase(9);
    cout << all_gods
         << "sizeof(Skip_list): " << sizeof(Skip_list)
         << "\nall_gods: size: " << all_gods.size()
         << "; level: " << all_gods.level()
         << "; max_level: " << all_gods.max_level()
         << "\nfind(3): " << all_gods.find(3) <<'\n';

    for(int i=0; i < 10; ++i)
        cout << "all_gods(" << i << "): "
             << all_gods.find(i) << '\n';

    for (int i=0; i < all_gods.size(); ++i) {
        cout << all_gods[i] << '\n';
    }

}

//------------------------------------------------------------------------------

int main()
try
{
    test_skip_list();
    return 0;
}
catch(exception& e) {
    cout << "error: " << e.what() << '\n';
    return -1;
}
catch(...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
