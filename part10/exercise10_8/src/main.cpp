//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

void fill_on_file(const vector<string>& data, const string& name)
{
    ofstream ost {name};    // Поток для записи в файл
    if (!ost) error("невозможно открыть файл: ", name);
    for (const string& d : data)
        ost << d << ' ';
}

//------------------------------------------------------------------------------

void end_of_loop(ifstream& ist, char term, const string& message)
{
    if (ist.eof()) {        // Конец файла
        ist.clear();
        return;
    }
    ist.clear();
    char c;
    if (ist >> c && c==term) return;
    error("end_of_loop: ", message);
}

//------------------------------------------------------------------------------

void fill_from_file(ifstream& ist, vector<string>& data_tb, char terminator)
{
    string data;
    while (ist >> data)
        data_tb.push_back(data);
    end_of_loop(ist, terminator, "Неправильное завершение файла");
}

//------------------------------------------------------------------------------
// input_from_file() создает поток для файла с именем
// iname и записывает данные в data
void input_from_file(vector<string>& data, const string& iname)
{
    ifstream ist{iname};
    if (!ist)
        error("temp_stats: ", "Невозможно открыть входной файл");
    ist.exceptions(ist.exceptions()|ios_base::badbit);
    char term = '*';                 // Символ прекращения ввода
    fill_from_file(ist, data, term); // Ввод из файла
}

//------------------------------------------------------------------------------

void sum_files()
{
    try {
        const string path = "./";
        string summand1;
        string summand2;
        cout << "Введите имя первого входного файла: ";
        cin >> summand1;
        cout << "Введите имя второго входного файла: ";
        cin >> summand2;
        summand1 = path + summand1;
        summand2 = path + summand2;

        vector<string> summa_tb;
        input_from_file(summa_tb, summand1);    // Ввод из первого файла
        input_from_file(summa_tb, summand2);    // Ввод из второго файла
        sort(summa_tb.begin(), summa_tb.end());
        string oname = path + "summa.txt";
        fill_on_file(summa_tb, oname);          // Вывод в файл результат
                                                // file1 + file2
    }
    catch(exception& e) {
        cout << "ошибка: " << e.what() << '\n';
    }
    catch(...) {
        cout << "Неизвестная ошибка!\n";
    }
}

//------------------------------------------------------------------------------

int main()
{    
    sum_files();
    keep_window_open("~~");
    return 0;
}

//------------------------------------------------------------------------------
