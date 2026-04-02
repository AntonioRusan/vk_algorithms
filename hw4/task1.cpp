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
};
TEST(TreeRestoreTest, EmptyArray)
{
    Tree t({});
    EXPECT_TRUE(t.root == nullptr);
    EXPECT_TRUE(t.toVector().empty());
}

TEST(TreeRestoreTest, SingleElement)
{
    vector<int> input = {42};
    Tree t(input);
    ASSERT_NE(t.root, nullptr);
    EXPECT_EQ(t.root->val, 42);
    EXPECT_EQ(t.root->left, nullptr);
    EXPECT_EQ(t.root->right, nullptr);
    EXPECT_EQ(t.toVector(), input);
}

TEST(TreeRestoreTest, ThreeElementsComplete)
{
    vector<int> input = {1, 2, 3};
    Tree t(input);
    ASSERT_NE(t.root, nullptr);
    EXPECT_EQ(t.root->val, 1);
    ASSERT_NE(t.root->left, nullptr);
    EXPECT_EQ(t.root->left->val, 2);
    ASSERT_NE(t.root->right, nullptr);
    EXPECT_EQ(t.root->right->val, 3);
    EXPECT_EQ(t.toVector(), input);
}

TEST(TreeRestoreTest, LargeArray)
{
    vector<int> input = {10, 20, 30, 40, 50, 60, 70};
    Tree t(input);
    EXPECT_EQ(t.toVector(), input);

    EXPECT_EQ(t.root->left->left->val, 40);
    EXPECT_EQ(t.root->left->right->val, 50);
    EXPECT_EQ(t.root->right->left->val, 60);
    EXPECT_EQ(t.root->right->right->val, 70);
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
            resultTree.print();
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}