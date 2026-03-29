#include <iostream>
#include <map>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

vector <int> getSumPair(vector<int> arr, int target) {
    map <int, int> sumMap;
    for (int i = 0; i < arr.size(); i++) {
        if (sumMap.find(arr[i]) != sumMap.end()) {
            sumMap[arr[i]]++;
        }
        else {
            sumMap.insert({arr[i], 1});
        }
    }
    vector <int> pairRes;
    for (int i = 0; i < arr.size(); i++) {
        if (sumMap.find(target - arr[i]) != sumMap.end()) {
            pairRes.push_back(arr[i]);
            pairRes.push_back(target - arr[i]);
            break;
        }
    }
    return pairRes;
}
TEST(GetSumPairTest, BasicCase) {
    vector<int> arr = {2, 7, 11, 15};
    vector<int> result = getSumPair(arr, 9);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE((result[0] == 2 && result[1] == 7) || 
                (result[0] == 7 && result[1] == 2));
}

TEST(GetSumPairTest, NoPairFound) {
    vector<int> arr = {1, 2, 3};
    vector<int> result = getSumPair(arr, 10);
    EXPECT_EQ(result.size(), 0);
}

TEST(GetSumPairTest, NegativeNumbers) {
    vector<int> arr = {-1, -2, -3, -4, -5};
    vector<int> result = getSumPair(arr, -8);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE((result[0] == -3 && result[1] == -5) || 
                (result[0] == -5 && result[1] == -3));
}
TEST(GetSumPairTest, SameElementTwice) {
    vector<int> arr = {3, 3, 4, 5};
    vector<int> result = getSumPair(arr, 6);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 3);
}
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            int n, target;
            cin >> n >> target;
            vector <int> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            vector <int> res = getSumPair(arr, target);
            if (res.empty()) {
                cout << "No pair" << endl;
            }
            else 
            {
                cout << res[0] << " " << res[1] << endl;
            }
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}