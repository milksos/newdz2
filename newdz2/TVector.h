#ifndef TVECTOR_H
#define TVECTOR_H

#include "TDMassive.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <string>

// Класс TVector для математических операций с векторами
// Реализован с использованием класса TDMassive для хранения данных

template <typename T>
class TVector {
    TDMassive<T> _data; // Внутренний массив для хранения данных вектора
    size_t _start_index; // Начальный индекс вектора (например, для смещенных векторов)

public:
    // Конструкторы
    TVector();
    explicit TVector(size_t size, T value = T());
    TVector(const TVector& other);

    // Оператор доступа к элементу
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Перегрузка математических операторов
    TVector<T> operator+(const TVector<T>& other) const;
    TVector<T> operator-(const TVector<T>& other) const;
    T operator*(const TVector<T>& other) const; // Скалярное произведение (многопоточная версия)

    TVector<T>& operator+=(const TVector<T>& other);
    TVector<T>& operator-=(const TVector<T>& other);
    TVector<T> operator*(T scalar) const;
    TVector<T>& operator*=(T scalar);

    // Сравнительные операторы
    bool operator==(const TVector<T>& other) const;
    bool operator!=(const TVector<T>& other) const;

    // Другие полезные методы
    size_t size() const noexcept;
    double magnitude() const; // Длина вектора

    // Печать вектора для отладки
    void print() const;
};

// Реализация конструкторов и методов TVector
// Конструктор по умолчанию
template <typename T>
TVector<T>::TVector() : _data(), _start_index(0) {}

// Конструктор с заданным размером и значением элементов
template <typename T>
TVector<T>::TVector(size_t size, T value) : _data(size), _start_index(0) {
    for (size_t i = 0; i < size; i++) {
        _data.push_back(value);
    }
}

// Конструктор копирования
template <typename T>
TVector<T>::TVector(const TVector<T>& other) : _data(other._data), _start_index(other._start_index) {}

// Оператор доступа к элементу
// Непостоянный вариант
template <typename T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _data.size()) {
        throw std::out_of_range("Индекс вне диапазона: " + std::to_string(index));
    }
    return _data[index];
}

// Константный вариант
template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _data.size()) {
        throw std::out_of_range("Индекс вне диапазона: " + std::to_string(index));
    }
    return _data[index];
}

// Перегрузка математических операторов
// Сложение векторов
template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] + other[i];
    }
    return result;
}

// Вычитание векторов
template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] - other[i];
    }
    return result;
}

// Скалярное произведение векторов (многопоточная версия)
template <typename T>
T TVector<T>::operator*(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }

    const size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<T> partial_results(num_threads, T());

    auto thread_func = [&](size_t start, size_t end, size_t thread_index) {
        T sum = T();
        for (size_t i = start; i < end; ++i) {
            sum += _data[i] * other[i];
        }
        partial_results[thread_index] = sum;
        };

    size_t chunk_size = _data.size() / num_threads;
    size_t remainder = _data.size() % num_threads;

    size_t start = 0;
    for (size_t i = 0; i < num_threads; ++i) {
        size_t end = start + chunk_size + (i < remainder ? 1 : 0);
        threads.emplace_back(thread_func, start, end, i);
        start = end;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    T result = T();
    for (const T& partial_result : partial_results) {
        result += partial_result;
    }

    return result;
}

// Увеличение вектора на другой вектор
template <typename T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& other) {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] += other[i];
    }
    return *this;
}

// Уменьшение вектора на другой вектор
template <typename T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& other) {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("Размеры векторов должны совпадать");
    }
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] -= other[i];
    }
    return *this;
}

// Умножение вектора на число
template <typename T>
TVector<T> TVector<T>::operator*(T scalar) const {
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] * scalar;
    }
    return result;
}

// Умножение вектора на число (присваивание)
template <typename T>
TVector<T>& TVector<T>::operator*=(T scalar) {
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] *= scalar;
    }
    return *this;
}

// Сравнение векторов на равенство
template <typename T>
bool TVector<T>::operator==(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        return false;
    }
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[i] != other[i]) {
            return false;
        }
    }
    return true;
}

// Сравнение векторов на неравенство
template <typename T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

// Получение размера вектора
template <typename T>
size_t TVector<T>::size() const noexcept {
    return _data.size();
}

// Длина вектора
template <typename T>
double TVector<T>::magnitude() const {
    double sum = 0;
    for (size_t i = 0; i < _data.size(); i++) {
        sum += static_cast<double>(_data[i]) * static_cast<double>(_data[i]);
    }
    return std::sqrt(sum);
}

// Печать вектора для отладки
template <typename T>
void TVector<T>::print() const {
    for (size_t i = 0; i < _data.size(); i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << "\n";
}

#endif // TVECTOR_H