//------------------------------------------------------------------------------

#include "Query_window.hpp"

//------------------------------------------------------------------------------

namespace Graph_lib {

//------------------------------------------------------------------------------

Quit_window::Quit_window(Graph_lib::Point xy, int w, int h,
                         const string& title)
    : Window{xy, w, h, title},
      qb{Point{x_max()-70, 0}, 70, 20, "Quit",
         [] (Address, Address pw) {
            reference_to<Quit_window>(pw).quit_pressed();
         }}
{
    attach(qb);
}

//------------------------------------------------------------------------------

Plain_window::Plain_window(Point xy, int w, int h, const string& title)
    : Quit_window{xy, w, h, title},
      plain_in{Point{x_max()-260, 0}, 100, 20, ""},
      plain_out{Point{100, 120}, x_max()-110, 20, ""},
      plain_button{Point{x_max()-150, 0}, 70, 20, "",
                   [] (Address, Address pw) {
                      reference_to<Plain_window>(pw).plain_pressed();
                   }}

{
    // attach()
    // attach(plain_button);
}

//------------------------------------------------------------------------------

Plain_order_window::Plain_order_window(Point xy, int w, int h,
                                         const string& title)
    : Plain_window{xy, w, h, title},
      order_nm_in{Point{140, 0}, 250, 20, "Name client:"}
{
}

//------------------------------------------------------------------------------

Input_order_window::Input_order_window(Point xy, int w, int h,
                                       const string &title)
    : Plain_order_window(xy, w, h, title),
      order_addr_in{Point{140, 30}, 250, 20, "Address client"},
      order_dbirth_in{Point{140, 60}, 250, 20, "Date of birth client"},
      purchase_nm_in{Point{480, 0}, 125, 20, "Name unit"},
      purchase_price_in{Point{480, 30}, 125, 20, "Price unit"},
      purchase_count_in{Point{480, 60}, 125, 20, "Count unit"},
      prepare_order_button{Point{140, 90}, 110, 20, "Next",
                           cb_prepare_order},
      add_order_button{Point{280, 90}, 110, 20, "Add order",
                       cb_add_order},
      set_order_button{Point{280, 90}, 110, 20, "Set order",
                       cb_set_order},
      add_purchase_button{Point{480, 90}, 110, 20, "Add purchase",
                          cb_add_purchase}
{
    init();
}

//------------------------------------------------------------------------------

void Input_order_window::init()
{
    plain_in.label = "File name";
    plain_out.label = "Error";
    plain_button.label = "Save";

    attach(plain_in);
    attach(order_nm_in);
    attach(order_addr_in);
    attach(order_dbirth_in);
    attach(purchase_nm_in);
    attach(purchase_price_in);
    attach(purchase_count_in);
    attach(plain_out);

    attach(prepare_order_button);
    attach(add_order_button);
    attach(set_order_button);
    attach(add_purchase_button);
    attach(plain_button);

    hide_purchase_feat();
    set_order_button.hide();
}

//------------------------------------------------------------------------------

void Input_order_window::clear_all_in()
{
    order_nm_in.clear();
    order_addr_in.clear();
    order_dbirth_in.clear();

    purchase_nm_in.clear();
    purchase_price_in.clear();
    purchase_count_in.clear();
}

//------------------------------------------------------------------------------

void Input_order_window::hide_purchase_feat()
{
    purchase_nm_in.hide();
    purchase_price_in.hide();
    purchase_count_in.hide();
    add_purchase_button.hide();
}

//------------------------------------------------------------------------------

void Input_order_window::show_purchase_feat()
{
    purchase_nm_in.show();
    purchase_price_in.show();
    purchase_count_in.show();
    add_purchase_button.show();
}

//------------------------------------------------------------------------------

void Input_order_window::plain_pressed()
try
{
    plain_out.put("");
    if (orders.empty()) error("Нет заказов!!");

    string fname{plain_in.get_string()};
    if (fname.empty()) error("file name is empty");

    ofstream ofs{"./" + fname, ios_base::app};
    if (!ofs)
        error("exercise_21_11: ", "Невозможно открыть выходной файл");

    std::copy(orders.begin(), orders.end(),
              ostream_iterator<Order>{ofs, "\n"});

    orders.clear();
    prepare_order_pressed();
    redraw();
}
catch (const exception& e) {
    plain_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Input_order_window::prepare_order_pressed()
{
    clear_all_in();
    hide_purchase_feat();
    add_order_button.show();
}

//------------------------------------------------------------------------------

void Input_order_window::add_order_pressed()
try
{
    plain_out.put("");
    Order ord {
        order_nm_in.get_string(),
        order_addr_in.get_string(),
        order_dbirth_in.get_string(),
        vector<Purchase>{}
    };
    orders.push_back(ord);

    show_purchase_feat();
    add_order_button.hide();
    set_order_button.show();

    redraw();
}
catch (const exception& e) {
    plain_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Input_order_window::set_order_pressed()
try
{
    plain_out.put("");
    orders.back().set_name(order_nm_in.get_string());
    orders.back().set_address(order_addr_in.get_string());
    orders.back().set_name(order_dbirth_in.get_string());

    redraw();
}
catch (const exception& e) {
    plain_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Input_order_window::add_purchase_pressed()
try
{
    plain_out.put("");
    Purchase p {
        purchase_nm_in.get_string(),
        purchase_price_in.get_double(),
        purchase_count_in.get_int()
    };
    orders.back().add(p);

    purchase_nm_in.clear();
    purchase_price_in.clear();
    purchase_count_in.clear();

    redraw();
}
catch (const exception& e) {
    plain_out.put(e.what());
    redraw();
}

//------------------------------------------------------------------------------

void Input_order_window::cb_prepare_order(Address, Address pw)
{
    reference_to<Input_order_window>(pw).prepare_order_pressed();
}

//------------------------------------------------------------------------------

void Input_order_window::cb_add_order(Address, Address pw)
{
    reference_to<Input_order_window>(pw).add_order_pressed();
}

//------------------------------------------------------------------------------

void Input_order_window::cb_set_order(Address, Address pw)
{
    reference_to<Input_order_window>(pw).set_order_pressed();
}

//------------------------------------------------------------------------------

void Input_order_window::cb_add_purchase(Address, Address pw)
{
    reference_to<Input_order_window>(pw).add_purchase_pressed();
}

//------------------------------------------------------------------------------

double Clear_in_box::get_double()
{
    Fl_Input& pi = reference_to<Fl_Input>(pw);
    const char* p = pi.value();
    if (!isdigit(p[0])) return -999999;
    return atof(p);
}

//------------------------------------------------------------------------------

Query_order_window::Query_order_window(Point xy, int w, int h,
                                       const string& title)
    : Plain_order_window(xy, w, h, title),
      fnd_by_nm_clnt_button{Point{400, 30}, 70, 20,
                            "Find", cb_fnd_by_nm_clnt},
      calc_total_sum_button{Point{400, 60}, 70, 20,
                            "Sum", cb_calc_total_sum},
      out_all_orders_button{Point{400, 90}, 70, 20,
                            "All orders", cb_out_all_orders},
      file_out{Point{140, 0}, 100, 20, "current file:"}
{
    init();    
}

//------------------------------------------------------------------------------

void Query_order_window::init()
{
    plain_in.label = "next file";
    plain_out.label = "result:";
    plain_button.label = "Next";

    attach(plain_button);
    attach(fnd_by_nm_clnt_button);
    attach(calc_total_sum_button);
    attach(out_all_orders_button);

    attach(plain_in);
    attach(order_nm_in);
    attach(file_out);
    attach(plain_out);

    order_nm_in.move(0, 30);
}

//------------------------------------------------------------------------------

void Query_order_window::plain_pressed()
try
{
    plain_out.put("");
    orders.clear();

    string fname{plain_in.get_string()};
    if (fname.empty()) error("file name is empty");
    fill_from_file(orders, Cmp_by_name{}, "./" + fname);

    // Обновление имени текущего файла
    ostringstream ss;
    ss << fname;
    file_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//-----------------------------------------------------------------------------

void Query_order_window::fnd_by_nm_clnt()
try
{
    plain_out.put("");

    string nm_clnt{order_nm_in.get_string()};
    if (nm_clnt.empty()) error("client name is empty");

    vector<Order> tmp(count_if(orders, Order_equal_name{nm_clnt}));
    copy_if(orders, tmp, Order_equal_name{nm_clnt});

    ostringstream ss;
    copy(tmp, ostream_iterator<Order>{ss, ";"});
    plain_out.put(ss.str());
    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//-----------------------------------------------------------------------------

void Query_order_window::calc_total_sum()
{
    ostringstream ss;
    ss << std::accumulate(orders.begin(), orders.end(),
                          0.0, sum_order_alternative);
    plain_out.put(ss.str());
    redraw();
}

//-----------------------------------------------------------------------------

void Query_order_window::out_all_orders()
{
    ostringstream ss;
    copy(orders, ostream_iterator<Order>{ss, ";"});
    plain_out.put(ss.str());
    redraw();
}

//-----------------------------------------------------------------------------

void Query_order_window::cb_fnd_by_nm_clnt(Address, Address pw)
{
    reference_to<Query_order_window>(pw).fnd_by_nm_clnt();
}

//-----------------------------------------------------------------------------

void Query_order_window::cb_calc_total_sum(Address, Address pw)
{
    reference_to<Query_order_window>(pw).calc_total_sum();
}

//-----------------------------------------------------------------------------

void Query_order_window::cb_out_all_orders(Address, Address pw)
{
    reference_to<Query_order_window>(pw).out_all_orders();
}

//-----------------------------------------------------------------------------

Finder_window::Finder_window(Point xy, int w, int h,
                             const string& title)
    : Plain_window{xy, w, h, title},
      word_counts_button{Point{400, 30}, 80, 20,
                         "Find", cb_word_counts},
      begin_with_button{Point{400, 60}, 80, 20,
                        "Find", cb_begin_with},
      str_with_cnt_ch_button{Point{400, 90}, 80, 20,
                             "Find", cb_str_with_cnt_ch},
      words_max_times_button{Point{400, 120}, 80, 20,
                             "Max times", cb_words_max_times},
      long_strs_button{Point{400, 150}, 80, 20,
                       "Long strs", cb_long_strs},
      short_strs_button{Point{400, 180}, 80, 20,
                        "Short strs", cb_short_strs},
      word_counts_in{Point{140, 30}, 250, 20, "Word's frequency :"},
      begin_with_in{Point{140, 60}, 250, 20, "Begin with:"},
      str_with_cnt_ch_in{Point{140, 90}, 250, 20, "Start with count ch:"},
      file_out{Point{140, 0}, 100, 20, "Current file:"}
{
    init();
}

//-----------------------------------------------------------------------------

void Finder_window::init()
{
    plain_in.label = "Next file:";
    plain_out.label = "Result:";
    plain_button.label = "Next";



    attach(plain_in);
    attach(plain_out);
    attach(plain_button);

    attach(word_counts_button);
    attach(begin_with_button);
    attach(str_with_cnt_ch_button);
    attach(words_max_times_button);
    attach(long_strs_button);
    attach(short_strs_button);
    attach(word_counts_in);
    attach(begin_with_in);
    attach(str_with_cnt_ch_in);
    attach(file_out);

    plain_out.move(0, 90);
}

//------------------------------------------------------------------------------

void Finder_window::plain_pressed()
try {
    plain_out.put("");
    words.clear();

    string fname{plain_in.get_string()};
    if (fname.empty()) error("file name is empty");
    words = get_data_from_file(fname);

    // Обновление текущего имени файла
    ostringstream ss;
    ss << fname;
    file_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::word_counts_pressed()
try {
    plain_out.put("");

    string w{word_counts_in.get_string()};
    if (w.empty()) error("word is empty");

    ostringstream ss;
    ss << w << ": " << get_word_counts(words, w);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::begin_with_pressed()
try {
    plain_out.put("");

    string w{begin_with_in.get_string()};
    if (w.empty()) error("word is empty");

    ostringstream ss;
    auto m{get_str_begin_with(words, w)};
    out_countaner_pair(ss, m);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::str_with_cnt_ch_pressed()
try {
    plain_out.put("");

    int cnt{str_with_cnt_ch_in.get_int()};
    ostringstream ss;
    auto m{get_str_with_count_ch(words, cnt)};
    out_countaner_pair(ss, m);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::words_max_times_pressed()
try {
    plain_out.put("");

    auto max_times{get_words_max_times(words)};

    ostringstream ss;
    ss << "max times: ";

    out_countaner_pair(ss, max_times);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::long_strs_pressed()
try {
    plain_out.put("");

    if (words.begin() == words.end()) return;

    auto long_str_tb{
        get_long_str(words, Longer_than{words.begin()->first})
    };

    ostringstream ss;
    ss << "long str: ";

    out_countaner_pair(ss, long_str_tb);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::short_strs_pressed()
try {
    plain_out.put("");

    if (words.begin() == words.end()) return;

    auto short_str_tb{
        get_long_str(words, Shorter_than{words.begin()->first})
    };

    ostringstream ss;
    ss << "short str: ";

    out_countaner_pair(ss, short_str_tb);
    plain_out.put(ss.str());

    redraw();
}
catch (const exception& e) {
    plain_out.put("error: " + to_string(e.what()));
    redraw();
}

//------------------------------------------------------------------------------

void Finder_window::cb_word_counts(Address, Address pw)
{
    reference_to<Finder_window>(pw).word_counts_pressed();
}

//------------------------------------------------------------------------------

void Finder_window::cb_begin_with(Address, Address pw)
{
    reference_to<Finder_window>(pw).begin_with_pressed();
}

//------------------------------------------------------------------------------

void Finder_window::cb_str_with_cnt_ch(Address, Address pw)
{
    reference_to<Finder_window>(pw).str_with_cnt_ch_pressed();
}

//------------------------------------------------------------------------------

void Finder_window::cb_words_max_times(Address, Address pw)
{
    reference_to<Finder_window>(pw).words_max_times_pressed();
}

//------------------------------------------------------------------------------

void Finder_window::cb_long_strs(Address, Address pw)
{
    reference_to<Finder_window>(pw).long_strs_pressed();
}

//------------------------------------------------------------------------------

void Finder_window::cb_short_strs(Address, Address pw)
{
    reference_to<Finder_window>(pw).short_strs_pressed();
}

//------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
