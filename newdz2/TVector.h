#ifndef TVECTOR_H
#define TVECTOR_H

#include "TDMassive.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <string>

// ����� TVector ��� �������������� �������� � ���������
// ���������� � �������������� ������ TDMassive ��� �������� ������

template <typename T>
class TVector {
    TDMassive<T> _data; // ���������� ������ ��� �������� ������ �������
    size_t _start_index; // ��������� ������ ������� (��������, ��� ��������� ��������)

public:
    // ������������
    TVector();
    explicit TVector(size_t size, T value = T());
    TVector(const TVector& other);

    // �������� ������� � ��������
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // ���������� �������������� ����������
    TVector<T> operator+(const TVector<T>& other) const;
    TVector<T> operator-(const TVector<T>& other) const;
    T operator*(const TVector<T>& other) const; // ��������� ������������ (������������� ������)

    TVector<T>& operator+=(const TVector<T>& other);
    TVector<T>& operator-=(const TVector<T>& other);
    TVector<T> operator*(T scalar) const;
    TVector<T>& operator*=(T scalar);

    // ������������� ���������
    bool operator==(const TVector<T>& other) const;
    bool operator!=(const TVector<T>& other) const;

    // ������ �������� ������
    size_t size() const noexcept;
    double magnitude() const; // ����� �������

    // ������ ������� ��� �������
    void print() const;
};

// ���������� ������������� � ������� TVector
// ����������� �� ���������
template <typename T>
TVector<T>::TVector() : _data(), _start_index(0) {}

// ����������� � �������� �������� � ��������� ���������
template <typename T>
TVector<T>::TVector(size_t size, T value) : _data(size), _start_index(0) {
    for (size_t i = 0; i < size; i++) {
        _data.push_back(value);
    }
}

// ����������� �����������
template <typename T>
TVector<T>::TVector(const TVector<T>& other) : _data(other._data), _start_index(other._start_index) {}

// �������� ������� � ��������
// ������������ �������
template <typename T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _data.size()) {
        throw std::out_of_range("������ ��� ���������: " + std::to_string(index));
    }
    return _data[index];
}

// ����������� �������
template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _data.size()) {
        throw std::out_of_range("������ ��� ���������: " + std::to_string(index));
    }
    return _data[index];
}

// ���������� �������������� ����������
// �������� ��������
template <typename T>
TVector<T> TVector<T>::operator+(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("������� �������� ������ ���������");
    }
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] + other[i];
    }
    return result;
}

// ��������� ��������
template <typename T>
TVector<T> TVector<T>::operator-(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("������� �������� ������ ���������");
    }
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] - other[i];
    }
    return result;
}

// ��������� ������������ �������� (������������� ������)
template <typename T>
T TVector<T>::operator*(const TVector<T>& other) const {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("������� �������� ������ ���������");
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

// ���������� ������� �� ������ ������
template <typename T>
TVector<T>& TVector<T>::operator+=(const TVector<T>& other) {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("������� �������� ������ ���������");
    }
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] += other[i];
    }
    return *this;
}

// ���������� ������� �� ������ ������
template <typename T>
TVector<T>& TVector<T>::operator-=(const TVector<T>& other) {
    if (_data.size() != other._data.size()) {
        throw std::invalid_argument("������� �������� ������ ���������");
    }
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] -= other[i];
    }
    return *this;
}

// ��������� ������� �� �����
template <typename T>
TVector<T> TVector<T>::operator*(T scalar) const {
    TVector<T> result(_data.size());
    for (size_t i = 0; i < _data.size(); i++) {
        result[i] = _data[i] * scalar;
    }
    return result;
}

// ��������� ������� �� ����� (������������)
template <typename T>
TVector<T>& TVector<T>::operator*=(T scalar) {
    for (size_t i = 0; i < _data.size(); i++) {
        _data[i] *= scalar;
    }
    return *this;
}

// ��������� �������� �� ���������
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

// ��������� �������� �� �����������
template <typename T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

// ��������� ������� �������
template <typename T>
size_t TVector<T>::size() const noexcept {
    return _data.size();
}

// ����� �������
template <typename T>
double TVector<T>::magnitude() const {
    double sum = 0;
    for (size_t i = 0; i < _data.size(); i++) {
        sum += static_cast<double>(_data[i]) * static_cast<double>(_data[i]);
    }
    return std::sqrt(sum);
}

// ������ ������� ��� �������
template <typename T>
void TVector<T>::print() const {
    for (size_t i = 0; i < _data.size(); i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << "\n";
}

#endif // TVECTOR_H