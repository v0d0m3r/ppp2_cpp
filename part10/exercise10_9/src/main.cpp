// Bjarne Stroustrup 7/26/2009
// Chapter 10 Exercise 9

/*
    Merge two sorted files; that is the files are ordered so that word[i]<word[i+1] in each input file,
    now copy from the two files so that word[i]<word[i+1] in the resulting output file,

*/

#include "../../../bstroustrup_code/std_lib_facilities.h"

int main()
try
{
    cout << "please enter two input file names: ";
    string n1,n2;
    cin>>n1>>n2;
    ifstream is1(n1.c_str());
    if (!is1) error("bad input file name ", n1);
    ifstream is2(n2.c_str());
    if (!is2) error("bad input file name ", n2);

    cout << "please enter an output file names: ";
    string n;
    cin>>n;
    ofstream os(n.c_str());
    if (!os) error("bad output file name ", n);

    string s1 = "";	// use "" to mean "no word available"
                    // note: cin>>s1 can never read an empty string into s1
                    // so we can use "" to indicate that we need to read
    string s2 = "";
    while (true) {
        if (s1=="" && !(is1>>s1)) break;	// no more words in n1
                                            // note: "break" breaks out of a loop
        if (s2=="" && !(is2>>s2)) break;	// no more words in n2
        if (s1<s2) {
            os << s1 << '\n';
            s1 = "";	// we have consumed s1
        }
        else {	// s1 >= s2
            os << s2 << '\n';
            s2 = "";	// we have consumed s2
        }
    }

    if (s1!="") os << s1 << '\n';	// in case s1 was left over
    if (s2!="") os << s2 << '\n';	// in case s2 was left over

    while (is1>>s1) os << s1 << '\n';	// in case n1 has more words
    while (is2>>s2) os << s2 << '\n';	// in case n2 has more words

    keep_window_open("~");	// For some Windows(tm) setups
}
catch (runtime_error e) {	// this code is to produce error messages; it will be described in Chapter 5
    cout << e.what() << '\n';
    keep_window_open("~");	// For some Windows(tm) setups
}
catch (...) {	// this code is to produce error messages; it will be described in Chapter 5
    cout << "exiting\n";
    keep_window_open("~");	// For some Windows(tm) setups
}
