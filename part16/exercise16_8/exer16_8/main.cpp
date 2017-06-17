//-----------------------------------------------------------------------------

#include "Converter_window.hpp"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

int main()
try {
    Exchange e;

    ifstream is{"./echange.txt"};
    if (!is) error("Ошибка открытия файла");
    is >> e;

    Converter_window cw{Point{100, 100}, 1024, 800, "Converter", e};
    return gui_main();
}
catch(exception& e) {
    cerr << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    return -2;
}

//-----------------------------------------------------------------------------
