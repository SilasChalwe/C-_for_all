// ============================================================
// 10_design_patterns.cpp
// Topic: Singleton, Factory, Observer patterns
// Author: Silas Chalwe
// ============================================================
//
// Design patterns are reusable solutions to common software
// design problems. Knowing them helps you write maintainable,
// extensible code.
// ============================================================

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>

// ============================================================
// 1. SINGLETON — ensures only one instance of a class exists
// ============================================================
class Logger {
private:
    static Logger* instance;
    Logger() { std::cout << "[Logger] Created" << std::endl; }

public:
    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* getInstance() {
        if (!instance) instance = new Logger();
        return instance;
    }

    void log(const std::string& msg) {
        std::cout << "[LOG] " << msg << std::endl;
    }

    // Note: for real code use Meyers' Singleton (local static):
    // static Logger& getInstance() { static Logger inst; return inst; }
};
Logger* Logger::instance = nullptr;

// ============================================================
// 2. FACTORY — creates objects without specifying exact class
// ============================================================
class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Dog: Woof!" << std::endl; }
};

class Cat : public Animal {
public:
    void speak() const override { std::cout << "Cat: Meow!" << std::endl; }
};

class AnimalFactory {
public:
    static std::unique_ptr<Animal> create(const std::string& type) {
        if (type == "dog") return std::make_unique<Dog>();
        if (type == "cat") return std::make_unique<Cat>();
        throw std::invalid_argument("Unknown animal type: " + type);
    }
};

// ============================================================
// 3. OBSERVER — allows objects to subscribe to events
// ============================================================
class Event {
    std::string data;
public:
    explicit Event(const std::string& d) : data(d) {}
    const std::string& getData() const { return data; }
};

class EventEmitter {
    std::vector<std::function<void(const Event&)>> listeners;
public:
    void subscribe(std::function<void(const Event&)> listener) {
        listeners.push_back(std::move(listener));
    }

    void emit(const Event& e) {
        for (const auto& listener : listeners) listener(e);
    }
};

// ============================================================
int main() {
    // --- Singleton ---
    std::cout << "=== Singleton ===" << std::endl;
    Logger* log1 = Logger::getInstance();
    Logger* log2 = Logger::getInstance();
    log1->log("Application started");
    log2->log("Same instance? " + std::string(log1 == log2 ? "YES" : "NO"));

    // --- Factory ---
    std::cout << "\n=== Factory ===" << std::endl;
    std::vector<std::string> types = {"dog", "cat", "dog"};
    for (const auto& t : types) {
        auto animal = AnimalFactory::create(t);
        animal->speak();
    }
    try {
        auto unknown = AnimalFactory::create("fish");
    } catch (const std::invalid_argument& e) {
        std::cout << "Factory error: " << e.what() << std::endl;
    }

    // --- Observer ---
    std::cout << "\n=== Observer ===" << std::endl;
    EventEmitter emitter;

    // Subscribe two listeners using lambdas
    emitter.subscribe([](const Event& e){
        std::cout << "[Listener 1] Got: " << e.getData() << std::endl;
    });
    emitter.subscribe([](const Event& e){
        std::cout << "[Listener 2] Got: " << e.getData() << std::endl;
    });

    emitter.emit(Event("user_login"));
    emitter.emit(Event("data_saved"));

    return 0;
}
