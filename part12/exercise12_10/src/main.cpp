//-----------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"
#include "../../../bstroustrup_code/Simple_window.h"
#include "../../../bstroustrup_code/Graph.h"
#include "FL/fl_utf8.h"
#include <locale.h>

//-----------------------------------------------------------------------------

using namespace Graph_lib;

//-----------------------------------------------------------------------------

enum Num_text
{
    one = 1, two, three
};

//-----------------------------------------------------------------------------

struct Block_rect {
    Block_rect(const Point& left, int width,
               int height, string title);
    static const int size_font = 16;
    static const int delta = 10;
    static const int delta_inside = 16;
    const Graph_lib::Font font{Graph_lib::Font::times_bold};

    Point upper_left{0,0};
    Text title_text{Point{0,0}, ""};
    Closed_polyline rect;
    Text inside{Point{0,0}, ""};
    Text inside2{Point{0,0}, ""};
    Text inside3{Point{0,0}, ""};
    vector<int> ins;
    void set_inside_text(int num_str, const string& inside_str);
};

//-----------------------------------------------------------------------------

Block_rect::Block_rect(const Point& left, int width, int height, string title)
    :upper_left{left}
{
    upper_left = left;
    title_text.move(upper_left.x, upper_left.y);
    title_text.set_label(title);
    title_text.set_font(font);
    title_text.set_font_size(size_font);

    upper_left.y += delta;
    rect.add(upper_left);
    rect.add(Point{upper_left.x+width, upper_left.y});
    rect.add(Point{upper_left.x+width, upper_left.y+height});
    rect.add(Point{upper_left.x, upper_left.y+height});

    upper_left.y += 2 * delta;
    upper_left.x += delta;

    ins.push_back(upper_left.x);
    ins.push_back(upper_left.y);

    upper_left.y += delta_inside;
    ins.push_back(upper_left.y);
    upper_left.y += delta_inside;
    ins.push_back(upper_left.y);

    inside.set_font(font);
    inside.set_font_size(size_font);
    inside2.set_font(font);
    inside2.set_font_size(size_font);
    inside3.set_font(font);
    inside3.set_font_size(size_font);
}

//-----------------------------------------------------------------------------

void Block_rect::set_inside_text(int num_str, const string& inside_str)
{
    switch(num_str) {
    case one:
        inside.move(ins[0],ins[one]);
        inside.set_label(inside_str);
        break;
    case two:
        inside2.move(ins[0],ins[two]);
        inside2.set_label(inside_str);
        break;
    case three:
        inside3.move(ins[0],ins[three]);
        inside3.set_label(inside_str);
        break;
    default:
        error("Нет такого ");
    }
}

//-----------------------------------------------------------------------------

void window_attach_block(Block_rect& br, Simple_window& w)
{
    w.attach(br.title_text);
    w.attach(br.rect);
    w.attach(br.inside);
    w.attach(br.inside2);
    w.attach(br.inside3);
}

//-----------------------------------------------------------------------------

