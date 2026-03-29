#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;
int minTime(int x, int y, int n) {
    if (n == 0) return 0;
    if (n == 1) {
        return min(x, y);
    }
    int l = min(x, y);
    int r = max(x, y) * (n - 1);
    while(l < r) {
        int m = (l + r) / 2;
        int copies = m / x + m / y;
        if (copies >= n - 1) {
            r = m;
        }
        else {
            l = m + 1;
        }
    }
    return r + min(x, y);
}

TEST(MinTimeTest, SingleCopy) {
    EXPECT_EQ(minTime(1, 2, 1), 1);
    EXPECT_EQ(minTime(5, 3, 1), 3);
    EXPECT_EQ(minTime(10, 10, 1), 10);
}

TEST(MinTimeTest, TwoCopies_DifferentSpeed) {
    EXPECT_EQ(minTime(2, 3, 2), 4);
}

TEST(MinTimeTest, ThreeCopies) {
    EXPECT_EQ(minTime(1, 2, 3), 3);
}

TEST(MinTimeTest, Example_Classic) {
    EXPECT_EQ(minTime(1, 2, 5), 4);
}

TEST(MinTimeTest, ZeroCopies) {
    EXPECT_EQ(minTime(1, 2, 0), 0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            int x, y, n;
            cin >> x >> y >> n;
            cout << minTime(x, y, n) << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}