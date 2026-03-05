#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

void sortNetherlands(int *arr, int n)
{
    int l = 0;
    int r = n - 1;
    int cur = 0;
    int tmp;
    while (cur <= r)
    {
        if (arr[cur] == 2)
        {
            tmp = arr[cur];
            arr[cur] = arr[r];
            arr[r] = tmp;

            r--;
        }
        else if (arr[cur] == 0)
        {
            tmp = arr[cur];
            arr[cur] = arr[l];
            arr[l] = tmp;

            cur++;
            l++;
        }
        else
        {
            cur++;
        }
    }
}

TEST(SortNetherlandsTest, BasicSort)
{
    int arr[] = {2, 0, 1, 2, 0, 1};
    sortNetherlands(arr, 6);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{0, 0, 1, 1, 2, 2}));
}

TEST(SortNetherlandsTest, AllZeros)
{
    int arr[] = {0, 0, 0, 0};
    sortNetherlands(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{0, 0, 0, 0}));
}

TEST(SortNetherlandsTest, AllOnes)
{
    int arr[] = {1, 1, 1, 1};
    sortNetherlands(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 1, 1, 1}));
}

TEST(SortNetherlandsTest, AllTwos)
{
    int arr[] = {2, 2, 2, 2};
    sortNetherlands(arr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{2, 2, 2, 2}));
}

TEST(SortNetherlandsTest, AlreadySorted)
{
    int arr[] = {0, 0, 1, 1, 2, 2};
    sortNetherlands(arr, 6);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{0, 0, 1, 1, 2, 2}));
}

TEST(SortNetherlandsTest, ReverseSorted)
{
    int arr[] = {2, 2, 1, 1, 0, 0};
    sortNetherlands(arr, 6);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{0, 0, 1, 1, 2, 2}));
}

TEST(SortNetherlandsTest, SingleElement)
{
    int arr[] = {1};
    sortNetherlands(arr, 1);
    EXPECT_EQ(vector<int>(arr, arr + 1), (vector<int>{1}));
}

TEST(SortNetherlandsTest, EmptyArray)
{
    int arr[] = {};
    sortNetherlands(arr, 0);
    EXPECT_TRUE(vector<int>(arr, arr + 0).empty());
}

TEST(SortNetherlandsTest, MixedWithDuplicates)
{
    int arr[] = {1, 2, 0, 1, 2, 0, 1, 2};
    sortNetherlands(arr, 8);
    EXPECT_EQ(vector<int>(arr, arr + 8), (vector<int>{0, 0, 1, 1, 1, 2, 2, 2}));
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
            sortNetherlands(arr, N);
            for (int i = 0; i < N; i++)
            {
                cout << arr[i] << " ";
            }
        }
    }
    return RUN_ALL_TESTS();
}