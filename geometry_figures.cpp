#include <cmath>          
#include <iostream>       
#include <utility>        
#include <vector>         
#include <memory>         // Подключаем заголовочный файл для умных указателей, таких как std::unique_ptr
#include <algorithm>      

// Абстрактный базовый класс для геометрических фигур
class GeometryFigure {
public:
    // Чисто виртуальная функция для подсчета площади. Должна быть реализована в производных классах.
    virtual double getSquare() const = 0;

    // Виртуальный деструктор. Позволяет правильно удалять объекты производных классов.
    virtual ~GeometryFigure() {}
};

// Класс для представления прямоугольника
class Rectangle : public GeometryFigure {
public:
    // Конструктор, который принимает ширину и высоту
    Rectangle(double w, double h) {
        // Проверяем, что ширина и высота неотрицательны
        if (w >= 0 && h >= 0) {
            width = w;   // Устанавливаем ширину
            height = h;  // Устанавливаем высоту
        } else {
            std::cerr << "Некорректные размеры прямоугольника. Значения заменены на 0.\n";
            width = 0;   // Если размеры некорректные, устанавливаем их на 0
            height = 0;
        }
    }

    // Реализация чисто виртуальной функции для расчета площади
    double getSquare() const override { return width * height; }

private:
    double width;  // Ширина прямоугольника
    double height; // Высота прямоугольника
};

// Класс для представления круга
class Circle : public GeometryFigure {
public:
    // Конструктор, который принимает радиус
    Circle(double r) {
        if (r >= 0) {
            radius = r; // Устанавливаем радиус
        } else {
            std::cerr << "Некорректное значение радиуса круга. Значение заменено на 0.\n";
            radius = 0; // Если радиус некорректный, устанавливаем его на 0
        }
    }

    // Реализация чисто виртуальной функции для расчета площади
    double getSquare() const override { return radius * radius * PI; }

private:
    double radius; // Радиус круга
    static constexpr double PI = 3.14; // Константа для числа Пи
};

// Класс для представления треугольника
class Triangle : public GeometryFigure {
public:
    // Конструктор, который принимает длины трех сторон
    Triangle(double s_1, double s_2, double s_3) {
        if (s_1 >= 0 && s_2 >= 0 && s_3 >= 0) {
            side_1 = s_1; // Устанавливаем длину первой стороны
            side_2 = s_2; // Устанавливаем длину второй стороны
            side_3 = s_3; // Устанавливаем длину третьей стороны
        } else {
            std::cerr << "Некорректные стороны треугольника. Значения заменены на 0.\n";
            side_1 = side_2 = side_3 = 0; // Если стороны некорректные, устанавливаем их на 0
        }
    }

    // Функция для расчета полупериметра треугольника
    double getSemiPerimeter() const { return (side_3 + side_2 + side_1) / 2; }

    // Реализация чисто виртуальной функции для расчета площади
    double getSquare() const override {
        if (side_1 == 0 || side_2 == 0 || side_3 == 0)
            return 0; // Если хотя бы одна сторона равна 0, площадь будет равна 0
        double P = getSemiPerimeter(); // Вычисляем полупериметр
        // Формула Герона для расчета площади треугольника
        return std::sqrt(P * (P - side_1) * (P - side_2) * (P - side_3));
    }

private:
    double side_1; // Длина первой стороны треугольника
    double side_2; // Длина второй стороны треугольника
    double side_3; // Длина третьей стороны треугольника
};

// Функция для сортировки фигур по площади с использованием сортировки пузырьком
void bubbleSort(std::vector<std::unique_ptr<GeometryFigure>>& figures) {
    size_t count = figures.size(); // Получаем общее количество фигур
    for (size_t i = 0; i < count; i++) {
        bool isSwap = false; // Переменная для проверки, произошли ли перестановки
        for (size_t j = 0; j < count - i - 1; j++) {
            // Сравниваем площади двух фигур
            if (figures[j]->getSquare() < figures[j + 1]->getSquare()) {
                std::swap(figures[j], figures[j + 1]); // Меняем местами фигуры
                isSwap = true; // Устанавливаем флаг, что произошла перестановка
            }
        }
        if (!isSwap) break; // Если не произошло перестановок, выходим из цикла
    }
}

// Функция для вывода площадей фигур
void printSquares(const std::vector<std::unique_ptr<GeometryFigure>>& figures) {
    for (const auto& figure : figures) { // Проходим по каждой фигуре
        std::cout << "Square: " << figure->getSquare() << '\n'; // Выводим площадь фигуры
    }
}

int main() {
    try {
        // Вектор, который будет хранить уникальные указатели на фигуры
        std::vector<std::unique_ptr<GeometryFigure>> figures;

        // Примеры добавления фигур с использованием emplace_back
        figures.emplace_back(std::make_unique<Rectangle>(10.8, 2));      // Корректный прямоугольник
        figures.emplace_back(std::make_unique<Rectangle>(-30, 50));       // Некорректные значения
        figures.emplace_back(std::make_unique<Triangle>(10, -12.2, 3));   // Некорректные значения
        figures.emplace_back(std::make_unique<Circle>(8.2));              // Корректный круг
        figures.emplace_back(std::make_unique<Rectangle>(5.5, 2));       // Корректный прямоугольник
        figures.emplace_back(std::make_unique<Triangle>(0, 0, 0));        // Все стороны 0
        figures.emplace_back(std::make_unique<Rectangle>(0, 0));          // Ширина и высота 0

        std::cout << "Изначальный массив:\n";
        printSquares(figures); // Печатаем площади исходных фигур

        // Сортируем фигуры по площади
        bubbleSort(figures);

        std::cout << "Отсортированный массив:\n";
        printSquares(figures); // Печатаем площади отсортированных фигур
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl; // Выводим сообщение об ошибке в случае исключения
    } catch (...) {
        std::cerr << "Неизвестная ошибка." << std::endl; // Выводим сообщение об общей ошибке
    }

    return 0; // Завершаем программу
}
