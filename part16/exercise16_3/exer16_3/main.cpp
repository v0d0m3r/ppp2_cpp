//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "image_button_window.h"

//-----------------------------------------------------------------------------

int main()
try {
    Image_button_window win{Point{100, 100}, 1024, 800,
                            "Image button", "1.jpg", -40, 40};
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
