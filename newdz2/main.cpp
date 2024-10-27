#include <iostream>
#include "TVector.h"

void runVectorTests() {
    int total_tests = 0;
    int passed_tests = 0;

    // ��������� �������, ������� ����� ������������ � ������
    TVector<int> v1(3, 5);
    TVector<int> v2(3, 2);

    // ���� �������� ������������
    try {
        std::cout << "������ v1: ";
        v1.print(); // ��������� �����: 5 5 5
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� ������������\n";
    }

    // ���� �������� ��������
    try {
        TVector<int> v3 = v1 + v2;
        std::cout << "������ v3 (v1 + v2): ";
        v3.print(); // ��������� �����: 7 7 7
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� ��������\n";
    }

    // ���� ��������� ��������
    try {
        TVector<int> v4 = v1 - v2;
        std::cout << "������ v4 (v1 - v2): ";
        v4.print(); // ��������� �����: 3 3 3
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ ��������� ��������\n";
    }

    // ���� ���������� ������������ (������������� ������)
    try {
        int dotProduct = v1 * v2;
        std::cout << "��������� ������������ v1 � v2: " << dotProduct << "\n"; // ��������� �����: 30
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ ���������� ������������\n";
    }

    // ���� �������� ==
    try {
        TVector<int> v5(3, 5);
        std::cout << "v1 == v5: " << (v1 == v5 ? "������" : "����") << "\n"; // ��������� �����: ������
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� ==\n";
    }

    // ���� �������� !=
    try {
        std::cout << "v1 != v2: " << (v1 != v2 ? "������" : "����") << "\n"; // ��������� �����: ������
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� !=\n";
    }

    // ���� ��������� ������� �� ������
    try {
        TVector<int> v6 = v1 * 2;
        std::cout << "������ v6 (v1 * 2): ";
        v6.print(); // ��������� �����: 10 10 10
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ ��������� �� ������\n";
    }

    // ���� �������� +=
    try {
        v1 += v2;
        std::cout << "������ v1 ����� v1 += v2: ";
        v1.print(); // ��������� �����: 7 7 7
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� +=\n";
    }

    // ���� �������� -=
    try {
        v1 -= v2;
        std::cout << "������ v1 ����� v1 -= v2: ";
        v1.print(); // ��������� �����: 5 5 5
        total_tests++;
        passed_tests++;
    }
    catch (...) {
        std::cout << "������ ��� ������������ �������� -=\n";
    }

    // ����� ������ ���������� ������ � ���������� �������� ������
    std::cout << "\n����� ���������� ������: " << total_tests << "\n";
    std::cout << "���������� �������� ������: " << passed_tests << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    runVectorTests();
    return 0;
}