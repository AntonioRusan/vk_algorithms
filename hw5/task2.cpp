#include <iostream>
#include <vector>
#include <utility>
#include <gtest/gtest.h>

using namespace std;

struct HeapElement
{
    int value;
    int arr_idx;
    int elem_idx;
};

struct MinHeap
{
    vector<HeapElement> data;

    void insert(const HeapElement &elem)
    {
        data.push_back(elem);
        int i = data.size() - 1;
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (data[i].value < data[p].value)
            {
                swap(data[i], data[p]);
                i = p;
            }
            else
                break;
        }
    }

    HeapElement pop()
    {
        HeapElement res = data[0];
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
                if (l < data.size() && data[l].value < data[smallest].value)
                    smallest = l;
                if (r < data.size() && data[r].value < data[smallest].value)
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

    const HeapElement &top()
    {
        return data[0];
    }
    bool empty()
    {
        return data.empty();
    }
    size_t size()
    {
        return data.size();
    }
};

vector<int> mergeKSortedArrays(vector<vector<int>> &arrays)
{
    vector<int> result;
    if (arrays.empty())
        return result;

    MinHeap heap;
    for (int i = 0; i < arrays.size(); ++i)
    {
        if (!arrays[i].empty())
        {
            heap.insert({arrays[i][0], i, 0});
        }
    }

    while (!heap.empty())
    {
        HeapElement cur = heap.pop();
        result.push_back(cur.value);

        int next_idx = cur.elem_idx + 1;
        if (next_idx < arrays[cur.arr_idx].size())
        {
            heap.insert({arrays[cur.arr_idx][next_idx], cur.arr_idx, next_idx});
        }
    }
    return result;
}

TEST(MergeKArraysTest, EmptyInput)
{
    vector<vector<int>> arrs = {};
    EXPECT_TRUE(mergeKSortedArrays(arrs).empty());
}

TEST(MergeKArraysTest, SingleArray)
{
    vector<vector<int>> arrs = {{1, 3, 5}};
    EXPECT_EQ(mergeKSortedArrays(arrs), (vector<int>{1, 3, 5}));
}

TEST(MergeKArraysTest, MultipleArraysSameLength)
{
    vector<vector<int>> arrs = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    EXPECT_EQ(mergeKSortedArrays(arrs), (vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(MergeKArraysTest, DifferentLengths)
{
    vector<vector<int>> arrs = {{1, 2}, {3}, {4, 5, 6, 7}};
    EXPECT_EQ(mergeKSortedArrays(arrs), (vector<int>{1, 2, 3, 4, 5, 6, 7}));
}

TEST(MergeKArraysTest, WithNegatives)
{
    vector<vector<int>> arrs = {{-5, -2, 0}, {-3, 1, 4}, {-10}};
    EXPECT_EQ(mergeKSortedArrays(arrs), (vector<int>{-10, -5, -3, -2, 0, 1, 4}));
}

TEST(MergeKArraysTest, ContainsEmptyArrays)
{
    vector<vector<int>> arrs = {{1, 3}, {}, {2, 4}, {}};
    EXPECT_EQ(mergeKSortedArrays(arrs), (vector<int>{1, 2, 3, 4}));
}

TEST(MinHeapTest, BasicOperations)
{
    MinHeap h;
    h.insert({5, 0, 0});
    h.insert({2, 1, 0});
    h.insert({8, 2, 0});
    EXPECT_EQ(h.pop().value, 2);
    EXPECT_EQ(h.pop().value, 5);
    EXPECT_EQ(h.pop().value, 8);
    EXPECT_TRUE(h.empty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--run")
        {
            int K;
            if (!(cin >> K))
                return 0;
            vector<vector<int>> arrays(K);
            for (int k = 0; k < K; ++k)
            {
                int sz;
                cin >> sz;
                arrays[k].resize(sz);
                for (int j = 0; j < sz; ++j)
                    cin >> arrays[k][j];
            }
            vector<int> merged = mergeKSortedArrays(arrays);
            for (int i = 0; i < merged.size(); i++)
                cout << merged[i] << " ";
            cout << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}