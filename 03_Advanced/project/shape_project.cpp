// ============================================================
// project — Shape Hierarchy
// Author: Silas Chalwe
//
// Description: A polymorphic shape drawing system that
// demonstrates advanced OOP: abstract classes, virtual functions,
// smart pointers, operator overloading, and STL containers.
//
// Compile: g++ -std=c++17 -Wall -o shapes shape_project.cpp && ./shapes
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

// ---- Abstract base class ----
class Shape {
protected:
    std::string color;
    std::string name;

public:
    Shape(const std::string& n, const std::string& c)
        : color(c), name(n) {}

    virtual ~Shape() = default;

    virtual double area()        const = 0;
    virtual double perimeter()   const = 0;
    virtual void   draw()        const = 0;

    const std::string& getName()  const { return name; }
    const std::string& getColor() const { return color; }

    // Comparison by area
    bool operator<(const Shape& other) const { return area() < other.area(); }

    void display() const {
        std::cout << std::left << std::setw(12) << name
                  << " | color=" << std::setw(8) << color
                  << " | area="  << std::fixed << std::setprecision(2) << std::setw(8) << area()
                  << " | perim=" << std::setw(8) << perimeter() << std::endl;
    }
};

// ---- Concrete shapes ----
class Circle : public Shape {
    double radius;
public:
    Circle(double r, const std::string& c = "white")
        : Shape("Circle", c), radius(r) {}

    double area()      const override { return M_PI * radius * radius; }
    double perimeter() const override { return 2.0 * M_PI * radius; }
    void   draw()      const override {
        std::cout << "Drawing " << color << " circle with radius=" << radius << std::endl;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h, const std::string& c = "white")
        : Shape("Rectangle", c), width(w), height(h) {}

    double area()      const override { return width * height; }
    double perimeter() const override { return 2.0 * (width + height); }
    void   draw()      const override {
        std::cout << "Drawing " << color << " rectangle " << width << "x" << height << std::endl;
    }
};

class Triangle : public Shape {
    double a, b, c; // sides
public:
    Triangle(double a, double b, double c, const std::string& col = "white")
        : Shape("Triangle", col), a(a), b(b), c(c) {}

    double perimeter() const override { return a + b + c; }
    double area()      const override {
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s-a) * (s-b) * (s-c));
    }
    void draw() const override {
        std::cout << "Drawing " << color << " triangle (" << a << "," << b << "," << c << ")" << std::endl;
    }
};

// ---- Canvas — manages a collection of shapes ----
class Canvas {
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    void add(std::unique_ptr<Shape> s) {
        shapes.push_back(std::move(s));
    }

    void drawAll() const {
        std::cout << "\n=== Drawing All Shapes ===" << std::endl;
        for (const auto& s : shapes) s->draw();
    }

    void displayStats() const {
        std::cout << "\n=== Shape Statistics ===" << std::endl;
        std::cout << std::left
                  << std::setw(12) << "Shape"
                  << " | " << std::setw(8) << "Color"
                  << " | " << std::setw(8) << "Area"
                  << " | " << std::setw(8) << "Perim" << std::endl;
        std::cout << std::string(46, '-') << std::endl;
        for (const auto& s : shapes) s->display();

        double totalArea = 0;
        for (const auto& s : shapes) totalArea += s->area();
        std::cout << "\nTotal shapes : " << shapes.size() << std::endl;
        std::cout << "Total area   : " << std::fixed << std::setprecision(2) << totalArea << std::endl;
    }

    void sortByArea() {
        std::sort(shapes.begin(), shapes.end(),
            [](const auto& a, const auto& b){ return a->area() < b->area(); });
    }

    const Shape* getLargest() const {
        if (shapes.empty()) return nullptr;
        auto it = std::max_element(shapes.begin(), shapes.end(),
            [](const auto& a, const auto& b){ return a->area() < b->area(); });
        return it->get(); // non-owning raw pointer — caller must not delete
    }
};

// ============================================================
int main() {
    Canvas canvas;
    canvas.add(std::make_unique<Circle>(5.0, "red"));
    canvas.add(std::make_unique<Rectangle>(4.0, 6.0, "blue"));
    canvas.add(std::make_unique<Triangle>(3.0, 4.0, 5.0, "green"));
    canvas.add(std::make_unique<Circle>(2.5, "yellow"));
    canvas.add(std::make_unique<Rectangle>(10.0, 2.0, "purple"));

    canvas.drawAll();
    canvas.displayStats();

    canvas.sortByArea();
    std::cout << "\n=== After Sorting by Area ===" << std::endl;
    canvas.displayStats();

    const Shape* largest = canvas.getLargest();
    if (largest) {
        std::cout << "\nLargest shape: ";
        largest->display();
    }

    return 0;
}
