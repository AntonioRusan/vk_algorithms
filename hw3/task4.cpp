#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>
using namespace std;
char getStrDiff(string a, string b) {
    map <char, int> letterToCnt;
    for (int i = 0; i < a.length(); i++) {
        if (letterToCnt.find(a[i])!= letterToCnt.end()) {
            letterToCnt[a[i]]++;
        }
        else {
            letterToCnt.insert({a[i], 1});
        }
    }
    for (int i = 0; i < b.length(); i++) {
        if (letterToCnt.find(b[i]) != letterToCnt.end()) {
            letterToCnt[b[i]]--;
            if (letterToCnt[b[i]] == 0) {
                letterToCnt.erase(b[i]);
                continue;
            }
            continue;
        }
        return b[i];
    }
    return '\0';
}
char getStrDiffXOR(string a, string b) {
    char result = 0;
    for (int i = 0; i < a.size(); i++) result ^= a[i];
    for (int i = 0; i < b.size(); i++) result ^= b[i];
    return result;
}
TEST(GetStrDiffTest, SingleCharacterAdded) {
    EXPECT_EQ(getStrDiff("abc", "abce"), 'e');
    EXPECT_EQ(getStrDiffXOR("abc", "abce"), 'e');
}

TEST(GetStrDiffTest, CharacterAddedInMiddle) {
    EXPECT_EQ(getStrDiff("abcd", "adbce"), 'e');
    EXPECT_EQ(getStrDiffXOR("abcd", "adbce"), 'e');
}

TEST(GetStrDiffTest, DuplicateCharacters) {
    EXPECT_EQ(getStrDiff("aab", "aabb"), 'b');
    EXPECT_EQ(getStrDiffXOR("aab", "aabb"), 'b');
}

TEST(GetStrDiffTest, EmptyStringA) {
    EXPECT_EQ(getStrDiff("", "z"), 'z');
    EXPECT_EQ(getStrDiffXOR("", "z"), 'z');
}

TEST(GetStrDiffTest, SameCharactersDifferentOrder) {
    EXPECT_EQ(getStrDiff("hello", "ollehx"), 'x');
    EXPECT_EQ(getStrDiffXOR("hello", "ollehx"), 'x');
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            string a, b;
            cin >> a;
            cin >> b;
            cout << getStrDiff(a, b);
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}
