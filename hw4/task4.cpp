#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <climits>
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
    int getMinMaxMulti()
    {
        if (root == nullptr) return INT_MIN;
        Node* minNode = root;
        while (minNode->left) minNode = minNode->left;
        Node* maxNode = root;
        while (maxNode->right) maxNode = maxNode->right;
        return minNode->val*maxNode->val;
    }
};
TEST(BSTMinMaxTest, SingleNode) {
    vector<int> input = {42};
    Tree t(input);
    EXPECT_EQ(t.getMinMaxMulti(), 1764); 
}

TEST(BSTMinMaxTest, BalancedBST) {
    vector<int> input = {10, 5, 15, 2, 7, 12, 20};
    Tree t(input);
    EXPECT_EQ(t.getMinMaxMulti(), 40);
}

TEST(BSTMinMaxTest, NegativeValues) {
    vector<int> input = {0, -5, 5, -10, -2, 2, 10};
    Tree t(input);
    EXPECT_EQ(t.getMinMaxMulti(), -100);
}

TEST(BSTMinMaxTest, TwoLevelsOnly) {
    vector<int> input = {8, 4, 12, 2, 6, 10, 14};
    Tree t(input);
    EXPECT_EQ(t.getMinMaxMulti(), 28); 
}

TEST(BSTMinMaxTest, EmptyTree) {
    Tree t({});
    EXPECT_EQ(t.getMinMaxMulti(), INT_MIN);
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
            Tree a = Tree(arr);
            cout << a.getMinMaxMulti() << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}