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
bool nodeEqual(Node *a, Node *b)
{
    if (a == nullptr && b == nullptr)
        return true;
    if (a == nullptr || b == nullptr)
        return false;
    if (a->val != b->val)
        return false;
    return nodeEqual(a->left, b->left) && nodeEqual(a->right, b->right);
}
bool treeEqual(Tree &a, Tree &b)
{
    return nodeEqual(a.root, b.root);
}
TEST(TreeIdentityTest, BothEmpty)
{
    Tree t1({}), t2({});
    EXPECT_TRUE(treeEqual(t1, t2));
}

TEST(TreeIdentityTest, IdenticalStructureAndValues)
{
    vector<int> input1 = {1, 2, 3, 4, 5};
    vector<int> input2 = {1, 2, 3, 4, 5};
    Tree t1(input1);
    Tree t2(input2);
    EXPECT_TRUE(treeEqual(t1, t2));
}

TEST(TreeIdentityTest, DifferentValues)
{
    vector<int> input1 = {1, 2, 3};
    vector<int> input2 = {1, 5, 3};
    Tree t1(input1);
    Tree t2(input2);
    EXPECT_FALSE(treeEqual(t1, t2));
}

TEST(TreeIdentityTest, DifferentStructure)
{
    vector<int> input1 = {1, 2, 3};
    vector<int> input2 = {1, 2};
    Tree t1(input1);
    Tree t2(input2);
    EXPECT_FALSE(treeEqual(t1, t2));
}

TEST(TreeIdentityTest, OneEmptyOneNot)
{
    vector<int> input1 = {1, 2, 3};
    vector<int> input2 = {};
    Tree t1(input1);
    Tree t2(input2);
    EXPECT_FALSE(treeEqual(t1, t2));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            int n, m;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cin >> m;
            vector<int> brr(m);
            for (int i = 0; i < m; i++)
            {
                cin >> brr[i];
            }
            Tree a = Tree(arr);
            Tree b = Tree(brr);
            cout << treeEqual(a, b) << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}