#include "Keeper.h"
#include "FlatFigure.h"
#include "VolumetricFigure.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <clocale>

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) { clearInput(); return v; }
        std::cout << "Ошибка ввода. Введите целое число.\n";
        clearInput();
    }
}

static double readDouble(const std::string& prompt) {
    double v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) { clearInput(); return v; }
        std::cout << "Ошибка ввода. Введите число.\n";
        clearInput();
    }
}

static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

static Base* createFlatFigure() {
    std::cout << "Доступные типы: круг, квадрат, прямоугольник, треугольник, эллипс\n";
    std::string type = readLine("Введите тип: ");
    int dimCount = 0;
    if (type == "круг" || type == "квадрат") dimCount = 1;
    else if (type == "прямоугольник" || type == "эллипс") dimCount = 2;
    else if (type == "треугольник") dimCount = 3;
    else throw std::invalid_argument("Неизвестный тип плоской фигуры: " + type);

    double* dims = new double[dimCount];
    for (int i = 0; i < dimCount; ++i)
        dims[i] = readDouble("Размер " + std::to_string(i + 1) + ": ");

    Base* fig = nullptr;
    try { fig = new FlatFigure(type, dims, dimCount); }
    catch (...) { delete[] dims; throw; }
    delete[] dims;
    return fig;
}

static Base* createVolumetricFigure() {
    std::cout << "Доступные типы: куб, шар, цилиндр, конус, параллелепипед\n";
    std::string type = readLine("Введите тип: ");
    int dimCount = 0;
    if (type == "куб" || type == "шар") dimCount = 1;
    else if (type == "цилиндр" || type == "конус") dimCount = 2;
    else if (type == "параллелепипед") dimCount = 3;
    else throw std::invalid_argument("Неизвестный тип объёмной фигуры: " + type);

    double* dims = new double[dimCount];
    for (int i = 0; i < dimCount; ++i)
        dims[i] = readDouble("Размер " + std::to_string(i + 1) + ": ");

    Base* fig = nullptr;
    try { fig = new VolumetricFigure(type, dims, dimCount); }
    catch (...) { delete[] dims; throw; }
    delete[] dims;
    return fig;
}

static void editFigure(Base* fig) {
    if (!fig) throw std::invalid_argument("Пустой указатель на фигуру");
    std::cout << "Текущая фигура:\n";
    fig->print();
    std::cout << "1. Изменить имя\n2. Изменить размеры\n";
    int choice = readInt("Выбор: ");
    if (choice == 1) {
        fig->setName(readLine("Новое имя: "));
        std::cout << "Имя изменено.\n";
    } else if (choice == 2) {
        FlatFigure* ff = dynamic_cast<FlatFigure*>(fig);
        VolumetricFigure* vf = dynamic_cast<VolumetricFigure*>(fig);
        if (ff) {
            for (int i = 0; i < ff->getDimCount(); ++i)
                ff->setDimension(i, readDouble("Размер " + std::to_string(i + 1) + ": "));
        } else if (vf) {
            for (int i = 0; i < vf->getDimCount(); ++i)
                vf->setDimension(i, readDouble("Размер " + std::to_string(i + 1) + ": "));
        }
        std::cout << "Размеры изменены.\n";
    } else {
        std::cout << "Отмена.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Keeper keeper;
    bool running = true;

    while (running) {
        std::cout << "\n===== МЕНЮ =====\n"
                  << "1. Добавить плоскую фигуру\n"
                  << "2. Добавить объёмную фигуру\n"
                  << "3. Удалить фигуру по индексу\n"
                  << "4. Показать все фигуры\n"
                  << "5. Нарисовать все фигуры\n"
                  << "6. Изменить фигуру\n"
                  << "7. Сохранить в файл\n"
                  << "8. Загрузить из файла\n"
                  << "0. Выход\n";
        int choice = readInt("Ваш выбор: ");

        try {
            switch (choice) {
                case 1:
                    keeper.add(createFlatFigure());
                    std::cout << "Плоская фигура добавлена.\n";
                    break;
                case 2:
                    keeper.add(createVolumetricFigure());
                    std::cout << "Объёмная фигура добавлена.\n";
                    break;
                case 3:
                    keeper.remove(readInt("Индекс для удаления: "));
                    std::cout << "Фигура удалена.\n";
                    break;
                case 4:
                    keeper.printAll();
                    break;
                case 5:
                    keeper.drawAll();
                    break;
                case 6:
                    editFigure(keeper.getAt(readInt("Индекс для изменения: ")));
                    break;
                case 7:
                    keeper.saveToFile(readLine("Имя файла: "));
                    std::cout << "Сохранено.\n";
                    break;
                case 8:
                    keeper.loadFromFile(readLine("Имя файла: "));
                    std::cout << "Загружено.\n";
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Неверный пункт меню.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
    return 0;
}