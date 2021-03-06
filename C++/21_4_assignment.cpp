#include <iostream>
using namespace std;

class Kvector
{
protected:
    int *m;
    int len;

public:
    Kvector(int sz = 0, int value = 0) : len(sz)
    {
        cout << this << " : Kvector(" << sz << "," << value << ")\n";
        if (!sz)
        {
            m = NULL;
            return;
        }
        m = new int[sz];
        for (int i = 0; i < sz; i++)
            m[i] = value;
    }
    Kvector(const Kvector &v)
    {
        cout << this << " : Kvector(* " << &v << ")\n";
        len = v.len;
        if (!len)
        {
            m = NULL;
            return;
        }
        m = new int[len];
        for (int i = 0; i < len; i++)
            m[i] = v.m[i];
    }
    virtual ~Kvector()
    {
        cout << this << " : ~Kvector() \n";
        delete[] m;
    }
    void print() const
    {
        for (int i = 0; i < len; i++)
        {
            cout << m[i] << " ";
        }
        cout << endl;
    }

    Kvector &operator=(const Kvector &v)
    {
        delete[] m;
        len = v.len;
        for (int i = 0; i < len; i++)
        {
            m[i] = v.m[i];
        }
        return *this;
    }
};

class Avector : public Kvector
{
    char *table;
    int table_len;

public:
    Avector(int sz = 0, int v = 0, const char *t = "abc") : Kvector(sz, v)
    {
        cout << this << " : Avector(" << sz << "," << v << ",\"" << t << "\")\n";
        table_len = strlen(t);
        table = new char[table_len + 1];
        strcpy(table, t);
    }

    Avector(const Avector &v) : Kvector(v)
    {
        cout << this << " : Avector(*" << &v << ")\n";
        setTable(v.table);
    }

    ~Avector()
    {
        cout << this << " : ~Avector() \n";
        delete[] table;
    }
    void setTable(const char *t)
    {
        delete[] table;
        table_len = strlen(t);
        table = new char[table_len + 1];
        strcpy(table, t);
    }
    Avector &operator=(const Avector &v)
    {
        setTable(v.table);
        this->Kvector::operator=(v);
        return *this;
    }
};

int main(int argc, char *argv[])
{
    Avector v(3, 1, "abc");
    v.print();
    Avector *p = new Avector(v);
    p->print();
    Kvector *kp = new Avector(2, 5, "xyz");
    kp->print();
    delete kp;
    delete p;
    return 0;
}