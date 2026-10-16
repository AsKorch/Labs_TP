#include "FlatFigure.h"
#include <cmath>
#include <stdexcept>

FlatFigure::FlatFigure()
    : Base("Плоская фигура"), figureType("неизвестно"),
      dimensions(nullptr), dimCount(0) {
    std::cout << "[FlatFigure] Конструктор по умолчанию\n";
}

FlatFigure::FlatFigure(const std::string& figureType, const double* dims, int dimCount)
    : Base("Плоская фигура: " + figureType), figureType(figureType),
      dimensions(nullptr), dimCount(0) {
    if (dimCount <= 0)
        throw std::invalid_argument("Количество размеров должно быть > 0");
    if (!dims)
        throw std::invalid_argument("Массив размеров пуст");
    this->dimCount = dimCount;
    this->dimensions = new double[dimCount];
    for (int i = 0; i < dimCount; ++i) {
        if (dims[i] <= 0)
            throw std::invalid_argument("Размер должен быть > 0");
        this->dimensions[i] = dims[i];
    }
    std::cout << "[FlatFigure] Конструктор с параметрами: " << figureType << "\n";
}

FlatFigure::FlatFigure(const FlatFigure& other)
    : Base(other), figureType(other.figureType),
      dimensions(nullptr), dimCount(other.dimCount) {
    if (other.dimensions && other.dimCount > 0) {
        dimensions = new double[dimCount];
        for (int i = 0; i < dimCount; ++i) dimensions[i] = other.dimensions[i];
    }
    std::cout << "[FlatFigure] Конструктор копирования: " << figureType << "\n";
}

FlatFigure::~FlatFigure() {
    delete[] dimensions;
    std::cout << "[FlatFigure] Деструктор: " << figureType << "\n";
}

double FlatFigure::calculate() const { return calcArea(); }

double FlatFigure::calcArea() const {
    const double PI = 3.14159265358979;
    if (figureType == "круг" && dimCount >= 1)
        return PI * dimensions[0] * dimensions[0];
    if (figureType == "квадрат" && dimCount >= 1)
        return dimensions[0] * dimensions[0];
    if (figureType == "прямоугольник" && dimCount >= 2)
        return dimensions[0] * dimensions[1];
    if (figureType == "треугольник" && dimCount >= 3) {
        double a = dimensions[0], b = dimensions[1], c = dimensions[2];
        double p = (a + b + c) / 2.0;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
    if (figureType == "эллипс" && dimCount >= 2)
        return PI * dimensions[0] * dimensions[1];
    return 0.0;
}

void FlatFigure::draw() const {
    std::cout << "Изображение фигуры \"" << figureType << "\":\n";
    if (figureType == "круг")
        std::cout << "   ***   \n *     * \n*       *\n *     * \n   ***   \n";
    else if (figureType == "квадрат")
        std::cout << "+-----+\n|     |\n|     |\n|     |\n+-----+\n";
    else if (figureType == "прямоугольник")
        std::cout << "+-------+\n|       |\n|       |\n+-------+\n";
    else if (figureType == "треугольник")
        std::cout << "   /\\   \n  /  \\  \n /    \\ \n/______\\\n";
    else if (figureType == "эллипс")
        std::cout << "  *****  \n *     * \n*       *\n *     * \n  *****  \n";
    else
        std::cout << "(нет изображения для этого типа)\n";
}

void FlatFigure::print() const {
    std::cout << "Плоская фигура: " << figureType << "\n";
    std::cout << "  Размеры: ";
    for (int i = 0; i < dimCount; ++i) {
        std::cout << dimensions[i];
        if (i < dimCount - 1) std::cout << ", ";
    }
    std::cout << "\n  Площадь: " << calcArea() << "\n";
}

const char* FlatFigure::getCategory() const { return "Плоская"; }
int FlatFigure::getTypeId() const { return 1; }
Base* FlatFigure::clone() const { return new FlatFigure(*this); }

void FlatFigure::save(std::ofstream& out) const {
    out << figureType << " " << dimCount << " ";
    for (int i = 0; i < dimCount; ++i) out << dimensions[i] << " ";
    out << "\n";
}

void FlatFigure::load(std::ifstream& in) {
    in >> figureType >> dimCount;
    delete[] dimensions;
    dimensions = new double[dimCount];
    for (int i = 0; i < dimCount; ++i) in >> dimensions[i];
}

std::string FlatFigure::getFigureType() const { return figureType; }
void FlatFigure::setFigureType(const std::string& t) { figureType = t; }
int FlatFigure::getDimCount() const { return dimCount; }

double FlatFigure::getDimension(int i) const {
    if (i < 0 || i >= dimCount)
        throw std::out_of_range("Индекс размера вне диапазона");
    return dimensions[i];
}

void FlatFigure::setDimension(int i, double v) {
    if (i < 0 || i >= dimCount)
        throw std::out_of_range("Индекс размера вне диапазона");
    if (v <= 0)
        throw std::invalid_argument("Размер должен быть > 0");
    dimensions[i] = v;
}

FlatFigure& FlatFigure::operator=(const FlatFigure& other) {
    if (this != &other) {
        Base::operator=(other);
        figureType = other.figureType;
        delete[] dimensions;
        dimCount = other.dimCount;
        if (other.dimensions && dimCount > 0) {
            dimensions = new double[dimCount];
            for (int i = 0; i < dimCount; ++i)
                dimensions[i] = other.dimensions[i];
        } else {
            dimensions = nullptr;
        }
    }
    return *this;
}