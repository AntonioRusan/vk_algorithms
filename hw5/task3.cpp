#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <algorithm>

using namespace std;

struct MaxHeap
{
    vector<int> data;
    void insert(int val)
    {
        data.push_back(val);
        int i = data.size() - 1;
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (data[i] > data[p])
            {
                swap(data[i], data[p]);
                i = p;
            }
            else
                break;
        }
    }
    int pop()
    {
        int res = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty())
        {
            int i = 0;
            while (true)
            {
                int largest = i;
                int l = 2 * i + 1;
                int r = 2 * i + 2;
                if (l < data.size() && data[l] > data[largest])
                    largest = l;
                if (r < data.size() && data[r] > data[largest])
                    largest = r;
                if (largest != i)
                {
                    swap(data[i], data[largest]);
                    i = largest;
                }
                else
                    break;
            }
        }
        return res;
    }
    int top() const { return data[0]; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

struct MinHeap
{
    vector<int> data;
    void insert(int val)
    {
        data.push_back(val);
        int i = data.size() - 1;
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (data[i] < data[p])
            {
                swap(data[i], data[p]);
                i = p;
            }
            else
                break;
        }
    }
    int pop()
    {
        int res = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty())
        {
            int i = 0;
            while (true)
            {
                int smallest = i;
                int l = 2 * i + 1;
                int r = 2 * i + 2;
                if (l < data.size() && data[l] < data[smallest])
                    smallest = l;
                if (r < data.size() && data[r] < data[smallest])
                    smallest = r;
                if (smallest != i)
                {
                    swap(data[i], data[smallest]);
                    i = smallest;
                }
                else
                    break;
            }
        }
        return res;
    }
    int top() const { return data[0]; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

int findKMin(vector<int> &arr, int k)
{
    if (k <= 0 || k > arr.size())
        return -1;
    MaxHeap mh;
    for (int i = 0; i < arr.size(); i++)
    {
        if (mh.size() < k)
        {
            mh.insert(arr[i]);
        }
        else if (arr[i] < mh.top())
        {
            mh.pop();
            mh.insert(arr[i]);
        }
    }
    return mh.top();
}

int findKMax(vector<int> &arr, int k)
{
    if (k <= 0 || k > arr.size())
        return -1;
    MinHeap minh;
    for (int i = 0; i < arr.size(); i++)
    {
        if (minh.size() < k)
        {
            minh.insert(arr[i]);
        }
        else if (arr[i] > minh.top())
        {
            minh.pop();
            minh.insert(arr[i]);
        }
    }
    return minh.top();
}

TEST(KthElementTest, KthSmallestBasic)
{
    vector<int> arr = {7, 10, 4, 3, 20, 15};
    EXPECT_EQ(findKMin(arr, 3), 7);
}

TEST(KthElementTest, KthSmallestAllSame)
{
    vector<int> arr = {5, 5, 5, 5};
    EXPECT_EQ(findKMin(arr, 2), 5);
}

TEST(KthElementTest, KthSmallestKis1)
{
    vector<int> arr = {9, 1, 4, 2};
    EXPECT_EQ(findKMin(arr, 1), 1);
}

TEST(KthElementTest, KthSmallestKisN)
{
    vector<int> arr = {3, 1, 2};
    EXPECT_EQ(findKMin(arr, 3), 3);
}

TEST(KthElementTest, KthLargestBasic)
{
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    EXPECT_EQ(findKMax(arr, 2), 5);
}

TEST(KthElementTest, KthLargestNegatives)
{
    vector<int> arr = {-10, -5, -1, -8};
    EXPECT_EQ(findKMax(arr, 2), -5);
}

TEST(KthElementTest, InvalidK)
{
    vector<int> arr = {1, 2, 3};
    EXPECT_EQ(findKMin(arr, 0), -1);
    EXPECT_EQ(findKMax(arr, 5), -1);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--run")
        {
            int n, k, type;
            if (!(cin >> n >> k >> type))
                return 0;

            vector<int> arr(n);
            for (int j = 0; j < n; ++j)
                cin >> arr[j];

            if (type == 1)
            {
                cout << findKMin(arr, k) << endl;
            }
            else
            {
                cout << findKMax(arr, k) << endl;
            }
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}