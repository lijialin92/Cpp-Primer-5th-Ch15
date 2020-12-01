//
// Created by lijialin92 on 2020/12/1.
//

#ifndef CHAPTER15_SHAPE_H
#define CHAPTER15_SHAPE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class Shape {
public:
    virtual double area() = 0;
    virtual void print() = 0;

};

class Rectangle : public Shape
{
public:
    double weith, height;
    Rectangle(double w, double h) : weith(w),height(h) {};
    virtual double area() override;
    virtual void print() override;
};

class Circle : public Shape
{
public:
    double radio;
    Circle(double r) : radio(r) {};
    virtual double area() override;
    virtual void print() override;
};

class Triangle : public Shape
{
public:
    double a, b, c;
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {};
    virtual double area() override;
    virtual void print() override;
};

int compareShape(Shape* p1, Shape* p2);

#endif //CHAPTER15_SHAPE_H
