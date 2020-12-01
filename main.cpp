#include <iostream>
#include <string>
#include <ostream>
#include "Shape.h"

/*
*//**
 * exercise 15.1
 * 在类中被声明为virtual的成员就是虚函数，基类希望派生类重新定义虚函数。除了构造函数和static的函数之外，任何成员都可以是虚函数
 * 虚函数在运行时才解析，所以可以看是执行基类的版本还是执行派生类的版本*//*

*//**
 * exercise 15.2
 * protected 描述的成员能通过基类，友元和派生类的成员访问
 * private 描述的成员能通过基类和友元的成员访问*//*

*//**
 * exercise 15.3*//*

class Quate
{
public:

    Quate() = default;
    Quate(const std::string &book, double salesPrice) :
    bookNo(book), price(salesPrice)
    {
        std::cout << "Quote constructor is runing" << std::endl;
    }

    std::string isbn() const
    {
        return bookNo;
    }

    virtual double net_price(int n) const
    {
        return n * price;
    }

    virtual void debug() const
    {
        std::cout << "bookNo: "<< bookNo << "price: " << price << std::endl;
    }

    virtual ~Quate()
    {
        std::cout << "Quate deconstructor is running" << std::endl;
    }

    friend std::ostream& operator << (std::ostream& os, Quate& e)
    {
        os << "\tUsing operator << (std::ostream&, Quate& );" << std::endl;
        return os;
    }
private:
    std::string bookNo;

protected:
    double price;

};

double print_total(std::ostream& os, const Quate& item, int salesNumber)
{
    //根据形参item的类型来调用net_price()
    double ret = item.net_price(salesNumber);

    os << "ISBN: " << item.isbn() << " sold: " << salesNumber << " total due: " << ret << std::endl;

    return ret;
}



*//**
 * exercise 15.4
 * a. 是错误的不能用自己作为自己的基类
 * c. ，可以看出来这个只是声明派生类，声明的时候不可以包含派生列表*//*

*//**
 * exercise 15.5*//*
*//*
class Bulk_quote : public disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double salesPrice, int salesNumber, double disc):
    Quate(book, salesPrice), min_qty(salesNumber), discount(disc){}

    virtual void debug() const override
    {
        Quate::debug();
        std::cout << "discount" << discount << " min_qty: " << min_qty << std::endl;
    }

    virtual ~Bulk_quote() = default;
    double net_price(int n) const override;

private:
    double discount = 0.0;
    int min_qty = 0;

};

double Bulk_quote::net_price(int n) const
{
    if(n >= min_qty)
    {
        return n * price * (1 - discount);
    }
    else
    {
        return n * price;
    }
}*//*

*//**
 * exercise 15.6
 * int main() {
    Quate sale1("1", 10);
    print_total(std::cout, sale1, 10);
    Bulk_quote sale2("2", 10, 10, 0.1);
    print_total(std::cout, sale2, 10);

    return 0;
}
 * *//*

*//**
 * exercise 15.7

class Limited_quote : public Quate
{
public:
    Limited_quote() = default;
    Limited_quote(const std::string& book, double salesPrice, int maxNUmberOfDiscount, double disc):
    Quate(book, salesPrice), thresholdVlaue(maxNUmberOfDiscount), discount(disc){}
    virtual ~Limited_quote() = default;

    double net_price(int n) const override
    {
        if (n <= thresholdVlaue)
        {
            return n * price * (1 - discount);
        }
        else
        {
            return (thresholdVlaue * price * (1 - discount)) + (n - thresholdVlaue) * price;
        }

    }

private:
    int thresholdVlaue = 0;
    double discount = 0.0;
};

 *//*

*//**
 * exercise 15.8
 * 静态类型在编译的时候就已经确定了，他是变量的类型或者是表达式的类型。
 * 动态类型是变量或者表达式表示的内存中的对象的类型，动态类型一直到运行是才能知道。*//*

*//**
 * exercise 15.9
 * print_total(ostream& os, const Quote& item, int n)
 * 如果传入的实参是以下三种就表达式的静态类型和动态类型是不一样的
 * 1. Bulk_quote bulk;
 * 2. Quote* bulk_ptr = & bulk;
 * 3. Quote& bulk_ref = bulk;
 * *//*

*//**
 * exercise 15.10
 * 在要求使用基类对象的地方，可以使用派生类类型的对象来代替，是静态类型和动态类型的典型例子*//*

*//**
 * exercise 15.11
 * see the debug() in the class Quote and Bulk_quote*//*

*//**
 * exercise 15.12
 * 有的时候是有必要把一个函数同时声明override和final的。当这个函数覆盖基类中的虚函数，并且之后不再允许派生类覆盖这个函数。*//*

*//**
 * exercise 15.13
 * derived类中的print函数中调用print()应该是调用基类base类中的print()。如果没有加作用域的话就是调用自己本身，回到是死循环递归。
 * 应该改成：
 * void print(ostream& os) override
 * {
 * base::print();
 * os << " " << i;
 * }*//*

*//**
 * exercise 15.14
 * a. 基类的print()
 * b. 派生类的print()
 * c. 基类的name()
 * d. 基类的name()
 * e. 基类的print()
 * f. 派生类的print()*//*

*//**
 * exercise 15.15*//*
class disc_quote : public Quate
{
public:
    disc_quote() = default;
    disc_quote(const std::string& book, double salesPrice, int sales_qty, double disc):
    Quate(book, salesPrice), quantity(sales_qty), discount(disc){}

    virtual double net_price(int n) const = 0;

    virtual ~disc_quote() = default;

protected:
    int quantity;
    double discount;

};

class Bulk_quote : public disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double salesPrice, int salesNumber, double disc):
            disc_quote(book, salesPrice, salesNumber, disc){}

    virtual ~Bulk_quote() = default;
    double net_price(int n) const override;
};

double Bulk_quote::net_price(int n) const
{
    if(n >= quantity)
    {
        return n * price * (1 - discount);
    }
    else
    {
        return n * price;
    }
}


*//*
 * exercise 15.16*//*

class Limited_quote : public disc_quote
{
public:
    Limited_quote() = default;
    Limited_quote(const std::string& book, double salesPrice, int maxNUmberOfDiscount, double disc):
            disc_quote(book, salesPrice, maxNUmberOfDiscount, disc){}
    virtual ~Limited_quote() = default;

    double net_price(int n) const override
    {
        if (n <= quantity)
        {
            return n * price * (1 - discount);
        }
        else
        {
            return (quantity * price * (1 - discount)) + (n - quantity) * price;
        }

    }
};

*//**
 * exercise 15.17
 * Variable type 'disc_quote' is an abstract class*//*

*//**
 * exercise 15.18
 * 只有当派生类是public继承的时候，用户代码才能够转换成基类。*//*

*//**
 * exercise 15.19
 * 在struct Derived_form_Private:public Priv_Dev不可以
 * 1. 无论是private继承还是public继承，派生类的成员和友元都是可以从派生类向基类转换的；派生类向他的直接基类的类型转换对于派生类的成员永远可以访问
 * 2. 如果派生类是private继承基类，则派生类的派生类中的成员是不能把派生类的派生类类型转换为基类的。*//*

*//**
 * exercise 15.20*//*

class base
{
public:
    int pubMem(){return 0;};
protected:
    int protMem(){return 0;};
private:
    int privMem(){return 0;};
};

class pubDerv : public base
{
    int f() {return protMem();}
    //char g() {return privMem();} //因为privMem是base的private变量所以不能被派生类访问。
};

class privDerv : private base
{
    int f1() {return protMem();}
};

class proDerv : protected base
{
    int f2() { return protMem();}
};

class derivedFromPublic : public pubDerv
{
    int useBase() { return protMem();}
};

class derivedFromPrivate : public privDerv
{
    //int useBase() {return protMem();} //因为derivedFromPrivate是base的private的派生类的派生类所以不能访问hase的成员。
};

class derivedFromProteced : public proDerv
{
    int useBase() {return protMem();}
};

*//**
 * exercise 15.21*//*

class Figure
{
public:
    Figure() = default;
    Figure(double x, double y) : xSize(x), ySize(y){};

protected:
    double xSize, ySize;
};

class Figure2d : public Figure
{
public:
    Figure2d(double, double);
    virtual double area() const;
    virtual double perimeter () const;
};

class Figure3d : public Figure
{
public:
    Figure3d(double x, double y, double z) : Figure(x,y), zSize(z) {};
    virtual double cubage() const;
protected:
    double zSize;
};

class Rectangle : public Figure2d
{
public:
    Rectangle(double, double);
    virtual double area() const override;
    virtual double perimeter() const override;
};

class Circle : public Figure2d
{
public:
    Circle(double, double);
    virtual double area() const override;
    virtual double perimeter() const override;
};

class Sphere : public Figure3d
{
public:
    Sphere(double , double , double);
    virtual double cubage() const override;
};

class Clone : public Figure3d
{
public:
    Clone(double, double, double );
    virtual double cubage() const override;
};


*//**
 * exrcise 15.22 see exercise 15.21*//*

*//**
 * exercise 15.23
 * int fcn()去掉参数，就可以作为虚函数的覆盖了。
 * 后果就p2->fcn(42)这个调用错误了。因为D1类中没有fnc(int)成员函数。*//*

*//**
 * exercise 15.24
 * 作为基类被使用的类应该友虚析构函数。确保在删除delete的指向动态分配对象的基类指针时，根据指针实际指向的对象所属的类型运行适当的析构函数。
 * 析构函数必须能够执行删除类中定义的指针成员。*/



