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
    bool isComplete()
    {
        if (root == nullptr)
            return true;
        queue<Node *> q;
        q.push(root);
        bool seenNull = false;
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            if (cur == nullptr)
            {
                seenNull = true;
            }
            else
            {
                if (seenNull)
                    return false;
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return true;
    }
};

TEST(CompleteTreeTest, EmptyAndSingle)
{
    vector<int> input = {42};
    EXPECT_TRUE(Tree({}).isComplete());
    EXPECT_TRUE(Tree(input).isComplete());
}

TEST(CompleteTreeTest, CompleteButNotPerfect)
{
    vector<int> input = {1, 2, 3, 4, 5};
    Tree t(input);
    EXPECT_TRUE(t.isComplete());
}

TEST(CompleteTreeTest, NotComplete)
{
    Tree t;
    t.root = new Node(1);
    t.root->right = new Node(3);
    EXPECT_FALSE(t.isComplete());
}

TEST(CompleteTreeTest, NotCompleteGap)
{
    Tree t;
    t.root = new Node(1);
    t.root->left = new Node(2);
    t.root->right = new Node(3);
    t.root->left->right = new Node(5);
    t.root->right->left = new Node(6);
    t.root->right->right = new Node(7);
    EXPECT_FALSE(t.isComplete());
}

TEST(CompleteTreeTest, LeftSkewedTree)
{
    Tree t;
    t.root = new Node(1);
    t.root->left = new Node(2);
    t.root->left->left = new Node(3);
    t.root->left->left->left = new Node(4);
    EXPECT_FALSE(t.isComplete());
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
            cout << resultTree.isComplete() << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}