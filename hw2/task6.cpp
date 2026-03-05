#include <iostream>
#include <cstring>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

bool isPalindrom(char *arr)
{
    int N = strlen(arr);
    int i = 0, j = N - 1;
    bool result = true;
    while (i < j)
    {
        if (arr[i] == arr[j])
        {
            i++;
            j--;
        }
        else
        {
            result = false;
            break;
        }
    }
    return result;
}

TEST(IsPalindromeTest, NotPalindrome) {
    EXPECT_FALSE(isPalindrom(const_cast<char*>("hell")));
}

TEST(IsPalindromeTest, Single) {
    EXPECT_TRUE(isPalindrom(const_cast<char*>("a")));
}

TEST(IsPalindromeTest, EmptyString) {
    EXPECT_TRUE(isPalindrom(const_cast<char*>("")));
}

TEST(IsPalindromeTest, EvenLengthPalindrome) {
    EXPECT_TRUE(isPalindrom(const_cast<char*>("abba")));
}

TEST(IsPalindromeTest, OddLengthPalindrome) {
    EXPECT_TRUE(isPalindrom(const_cast<char*>("abcba")));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--run")
        {
            char arr[256];
            cin >> arr;
            cout << isPalindrom(arr) << endl;
            return 0;
        }
    }

    return RUN_ALL_TESTS();
}