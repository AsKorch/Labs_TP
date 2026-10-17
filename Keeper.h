#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>

class Keeper {
public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    void add(Base* item);
    void remove(int index);
    int getSize() const;
    Base* getAt(int index) const;

    void printAll() const;
    void drawAll() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    Keeper& operator=(const Keeper& other);

private:
    Base** items;
    int size;
    int capacity;

    void reserve(int newCapacity);
};

#endif