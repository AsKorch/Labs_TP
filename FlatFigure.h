#ifndef FLATFIGURE_H
#define FLATFIGURE_H

#include "Base.h"

class FlatFigure : public Base {
public:
    FlatFigure();
    FlatFigure(const std::string& figureType, const double* dims, int dimCount);
    FlatFigure(const FlatFigure& other);
    ~FlatFigure() override;

    double calculate() const override;
    void draw() const override;
    void print() const override;
    const char* getCategory() const override;
    int getTypeId() const override;
    Base* clone() const override;

    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;

    std::string getFigureType() const;
    void setFigureType(const std::string& t);
    int getDimCount() const;
    double getDimension(int i) const;
    void setDimension(int i, double v);

    FlatFigure& operator=(const FlatFigure& other);

private:
    std::string figureType;
    double* dimensions;
    int dimCount;

    double calcArea() const;
};

#endif