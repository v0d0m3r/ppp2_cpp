//------------------------------------------------------------------------------

#include "Test_facilities.hpp"

//------------------------------------------------------------------------------

enum class Test {
    with_arg, manager, copy_op, move_op, common_op
};

//------------------------------------------------------------------------------

const string& fct_name_tb(Test i)
{
    static vector<string> v {
        "constructor_with_arg_test",
        "counted_ptr_manager_test",
        "copy_operations_test",
        "move_operations_test",
        "common_test"
    };

    return v[static_cast<int>(i)];
}

//------------------------------------------------------------------------------

template<typename T>
void constructor_with_arg_test(T& val)
{
    Counted_ptr<T> cp_str{val};
    to_compare(*cp_str, val);
    to_compare(cp_str.count(), 0);
}

//------------------------------------------------------------------------------

void constructor_with_arg_test()
{
    string str1{"privet"};
    constructor_with_arg_test(str1);

    unique_ptr<vector<int>> v{new vector<int>(5)};
    constructor_with_arg_test(*v.get());

    int i{100};
    constructor_with_arg_test(i);
}

//------------------------------------------------------------------------------

void counted_ptr_manager_test()
{
    string* str{new string{"bla, bla"}};
    int* i{new int(1)};

    string* null_str{nullptr};
    counted_ptr_manager(null_str, i);
    counted_ptr_manager(str, nullptr);
    counted_ptr_manager(str, i);
    to_compare(*i, 0);

    counted_ptr_manager(str, i);
}

//------------------------------------------------------------------------------

template<typename T>
void copy_operations_test(T& val, T& val2)
{
    Counted_ptr<T> cp_str{val};
    Counted_ptr<T> cp_str2{cp_str};

    to_compare(cp_str.count(), cp_str2.count());
    to_compare(cp_str.count(), 1);

    Counted_ptr<T> cp_str3{cp_str2};

    to_compare(cp_str.count(), cp_str3.count());
    to_compare(cp_str.count(), 2);

    to_compare(*cp_str, *cp_str3);

    Counted_ptr<T> cp_str4{val2};
    cp_str2 = cp_str4;

    to_compare(cp_str4.count(), cp_str2.count());
    to_compare(cp_str4.count(), 1);

}

//------------------------------------------------------------------------------

void copy_operations_test()
{
    string str{"str"};
    string str1{"abra"};
    copy_operations_test(str, str1);

    unique_ptr<vector<int>> v{new vector<int>(5)};
    unique_ptr<vector<int>> v1{new vector<int>(2)};
    copy_operations_test(*v.get(), *v1.get());

    int i{100};
    int i1{200};
    copy_operations_test(i, i1);
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T> move_helper(T& v)
{
    Counted_ptr<T> val{v};
    return val;
}

//------------------------------------------------------------------------------

template <typename T>
void move_operations_test(T& v1, T& v2)
{
    Counted_ptr<T> val1{v1};
    Counted_ptr<T> val_cp{val1};
    to_compare(val1.count(), 1);

    Counted_ptr<T> val2{move(val1)};
    val_cp = val2;

    to_compare(val2.count(), 1);
    to_compare(*val2, v1);

    val1 = move_helper(v2);
    to_compare(*val1, v2);
    to_compare(val1.count(), 0);
}

//------------------------------------------------------------------------------

void move_operations_test()
{
    string str{"str"};
    string str1{"abra"};
    move_operations_test(str, str1);

    unique_ptr<vector<int>> v{new vector<int>(5)};
    unique_ptr<vector<int>> v1{new vector<int>(2)};
    move_operations_test(*v.get(), *v1.get());

    int i{100};
    int i1{200};
    move_operations_test(i, i1);
}

//------------------------------------------------------------------------------

template<typename T>
Counted_ptr<T> helper_common(Counted_ptr<T> p, vector<Counted_ptr<T>> vcp)
{
    Counted_ptr<T> val1{p};
    vcp.push_back(p);
    vcp.push_back(val1);
    vcp.push_back(Counted_ptr<T>{p});

    to_compare(vcp[vcp.size()-1].count(), vcp[vcp.size()-2].count());
    to_compare(*vcp[vcp.size()-1], *vcp[vcp.size()-2]);

    return p;
}

//------------------------------------------------------------------------------

void common_test()
{
    string str{"str"};
    string str1{"abra"};
    Counted_ptr<string> cps{str};

    vector<Counted_ptr<string>> vcp;
    vcp.push_back(cps);
    vcp.push_back(Counted_ptr<string>{str1});

    helper_common(cps, vcp);
}

//------------------------------------------------------------------------------

int main()
try
{   
    do_test(constructor_with_arg_test, fct_name_tb(Test::with_arg));
    do_test(counted_ptr_manager_test,  fct_name_tb(Test::manager));
    do_test(copy_operations_test,      fct_name_tb(Test::copy_op));
    do_test(move_operations_test,      fct_name_tb(Test::move_op));
    do_test(common_test,               fct_name_tb(Test::common_op));

    return 0;
}
catch (exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "Oops!";
    return -2;
}

//------------------------------------------------------------------------------
