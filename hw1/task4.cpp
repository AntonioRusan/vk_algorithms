#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

void sortBinArray(int *arr, int n)
{
    int i = 0;
    int j = n - 1;
    int tmp;
    while (i < j)
    {
        if (arr[i] == 1)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            j--;
        }
        else
        {
            i++;
        }
    }
}

TEST(SortBinArrayTest, BasicSort)
{
    int arr[] = {1, 0, 1, 0, 1};
    sortBinArray(arr, 5);
    EXPECT_EQ(vector<int>(arr, arr + 5), (vector<int>{0, 0, 1, 1, 1}));
}

TEST(SortBinArrayTest, AllZeros)
{
    int arr[] = {0, 0, 0, 0};
    sortBinArray(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{0, 0, 0, 0}));
}

TEST(SortBinArrayTest, AllOnes)
{
    int arr[] = {1, 1, 1, 1};
    sortBinArray(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 1, 1, 1}));
}

TEST(SortBinArrayTest, SingleElement)
{
    int arr[] = {1};
    sortBinArray(arr, 1);
    EXPECT_EQ(vector<int>(arr, arr + 1), (vector<int>{1}));
}

TEST(SortBinArrayTest, AlreadySorted)
{
    int arr[] = {0, 0, 1, 1};
    sortBinArray(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{0, 0, 1, 1}));
}

TEST(SortBinArrayTest, ReverseSorted)
{
    int arr[] = {1, 1, 0, 0};
    sortBinArray(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{0, 0, 1, 1}));
}

TEST(SortBinArrayTest, EmptyArray)
{
    int arr[] = {};
    sortBinArray(arr, 0);
    EXPECT_TRUE(vector<int>(arr, arr + 0).empty());
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
                sortBinArray(arr, N);
                for (int i = 0; i < N; i++)
                {
                    cout << arr[i] << " ";
                }
            }
        }
    }
    return RUN_ALL_TESTS();
}