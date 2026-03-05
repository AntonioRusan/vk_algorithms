#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

bool findPair(int *arr, int N, int target)
{
    int i = 0, j = N - 1;
    bool result = false;
    while (i < j)
    {
        if (arr[i] + arr[j] < target)
        {
            i++;
        }
        else if (arr[i] + arr[j] > target)
        {
            j--;
        }
        else
        {
            cout << arr[i] << " " << arr[j] << endl;
            result = true;
            i++;
            j--;
        }
    }
    return result;
}

TEST(FindPairTest, BasicPair) {
    vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(findPair(vec.data(), vec.size(), 7));
}

TEST(FindPairTest, NoPair) {
    vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_FALSE(findPair(vec.data(), vec.size(), 20));
}

TEST(FindPairTest, PairInMiddle) {
    vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_TRUE(findPair(vec.data(), vec.size(), 5));
}

TEST(FindPairTest, EmptyArray) {
    vector<int> vec = {};
    EXPECT_FALSE(findPair(vec.data(), vec.size(), 0));
}

TEST(FindPairTest, WithNegativeNumbers) {
    vector<int> vec = {-5, -2, 0, 3, 7};
    EXPECT_TRUE(findPair(vec.data(), vec.size(), 2));
}

TEST(FindPairTest, AllSame) {
    vector<int> vec = {5, 5, 5, 5};
    EXPECT_TRUE(findPair(vec.data(), vec.size(), 10));
}

TEST(FindPairTest, MultiplePairs) {
    vector<int> vec = {1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(findPair(vec.data(), vec.size(), 7));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int N, target;
            cin >> N >> target;
            int arr[N];
            for (int i = 0; i < N; i++)
            {
                cin >> arr[i];
            }
            cout << findPair(arr, N, target) << endl;
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}