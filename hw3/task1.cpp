#include <iostream>
#include <gtest/gtest.h>

using namespace std;
int findSquareRoot(int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    int l = 1;
    int r = n / 2 + 1;
    int m;
    long long mSquare;
    while (l <= r)
    {
        m = (l + r) / 2;
        mSquare = m * m;
        if (mSquare > n)
        {
            r = m - 1;
        }
        else if (mSquare < n)
        {
            l = m + 1;
        }
        else
        {
            return m;
        }
    }
    return r;
}
TEST(FindSquareRootTest, PerfectSquare_One)
{
    EXPECT_EQ(findSquareRoot(1), 1);
}

TEST(FindSquareRootTest, PerfectSquare_Four)
{
    EXPECT_EQ(findSquareRoot(4), 2);
}
TEST(FindSquareRootTest, PerfectSquare_Sixteen)
{
    EXPECT_EQ(findSquareRoot(16), 4);
}
TEST(FindSquareRootTest, PerfectSquare_TwentyFive)
{
    EXPECT_EQ(findSquareRoot(25), 5);
}
TEST(FindSquareRootTest, PerfectSquare_Hundred)
{
    EXPECT_EQ(findSquareRoot(100), 10);
}
TEST(FindSquareRootTest, NonPerfectSquare_Two)
{
    EXPECT_EQ(findSquareRoot(2), 1);
}
TEST(FindSquareRootTest, EdgeCase_Zero)
{
    EXPECT_EQ(findSquareRoot(0), 0);
}
TEST(FindSquareRootTest, NonPerfectSquare_Ten)
{
    EXPECT_EQ(findSquareRoot(10), 3);
}
TEST(FindSquareRootTest, NonPerfectSquare_Fifteen)
{
    EXPECT_EQ(findSquareRoot(15), 3);
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
            cout << findSquareRoot(n) << endl;
        }
    }
    return RUN_ALL_TESTS();
}