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

class Bulk_quote : public Quate
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double salesPrice, int salesNumber, double disc):
    Quate(book, salesPrice), min_qty(salesNumber), discount(disc){}
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
}

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
 * exercise 15.7*/

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

int main() {
    Quate sale1("1", 10);
    print_total(std::cout, sale1, 10);

    Bulk_quote sale2("2", 10, 10, 0.1);
    print_total(std::cout, sale2, 10);

    Limited_quote sale3("3", 10, 10, 0.1);
    print_total(std::cout, sale3, 20);
    return 0;
}

