// ============================================================
// 01_inheritance.cpp
// Topic: Single and multi-level inheritance
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <string>

// ---- Base class ----
class Animal {
protected:
    std::string name;
    int         age;

public:
    Animal(const std::string& n, int a) : name(n), age(a) {
        std::cout << "[Animal created: " << name << "]" << std::endl;
    }

    virtual ~Animal() {
        std::cout << "[Animal destroyed: " << name << "]" << std::endl;
    }

    void breathe() const {
        std::cout << name << " breathes." << std::endl;
    }

    // Virtual: can be overridden by derived classes
    virtual void makeSound() const {
        std::cout << name << " makes a generic sound." << std::endl;
    }

    virtual void display() const {
        std::cout << "Animal: " << name << "  Age: " << age << std::endl;
    }
};

// ---- Single inheritance: Dog inherits from Animal ----
class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(const std::string& n, int a, const std::string& b)
        : Animal(n, a), breed(b) {
        std::cout << "[Dog created: " << name << " (" << breed << ")]" << std::endl;
    }

    ~Dog() override {
        std::cout << "[Dog destroyed: " << name << "]" << std::endl;
    }

    // Override the base-class virtual function
    void makeSound() const override {
        std::cout << name << " barks: Woof!" << std::endl;
    }

    void display() const override {
        Animal::display();  // call base version, then add extra info
        std::cout << "  Breed: " << breed << std::endl;
    }

    void fetch() const {
        std::cout << name << " fetches the ball!" << std::endl;
    }
};

// ---- Multi-level inheritance: Puppy inherits from Dog ----
class Puppy : public Dog {
public:
    Puppy(const std::string& n, const std::string& b)
        : Dog(n, 0, b) {}  // puppies are 0 years old

    void makeSound() const override {
        std::cout << name << " yips: Yip yip!" << std::endl;
    }
};

// ============================================================
int main() {
    std::cout << "=== Creating objects ===" << std::endl;
    Animal a("Generic Animal", 3);
    Dog    d("Buddy", 4, "Labrador");
    Puppy  p("Max", "Poodle");

    std::cout << "\n=== Making sounds ===" << std::endl;
    a.makeSound();
    d.makeSound();
    p.makeSound();

    std::cout << "\n=== Inherited methods ===" << std::endl;
    d.breathe();    // inherited from Animal
    d.fetch();      // Dog-specific
    p.fetch();      // also inherited by Puppy

    std::cout << "\n=== Display ===" << std::endl;
    d.display();

    // Access specifier: protected members are accessible in derived classes
    // but not from outside.

    std::cout << "\n=== Destruction ===" << std::endl;
    // Destructors called in reverse order of construction

    return 0;
}
