#include <iostream>
#include <vector>
#include <iterator>
#include <gtest/gtest.h>
using namespace std;
vector <int> merge(vector <int> arr, vector <int> brr) {
    int i = 0, j = 0;
    int n = arr.size();
    int m = brr.size();
    vector<int> res;
    while (i < n && j < m) {
        if (arr[i] < brr[j]){
            res.push_back(arr[i]);
            i++;
        }
        else {
            res.push_back(brr[j]);
            j++;
        }
    }
    while(i < n) {
        res.push_back(arr[i]);
        i++;
    }
    while(j < m) {
        res.push_back(brr[j]);
        j++;
    }
    return res;
}
vector<int> mergeSort(vector <int> arr) {
    if (arr.size() < 2) {
        return arr;
    }
    int mid = arr.size() / 2;
    vector<int> leftPart(mid); 
    vector<int> rightPart(arr.size() - mid);
    copy(arr.begin(), arr.begin() + mid, leftPart.begin());
    copy(arr.begin() + mid, arr.end(), rightPart.begin());
    return merge(mergeSort(leftPart), mergeSort(rightPart));
}
int feedAnimalCnt(vector <int> food, vector <int> animals) {
    food = mergeSort(food);
    animals = mergeSort(animals);
    if (food.empty() || animals.empty()) return 0;
    int res = 0;
    for (int i = 0; i < food.size(); i++) {
        if (food[i] >= animals[res]) {
            res++;
        }
        if (res == animals.size()) break;       
    }
    return res;
}
TEST(FeedAnimalTest, BasicCase) {
    vector<int> food = {1, 3, 5};
    vector<int> animals = {2, 4, 6};
    EXPECT_EQ(feedAnimalCnt(food, animals), 2);
}

TEST(FeedAnimalTest, AllAnimalsFed) {
    vector<int> food = {5, 5, 5};
    vector<int> animals = {3, 4, 5};
    EXPECT_EQ(feedAnimalCnt(food, animals), 3);
}

TEST(FeedAnimalTest, NoAnimalsFed) {
    vector<int> food = {1, 1, 1};
    vector<int> animals = {5, 5, 5};
    EXPECT_EQ(feedAnimalCnt(food, animals), 0);
}

TEST(FeedAnimalTest, EmptyArrays) {
    vector<int> food = {};
    vector<int> animals = {1, 2, 3};
    EXPECT_EQ(feedAnimalCnt(food, animals), 0);
    
    food = {1, 2, 3};
    animals = {};
     EXPECT_EQ(feedAnimalCnt(food, animals), 0);
}
TEST(FeedAnimalTest, SingleAnimalAndFood) {
    vector<int> food = {10};
    vector<int> animals = {5};
    EXPECT_EQ(feedAnimalCnt(food, animals), 1);
    
    food = {3};
    animals = {5};
    EXPECT_EQ(feedAnimalCnt(food, animals), 0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--run") {
            int n, m;
            cin >> n;
            vector <int> food(n);
            for (int i = 0; i < n; i++) {
                cin >> food[i];
            }
            cin >> m;
            vector <int> animals(m);
            for (int i = 0; i < m; i++) {
                cin >> animals[i];
            }
            cout << feedAnimalCnt(food, animals) << endl;
            return 0;
        }
    }
    return RUN_ALL_TESTS();
}