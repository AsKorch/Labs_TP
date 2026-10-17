#include "Keeper.h"
#include "FlatFigure.h"
#include "VolumetricFigure.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

Keeper::Keeper() : items(nullptr), size(0), capacity(0) {
    std::cout << "[Keeper] Конструктор по умолчанию\n";
}

Keeper::Keeper(const Keeper& other)
    : items(nullptr), size(0), capacity(0) {
    std::cout << "[Keeper] Конструктор копирования\n";
    if (other.size > 0) {
        capacity = other.capacity;
        items = new Base*[capacity];
        for (int i = 0; i < other.size; ++i)
            items[i] = other.items[i]->clone();
        size = other.size;
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Деструктор\n";
    for (int i = 0; i < size; ++i) delete items[i];
    delete[] items;
}

void Keeper::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < size; ++i) newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void Keeper::add(Base* item) {
    if (!item)
        throw std::invalid_argument("Нельзя добавить пустой указатель");
    if (size >= capacity)
        reserve(capacity == 0 ? 4 : capacity * 2);
    items[size++] = item;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Индекс вне диапазона при удалении");
    delete items[index];
    for (int i = index; i < size - 1; ++i) items[i] = items[i + 1];
    --size;
}

int Keeper::getSize() const { return size; }

Base* Keeper::getAt(int index) const {
    if (index < 0 || index >= size)
        throw std::out_of_range("Индекс вне диапазона при доступе");
    return items[index];
}

void Keeper::printAll() const {
    if (size == 0) { std::cout << "Контейнер пуст.\n"; return; }
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "] ";
        items[i]->print();
    }
}

void Keeper::drawAll() const {
    if (size == 0) { std::cout << "Контейнер пуст.\n"; return; }
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "]\n";
        items[i]->draw();
        std::cout << "\n";
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    out << size << "\n";
    for (int i = 0; i < size; ++i) {
        out << items[i]->getTypeId() << " ";
        items[i]->save(out);
    }
    out.close();
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);

    for (int i = 0; i < size; ++i) delete items[i];
    size = 0;

    int count;
    in >> count;
    if (!in || count < 0)
        throw std::runtime_error("Повреждённый файл: неверное количество объектов");

    for (int i = 0; i < count; ++i) {
        int typeId;
        in >> typeId;
        Base* obj = nullptr;
        if (typeId == 1) obj = new FlatFigure();
        else if (typeId == 2) obj = new VolumetricFigure();
        else throw std::runtime_error("Неизвестный тип объекта в файле");
        obj->load(in);
        add(obj);
    }
    in.close();
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) delete items[i];
        delete[] items;
        items = nullptr; size = 0; capacity = 0;
        if (other.size > 0) {
            capacity = other.capacity;
            items = new Base*[capacity];
            for (int i = 0; i < other.size; ++i)
                items[i] = other.items[i]->clone();
            size = other.size;
        }
    }
    return *this;
}