#include <iostream>
#include <map>
#include <vector>
#include <queue>
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

    vector<int> dfs(Node *node, vector<int> &res)
    {
        if (node == nullptr)
        {
            return res;
        }
        dfs(node->left, res);
        res.push_back(node->val);
        dfs(node->right, res);
        return res;
    }
    bool isMirror(Node *left, Node *right) const
    {
        if (!left && !right)
            return true;
        if (!left || !right)
            return false;
        if (left->val != right->val)
            return false;

        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }
    bool isSymmetric()
    {
        if (!root)
            return true;
        return isMirror(root->left, root->right);
    }
};
TEST(SymmetricTreeTest, EmptyAndSingleNode)
{
    vector<int> input = {42};
    EXPECT_TRUE(Tree({}).isSymmetric());
    EXPECT_TRUE(Tree(input).isSymmetric());
}

TEST(SymmetricTreeTest, SimpleSymmetric)
{
    vector<int> input = {1, 2, 3};
    Tree t(input);
    EXPECT_FALSE(t.isSymmetric());
}

TEST(SymmetricTreeTest, ComplexSymmetric)
{
    vector<int> input = {1, 2, 2, 3, 4, 4, 3};
    Tree t(input);
    EXPECT_TRUE(t.isSymmetric());
}

TEST(SymmetricTreeTest, AsymmetricValues)
{
    Tree t;
    t.root = new Node(1);
    t.root->left = new Node(2);
    t.root->right = new Node(2);
    t.root->left->left = new Node(3);
    t.root->right->left = new Node(4);
    t.root->right->right = new Node(3);
    EXPECT_FALSE(t.isSymmetric());
}
TEST(SymmetricTreeTest, DifferentDepths) {
    Tree t;
    t.root = new Node(1);
    t.root->left = new Node(2);
    t.root->left->left = new Node(3);
    EXPECT_FALSE(t.isSymmetric());
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
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            Tree resultTree = Tree(arr);
            cout << resultTree.isSymmetric() << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}