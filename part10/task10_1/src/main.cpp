#include "point.h"

//------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------

const string ipath = "/home/lost/project/princip_straustrup/part10/task10_1/";
const string opath = "/home/lost/project/princip_straustrup/part10/task10_1/";

//------------------------------------------------------------------------------

void error(string from_err, string err)
{
  throw runtime_error(from_err+": "+ err);
}

//------------------------------------------------------------------------------

inline void keep_window_open(string str1)
{
  cout << "Чтобы выйти, введите " << str1 << '\n';
  for (string str2; cin>>str2;)
     if (str1 == str2)  { break; }
}

//------------------------------------------------------------------------------
// Ввод из файла
void fill_from_file(vector<Point>& points, string& name)
{
    ifstream ist {name};    // Поток для чтения из файла
    if (!ist) error("невозможно открыть файл:", name);
    for (Point p; ist >> p; )
        points.push_back(p);
}

//------------------------------------------------------------------------------
// Вывод в файл
void fill_on_file(const vector<Point>& points, string& name)
{
    ofstream ost {name};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл:", name);
    for (const Point& p : points)
        ost << p;
}

//------------------------------------------------------------------------------
// Ввод из консоли
void fill_from_console(vector<Point>& points, const string& invitation_inp)
{
    cout << invitation_inp;
    for (int i=0; i<points.size(); ++i) {
        cin >> points[i];
        if (!cin)
            error("fill_from_console", "Не вверный ввод из консоли!");
    }
}

//------------------------------------------------------------------------------
// print_point_tb() печатает элементы массива
void print_point_tb(const vector<Point>& points)
{
    for (const Point& p:points)
        cout << p;
}

//------------------------------------------------------------------------------
// compare_point_tb() сравнивает два вектора
void compare_point_tb(const vector<Point>& a, const vector<Point>& b)
{
    if (a.size() != b.size())
        error("compare_point_tb", "Что-то не так!");
    for (int i=0; i<a.size(); ++i)
        if (a[i] != b[i])
            error("compare_point_tb", "Что-то не так!");
}

//------------------------------------------------------------------------------

void work_point()
{
    try {
        constexpr int num_elem = 7;
        string file_name = opath + "mydata.txt";
        const string invitation_inp = "Введите 7 пар координат x и y"
                                      " через пробел\n";
        vector<Point> original_points(num_elem);
        // Ввод точек с консоли
        fill_from_console(original_points, invitation_inp);
        print_point_tb(original_points);
        // Вывод в файл
        fill_on_file(original_points, file_name);

        vector<Point> processed_points;
        // Ввод из файла
        fill_from_file(processed_points, file_name);

        cout << "original_point\n";
        print_point_tb(original_points);

        cout << "processed_points\n";
        print_point_tb(processed_points);

    }
    catch(exception& e) {
        cout << "error: " << e.what() << '\n';
    }
}

//------------------------------------------------------------------------------

int main()
{
    work_point();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
