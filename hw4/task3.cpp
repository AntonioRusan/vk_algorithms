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

    int getMinDepth()
    {
        if (root == nullptr)
            return 0;
        queue<pair<Node *, int>> q;
        q.push({root, 1});
        while (!q.empty())
        {
            Node *cur = q.front().first;
            int depth = q.front().second;
            q.pop();
            if (cur->left == nullptr && cur->right == nullptr)
                return depth;
            if (cur->left)
                q.push({cur->left, depth + 1});
            if (cur->right)
                q.push({cur->right, depth + 1});
        }
        return 0;
    }
};
TEST(MinDepthTest, EmptyTree)
{
    EXPECT_EQ(Tree({}).getMinDepth(), 0);
}

TEST(MinDepthTest, SingleNode)
{
    vector<int> input = {42};
    EXPECT_EQ(Tree(input).getMinDepth(), 1);
}

TEST(MinDepthTest, BalancedTree)
{
    vector<int> input = {1, 2, 3};
    Tree t(input);
    EXPECT_EQ(t.getMinDepth(), 2);
}

TEST(MinDepthTest, SkewedLeft)
{
    vector<int> input = {1, 2, 3, 4, 5};
    Tree t(input);
    EXPECT_EQ(t.getMinDepth(), 2);
}

TEST(MinDepthTest, EarlyLeafOnRight)
{
    vector<int> input = {1, 2, 3, 4, 5, 6, 7};
    Tree t(input);
    EXPECT_EQ(t.getMinDepth(), 3);
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
            cout << resultTree.getMinDepth() << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}