int main() {
    /*Quate sale1("1", 10);
    print_total(std::cout, sale1, 10);

    Bulk_quote sale2("2", 10, 10, 0.1);
    print_total(std::cout, sale2, 10);

    Limited_quote sale3("3", 10, 10, 0.1);
    print_total(std::cout, sale3, 20);

    pubDerv d1;
    privDerv d2;
    proDerv d3;
    derivedFromPublic dd1;
    derivedFromPrivate dd2;
    derivedFromProteced dd3;
    d1.pubMem();
    //d2.pubMem();//pubMem在派生类中是private的
    //d3.pubMem();//pubMem在派生类中是proteced的

    base* p = &d1;
    //p = &d2; //因为d2是private的派生类的对象，所以不能转换类型为基类的对象。类型转换之能在派生类的成员函数中。
    //p = &d3;
    p = &dd1;
    //p = &dd2;
    //p = &dd3;*/



    std::vector<Shape*> vec;

    Rectangle* pRec = new Rectangle(2,4);

    Circle* pCir = new Circle(8);

    Triangle* pTri = new Triangle(3,4,5);


    vec.push_back(pCir);
    vec.push_back(pRec);
    vec.push_back(pTri);

    std::sort(vec.begin(), vec.end(), compareShape);

    for (auto& i : vec) {
        i->print();
    }

    return 0;
}

