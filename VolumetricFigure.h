#ifndef VOLUMETRICFIGURE_H
#define VOLUMETRICFIGURE_H

#include "Base.h"

class VolumetricFigure : public Base {
public:
    VolumetricFigure();
    VolumetricFigure(const std::string& figureType, const double* dims, int dimCount);
    VolumetricFigure(const VolumetricFigure& other);
    ~VolumetricFigure() override;

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

    VolumetricFigure& operator=(const VolumetricFigure& other);

private:
    std::string figureType;
    double* dimensions;
    int dimCount;

    double calcVolume() const;
};

#endif