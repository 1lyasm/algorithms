#ifndef DSA_H
#define DSA_H

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <climits>

struct Regex {
    static void test();
};

struct IsPalindrome {
    static bool isPalindrome(int);
    static void test();
};

struct MySqrt {
    static int mySqrt(int);
    static void test();
};

struct ClimbStairs {
    static int climbStairs(int);
    static void test();
};

struct DeleteDuplicates {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    static DeleteDuplicates::ListNode *deleteDuplicates(DeleteDuplicates::ListNode*);
    static void test();
};

struct MergeSortedArray {
    static void merge(std::vector<int>&, int, std::vector<int>&, int);
    static void test();
};

struct FindMedianSortedArrays {
    static double findMedianSortedArrays(std::vector<int>&, std::vector<int>&);
    static void test();
};

struct PageRank {
    static std::vector<double> pageRank(std::vector<std::vector<double> >, int, double);
    static double sumVector(std::vector<double>);
    static std::vector<int> computeOutgoingWeights(std::vector<std::vector<double> >, int);
    static inline double updatePageRankValue(std::vector<double>, int, std::vector<std::vector<double> >,
        int, std::vector<double>, double, std::vector<int>, double);
    static void assertCloseVector(std::vector<double>, std::vector<double>, int);
    static void assertClose(double, double);

    template <typename T>
    static void printVector(std::vector<T>);

    static void test();
};

struct LongestPalindrome {
    static std::string longestPalindrome(std::string);
    static void test();
};

struct ZigzagConversion {
    static std::string zigzag_conv(std::string, int);
    static void test();
};

struct ReverseInteger {
    static int reverse(int);
    static int string_to_int(std::string);
};

#endif
