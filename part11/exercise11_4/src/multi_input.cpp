//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.eof()) {        // Символ завершения ввода
        ist.clear();
        return;
    }
    ist.clear();
    char c;
    if (ist >> c && c==term) return;
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------

const string base10 = "(десятичное)";
const string base8 = "(восьмеричное)";
const string base16 = "(шестнадцатеричное)";
constexpr char terminator = '*';

//------------------------------------------------------------------------------

string get_name_base()
{
    char ch;
    // Съедает пробельные символы
    while (cin.get(ch) && isspace(ch)) {}
    if (!cin) return "";

    switch (ch) {
    case '0':
        cin.get(ch);
        if (!cin) return "";
        if (tolower(ch) == 'x')
            return base16;
        else {
            cin.putback(ch);
            return base8;
        }
    case terminator:
        cin.putback(ch);
        return "";
    default:
        cin.putback(ch);
        return base10;
    }
}

//------------------------------------------------------------------------------

void out_int_digit(vector<int>& digit_tb,
                   vector<string>& name_base_tb)
{
    if (digit_tb.size() != name_base_tb.size())
        error("out_int_digit: ", "Не совпадают размеры массивов");
    cout << showbase;
    for (size_t i=0; i < digit_tb.size(); ++i)
        if (name_base_tb[i] == base10)
            cout << dec << digit_tb[i] << '\t' << name_base_tb[i]
                 << "\t\tпревращается в десятичное "
                 << digit_tb[i] << '\n';
        else if (name_base_tb[i] == base8)
            cout << oct << digit_tb[i] << '\t' << name_base_tb[i]
                 << "\t\tпревращается в десятичное "
                 << dec << digit_tb[i] << '\n';
        else if (name_base_tb[i] == base16)
            cout << hex << digit_tb[i] << '\t' << name_base_tb[i]
                 << "\tпревращается в десятичное "
                 << dec << digit_tb[i] << '\n';
}

//------------------------------------------------------------------------------

void input_int_digit(vector<int>& digit_tb,
                     vector<string>& name_base_tb)
{
    string name_base;
    int digit = 0;
    while (true) {
        name_base = get_name_base();
        if (name_base == "") break;
        else if (name_base == base10)
            cin >> dec >> digit;
        else if (name_base == base8)
            cin >> oct >> digit;
        else if (name_base == base16)
            cin >> hex >> digit;

        if (!cin) break;
        digit_tb.push_back(digit);
        name_base_tb.push_back(name_base);
    }
    end_of_loop(cin, terminator, "Неправильное завершение ввода");
}

//------------------------------------------------------------------------------

void iodigit()
{
    cout << "Введите несколько целых восьмеричных,\n"
         << "десятичных и шестнадцатеричных чисел\n"
         << "в любом сочетании, используя суффиксы\n"
         << "0 и 0x; Для завершения ввода используйте *\n";
    vector<int> digit_tb;
    vector<string> name_base_tb;
    input_int_digit(digit_tb, name_base_tb);
    out_int_digit(digit_tb, name_base_tb);

}

//------------------------------------------------------------------------------

int main()
try {
    iodigit();
    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}

//------------------------------------------------------------------------------
