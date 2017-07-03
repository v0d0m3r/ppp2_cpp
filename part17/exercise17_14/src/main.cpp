//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Link.hpp"

//------------------------------------------------------------------------------

int main()
try {

    Link* norse_gods{new Link{"Thor"}};
    List* norse_head{new List{norse_gods}};

    norse_gods = norse_gods->insert(norse_head, new Link{"Odin"});
    norse_gods = norse_gods->insert(norse_head, new Link{"Zeus"});
    norse_gods = norse_gods->insert(norse_head, new Link{"Freia"});

    Link* greek_gods{new Link{"Hera"}};
    List* greek_head{new List{greek_gods}};

    greek_gods = greek_gods->insert(greek_head, new Link{"Athena"});
    greek_gods = greek_gods->insert(greek_head, new Link{"Mars"});
    greek_gods = greek_gods->insert(greek_head, new Link{"Poseidon"});

    Link* p{greek_gods->find(greek_head, "Mars")};
    if (p) p->value = "Ares";

    p = norse_gods->find(norse_head, "Zeus");
    if (p) {
        if (p == norse_gods) norse_gods = p->next();
        p->erase(norse_head);
        greek_gods = greek_gods->insert(greek_head, p);
    }

    print_all(norse_head);
    cout << '\n';

    print_all(greek_head);
    cout << '\n';

    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "Exiting\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
