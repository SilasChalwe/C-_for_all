// ============================================================
// 03_abstract_classes.cpp
// Topic: Pure virtual functions and interfaces
// Author: Silas Chalwe
// ============================================================
//
// A class with at least one pure virtual function (= 0) is abstract.
// You cannot instantiate an abstract class directly.
// Abstract classes define an interface contract that all derived
// classes must fulfil.
// ============================================================

#include <iostream>
#include <string>
#include <memory>

// ---- Abstract "interface" ----
class Drawable {
public:
    virtual void draw()   const = 0;  // pure virtual
    virtual void resize(double factor) = 0;
    virtual ~Drawable() = default;
};

class Colorable {
public:
    virtual void setColor(const std::string& color) = 0;
    virtual std::string getColor() const = 0;
    virtual ~Colorable() = default;
};

// ---- Concrete class implementing two interfaces ----
class Square : public Drawable, public Colorable {
    double side;
    std::string color;
public:
    Square(double s, const std::string& c) : side(s), color(c) {}

    void draw() const override {
        std::cout << "Drawing a " << color << " square with side=" << side << std::endl;
    }

    void resize(double factor) override {
        side *= factor;
        std::cout << "Square resized to side=" << side << std::endl;
    }

    void setColor(const std::string& c) override { color = c; }
    std::string getColor() const override { return color; }
};

// ---- Abstract base with a template method pattern ----
class Report {
public:
    // Template method: defines the skeleton of the algorithm
    void generate() const {
        printHeader();
        printBody();
        printFooter();
    }

    virtual ~Report() = default;

private:
    void printHeader() const { std::cout << "===== REPORT =====" << std::endl; }
    void printFooter() const { std::cout << "=================="  << std::endl; }
    virtual void printBody() const = 0;  // subclasses fill in the body
};

class SalesReport : public Report {
    void printBody() const override {
        std::cout << "Sales Q1: $120,000" << std::endl;
        std::cout << "Sales Q2: $145,000" << std::endl;
    }
};

class InventoryReport : public Report {
    void printBody() const override {
        std::cout << "Items in stock: 450" << std::endl;
        std::cout << "Items low:       12" << std::endl;
    }
};

// ============================================================
int main() {
    // Polymorphism through abstract interface
    std::unique_ptr<Drawable> shape = std::make_unique<Square>(5.0, "blue");
    shape->draw();
    shape->resize(2.0);
    shape->draw();

    // Access Colorable interface via static_cast
    auto* colorableShape = dynamic_cast<Colorable*>(shape.get());
    if (colorableShape) {
        colorableShape->setColor("red");
        std::cout << "Color: " << colorableShape->getColor() << std::endl;
    }

    // Template method pattern
    std::cout << std::endl;
    SalesReport    sr;
    InventoryReport ir;
    sr.generate();
    std::cout << std::endl;
    ir.generate();

    return 0;
}
