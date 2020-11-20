#include <iostream>
#include <string>
#include <ostream>


/**
 * exercise 15.1
 * 在类中被声明为virtual的成员就是虚函数，基类希望派生类重新定义虚函数。除了构造函数和static的函数之外，任何成员都可以是虚函数
 * 虚函数在运行时才解析，所以可以看是执行基类的版本还是执行派生类的版本*/

/**
 * exercise 15.2
 * protected 描述的成员能通过基类，友元和派生类的成员访问
 * private 描述的成员能通过基类和友元的成员访问*/

/**
 * exercise 15.3*/

class Quate
{
public:

    Quate() = default;
    Quate(const std::string &book, double salesPrice) :
    bookNo(book), price(salesPrice){}

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

    virtual ~Quate() = default;

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

/**
 * exercise 15.4
 * a. 是错误的不能用自己作为自己的基类
 * c. ，可以看出来这个只是声明派生类，声明的时候不可以包含派生列表*/

/**
 * exercise 15.5*/
/*
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
}*/

/**
 * exercise 15.6
 * int main() {
    Quate sale1("1", 10);
    print_total(std::cout, sale1, 10);
    Bulk_quote sale2("2", 10, 10, 0.1);
    print_total(std::cout, sale2, 10);

    return 0;
}
 * */

/**
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

 */

/**
 * exercise 15.8
 * 静态类型在编译的时候就已经确定了，他是变量的类型或者是表达式的类型。
 * 动态类型是变量或者表达式表示的内存中的对象的类型，动态类型一直到运行是才能知道。*/

/**
 * exercise 15.9
 * print_total(ostream& os, const Quote& item, int n)
 * 如果传入的实参是以下三种就表达式的静态类型和动态类型是不一样的
 * 1. Bulk_quote bulk;
 * 2. Quote* bulk_ptr = & bulk;
 * 3. Quote& bulk_ref = bulk;
 * */

/**
 * exercise 15.10
 * 在要求使用基类对象的地方，可以使用派生类类型的对象来代替，是静态类型和动态类型的典型例子*/

/**
 * exercise 15.11
 * see the debug() in the class Quote and Bulk_quote*/

/**
 * exercise 15.12
 * 有的时候是有必要把一个函数同时声明override和final的。当这个函数覆盖基类中的虚函数，并且之后不再允许派生类覆盖这个函数。*/

/**
 * exercise 15.13
 * derived类中的print函数中调用print()应该是调用基类base类中的print()。如果没有加作用域的话就是调用自己本身，回到是死循环递归。
 * 应该改成：
 * void print(ostream& os) override
 * {
 * base::print();
 * os << " " << i;
 * }*/

/**
 * exercise 15.14
 * a. 基类的print()
 * b. 派生类的print()
 * c. 基类的name()
 * d. 基类的name()
 * e. 基类的print()
 * f. 派生类的print()*/

/**
 * exercise 15.15*/
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


/*
 * exercise 15.16*/

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
}

/**
 * exercise 15.17
 * Variable type 'disc_quote' is an abstract class*/


int main() {
    Quate sale1("1", 10);
    print_total(std::cout, sale1, 10);

    Bulk_quote sale2("2", 10, 10, 0.1);
    print_total(std::cout, sale2, 10);

    Limited_quote sale3("3", 10, 10, 0.1);
    print_total(std::cout, sale3, 20);
    return 0;
}

