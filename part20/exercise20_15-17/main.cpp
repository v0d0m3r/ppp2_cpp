//------------------------------------------------------------------------------

#include "../../bstroustrup_code/std_lib_facilities.h"

//------------------------------------------------------------------------------

template<typename T>
struct pvector : vector<T*> {
    using vector<T*>::vector;
    ~pvector() { for (const T* e : *this) delete e; }
};

//------------------------------------------------------------------------------

template<typename T>
struct ovector : pvector<T> {
    using size_type = typename pvector<T>::size_type;

    using pvector<T>::pvector;

    T& operator[](size_type i)
    {
        return *pvector<T>::operator[](i);
    }
    const T& operator[](size_type i) const
    {
        return *pvector<T>::operator[](i);
    }
};

//------------------------------------------------------------------------------

template<typename T>
struct ownership_vector : public pvector<T> {
    using pvector<T>::pvector;

    void attach(T* v) { this->push_back(v); }

    void detach(T* v)
    {
        for (auto i{this->size()}; 0 < i; --i)	// guess last attached will be first released
            if ((*this)[i-1]==v)
                this->erase(this->begin()+(i-1));
    }
};

//------------------------------------------------------------------------------

void exercises()
{
    ovector<int> vp{new int(1), new int(2)};

    cout << vp[0] << '\n';

    ownership_vector<int> own_vp{new int(1), new int(2)};
    int* pi{new int(4)};
    int* pi1{new int(5)};
    own_vp.attach(pi);
    own_vp.attach(pi1);

    own_vp.detach(pi);

    delete pi;
}

//------------------------------------------------------------------------------

int main()
try
{
    exercises();
    return 0;
}
catch(const exception& e) {
    cout << "\nerror: " << e.what() << '\n';
    return -1;
}
catch (...) {
    cerr << "oops!";
    return -2;
}

//------------------------------------------------------------------------------
