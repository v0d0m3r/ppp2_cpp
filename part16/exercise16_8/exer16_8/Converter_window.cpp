//-----------------------------------------------------------------------------

#include "Converter_window.hpp"

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

Converter_window::Converter_window(Point xy, int w, int h,
                                   const string& title, Exchange& ee)
    : Window(xy, w, h, title),
      e{ee},      
      equal_lab{Point{x_max()-385, 15}, "="},
      conv_button{Point{x_max()-150, 0}, 70, 20, "Convert", cb_convert},
      quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit},
      lcur_in {Point{x_max()-450, 0}, 50, 20, e(Currency::usd)},
      rcur_out{Point{x_max()-330, 0}, 50, 20, e(Currency::eur)},
      lmenu{Point{x_max()-470, 30}, 70, 20,
            Menu::vertical, "lvalue"},
      rmenu{Point{x_max()-350, 30}, 70, 20,
            Menu::vertical, "rvalue"}
{
    attach(equal_lab);

    attach(conv_button);
    attach(quit_button);

    attach(lcur_in);
    attach(rcur_out);

    lmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::usd), cb_lusd});
    lmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::eur), cb_leur});
    lmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::rub), cb_lrub});

    rmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::usd), cb_rusd});
    rmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::eur), cb_reur});
    rmenu.attach(new Button{Point{0, 0}, 0, 0,
                            e(Currency::rub), cb_rrub});

    attach(lmenu);
    attach(rmenu);
}

//-----------------------------------------------------------------------------
// Конвертируем lvalue в rvalue
void Converter_window::convert()
{
    istringstream is{lcur_in.get_string() + " " + lcur_in.label};
    Money lmoney;

    is >> lmoney;
    if (!is) error("Bad input");

    ostringstream ss;
    ss << get_convert_money(e, lmoney, e(rcur_out.label));
    rcur_out.put(ss.str());

    redraw();
}

//-----------------------------------------------------------------------------
// Действия меню
void Converter_window::leur_pressed()
{
    lcur_in.label = e(Currency::eur);
    convert();
}

//-----------------------------------------------------------------------------

void Converter_window::lrub_pressed()
{
    lcur_in.label = e(Currency::rub);
    convert();
}

//-----------------------------------------------------------------------------

void Converter_window::lusd_pressed()
{
    lcur_in.label = e(Currency::usd);
    convert();
}

//-----------------------------------------------------------------------------

void Converter_window::reur_pressed()
{
    rcur_out.label = e(Currency::eur);
    convert();
}

//-----------------------------------------------------------------------------

void Converter_window::rrub_pressed()
{
    rcur_out.label = e(Currency::rub);
    convert();
}

//-----------------------------------------------------------------------------

void Converter_window::rusd_pressed()
{
    rcur_out.label = e(Currency::usd);
    convert();
}

//-----------------------------------------------------------------------------
// Callback функции
void Converter_window::cb_convert(Address, Address pw)
{
    reference_to<Converter_window>(pw).convert();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_leur(Address, Address pw)
{
    reference_to<Converter_window>(pw).leur_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_lrub(Address, Address pw)
{
    reference_to<Converter_window>(pw).lrub_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_lusd(Address, Address pw)
{
    reference_to<Converter_window>(pw).lusd_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_quit(Address, Address pw)
{
    reference_to<Converter_window>(pw).quit_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_reur(Address, Address pw)
{
    reference_to<Converter_window>(pw).reur_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_rrub(Address, Address pw)
{
    reference_to<Converter_window>(pw).rrub_pressed();
}

//-----------------------------------------------------------------------------

void Converter_window::cb_rusd(Address, Address pw)
{
    reference_to<Converter_window>(pw).rusd_pressed();
}

//-----------------------------------------------------------------------------
