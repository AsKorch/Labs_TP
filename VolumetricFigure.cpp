#include "VolumetricFigure.h"
#include <cmath>
#include <stdexcept>

VolumetricFigure::VolumetricFigure()
    : Base("Объёмная фигура"), figureType("неизвестно"),
      dimensions(nullptr), dimCount(0) {
    std::cout << "[VolumetricFigure] Конструктор по умолчанию\n";
}

VolumetricFigure::VolumetricFigure(const std::string& figureType, const double* dims, int dimCount)
    : Base("Объёмная фигура: " + figureType), figureType(figureType),
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
    std::cout << "[VolumetricFigure] Конструктор с параметрами: " << figureType << "\n";
}

VolumetricFigure::VolumetricFigure(const VolumetricFigure& other)
    : Base(other), figureType(other.figureType),
      dimensions(nullptr), dimCount(other.dimCount) {
    if (other.dimensions && other.dimCount > 0) {
        dimensions = new double[dimCount];
        for (int i = 0; i < dimCount; ++i)
            dimensions[i] = other.dimensions[i];
    }
    std::cout << "[VolumetricFigure] Конструктор копирования: " << figureType << "\n";
}

VolumetricFigure::~VolumetricFigure() {
    delete[] dimensions;
    std::cout << "[VolumetricFigure] Деструктор: " << figureType << "\n";
}

double VolumetricFigure::calculate() const { return calcVolume(); }

double VolumetricFigure::calcVolume() const {
    const double PI = 3.14159265358979;
    if (figureType == "куб" && dimCount >= 1)
        return dimensions[0] * dimensions[0] * dimensions[0];
    if (figureType == "шар" && dimCount >= 1)
        return (4.0 / 3.0) * PI * dimensions[0] * dimensions[0] * dimensions[0];
    if (figureType == "цилиндр" && dimCount >= 2)
        return PI * dimensions[0] * dimensions[0] * dimensions[1];
    if (figureType == "конус" && dimCount >= 2)
        return (1.0 / 3.0) * PI * dimensions[0] * dimensions[0] * dimensions[1];
    if (figureType == "параллелепипед" && dimCount >= 3)
        return dimensions[0] * dimensions[1] * dimensions[2];
    return 0.0;
}

void VolumetricFigure::draw() const {
    std::cout << "Проекция объёмной фигуры \"" << figureType << "\":\n";
    if (figureType == "куб")
        std::cout << "  +-----+\n /     /|\n+-----+ |\n|     | |\n|     | +\n|     |/\n+-----+\n";
    else if (figureType == "шар")
        std::cout << "   ***   \n *     * \n*       *\n *     * \n   ***   \n";
    else if (figureType == "цилиндр")
        std::cout << "  *****  \n *     * \n *     * \n *     * \n *     * \n  *****  \n";
    else if (figureType == "конус")
        std::cout << "    /\\    \n   /  \\   \n  /    \\  \n /      \\ \n/________\\\n";
    else if (figureType == "параллелепипед")
        std::cout << "  +-------+\n /       /|\n+-------+ |\n|       | |\n|       | +\n|       |/\n+-------+\n";
    else
        std::cout << "(нет проекции для этого типа)\n";
}

void VolumetricFigure::print() const {
    std::cout << "Объёмная фигура: " << figureType << "\n";
    std::cout << "  Размеры: ";
    for (int i = 0; i < dimCount; ++i) {
        std::cout << dimensions[i];
        if (i < dimCount - 1) std::cout << ", ";
    }
    std::cout << "\n  Объём: " << calcVolume() << "\n";
}

const char* VolumetricFigure::getCategory() const { return "Объёмная"; }
int VolumetricFigure::getTypeId() const { return 2; }
Base* VolumetricFigure::clone() const { return new VolumetricFigure(*this); }

void VolumetricFigure::save(std::ofstream& out) const {
    out << figureType << " " << dimCount << " ";
    for (int i = 0; i < dimCount; ++i) out << dimensions[i] << " ";
    out << "\n";
}

void VolumetricFigure::load(std::ifstream& in) {
    in >> figureType >> dimCount;
    delete[] dimensions;
    dimensions = new double[dimCount];
    for (int i = 0; i < dimCount; ++i) in >> dimensions[i];
}

std::string VolumetricFigure::getFigureType() const { return figureType; }
void VolumetricFigure::setFigureType(const std::string& t) { figureType = t; }
int VolumetricFigure::getDimCount() const { return dimCount; }

double VolumetricFigure::getDimension(int i) const {
    if (i < 0 || i >= dimCount)
        throw std::out_of_range("Индекс размера вне диапазона");
    return dimensions[i];
}

void VolumetricFigure::setDimension(int i, double v) {
    if (i < 0 || i >= dimCount)
        throw std::out_of_range("Индекс размера вне диапазона");
    if (v <= 0)
        throw std::invalid_argument("Размер должен быть > 0");
    dimensions[i] = v;
}

VolumetricFigure& VolumetricFigure::operator=(const VolumetricFigure& other) {
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