//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "Link.hpp"

//------------------------------------------------------------------------------

Link* show_norse_gods(Link* all_gods)
{
    if (all_gods == nullptr) return nullptr;

    auto extr = extract(all_gods, "Odin");
    all_gods = extr.first;
    Link* norse_gods{extr.second};

    extr = extract(all_gods, "Freia");
    all_gods = extr.first;
    if (norse_gods && extr.second)
        norse_gods = norse_gods->add_ordered(extr.second);

    extr = extract(all_gods, "Thor");
    all_gods = extr.first;
    if (norse_gods && extr.second)
        norse_gods = norse_gods->add_ordered(extr.second);

    print_all(norse_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

Link* show_greek_gods(Link* all_gods)
{
    auto extr = extract(all_gods, "Athena");
    all_gods = extr.first;
    Link* greek_gods{extr.second};

    extr = extract(all_gods, "Zeus");
    all_gods = extr.first;
    if (greek_gods && extr.second)
        greek_gods = greek_gods->add_ordered(extr.second);

    extr = extract(all_gods, "Poseidon");
    all_gods = extr.first;
    if (greek_gods && extr.second)
        greek_gods = greek_gods->add_ordered(extr.second);

    print_all(greek_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

Link* show_roman_gods(Link* all_gods)
{
    auto extr = extract(all_gods, "Mars");
    all_gods = extr.first;
    Link* roman_gods{extr.second};

    extr = extract(all_gods, "Jupiter");
    all_gods = extr.first;
    if (roman_gods && extr.second)
        roman_gods = roman_gods->add_ordered(extr.second);

    extr = extract(all_gods, "Neptune");
    all_gods = extr.first;
    if (roman_gods && extr.second)
        roman_gods = roman_gods->add_ordered(extr.second);

    print_all(roman_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

void show_gods()
{
    Link* all_gods{new Link{God{"Freia", "norse"}}};
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Poseidon", "greek"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Odin", "norse"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Jupiter", "roman"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Thor", "norse"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Neptune", "roman"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Zeus", "greek"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Mars", "roman"}});
    if (all_gods)
        all_gods = all_gods->insert(new Link{God{"Athena", "greek"}});

    print_all(all_gods);

    all_gods = show_norse_gods(all_gods);
    all_gods = show_greek_gods(all_gods);
    all_gods = show_roman_gods(all_gods);
}

//------------------------------------------------------------------------------

int main()
try {
    show_gods();
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
