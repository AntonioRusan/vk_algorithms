#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

void moveEven(int *arr, int n)
{
    int cur = 0;
    int l = 0;
    int tmp;
    while (cur <= n - 1)
    {
        if (arr[cur] % 2 == 0)
        {
            tmp = arr[l];
            arr[l] = arr[cur];
            arr[cur] = tmp;
            l++;
        }
        cur++;
    }
}

TEST(MoveEvenTest, BasicExample)
{
    int arr[] = {3, 2, 4, 1, 11, 8, 9};
    moveEven(arr, 7);
    EXPECT_EQ(vector<int>(arr, arr + 7), (vector<int>{2, 4, 8, 1, 11, 3, 9}));
}

TEST(MoveEvenTest, AllEven)
{
    int arr[] = {2, 4, 6, 8};
    moveEven(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{2, 4, 6, 8}));
}

TEST(MoveEvenTest, AllOdd)
{
    int arr[] = {1, 3, 5, 7};
    moveEven(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 3, 5, 7}));
}

TEST(MoveEvenTest, AlreadyCorrect)
{
    int arr[] = {2, 4, 1, 3};
    moveEven(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{2, 4, 1, 3}));
}

TEST(MoveEvenTest, ReverseOrder)
{
    int arr[] = {9, 8, 7, 6, 5, 4};
    moveEven(arr, 6);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{8, 6, 4, 9, 5, 7}));
}

TEST(MoveEvenTest, SingleEven)
{
    int arr[] = {1, 3, 2, 5};
    moveEven(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{2, 3, 1, 5}));
}

TEST(MoveEvenTest, EmptyArray)
{
    int arr[] = {};
    moveEven(arr, 0);
    EXPECT_TRUE(vector<int>(arr, arr + 0).empty());
}

TEST(MoveEvenTest, NegativeNumbers)
{
    int arr[] = {-3, -2, 4, -1, 0};
    moveEven(arr, 5);
    EXPECT_EQ(vector<int>(arr, arr + 5), (vector<int>{-2, 4, 0, -1, -3}));
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
            moveEven(arr, N);
            for (int i = 0; i < N; i++)
            {
                cout << arr[i] << " ";
            }
        }
    }
    return RUN_ALL_TESTS();
}
