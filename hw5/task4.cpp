#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <gtest/gtest.h>
using namespace std;
struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};
struct Tree
{
    Node *root;
    Tree()
    {
        root = nullptr;
    }
    Tree(vector<int> &arr)
    {
        root = buildTree(arr, 0);
    }
    Node *buildTree(vector<int> &arr, int ind)
    {
        if (ind >= arr.size())
            return nullptr;

        Node *node = new Node(arr[ind]);
        node->left = buildTree(arr, 2 * ind + 1);
        node->right = buildTree(arr, 2 * ind + 2);
        return node;
    }
    vector<int> toVector() const
    {
        vector<int> res;
        if (root == nullptr)
            return res;

        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            if (cur != nullptr)
            {
                res.push_back(cur->val);
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return res;
    }

    ~Tree()
    {
        clear(root);
    }

    void clear(Node *node)
    {
        if (node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void print() const
    {
        if (root == nullptr)
        {
            return;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            cout << cur->val << " ";
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        cout << endl;
    }
    void insert(int val)
    {
        if (!root)
        {
            root = new Node(val);
            return;
        }
        Node *cur = root;
        while (true)
        {
            if (val < cur->val)
            {
                if (!cur->left)
                {
                    cur->left = new Node(val);
                    break;
                }
                cur = cur->left;
            }
            else
            {
                if (!cur->right)
                {
                    cur->right = new Node(val);
                    break;
                }
                cur = cur->right;
            }
        }
    }
    static Tree fromArrayAsBST(vector<int> &arr)
    {
        Tree t;
        for (int i = 0; i < arr.size(); i++)
            t.insert(arr[i]);
        return t;
    }

    int kMin(int k)
    {
        if (!root || k <= 0) return INT_MIN;
        int cnt = 0;
        stack<Node *> st;
        Node *cur = root;
        while (!st.empty() || cur)
        {
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            cnt++;
            if (cnt == k)
                return cur->val;
            cur = cur->right;
        }
        return INT_MIN;
    }
    int kMax(int k)
    {
        if (!root || k <= 0) return INT_MIN;
        int cnt = 0;
        stack<Node *> st;
        Node *cur = root;
        while (!st.empty() || cur)
        {
            while (cur)
            {
                st.push(cur);
                cur = cur->right;
            }
            cur = st.top();
            st.pop();
            cnt++;
            if (cnt == k)
                return cur->val;
            cur = cur->left;
        }
        return INT_MIN;
    }
};

TEST(BSTKthTest, KthSmallest_Basic)
{
    vector<int> arr = {5, 3, 7, 2, 4, 6, 8};
    Tree t = Tree::fromArrayAsBST(arr);
    EXPECT_EQ(t.kMin(1), 2);
    EXPECT_EQ(t.kMin(3), 4);
    EXPECT_EQ(t.kMin(7), 8);
}

TEST(BSTKthTest, KthLargest_Basic)
{
    vector<int> arr = {5, 3, 7, 2, 4, 6, 8};
    Tree t = Tree::fromArrayAsBST(arr);
    EXPECT_EQ(t.kMax(1), 8);
    EXPECT_EQ(t.kMax(3), 6);
    EXPECT_EQ(t.kMax(7), 2);
}

TEST(BSTKthTest, SingleNode)
{
    vector<int> arr = {10};
    Tree t = Tree::fromArrayAsBST(arr);
    EXPECT_EQ(t.kMin(1), 10);
    EXPECT_EQ(t.kMax(1), 10);
}

TEST(BSTKthTest, SkewedLeft)
{
    vector<int> arr = {5, 4, 3, 2, 1};
    Tree t = Tree::fromArrayAsBST(arr);
    EXPECT_EQ(t.kMin(3), 3);
    EXPECT_EQ(t.kMax(2), 4);
}

TEST(BSTKthTest, InvalidK)
{
    vector<int> arr = {10, 20, 30};
    Tree t = Tree::fromArrayAsBST(arr);
    EXPECT_EQ(t.kMin(0), INT_MIN);
    EXPECT_EQ(t.kMax(5), INT_MIN);
    EXPECT_EQ(t.kMin(100), INT_MIN);
}

TEST(BSTKthTest, EmptyTree)
{
    Tree t;
    EXPECT_EQ(t.kMin(1), INT_MIN);
    EXPECT_EQ(t.kMax(1), INT_MIN);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int n, k, type;
            cin >> n >> k >> type;

            vector<int> arr(n);
            for (int j = 0; j < n; ++j)
                cin >> arr[j];

            Tree t = Tree::fromArrayAsBST(arr);
            if (type == 1)
                cout << t.kMin(k) << endl;
            else
                cout << t.kMax(k) << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}