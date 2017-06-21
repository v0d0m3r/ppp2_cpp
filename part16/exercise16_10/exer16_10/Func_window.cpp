//------------------------------------------------------------------------------

#include "Func_window.hpp"

//------------------------------------------------------------------------------

using namespace Graph_lib;

//------------------------------------------------------------------------------

Func_window::Func_window(Graph_lib::Point xy, int w, int h,
                         const string &title, Graph_lib::Funct &ff)
    : Window(xy, w, h, title),
      f{ff},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      func_menu{Point{x_max()-70, 40}, 70, 20,
                 Menu::vertical, "func"},
      menu_button{Point{x_max()-80, 30}, 80, 20,
                  "func menu", cb_menu}
{
    load_func_inbox();

    attach(quit_button);
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "sin", cb_sin});
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "cos", cb_cos});
    func_menu.attach(new Button{Point{0, 0}, 0, 0,
                                "exp", cb_exp});
    attach(func_menu);
    func_menu.hide();
    attach(menu_button);
}

//------------------------------------------------------------------------------

void Func_window::load_func_inbox()
{
    inboxs.push_back(new In_box{Point{x_max()-310, 0}, 50, 20,
           get_name_in_box(Func_window::r_min)});
    inboxs.push_back(new In_box{Point{x_max()-310, 0}, 50, 20,
           get_name_in_box(Func_window::r_max)});
    inboxs.push_back(new In_box{Point{x_max()-310, 0}, 50, 20,
           get_name_in_box(Func_window::count)});
    inboxs.push_back(new In_box{Point{x_max()-310, 0}, 50, 20,
           get_name_in_box(Func_window::xscale)});
    inboxs.push_back(new In_box{Point{x_max()-310, 0}, 50, 20,
           get_name_in_box(Func_window::yscale)});

    for (int i=0; i < inboxs.size(); ++i)
        attach(inboxs[i]);
}

//------------------------------------------------------------------------------

void Func_window::recalculate(Fct f)
{

}

//------------------------------------------------------------------------------

void Func_window::cb_sin(Address, Address)
{

}

//------------------------------------------------------------------------------

void Func_window::cb_cos(Address, Address)
{

}

//------------------------------------------------------------------------------

void Func_window::cb_exp(Address, Address)
{

}

//------------------------------------------------------------------------------

void Func_window::cb_menu(Address, Address)
{

}

//------------------------------------------------------------------------------

void Func_window::cb_quit(Address, Address)
{

}

//------------------------------------------------------------------------------
