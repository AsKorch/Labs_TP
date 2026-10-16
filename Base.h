#ifndef BASE_H
#define BASE_H

#include <string>
#include <iostream>
#include <fstream>

class Base {
public:
    Base();
    Base(const std::string& name);
    Base(const Base& other);
    virtual ~Base();

    virtual double calculate() const = 0;
    virtual void draw() const = 0;
    virtual void print() const = 0;
    virtual const char* getCategory() const = 0;
    virtual int getTypeId() const = 0;
    virtual Base* clone() const = 0;

    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;

    std::string getName() const;
    void setName(const std::string& name);

    virtual bool operator==(const Base& other) const;
    Base& operator=(const Base& other);

protected:
    std::string name;
};

#endif