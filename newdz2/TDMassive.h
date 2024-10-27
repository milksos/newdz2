#ifndef TDMASSIVE_H
#define TDMASSIVE_H

#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <string>

#define STEP_CAPACITY 15
#define MAX_CAPACITY 100000

// Состояния элементов массива
enum State { empty, busy, deleted };

// Шаблонный класс TDMassive
// Реализация динамического массива с возможностью добавления, удаления и замены элементов
// Класс поддерживает состояния элементов: пустой, занятый и удаленный

template <typename T>
class TDMassive {
    T* _data; // Указатель на массив данных
    State* _states; // Указатель на массив состояний
    size_t _capacity; // Текущая вместимость массива
    size_t _size; // Текущий размер (количество элементов)
    size_t _deleted; // Количество удаленных элементов

public:
    TDMassive(); // Конструктор по умолчанию
    explicit TDMassive(size_t n); // Конструктор с заданной вместимостью
    ~TDMassive(); // Деструктор

    bool empty() const noexcept; // Проверка, пуст ли массив
    bool full() const noexcept; // Проверка, полон ли массив
    size_t size() const noexcept; // Получение текущего размера
    size_t capacity() const noexcept; // Получение текущей вместимости
    void clear(); // Очистка массива
    void push_back(T value); // Добавление элемента в конец массива
    void remove_by_index(size_t pos); // Удаление элемента по индексу
    void replace(size_t pos, T new_value); // Замена элемента по индексу
    void repacking(); // Перепаковка массива для удаления "пустых" мест
    size_t find_first(T value) const noexcept; // Поиск первого элемента с заданным значением
    size_t find_last(T value) const noexcept; // Поиск последнего элемента с заданным значением
    T& operator[](size_t index); // Оператор доступа к элементу по индексу
    const T& operator[](size_t index) const; // Константный оператор доступа к элементу по индексу
};

// Реализация методов TDMassive
// Конструктор по умолчанию
// Инициализирует массив с вместимостью равной STEP_CAPACITY
template <typename T>
TDMassive<T>::TDMassive() : _size(0), _capacity(STEP_CAPACITY), _deleted(0) {
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Конструктор с заданной вместимостью
// Инициализирует массив с заданной вместимостью n
template <typename T>
TDMassive<T>::TDMassive(size_t n) : _capacity(n), _size(0), _deleted(0) {
    if (_capacity == 0) {
        _capacity = STEP_CAPACITY;
    }
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

// Деструктор
// Освобождает выделенную память
template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    delete[] _states;
}

// Проверка на пустоту
// Возвращает true, если массив пуст
template <typename T>
bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

// Проверка на заполненность
// Возвращает true, если массив полон
template <typename T>
bool TDMassive<T>::full() const noexcept {
    return _size >= _capacity;
}

// Получение текущего размера
// Возвращает количество элементов в массиве
template <typename T>
size_t TDMassive<T>::size() const noexcept {
    return _size;
}

// Добавление элемента в конец массива
// Добавляет элемент в конец массива, если есть свободное место, иначе увеличивает вместимость
template <typename T>
void TDMassive<T>::push_back(T value) {
    if (full()) {
        size_t new_capacity = _capacity * 2;
        if (new_capacity > MAX_CAPACITY) {
            throw std::logic_error("Превышена максимальная вместимость");
        }

        T* new_data = new T[new_capacity];
        State* new_states = new State[new_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = State::empty;
        }
    }
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

// Удаление элемента по индексу
// Устанавливает состояние элемента как "удаленный"
template <typename T>
void TDMassive<T>::remove_by_index(size_t pos) {
    if (pos >= _size || _states[pos] == State::deleted) {
        throw std::out_of_range("Неверный индекс: " + std::to_string(pos));
    }
    _states[pos] = State::deleted;
    _deleted++;
}

// Оператор доступа к элементу по индексу
// Непостоянный вариант
template <typename T>
T& TDMassive<T>::operator[](size_t index) {
    if (index >= _size || _states[index] == State::deleted) {
        throw std::out_of_range("Индекс вне диапазона: " + std::to_string(index));
    }
    return _data[index];
}

// Оператор доступа к элементу по индексу
// Константный вариант
template <typename T>
const T& TDMassive<T>::operator[](size_t index) const {
    if (index >= _size || _states[index] == State::deleted) {
        throw std::out_of_range("Индекс вне диапазона: " + std::to_string(index));
    }
    return _data[index];
}

#endif // TDMASSIVE_H