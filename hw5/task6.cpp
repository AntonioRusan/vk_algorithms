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
    int balanceFactor;
    Node(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
        balanceFactor = 0;
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
    Node *mirrorTree(Node *node)
    {
        if (!node)
            return nullptr;
        queue<Node *> q;
        q.push(node);
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            Node *tmp = cur->left;
            cur->left = cur->right;
            cur->right = tmp;
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        return node;
    }
};

TEST(MirrorTreeTest, EmptyTree)
{
    vector<int> arr = {};
    Tree t(arr);
    t.mirrorTree(t.root);
    EXPECT_TRUE(t.toVector().empty());
}

TEST(MirrorTreeTest, SingleNode)
{
    vector<int> arr = {42};
    Tree t(arr);
    t.mirrorTree(t.root);
    EXPECT_EQ(t.toVector(), (vector<int>{42}));
}

TEST(MirrorTreeTest, SimpleSwap)
{
    vector<int> arr = {1, 2, 3};
    Tree t(arr);
    t.mirrorTree(t.root);
    EXPECT_EQ(t.toVector(), (vector<int>{1, 3, 2}));
}

TEST(MirrorTreeTest, FullBinaryTree)
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    Tree t(arr);
    t.mirrorTree(t.root);
    EXPECT_EQ(t.toVector(), (vector<int>{1, 3, 2, 7, 6, 5, 4}));
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int j = 0; j < n; ++j)
                cin >> arr[j];

            Tree t = Tree(arr);
            t.print();
            t.mirrorTree(t.root);
            t.print();
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}