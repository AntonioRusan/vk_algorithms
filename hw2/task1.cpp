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

    void reverse()
    {
        Node *prev = nullptr;
        Node *cur = head;
        Node *tmp;
        while (cur != nullptr)
        {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        tail = head;
        head = prev;
    }
};

TEST(ReverseListTest, EmptyList) {
    LinkedList l = LinkedList::fromVector({});
    l.reverse();
    EXPECT_TRUE(l.isEmpty());
}

TEST(ReverseListTest, SingleElement) {
    LinkedList l = LinkedList::fromVector({1});
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{1}));
}

TEST(ReverseListTest, TwoElements) {
    LinkedList l = LinkedList::fromVector({1, 2});
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{2, 1}));
}

TEST(ReverseListTest, MultipleElements) {
    LinkedList l = LinkedList::fromVector({1, 2, 3, 4, 5});
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{5, 4, 3, 2, 1}));
}

TEST(ReverseListTest, DoubleReverse) {
    LinkedList l = LinkedList::fromVector({1, 2, 3});
    l.reverse();
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{1, 2, 3}));
}

TEST(ReverseListTest, WithDuplicates) {
    LinkedList l = LinkedList::fromVector({1, 2, 2, 1});
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{1, 2, 2, 1}));
}

TEST(ReverseListTest, WithNegativeNumbers) {
    LinkedList l = LinkedList::fromVector({-1, 0, 1});
    l.reverse();
    EXPECT_EQ(l.toVector(), (vector<int>{1, 0, -1}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            LinkedList l;
            int N, x;
            cin >> N;
            for (int i = 0; i < N; i++)
            {
                cin >> x;
                l.pushBack(x);
            }
            l.reverse();
            l.print();
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}