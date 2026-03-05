#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void reversePartArray(int* arr, int n, int left, int right) {
    if (left >= 0 && left < n && right >= 0 && right < n)
        while (left < right) {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
            right--;
        }
}
void rotateArray(int* arr, int n, int k) {
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;

    reversePartArray(arr, n, 0, n - 1);
    reversePartArray(arr, n, 0, k - 1);
    reversePartArray(arr, n, k, n - 1);
}


#include "catch.hpp"

TEST_CASE("ReversePartArray - Reverse full array") {
    vector<int> vec = {1, 2, 3, 4, 5};
    reversePartArray(vec.data(), vec.size(), 0, 4);
    REQUIRE(vec == vector<int>{5, 4, 3, 2, 1});
}

TEST_CASE("ReversePartArray - Reverse part of array") {
    vector<int> vec = {1, 2, 3, 4, 5};
    reversePartArray(vec.data(), vec.size(), 1, 3);
    REQUIRE(vec == vector<int>{1, 4, 3, 2, 5});
}

TEST_CASE("ReversePartArray - Invalid bounds") {
    vector<int> vec = {1, 2, 3};
    reversePartArray(vec.data(), vec.size(), -1, 5);
    REQUIRE(vec == vector<int>{1, 2, 3});
}

TEST_CASE("RotateArray - Example") {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    rotateArray(vec.data(), vec.size(), 3);
    REQUIRE(vec == vector<int>{5, 6, 7, 1, 2, 3, 4});
}

TEST_CASE("RotateArray - K equals zero") {
    vector<int> vec = {1, 2, 3};
    rotateArray(vec.data(), vec.size(), 0);
    REQUIRE(vec == vector<int>{1, 2, 3});
}

TEST_CASE("RotateArray - K greater than array size") {
    vector<int> vec = {1, 2, 3};
    rotateArray(vec.data(), vec.size(), 5);
    REQUIRE(vec == vector<int>{2, 3, 1});
}

TEST_CASE("RotateArray - Empty array") {
    vector<int> vec = {};
    rotateArray(vec.data(), vec.size(), 1);
    REQUIRE(vec.empty());
}

TEST_CASE("RotateArray - Single element") {
    vector<int> vec = {10};
    rotateArray(vec.data(), vec.size(), 1);
    REQUIRE(vec == vector<int>{10});
}


int main(int argc, char* argv[]){
     // Ваш код ДО запуска тестов
    std::cout << "Инициализация..." << std::endl;

    // Инициализация Catch2
    Catch::Session session;

    // Запуск тестов
    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0) return returnCode;

    returnCode = session.run();

    // Ваш код ПОСЛЕ запуска тестов
    std::cout << "Завершение..." << std::endl;

    return returnCode;
}
