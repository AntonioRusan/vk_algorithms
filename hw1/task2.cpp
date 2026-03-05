#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

int* mergeArray(int* arr, int n, int* brr, int m) {
    int* result = new int[n + m];
    int i = 0, j = 0, k = 0;
    
    while (i < n && j < m) {
        if (arr[i] < brr[j]) 
            result[k++] = arr[i++];
        else
            result[k++] = brr[j++];
    }
    
    while (i < n) 
        result[k++] = arr[i++];
    while (j < m) 
        result[k++] = brr[j++];
    
    return result;
}

TEST(MergeArrayTest, BasicMerge) {
    int arr[] = {1, 3, 5};
    int brr[] = {2, 4, 6};
    int* result = mergeArray(arr, 3, brr, 3);
    vector<int> res(result, result + 6);
    EXPECT_EQ(res, (vector<int>{1, 2, 3, 4, 5, 6}));
    delete[] result;
}

TEST(MergeArrayTest, DifferentSizes) {
    int arr[] = {1, 2, 3};
    int brr[] = {4, 5};
    int* result = mergeArray(arr, 3, brr, 2);
    vector<int> res(result, result + 5);
    EXPECT_EQ(res, (vector<int>{1, 2, 3, 4, 5}));
    delete[] result;
}

TEST(MergeArrayTest, OneEmpty) {
    int arr[] = {1, 2, 3};
    int brr[] = {};
    int* result = mergeArray(arr, 3, brr, 0);
    vector<int> res(result, result + 3);
    EXPECT_EQ(res, (vector<int>{1, 2, 3}));
    delete[] result;
}

TEST(MergeArrayTest, BothEmpty) {
    int arr[] = {};
    int brr[] = {};
    int* result = mergeArray(arr, 0, brr, 0);
    vector<int> res(result, result);
    EXPECT_EQ(res, (vector<int>{}));
    delete[] result;
}

TEST(MergeArrayTest, DuplicateElements) {
    int arr[] = {1, 3, 3};
    int brr[] = {3, 4, 5};
    int* result = mergeArray(arr, 3, brr, 3);
    vector<int> res(result, result + 6);
    EXPECT_EQ(res, (vector<int>{1, 3, 3, 3, 4, 5}));
    delete[] result;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            int N, M;
            cin >> N >> M;
            int* arr = new int[N];
            int* brr = new int[M];
            for (int i = 0; i < N; i++) cin >> arr[i];
            for (int i = 0; i < M; i++) cin >> brr[i];
            int* crr = mergeArray(arr, N, brr, M);
            for (int i = 0; i < N + M; i++) cout << crr[i] << " ";
            delete[] arr;
            delete[] brr;
            delete[] crr;
            return 0;
        }
    }
    
    return RUN_ALL_TESTS();
}