// ============================================================
// 02_polymorphism.cpp
// Topic: Virtual functions, vtables, runtime polymorphism
// Author: Silas Chalwe
// ============================================================
//
// Polymorphism allows a base-class pointer/reference to call the
// correct derived-class method at runtime — the right function is
// selected dynamically via the virtual function table (vtable).
//
// Key rule: if a class has virtual functions, its destructor
// should ALSO be virtual.
// ============================================================

#include <iostream>
#include <vector>
#include <memory>   // std::unique_ptr
#include <cmath>    // std::sqrt

class Shape {
public:
    virtual ~Shape() = default;

    // Pure-virtual-like interface — every shape must implement these
    virtual double area()        const = 0;
    virtual double perimeter()   const = 0;
    virtual void   display()     const = 0;
};

class Circle : public Shape {
    double radius;
public:
    explicit Circle(double r) : radius(r) {}
    double area()      const override { return 3.14159265 * radius * radius; }
    double perimeter() const override { return 2 * 3.14159265 * radius; }
    void   display()   const override {
        std::cout << "Circle(r=" << radius << ") area=" << area() << std::endl;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area()      const override { return width * height; }
    double perimeter() const override { return 2 * (width + height); }
    void   display()   const override {
        std::cout << "Rectangle(" << width << "x" << height
                  << ") area=" << area() << std::endl;
    }
};

class Triangle : public Shape {
    double a, b, c; // side lengths
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    double perimeter() const override { return a + b + c; }
    double area()      const override {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s-a) * (s-b) * (s-c));
    }
    void   display()   const override {
        std::cout << "Triangle(" << a << "," << b << "," << c
                  << ") area=" << area() << std::endl;
    }
};

// ---- Polymorphic function — works with ANY Shape ----
void printShapeInfo(const Shape& shape) {
    shape.display();
    std::cout << "  perimeter = " << shape.perimeter() << std::endl;
}

// ---- Total area of a collection ----
double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double total = 0;
    for (const auto& s : shapes) total += s->area();
    return total;
}

// ============================================================
int main() {
    // Base-class pointer pointing to derived-class objects
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    std::cout << "=== Polymorphic dispatch ===" << std::endl;
    for (const auto& s : shapes) {
        printShapeInfo(*s);
    }

    std::cout << "\nTotal area: " << totalArea(shapes) << std::endl;

    // typeid — runtime type information
    std::cout << "\n=== Runtime Type Info ===" << std::endl;
    for (const auto& s : shapes) {
        std::cout << typeid(*s).name() << std::endl;
    }

    return 0;
}
