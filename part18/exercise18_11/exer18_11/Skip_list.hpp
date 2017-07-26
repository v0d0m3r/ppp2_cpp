#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

//------------------------------------------------------------------------------

#include "../../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

class Link
{
public:
    string value;
    explicit Link(int ll, int kk = 0, const string& vv = "")
        : value{vv}, l{ll}, k{kk}, succ{new Link*[l]}
    {
        for (int i=0; i < l; ++i) // Инициализация элементов
            succ[i] = nullptr;
    }
    ~Link() { delete[] succ;}

    int level()       const { return l; }
    int key()         const { return k; }

    void set_next(int i, Link* s) { succ[i] = s; }
    Link* next(int i) const { return succ[i]; }

protected:
    void set_level(int ll) { l = ll; }
    void set_key  (int kk) { k = kk; }

private:
    int l;
    int k;    
    Link** succ;
};

//------------------------------------------------------------------------------

class Skip_list
{
public:
    explicit Skip_list(int mm, int kk = 0, const string& vv = "");
    Skip_list(initializer_list<string> lst);
    ~Skip_list();

    const string& find(int key) const;
    void insert(int key, const string& val);
    void erase(int key);

    int max_level() const { return m; }
    int level()     const { return l; }
    int size()      const { return sz; }

    string& operator[](int n);
    const string& operator[](int n) const;

    // Запрет копирования
    Skip_list(const Skip_list& a) = delete;
    Skip_list& operator=(const Skip_list& a) = delete;

    // Для тестирования класса
    friend ostream& operator<<(ostream& os, const Skip_list& sl);
private:    
    int m;      // Максимально возможное количество узлов
    int l{1};   // Уровень списка - максимальный уровень узла
    int sz{0};
    Link* head;
};

//------------------------------------------------------------------------------

const string& empty_value();
int random_level(int max_lvl);
void print_all(Skip_list* sl);

//------------------------------------------------------------------------------

#endif // SKIP_LIST_HPP
