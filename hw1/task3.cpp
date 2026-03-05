#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

void mergeArray(int *arr, int n, int *brr, int m)
{
    int i = n - m - 1;
    int k = n - 1;
    int j = m - 1;
    while (j >= 0)
    {
        if (i >= 0 && brr[j] < arr[i])
        {
            arr[k] = arr[i];
            i--;
        }
        else
        {
            arr[k] = brr[j];
            j--;
        }
        k--;
    }
}

TEST(MergeInPlaceTest, BasicMerge)
{
    int arr[7] = {1, 3, 5, 0, 0, 0, 0};
    int brr[] = {2, 4, 6, 8};
    mergeArray(arr, 7, brr, 4);
    EXPECT_EQ(vector<int>(arr, arr + 7), (vector<int>{1, 2, 3, 4, 5, 6, 8}));
}

TEST(MergeInPlaceTest, SecondArrayEmpty)
{
    int arr[3] = {1, 2, 3};
    int brr[] = {};
    mergeArray(arr, 3, brr, 0);
    EXPECT_EQ(vector<int>(arr, arr + 3), (vector<int>{1, 2, 3}));
}

TEST(MergeInPlaceTest, FirstArrayEmpty)
{
    int arr[3] = {0, 0, 0};
    int brr[] = {1, 2, 3};
    mergeArray(arr, 3, brr, 3);
    EXPECT_EQ(vector<int>(arr, arr + 3), (vector<int>{1, 2, 3}));
}

TEST(MergeInPlaceTest, DuplicateElements)
{
    int arr[6] = {1, 3, 3, 0, 0, 0};
    int brr[] = {3, 4, 5};
    mergeArray(arr, 6, brr, 3);
    EXPECT_EQ(vector<int>(arr, arr + 6), (vector<int>{1, 3, 3, 3, 4, 5}));
}

TEST(MergeInPlaceTest, AllElementsFromSecond)
{
    int arr[4] = {5, 6, 0, 0};
    int brr[] = {1, 2};
    mergeArray(arr, 4, brr, 2);
    EXPECT_EQ(vector<int>(arr, arr + 4), (vector<int>{1, 2, 5, 6}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int N, M;
            cin >> N >> M;
            int arr[N], brr[M];
            for (int i = 0; i < N; i++)
            {
                cin >> arr[i];
                for (int i = 0; i < M; i++)
                {
                    cin >> brr[i];
                }
                mergeArray(arr, N, brr, M);
                for (int i = 0; i < N; i++)
                {
                    cout << arr[i] << " ";
                }
            }
        }
    }
    return RUN_ALL_TESTS();
}