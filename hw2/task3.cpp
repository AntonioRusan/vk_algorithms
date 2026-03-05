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

    static LinkedList fromVector(const vector<int>& vec) {
        LinkedList list;
        for (int x : vec) {
            list.pushBack(x);
        }
        return list;
    }

    void deleteElem(int val)
    {
        Node *first = new Node(val);
        first->next = head;
        Node *prev = first;
        Node *cur = head;
        if (!isEmpty())
        {
            while (cur != nullptr)
            {
                if (cur->val == val)
                {
                    prev->next = cur->next;
                }
                else
                {
                    prev = cur;
                }
                cur = cur->next;
            }
        }
        head = first->next;
    }
};

TEST(DeleteElemTest, DeleteFromMiddle) {
    LinkedList l = LinkedList::fromVector({1, 2, 3, 4, 5});
    l.deleteElem(3);
    EXPECT_EQ(l.toVector(), (vector<int>{1, 2, 4, 5}));
}

TEST(DeleteElemTest, DeleteHead) {
    LinkedList l = LinkedList::fromVector({1, 2, 3});
    l.deleteElem(1);
    EXPECT_EQ(l.toVector(), (vector<int>{2, 3}));
}

TEST(DeleteElemTest, DeleteTail) {
    LinkedList l = LinkedList::fromVector({1, 2, 3});
    l.deleteElem(3);
    EXPECT_EQ(l.toVector(), (vector<int>{1, 2}));
}

TEST(DeleteElemTest, DeleteAllOccurrences) {
    LinkedList l = LinkedList::fromVector({1, 2, 2, 3, 2});
    l.deleteElem(2);
    EXPECT_EQ(l.toVector(), (vector<int>{1, 3}));
}

TEST(DeleteElemTest, DeleteNonExistent) {
    LinkedList l = LinkedList::fromVector({1, 2, 3});
    l.deleteElem(5);
    EXPECT_EQ(l.toVector(), (vector<int>{1, 2, 3}));
}

TEST(DeleteElemTest, DeleteSingleElement) {
    LinkedList l = LinkedList::fromVector({1});
    l.deleteElem(1);
    EXPECT_TRUE(l.isEmpty());
}

TEST(DeleteElemTest, DeleteFromEmptyList) {
    LinkedList l = LinkedList::fromVector({});
    l.deleteElem(1);
    EXPECT_TRUE(l.isEmpty());
}

TEST(DeleteElemTest, DeleteAllElements) {
    LinkedList l = LinkedList::fromVector({5, 5, 5});
    l.deleteElem(5);
    EXPECT_TRUE(l.isEmpty());
}

TEST(DeleteElemTest, WithNegativeNumbers) {
    LinkedList l = LinkedList::fromVector({-1, 0, -1, 1});
    l.deleteElem(-1);
    EXPECT_EQ(l.toVector(), (vector<int>{0, 1}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            LinkedList l;
            int N, val, x;
            cin >> N >> val;
            for (int i = 0; i < N; i++)
            {
                cin >> x;
                l.pushBack(x);
            }
            l.deleteElem(val);
            l.print();
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}