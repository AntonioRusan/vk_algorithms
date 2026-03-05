#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

void reversePartArray(int* arr, int n, int left, int right) {
    if (left >= 0 && left < n && right >= 0 && right < n) {
        while (left < right) {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
            right--;
        }
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

TEST(ReversePartArrayTest, ReverseFullArray) {
    vector<int> vec = {1, 2, 3, 4, 5};
    reversePartArray(vec.data(), vec.size(), 0, 4);
    EXPECT_EQ(vec, (vector<int>{5, 4, 3, 2, 1}));
}

TEST(ReversePartArrayTest, ReversePartOfArray) {
    vector<int> vec = {1, 2, 3, 4, 5};
    reversePartArray(vec.data(), vec.size(), 1, 3);
    EXPECT_EQ(vec, (vector<int>{1, 4, 3, 2, 5}));
}

TEST(ReversePartArrayTest, InvalidBounds) {
    vector<int> vec = {1, 2, 3};
    reversePartArray(vec.data(), vec.size(), -1, 5);
    EXPECT_EQ(vec, (vector<int>{1, 2, 3}));
}

TEST(RotateArrayTest, Example) {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    rotateArray(vec.data(), vec.size(), 3);
    EXPECT_EQ(vec, (vector<int>{5, 6, 7, 1, 2, 3, 4}));
}

TEST(RotateArrayTest, KEqualsZero) {
    vector<int> vec = {1, 2, 3};
    rotateArray(vec.data(), vec.size(), 0);
    EXPECT_EQ(vec, (vector<int>{1, 2, 3}));
}

TEST(RotateArrayTest, KGreaterThanArraySize) {
    vector<int> vec = {1, 2, 3};
    rotateArray(vec.data(), vec.size(), 5);
    EXPECT_EQ(vec, (vector<int>{2, 3, 1}));
}
TEST(RotateArrayTest, SingleElement) {
    vector<int> vec = {10};
    rotateArray(vec.data(), vec.size(), 1);
    EXPECT_EQ(vec, (vector<int>{10}));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            int N, k;
            cin >> N >> k;
            vector<int> arr(N);
            for (int i = 0; i < N; i++) {
                cin >> arr[i];
            }
            rotateArray(arr.data(), N, k);
            for (int i = 0; i < N; i++) {
                cout << arr[i] << " ";
            }
            return 0;
        }
    }
    
    return RUN_ALL_TESTS();
}