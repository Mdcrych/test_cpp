#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>

class GeometryFigure {
public:
    virtual double getSquare() const = 0;
    virtual ~GeometryFigure() {}
};

class Rectangle : public GeometryFigure {
public:
    Rectangle(double w, double h) {
        if (w >= 0 && h >= 0) {
            width = w;
            height = h;
        } else {
            std::cerr << "Некорректные размеры прямоугольника. Значения заменены на 0.\n";
            width = 0;
            height = 0;
        }
    }

    double getSquare() const override { return width * height; }

private:
    double width;
    double height;
};

class Circle : public GeometryFigure {
public:
    Circle(double r) {
        if (r >= 0) {
            radius = r;
        } else {
            std::cerr << "Некорректное значение радиуса круга. Значение заменено на 0.\n";
            radius = 0;
        }
    }

    double getSquare() const override { return radius * radius * PI; }

private:
    double radius;
    static constexpr double PI = 3.14;
};

class Triangle : public GeometryFigure {
public:
    Triangle(double s_1, double s_2, double s_3) {
        if (s_1 >= 0 && s_2 >= 0 && s_3 >= 0) {
            side_1 = s_1;
            side_2 = s_2;
            side_3 = s_3;
        } else {
            std::cerr << "Некорректные стороны треугольника. Значения заменены на 0.\n";
            side_1 = side_2 = side_3 = 0;
        }
    }

    double getSemiPerimeter() const { return (side_3 + side_2 + side_1) / 2; }

    double getSquare() const override {
        if (side_1 == 0 || side_2 == 0 || side_3 == 0)
            return 0;
        double P = getSemiPerimeter();
        return std::sqrt(P * (P - side_1) * (P - side_2) * (P - side_3));
    }

private:
    double side_1;
    double side_2;
    double side_3;
};

void bubbleSort(std::vector<std::unique_ptr<GeometryFigure>>& figures) {
    size_t count = figures.size();
    for (size_t i = 0; i < count; i++) {
        bool isSwap = false;
        for (size_t j = 0; j < count - i - 1; j++) {
            if (figures[j]->getSquare() < figures[j + 1]->getSquare()) {
                std::swap(figures[j], figures[j + 1]);
                isSwap = true;
            }
        }
        if (!isSwap) break;
    }
}

void printSquares(const std::vector<std::unique_ptr<GeometryFigure>>& figures) {
    for (const auto& figure : figures) {
        std::cout << "Square: " << figure->getSquare() << '\n';
    }
}

int main() {
    try {
        std::vector<std::unique_ptr<GeometryFigure>> figures;

        // Примеры добавления фигур
        figures.emplace_back(std::make_unique<Rectangle>(10.8, 2));
        figures.emplace_back(std::make_unique<Rectangle>(-30, 50)); // Некорректный
        figures.emplace_back(std::make_unique<Triangle>(10, -12.2, 3)); // Некорректный
        figures.emplace_back(std::make_unique<Circle>(8.2));
        figures.emplace_back(std::make_unique<Rectangle>(5.5, 2));
        figures.emplace_back(std::make_unique<Triangle>(0, 0, 0)); // Площадь будет равна 0
        figures.emplace_back(std::make_unique<Rectangle>(0, 0)); // Площадь будет равна 0

        std::cout << "Изначальный массив:\n";
        printSquares(figures);

        // Сортируем фигуры
        bubbleSort(figures);

        std::cout << "Отсортированный массив:\n";
        printSquares(figures);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Неизвестная ошибка." << std::endl;
    }

    return 0;
}