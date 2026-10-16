#include "Base.h"

Base::Base() : name("Без имени") {
    std::cout << "[Base] Конструктор по умолчанию\n";
}

Base::Base(const std::string& name) : name(name) {
    std::cout << "[Base] Конструктор с параметром: " << name << "\n";
}

Base::Base(const Base& other) : name(other.name) {
    std::cout << "[Base] Конструктор копирования: " << name << "\n";
}

Base::~Base() {
    std::cout << "[Base] Деструктор: " << name << "\n";
}

std::string Base::getName() const { return name; }
void Base::setName(const std::string& n) { name = n; }

bool Base::operator==(const Base& other) const { return name == other.name; }

Base& Base::operator=(const Base& other) {
    if (this != &other) name = other.name;
    return *this;
}