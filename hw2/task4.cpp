#include <iostream>
#include <cstring>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

bool iSubSeq(char *arr, char *brr)
{
    int i = 0, j = 0;
    int n = strlen(arr);
    int m = strlen(brr);
    while (i < n && j < m)
    {
        if (arr[i] == brr[j])
        {
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }
    return i == strlen(arr);
}

TEST(IsSubsequenceTest, BasicSubsequence) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>("abc"), const_cast<char*>("ahbgdc")));
}

TEST(IsSubsequenceTest, NotSubsequence) {
    EXPECT_FALSE(iSubSeq(const_cast<char*>("axc"), const_cast<char*>("ahbgdc")));
}

TEST(IsSubsequenceTest, IdenticalStrings) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>("abc"), const_cast<char*>("abc")));
}

TEST(IsSubsequenceTest, EmptySource) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>(""), const_cast<char*>("abc")));
}

TEST(IsSubsequenceTest, EmptyTarget) {
    EXPECT_FALSE(iSubSeq(const_cast<char*>("a"), const_cast<char*>("")));
}

TEST(IsSubsequenceTest, AllCharsAtEnd) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>("abc"), const_cast<char*>("xxxyyyabc")));
}

TEST(IsSubsequenceTest, AllCharsAtBeginning) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>("abc"), const_cast<char*>("abcxxxyyy")));
}

TEST(IsSubsequenceTest, AllCharsInMiddle) {
    EXPECT_TRUE(iSubSeq(const_cast<char*>("abc"), const_cast<char*>("xxxabcyyy")));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            char arr[256];
            char brr[256];
            cin >> arr;
            cin >> brr;
            cout << iSubSeq(arr, brr) << endl;
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}