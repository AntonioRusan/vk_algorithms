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
    static Tree fromArrayAsBST(vector<int> &arr)
    {
        Tree t;
        for (int i = 0; i < arr.size(); i++)
            t.insert(arr[i]);
        return t;
    }

    int getBalanceFactor(Node *node)
    {
        if (!node)
            return 0;
        int leftHeight = getBalanceFactor(node->left);
        int rightHeight = getBalanceFactor(node->right);
        node->balanceFactor = leftHeight - rightHeight;
        return 1 + max(leftHeight, rightHeight);
    }

    void fillBalanceFactor()
    {
        getBalanceFactor(root);
    }

    int getBF(int val)
    {
        Node *cur = root;
        while (cur)
        {
            if (val == cur->val)
                return cur->balanceFactor;
            cur = (val < cur->val) ? cur->left : cur->right;
        }
        return INT_MIN;
    }
};

TEST(BalanceFactorTest, EmptyTree)
{
    Tree t;
    t.fillBalanceFactor();
    EXPECT_EQ(t.root, nullptr);
}

TEST(BalanceFactorTest, SingleNode)
{
    vector<int> arr = {10};
    Tree t = Tree::fromArrayAsBST(arr);
    t.fillBalanceFactor();
    EXPECT_EQ(t.getBF(10), 0);
}

TEST(BalanceFactorTest, PerfectlyBalanced)
{
    vector<int> arr = {2, 1, 3};
    Tree t = Tree::fromArrayAsBST(arr);
    t.fillBalanceFactor();
    EXPECT_EQ(t.getBF(2), 0);
    EXPECT_EQ(t.getBF(1), 0);
    EXPECT_EQ(t.getBF(3), 0);
}

TEST(BalanceFactorTest, LeftSkewed)
{
    vector<int> arr = {3, 2, 1};
    Tree t = Tree::fromArrayAsBST(arr);
    t.fillBalanceFactor();
    EXPECT_EQ(t.getBF(3), 2);
    EXPECT_EQ(t.getBF(2), 1);
    EXPECT_EQ(t.getBF(1), 0);
}

TEST(BalanceFactorTest, RightHeavy)
{
    vector<int> arr = {5, 8, 6, 9};
    Tree t = Tree::fromArrayAsBST(arr);
    t.fillBalanceFactor();
    EXPECT_EQ(t.getBF(5), -2);
    EXPECT_EQ(t.getBF(8), 0);
    EXPECT_EQ(t.getBF(6), 0);
    EXPECT_EQ(t.getBF(9), 0);
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

            Tree t = Tree::fromArrayAsBST(arr);
            t.fillBalanceFactor();
            queue<Node *> q;
            q.push(t.root);
            while (!q.empty())
            {
                Node *cur = q.front();
                q.pop();
                cout << "Node: " << cur->val << " BalanceFactor: " << cur->balanceFactor << endl;
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}