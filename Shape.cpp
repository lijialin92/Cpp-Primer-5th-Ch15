//
// Created by lijialin92 on 2020/12/1.
//

#include "Shape.h"

void Rectangle::print()
{
    std::cout << "Rectangle: " << area() << std::endl;
}

double Rectangle::area()
{
    return weith * height;
}

double Circle::area() {
    return 3.14 * radio * radio;
}

void Circle::print() {
    std::cout << "Circle: " << area() << std::endl;
}

double Triangle::area() {
    double p = (a + b + c) / 2;
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}

void Triangle::print() {
    std::cout << "Triangle: " << area() << std::endl;

}

int compareShape(Shape* p1, Shape* p2)
{
    return (*p1).area() < (*p2).area();
}
