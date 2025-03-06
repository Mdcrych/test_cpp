#include <iostream>   
#include <vector>     
#include <thread>     // Для работы с потоками
#include <algorithm>   
#include <mutex>      // Для использования мьютексов, обеспечивающих потокобезопасность

// Мьютекс для защиты консольного вывода
std::mutex con_mut;

// Функция быстрой сортировки
void quickSort(std::vector<int> arr) {
    std::sort(arr.begin(), arr.end());  // Используем встроенный алгоритм сортировки для упорядочивания массива
    std::lock_guard<std::mutex> guard(con_mut); // Блокируем консольный вывод другим потокам
    std::cout << "Сортировка: быстрая\nРезультат: "; // Выводим результат сортировки
    for (const int& num : arr) { // Проходим по отсортированному массиву и выводим элементы
        std::cout << num << " "; // Выводим каждый элемент с пробелом
    }
    std::cout << "\n"; // Переход на новую строку в выводе
}

// Функция сортировки пузырьком
void bubbleSort(std::vector<int> arr) {
    int n = arr.size(); // Получаем размер массива
    for (int i = 0; i < n - 1; ++i) { // Внешний цикл для итерации по массиву
        for (int j = 0; j < n - i - 1; ++j) { // Внутренний цикл для сравнения соседних элементов
            if (arr[j] > arr[j + 1]) { // Если текущий элемент больше следующего
                std::swap(arr[j], arr[j + 1]); // Меняем их местами
            }
        }
    }
    std::lock_guard<std::mutex> guard(con_mut); // Этот блок кода анологичен прдыдущему блоку из быстрой сортировки
    std::cout << "Сортировка: пузырьком\nРезультат: "; 
    for (const int& num : arr) {
        std::cout << num << " "; 
    }
    std::cout << "\n";
}

// Функция сортировки выбором
void selectionSort(std::vector<int> arr) {
    int n = arr.size(); // Получаем размер массива
    for (int i = 0; i < n - 1; ++i) { // Внешний цикл для итерации по массиву
        int minIndex = i; // Предполагаем, что текущий элемент минимальный
        for (int j = i + 1; j < n; ++j) { // Внутренний цикл для нахождения минимального элемента
            if (arr[j] < arr[minIndex]) { // Если текущий элемент меньше минимального
                minIndex = j; // Обновляем индекс минимального элемента
            }
        }
        std::swap(arr[i], arr[minIndex]); // Меняем текущий элемент с найденным минимальным
    }
    std::lock_guard<std::mutex> guard(con_mut); 
    std::cout << "Сортировка: выбором\nРезультат: "; 
    for (const int& num : arr) {
        std::cout << num << " "; 
    }
    std::cout << "\n";
}

int main() {
    // Исходный массив
    std::vector<int> arr = {4, 1, 3, 2, 8, 5, 1, 9, 7}; // Инициализируем массив целых чисел

    // Создаем потоки, которые запускают сортировку на отдельных потоках
    std::thread quick_thread(quickSort, arr); 
    std::thread bubble_thread(bubbleSort, arr); 
    std::thread selection_thread(selectionSort, arr); 

    // Ждем завершения потоков
    quick_thread.join(); 
    bubble_thread.join(); 
    selection_thread.join(); 

    return 0; 
}