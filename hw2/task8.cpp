#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node(int x)
    {
        val = x;
        next = nullptr;
    }
};

struct LinkedList
{
    Node *head;
    Node *tail;
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    ~LinkedList()
    {
        Node *cur = head;
        while (cur != nullptr)
        {
            Node *tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void pushBack(int x)
    {
        Node *a = new Node(x);
        if (isEmpty())
        {
            head = a;
            tail = a;
        }
        else
        {
            tail->next = a;
            tail = a;
        }
    }

    void print()
    {
        Node *tmp = head;
        if (!isEmpty())
        {
            while (tmp != nullptr)
            {
                cout << tmp->val << " ";
                tmp = tmp->next;
            }
            cout << endl;
        }
    }
    vector<int> toVector()
    {
        vector<int> result;
        Node *cur = head;
        while (cur != nullptr)
        {
            result.push_back(cur->val);
            cur = cur->next;
        }
        return result;
    }

    static LinkedList fromVector(const vector<int> &vec)
    {
        LinkedList list;
        for (int x : vec)
        {
            list.pushBack(x);
        }
        return list;
    }
};

void mergeLinkedLists(LinkedList *arr, LinkedList *brr)
{
    if (arr->isEmpty())
    {
        arr->head = brr->head;
        arr->tail = brr->tail;
        brr->head = nullptr;
        brr->tail = nullptr;
        return;
    }
    if (brr->isEmpty())
    {
        return;
    }

    Node *cur1 = arr->head;
    Node *cur2 = brr->head;
    Node *first = nullptr;
    Node *last = nullptr;

    if (cur1->val < cur2->val)
        first = cur1;
    else
        first = cur2;

    while (cur1 != nullptr && cur2 != nullptr)
    {
        if (cur1->val < cur2->val)
        {
            while (cur1 != nullptr && cur1->val < cur2->val)
            {
                last = cur1;
                cur1 = cur1->next;
            }
            last->next = cur2;
        }
        else
        {
            while (cur2 != nullptr && cur2->val <= cur1->val)
            {
                last = cur2;
                cur2 = cur2->next;
            }
            last->next = cur1;
        }
    }
    arr->head = first;
    arr->tail = last->next;

    brr->head = nullptr;
    brr->tail = nullptr;
}
TEST(MergeListsTest, BasicMerge)
{
    LinkedList l1 = LinkedList::fromVector({3, 6, 8});
    LinkedList l2 = LinkedList::fromVector({4, 7, 9, 11});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{3, 4, 6, 7, 8, 9, 11}));
}

TEST(MergeListsTest, FirstEmpty)
{
    LinkedList l1 = LinkedList::fromVector({});
    LinkedList l2 = LinkedList::fromVector({1, 2, 3});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{1, 2, 3}));
}

TEST(MergeListsTest, SecondEmpty)
{
    LinkedList l1 = LinkedList::fromVector({1, 2, 3});
    LinkedList l2 = LinkedList::fromVector({});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{1, 2, 3}));
}

TEST(MergeListsTest, SingleElements)
{
    LinkedList l1 = LinkedList::fromVector({1});
    LinkedList l2 = LinkedList::fromVector({2});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{1, 2}));
}

TEST(MergeListsTest, DifferentSizes)
{
    LinkedList l1 = LinkedList::fromVector({1, 5});
    LinkedList l2 = LinkedList::fromVector({2, 3, 4, 6, 7});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{1, 2, 3, 4, 5, 6, 7}));
}

TEST(MergeListsTest, AllSecondSmaller) {
    LinkedList l1 = LinkedList::fromVector({4, 5, 6});
    LinkedList l2 = LinkedList::fromVector({1, 2, 3});
    mergeLinkedLists(&l1, &l2);
    EXPECT_EQ(l1.toVector(), (vector<int>{1, 2, 3, 4, 5, 6}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            LinkedList arr;
            LinkedList brr;
            int N, x, M;
            cin >> N;
            for (int i = 0; i < N; i++)
            {
                cin >> x;
                arr.pushBack(x);
            }
            cin >> M;
            for (int i = 0; i < M; i++)
            {
                cin >> x;
                brr.pushBack(x);
            }
            mergeLinkedLists(&arr, &brr);
            arr.print();
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}