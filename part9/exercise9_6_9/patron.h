#include "book.h"

class Patron
{
public:
    class Invalid {};   // Для генерации исключений
    Patron();
    Patron(string uname, int ncard,
           double memb, bool pay);
    string usr_name() const { return uname; }
    int num_card() const { return ncard; }
    double memb_fee() const { return memb; }
    bool is_paid() const { return pay; }
    void set_memb_fee(double new_memb);
    void set_paid(bool p);

private:
    string uname;
    int ncard;
    double memb;
    bool pay;
};

bool operator==(const Patron& a, const Patron& b);
bool operator!=(const Patron& a, const Patron& b);

