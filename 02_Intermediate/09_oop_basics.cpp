// ============================================================
// 09_oop_basics.cpp
// Topic: Encapsulation, getters/setters, member functions
// Author: Silas Chalwe
// ============================================================
//
// Encapsulation means bundling data and methods together and
// hiding implementation details behind a public interface.
// This protects data integrity and makes code easier to maintain.
// ============================================================

#include <iostream>
#include <string>
#include <stdexcept> // std::invalid_argument

class Circle {
private:
    double radius;

public:
    // Constructor with validation
    explicit Circle(double r) {
        setRadius(r); // reuse the setter for validation
    }

    // Setter with validation
    void setRadius(double r) {
        if (r <= 0) throw std::invalid_argument("Radius must be positive");
        radius = r;
    }

    // Getter
    double getRadius() const { return radius; }

    // Computed properties
    double area()        const { return 3.14159265358979 * radius * radius; }
    double circumference() const { return 2 * 3.14159265358979 * radius; }

    // Display
    void display() const {
        std::cout << "Circle(r=" << radius
                  << ") area=" << area()
                  << " circumference=" << circumference() << std::endl;
    }
};

// ---- Temperature class — another encapsulation example ----
class Temperature {
private:
    double celsius; // internal storage always in Celsius

public:
    explicit Temperature(double c = 0.0) : celsius(c) {}

    // Multiple setters for different scales
    void setCelsius   (double c) { celsius = c; }
    void setFahrenheit(double f) { celsius = (f - 32.0) * 5.0 / 9.0; }
    void setKelvin    (double k) { celsius = k - 273.15; }

    // Multiple getters for different scales
    double getCelsius()    const { return celsius; }
    double getFahrenheit() const { return celsius * 9.0 / 5.0 + 32.0; }
    double getKelvin()     const { return celsius + 273.15; }

    void display() const {
        std::cout << getCelsius()    << "°C  = "
                  << getFahrenheit() << "°F  = "
                  << getKelvin()     << " K" << std::endl;
    }
};

// ============================================================
int main() {
    // Circle
    try {
        Circle c(5.0);
        c.display();
        c.setRadius(10.0);
        c.display();
        Circle bad(-1.0); // throws
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    // Temperature
    std::cout << std::endl;
    Temperature t;
    t.setCelsius(100.0);
    t.display();

    t.setFahrenheit(32.0);
    t.display(); // 0°C

    t.setKelvin(0.0);
    t.display(); // absolute zero

    return 0;
}
