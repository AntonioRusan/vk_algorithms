#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

int deleteDuplicates(int *arr, int N)
{
    int newN = N;
    if (N > 1)
    {
        int j = 0;
        for (int i = 1; i < N; i++)
        {
            if (arr[i] != arr[j])
            {
                j++;
                arr[j] = arr[i];
            }
        }
        newN = j + 1;
    }
    return newN;
}

TEST(DeleteDuplicatesTest, BasicDuplicates) {
    vector<int> vec = {1, 1, 2, 2, 3};
    int newLen = deleteDuplicates(vec.data(), vec.size());
    EXPECT_EQ(newLen, 3);
    EXPECT_EQ(vector<int>(vec.begin(), vec.begin() + newLen), (vector<int>{1, 2, 3}));
}

TEST(DeleteDuplicatesTest, NoDuplicates) {
    vector<int> vec = {1, 2, 3, 4, 5};
    int newLen = deleteDuplicates(vec.data(), vec.size());
    EXPECT_EQ(newLen, 5);
    EXPECT_EQ(vector<int>(vec.begin(), vec.begin() + newLen), (vector<int>{1, 2, 3, 4, 5}));
}

TEST(DeleteDuplicatesTest, AllDuplicates) {
    vector<int> vec = {1, 1, 1, 1};
    int newLen = deleteDuplicates(vec.data(), vec.size());
    EXPECT_EQ(newLen, 1);
    EXPECT_EQ(vector<int>(vec.begin(), vec.begin() + newLen), (vector<int>{1}));
}

TEST(DeleteDuplicatesTest, SingleElement) {
    vector<int> vec = {5};
    int newLen = deleteDuplicates(vec.data(), vec.size());
    EXPECT_EQ(newLen, 1);
    EXPECT_EQ(vector<int>(vec.begin(), vec.begin() + newLen), (vector<int>{5}));
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
            int M = deleteDuplicates(arr, N);
            for (int i = 0; i < M; i++)
            {
                cout << arr[i] << " ";
            }
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}