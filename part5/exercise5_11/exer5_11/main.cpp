//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//-----------------------------------------------------------------------------

int main()
try {   
    cout << "Последовательность Фибоначи:\n";

    constexpr int max_int = 2147483647;
    int last = 0;
    int current = 1;
    int next = 0;
    cout << current << '\t';
    int different = 0;
    for (;;)
    {
        different = max_int - current;
        if (different < last)
            error("\nНельзя больше искать Фибоначи в типе int");
        next = current + last;
        cout << next << '\t';
        last = current;
        current = next;
    }

    keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open();
    return -1;
}
catch (...) {
    cerr << "exiting\n";
    keep_window_open();
    return -2;
}

//-----------------------------------------------------------------------------