int main()
try {

    using namespace Graph_lib;    
    Point t1{0, 0};
    Simple_window win{t1, x_max(), y_max(), "Canvas #12_10"};

    int width_rect = 0;
    int height_rect = 0;
    Point upper_left{0, 0};
    // Формируем chapter12.cpp
    width_rect = 320;
    height_rect = 70;
    upper_left = Point{100, y_max()-110};
    Block_rect chap12_br(upper_left, width_rect, height_rect, "chapter12.cpp:");
    chap12_br.set_inside_text(one, "#include \"Graph.h\"");
    chap12_br.set_inside_text(two, "#include \"Simple_window\"");
    chap12_br.set_inside_text(three, "int main { ... }");
    window_attach_block(chap12_br, win);
    // Формируем Simple_window
    width_rect = 280;
    height_rect = 70;
    upper_left = Point{300, y_max()-250};
    Block_rect simpl_br(upper_left, width_rect, height_rect, "Simple_window.h:");
    simpl_br.set_inside_text(one, "// Window interface:");
    simpl_br.set_inside_text(two, "class Simple_window {...};");
    simpl_br.set_inside_text(three, "...");
    window_attach_block(simpl_br, win);
    // Соединяем chapter12.cpp и Simple_window.h
    Arrow chap12_to_simpl(Point{260, y_max() -100},
                             Point{340, y_max()-170}, 13, 5);
    win.attach(chap12_to_simpl);
    // Формируем Graph.cpp
    width_rect = 160;
    height_rect = 35;
    upper_left = Point{45, y_max()-260};
    Block_rect graphcpp_br(upper_left, width_rect, height_rect, "Graph.cpp:");
    graphcpp_br.set_inside_text(one, "Graphical code");
    window_attach_block(graphcpp_br, win);
    // Формируем window.cpp
    width_rect = 160;
    height_rect = 35;
    upper_left = Point{260, y_max()-390};
    Block_rect windowcpp_br(upper_left, width_rect, height_rect, "window.cpp:");
    windowcpp_br.set_inside_text(one, "Window code");
    window_attach_block(windowcpp_br, win);
    // Формируем Graph.h
    width_rect = 205;
    height_rect = 70;
    upper_left = Point{113, y_max()-510};
    Block_rect graph_hbr(upper_left, width_rect, height_rect, "Graph.h:");
    graph_hbr.set_inside_text(one, "// Grafical interface:");
    graph_hbr.set_inside_text(two, "struct Shape {...};");
    graph_hbr.set_inside_text(three, "...");
    window_attach_block(graph_hbr, win);
    // Соединяем Graph.cpp и Graph.h
    Arrow graphcpp_to_graphh(Point{160, y_max() -250},
                             Point{210, y_max() -430}, 13, 5);
    win.attach(graphcpp_to_graphh);
    // Соединяем chapter12.cpp и Graph.h
    Arrow chap12_to_graphh(Point{260, y_max() -100},
                             Point{225, y_max() -430}, 13, 5);
    win.attach(chap12_to_graphh);
    // Формируем GUI.cpp
    width_rect = 120;
    height_rect = 35;
    upper_left = Point{610, y_max()-260};
    Block_rect guicpp_br(upper_left, width_rect, height_rect, "GUI.cpp:");
    guicpp_br.set_inside_text(one, "Code GUI");
    window_attach_block(guicpp_br, win);
    // Формируем GUI.h
    width_rect = 210;
    height_rect = 70;
    upper_left = Point{570, y_max()-410};
    Block_rect br(upper_left, width_rect, height_rect, "GUI.h:");
    br.set_inside_text(one, "// Interface GUI:");
    br.set_inside_text(two, "struct In_box {...};");
    br.set_inside_text(three, "...");
    window_attach_block(br, win);
    // Соединяем GUI.cpp и GUI.h
    Arrow guicpp_to_guih(Point{710, y_max() - 250},
                             Point{680, y_max() - 330}, 13, 5);
    win.attach(guicpp_to_guih);
    // Соединяем Simple_window.h и GUI.h
    Arrow simpl_to_guih(Point{500, y_max() - 240},
                             Point{600, y_max() - 330}, 13, 5);
    win.attach(simpl_to_guih);
    // Формируем Window.h
    width_rect = 210;
    height_rect = 70;
    upper_left = Point{400, y_max()-550};
    Block_rect windowh_br(upper_left, width_rect, height_rect, "Window.h:");
    windowh_br.set_inside_text(one, "// Window interface:");
    windowh_br.set_inside_text(two, "class Window {...};");
    windowh_br.set_inside_text(three, "...");
    window_attach_block(windowh_br, win);
    // Соединяем GUI.h и Window.h
    Arrow guih_to_windowh(Point{710, y_max() - 400},
                             Point{595, y_max() - 470}, 13, 5);
    win.attach(guih_to_windowh);
    // Соединяем Simple_window.h и Window.h
    Arrow simpl_to_windowh(Point{500, y_max() - 240},
                             Point{500, y_max() - 470}, 13, 5);
    win.attach(simpl_to_windowh);
    // Соединяем Window.cpp и Window.h
    Arrow windowcpp_to_windowh(Point{390, y_max() - 380},
                             Point{470, y_max() - 470}, 13, 5);
    win.attach(windowcpp_to_windowh);
    // Формируем Point.h
    width_rect = 200;
    height_rect = 35;
    upper_left = Point{113, y_max()-650};
    Block_rect pointh_br(upper_left, width_rect, height_rect, "Point.h:");
    pointh_br.set_inside_text(one, "struct Point {...};");
    window_attach_block(pointh_br, win);
    // Соединяем Graph.h и Point.h
    Arrow graphh_to_pointh(Point{220, y_max() -500},
                             Point{220, y_max() -605}, 13, 5);
    win.attach(graphh_to_pointh);
    // Соединяем Window.h и Point.h
    Arrow windowh_to_pointh(Point{420, y_max()-540},
                             Point{270, y_max() -605}, 13, 5);
    win.attach(windowh_to_pointh);
    // Формируем headers
    width_rect = 140;
    height_rect = 60;
    upper_left = Point{430, y_max()-700};
    Block_rect header_br(upper_left, width_rect, height_rect, "");
    header_br.set_inside_text(one, "Header files");
    header_br.set_inside_text(two, "fltk");
    window_attach_block(header_br, win);
    // Формируем обложку headers
    width_rect = 140;
    height_rect = 60;
    Open_polyline header_frame;
    header_frame.add(Point{430, y_max()-635});
    header_frame.add(Point{425, y_max()-635});
    header_frame.add(Point{425, y_max()-695});
    header_frame.add(Point{565, y_max()-695});
    header_frame.add(Point{565, y_max()-690});
    win.attach(header_frame);
    Open_polyline header_frame2;
    header_frame2.add(Point{425, y_max()-640});
    header_frame2.add(Point{420, y_max()-640});
    header_frame2.add(Point{420, y_max()-700});
    header_frame2.add(Point{560, y_max()-700});
    header_frame2.add(Point{560, y_max()-695});
    win.attach(header_frame2);
    // Соединяем Window.h и headers
    Arrow windowh_to_header(Point{500, y_max() - 540},
                             Point{500, y_max() - 630}, 13, 5);
    win.attach(windowh_to_header);
    // Соединяем Graph.h и headers
    Arrow graphh_to_header(Point{220, y_max() -500},
                             Point{450, y_max() - 630}, 13, 5);
    win.attach(graphh_to_header);
    // Соединяем GUI.h и Window.h
    Arrow guih_to_header(Point{710, y_max() - 400},
                             Point{560, y_max() - 630}, 13, 5);
    win.attach(guih_to_header);
    // Формируем code fltk
    width_rect = 140;
    height_rect = 60;
    upper_left = Point{660, y_max()-630};
    Block_rect source_br(upper_left, width_rect, height_rect, "");
    source_br.set_inside_text(one, "Code fltk");
    window_attach_block(source_br, win);
    // Формируем обложку code fltk
    width_rect = 140;
    height_rect = 60;
    Open_polyline source_frame;
    source_frame.add(Point{660, y_max()-565});
    source_frame.add(Point{655, y_max()-565});
    source_frame.add(Point{655, y_max()-625});
    source_frame.add(Point{795, y_max()-625});
    source_frame.add(Point{795, y_max()-620});
    win.attach(source_frame);
    Open_polyline source_frame2;
    source_frame2.add(Point{655, y_max()-570});
    source_frame2.add(Point{650, y_max()-570});
    source_frame2.add(Point{650, y_max()-630});
    source_frame2.add(Point{790, y_max()-630});
    source_frame2.add(Point{790, y_max()-625});
    win.attach(source_frame2);
    // Соединяем code fltk и headers
    Arrow source_to_header(Point{650, y_max() - 600},
                           Point{570, y_max() - 660}, 13, 5);
    win.attach(source_to_header);

    win.wait_for_button();

    keep_window_open("~~");
    return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return -1;
}
catch (...) {
    cout << "exiting\n";
    keep_window_open("~");
}

//-----------------------------------------------------------------------------
