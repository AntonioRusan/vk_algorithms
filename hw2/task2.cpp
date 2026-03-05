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

    int findMid()
    {
        if (isEmpty())
        {
            return -1;
        }
        Node *slow = head;
        Node *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow->val;
    }
};

TEST(FindMidTest, SingleElement) {
    LinkedList l = LinkedList::fromVector({1});
    EXPECT_EQ(l.findMid(), 1);
}

TEST(FindMidTest, TwoElements) {
    LinkedList l = LinkedList::fromVector({1, 2});
    EXPECT_EQ(l.findMid(), 2);
}

TEST(FindMidTest, ThreeElements) {
    LinkedList l = LinkedList::fromVector({1, 2, 3});
    EXPECT_EQ(l.findMid(), 2);
}

TEST(FindMidTest, FiveElements) {
    LinkedList l = LinkedList::fromVector({1, 2, 3, 4, 5});
    EXPECT_EQ(l.findMid(), 3);
}

TEST(FindMidTest, SixElements) {
    LinkedList l = LinkedList::fromVector({1, 2, 3, 4, 5, 6});
    EXPECT_EQ(l.findMid(), 4);
}

TEST(FindMidTest, EmptyList) {
    LinkedList l = LinkedList::fromVector({});
    EXPECT_EQ(l.findMid(), -1);
}

TEST(FindMidTest, WithDuplicates) {
    LinkedList l = LinkedList::fromVector({5, 5, 5});
    EXPECT_EQ(l.findMid(), 5);
}

TEST(FindMidTest, WithNegativeNumbers) {
    LinkedList l = LinkedList::fromVector({-1, 0, 1});
    EXPECT_EQ(l.findMid(), 0);
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
            int mid = l.findMid();
            cout << mid << endl;
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}