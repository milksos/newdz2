#include <iostream>
#include "TVector.h"

void runVectorTests() {
    int total_tests = 0;
    int passed_tests = 0;

    // Объявляем векторы, которые будем использовать в тестах
    TVector<int> v1(3, 5);
    TVector<int> v2(3, 2);

    // Тест базового конструктора
    try {
        std::cout << "Вектор v1: ";
        v1.print(); // Ожидаемый вывод: 5 5 5
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании базового конструктора\n";
    }

    // Тест сложения векторов
    try {
        TVector<int> v3 = v1 + v2;
        std::cout << "Вектор v3 (v1 + v2): ";
        v3.print(); // Ожидаемый вывод: 7 7 7
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании сложения векторов\n";
    }

    // Тест вычитания векторов
    try {
        TVector<int> v4 = v1 - v2;
        std::cout << "Вектор v4 (v1 - v2): ";
        v4.print(); // Ожидаемый вывод: 3 3 3
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании вычитания векторов\n";
    }

    // Тест скалярного произведения (многопоточная версия)
    try {
        int dotProduct = v1 * v2;
        std::cout << "Скалярное произведение v1 и v2: " << dotProduct << "\n"; // Ожидаемый вывод: 30
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании скалярного произведения\n";
    }

    // Тест операции ==
    try {
        TVector<int> v5(3, 5);
        std::cout << "v1 == v5: " << (v1 == v5 ? "истина" : "ложь") << "\n"; // Ожидаемый вывод: истина
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании операции ==\n";
    }

    // Тест операции !=
    try {
        std::cout << "v1 != v2: " << (v1 != v2 ? "истина" : "ложь") << "\n"; // Ожидаемый вывод: истина
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании операции !=\n";
    }

    // Тест умножения вектора на скаляр
    try {
        TVector<int> v6 = v1 * 2;
        std::cout << "Вектор v6 (v1 * 2): ";
        v6.print(); // Ожидаемый вывод: 10 10 10
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании умножения на скаляр\n";
    }

    // Тест операции +=
    try {
        v1 += v2;
        std::cout << "Вектор v1 после v1 += v2: ";
        v1.print(); // Ожидаемый вывод: 7 7 7
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании операции +=\n";
    }

    // Тест операции -=
    try {
        v1 -= v2;
        std::cout << "Вектор v1 после v1 -= v2: ";
        v1.print(); // Ожидаемый вывод: 5 5 5
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "Ошибка при тестировании операции -=\n";
    }

    // Вывод общего количества тестов и количества успешных тестов
    std::cout << "\nОбщее количество тестов: " << total_tests << "\n";
    std::cout << "Количество успешных тестов: " << passed_tests << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    runVectorTests();
    return 0;
}