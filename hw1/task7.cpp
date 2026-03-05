#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

void moveZero(int *arr, int n)
{
    int cur = 0;
    int l = 0;
    int tmp;
    while (cur < n)
    {
        if (arr[cur] != 0)
        {
            tmp = arr[l];
            arr[l] = arr[cur];
            arr[cur] = tmp;
            l++;
        }
        cur++;
    }
}
TEST(MoveZeroTest, BasicExample) {
    int arr[] = {1, 0, 3, 0, 5, 0, 7};
    moveZero(arr, 7);
    EXPECT_EQ(vector<int>(arr, arr + 7), (vector<int>{1, 3, 5, 7, 0, 0, 0}));
}

TEST(MoveZeroTest, AllZeros) {
    int arr[] = {0, 0, 0, 0};
    moveZero(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{0, 0, 0, 0}));
}

TEST(MoveZeroTest, NoZeros) {
    int arr[] = {1, 2, 3, 4};
    moveZero(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 2, 3, 4}));
}

TEST(MoveZeroTest, ZeroAtStart) {
    int arr[] = {0, 1, 2, 3};
    moveZero(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 2, 3, 0}));
}

TEST(MoveZeroTest, ZeroAtEnd) {
    int arr[] = {1, 2, 3, 0};
    moveZero(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 2, 3, 0}));
}

TEST(MoveZeroTest, AlternatingZeros) {
    int arr[] = {1, 0, 2, 0, 3, 0};
    moveZero(arr, 6);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{1, 2, 3, 0, 0, 0}));
}

TEST(MoveZeroTest, SingleElement) {
    int arr[] = {0};
    moveZero(arr, 1);
    EXPECT_EQ(vector<int>(arr, arr + 1), (vector<int>{0}));
}

TEST(MoveZeroTest, EmptyArray) {
    int arr[] = {};
    moveZero(arr, 0);
    EXPECT_TRUE(vector<int>(arr, arr + 0).empty());
}

TEST(MoveZeroTest, NegativeNumbers) {
    int arr[] = {-1, 0, -2, 0, 3};
    moveZero(arr, 5);
    EXPECT_EQ(vector<int>(arr, arr + 5), (vector<int>{-1, -2, 3, 0, 0}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int N;
            cin >> N;
            int arr[N];
            for (int i = 0; i < N; i++)
            {
                cin >> arr[i];
            }
            moveZero(arr, N);
            for (int i = 0; i < N; i++)
            {
                cout << arr[i] << " ";
            }
        }
    }
    return RUN_ALL_TESTS();
}
