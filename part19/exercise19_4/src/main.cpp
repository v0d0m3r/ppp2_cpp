//-----------------------------------------------------------------------------

#include "Link.hpp"

//------------------------------------------------------------------------------

Link<God>* show_norse_gods(Link<God>* all_gods)
{
    if (all_gods == nullptr) return nullptr;

    auto extr = extract(all_gods, God{"Odin"});
    all_gods = extr.first;
    Link<God>* norse_gods{extr.second};

    extr = extract(all_gods, God{"Freia"});
    all_gods = extr.first;
    if (norse_gods && extr.second)
        norse_gods = add_ordered(norse_gods, extr.second);

    extr = extract(all_gods, God{"Thor"});
    all_gods = extr.first;
    if (norse_gods && extr.second)
        norse_gods = add_ordered(norse_gods, extr.second);

    print_all(norse_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

Link<God>* show_greek_gods(Link<God>* all_gods)
{
    auto extr = extract(all_gods, God{"Athena"});
    all_gods = extr.first;
    Link<God>* greek_gods{extr.second};

    extr = extract(all_gods, God{"Zeus"});
    all_gods = extr.first;
    if (greek_gods && extr.second)
        greek_gods = add_ordered(greek_gods,extr.second);

    extr = extract(all_gods, God{"Poseidon"});
    all_gods = extr.first;
    if (greek_gods && extr.second)
        greek_gods = add_ordered(greek_gods, extr.second);

    print_all(greek_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

Link<God>* show_roman_gods(Link<God>* all_gods)
{
    auto extr = extract(all_gods, God{"Mars"});
    all_gods = extr.first;
    Link<God>* roman_gods{extr.second};

    extr = extract(all_gods, God{"Jupiter"});
    all_gods = extr.first;
    if (roman_gods && extr.second)
        roman_gods = add_ordered(roman_gods, extr.second);

    extr = extract(all_gods, God{"Neptune"});
    all_gods = extr.first;
    if (roman_gods && extr.second)
        roman_gods = add_ordered(roman_gods, extr.second);

    print_all(roman_gods);
    return all_gods;
}

//------------------------------------------------------------------------------

void show_gods()
{
    Link<God>* all_gods{new Link<God>{God{"Freia", "norse"}}};
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Poseidon", "greek"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Odin", "norse"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Jupiter", "roman"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Thor", "norse"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Neptune", "roman"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Zeus", "greek"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Mars", "roman"}});
    if (all_gods)
        all_gods = insert(all_gods, new Link<God>{God{"Athena", "greek"}});

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
