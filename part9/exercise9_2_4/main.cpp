// Глава 9, задание №3-4.
//------------------------------------------------------------------------------

#include "name_pairs.h"

//------------------------------------------------------------------------------

void registration()
{
    try {
        Registr::Name_pairs np;
        Registr::Name_pairs np1;
        while(true) {
        //while (true) {
            np.read_names();
            np.read_ages();
            np.my_sort();
            cout << np;
            //np.clear();
        //}

            //while (true) {
                np1.read_names();
                np1.read_ages();
                np1.my_sort();
                cout << np1;
                //np.clear();
                if (np == np1)
                    cout << "np == np1\n";
                if (np != np1)
                    cout << "np != np1\n";
                np.clear();np1.clear();
        }
    }
    catch(exception& e) {
        cout << "error: " << e.what() << '\n';
    }
    // Данные для теста
    /*
     * dfg hfg sdf sda abc
     * 1 2 3 4 5
     * bbc gfd sas fssf fdgd dsfs
     * 23 23 21 21 34 45
     *
*/

}

//------------------------------------------------------------------------------

int main()
{
    registration();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------

// Задание 4
struct X {
    void f(int x)
    {
        struct Y
        {
            int f() { return 1; }
            int m;
        };
        int m;
        m=x;
        Y m2;
        return f(m2.f());
    }
    int m;
    void g(int m)
    {
        if (m) f(m+2);
        else { g(m+2); }
    }
    X() { }
    void m3()
    {

    }
    void main() { X a; a.f(2); }
};

//------------------------------------------------------------------------------
