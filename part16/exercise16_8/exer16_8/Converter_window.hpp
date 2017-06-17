#ifndef CONVERTER_WINDOW_H
#define CONVERTER_WINDOW_H

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/GUI.h"
#include "Money.hpp"

//------------------------------------------------------------------------------

class Converter_window : public Graph_lib::Window
{
public:
    Converter_window(Graph_lib::Point xy, int w, int h,
                     const string& title, Exchange& ee);
private:
    // Данные
    Exchange& e;                   // Обменный курс

    Graph_lib::Text equal_lab;

    // Виджеты
    Graph_lib::Button conv_button; // Конвертирует валюту
    Graph_lib::Button quit_button; // Завершает работу программы

    Graph_lib::In_box lcur_in;
    Graph_lib::Out_box rcur_out;

    Graph_lib::Menu lmenu;
    Graph_lib::Menu rmenu;

    // Действия
    void lusd_pressed();
    void leur_pressed();
    void lrub_pressed();

    void rusd_pressed();
    void reur_pressed();
    void rrub_pressed();

    void convert();
    void quit_pressed() { hide(); }

    // Callback-функции
    static void cb_convert(Graph_lib::Address, Graph_lib::Address);
    static void cb_quit(Graph_lib::Address, Graph_lib::Address);

    static void cb_lusd(Graph_lib::Address, Graph_lib::Address);
    static void cb_leur(Graph_lib::Address, Graph_lib::Address);
    static void cb_lrub(Graph_lib::Address, Graph_lib::Address);

    static void cb_rusd(Graph_lib::Address, Graph_lib::Address);
    static void cb_reur(Graph_lib::Address, Graph_lib::Address);
    static void cb_rrub(Graph_lib::Address, Graph_lib::Address);
};

//------------------------------------------------------------------------------

#endif // CONVERTER_WINDOW_H
