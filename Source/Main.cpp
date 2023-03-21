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

class Regex {
public:
    static void test() {
        std::cout << "\ntestRegex: Start\n"; {
            std::regex Regex("(a|xy)*");
            std::smatch Match;
            std::vector<std::string> TestStrings = {"a", "aa", "aaa", "xy", "xyxy", "xyxyxy", ""};
            for (const auto &TestString : TestStrings) {
                assert(std::regex_match(TestString, Match, Regex) == 1);
            }
        }
        {
            std::regex Regex("b(oz)+o");
            std::smatch Match;
            std::vector<std::string> TestStrings = {"bozo", "bozozo", "bozozozo"};
            for (const auto &TestString : TestStrings) {
                assert(std::regex_match(TestString, Match, Regex) == 1);
            }
        }
        {
            std::regex Regex("((|0)1)*");
            std::smatch Match;
            std::vector<std::string> TestStrings = {"01", "0101", "010101", "1", "11", "111", ""};
            for (const auto &TestString : TestStrings) {
                assert(std::regex_match(TestString, Match, Regex) == 1);
            }
        }
        {
            std::regex Regex("[ab]*a[ab]*a[ab]*a[ab]*");
            std::smatch Match;
            std::vector<std::string> TestStrings =
                {"aaab", "baaa", "abaa", "aaba", "aaab", "aaa", "aaaa", "aaaab",
                 "abababa", "bbbbbbbbbbaaa", "bbabbabbab"};
            for (const auto &TestString : TestStrings) {
                assert(std::regex_match(TestString, Match, Regex) == 1);
            }
        }
        {
            std::regex Regex("(a*(bb)*a*)*");
            std::smatch Match;
            std::vector<std::string> MatchingStrings = {"abba", "bbbbabbaaa", "a", ""};
            for (const auto &MatchingString : MatchingStrings) {
                assert(std::regex_match(MatchingString, Match, Regex) == 1);
            }
            std::vector<std::string> NonMatchingStrings = {"aba", "b", "ababa", "abbab"};
            for (const auto &NonMatchingString : NonMatchingStrings) {
                assert(std::regex_match(NonMatchingString, Match, Regex) == 0);
            }
        }
        {
            std::regex Regex(
                "[bcdfghjklmnpqrstvwxyz]*a[bcdfghjklmnpqrstvwxyz]*e[bcdfghjklmnpqrstvwxyz]*i[bcdfghjklmnpqrstvwxyz]*o[bcdfghjklmnpqrstvwxyz]*u[bcdfghjklmnpqrstvwxyz]*");
            std::smatch Match;
            std::vector<std::string> MatchingStrings = {"aeiou", "baeiou", "aeioub", "abeioub",
                                                        "zbabebibobubz"};
            for (const auto &MatchingString : MatchingStrings) {
                assert(std::regex_match(MatchingString, Match, Regex) == 1);
            }
            std::vector<std::string> NonMatchingStrings = {"aba", "b", "ababa", "abbab"};
            for (const auto &NonMatchingString : NonMatchingStrings) {
                assert(std::regex_match(NonMatchingString, Match, Regex) == 0);
            }
        }
        {
            std::regex Regex(
                "(([1-9][0-9]*)|(0[xX][0-9a-fA-F]+)|(0+[1-7]*))(u|U|l|L|ll|LL|)");
            std::smatch Match;
            std::vector<std::string> MatchingStrings = {
                "0x0", "0X0", "0xa", "0XA", "0x123450",
                "0x00", "0X00000", "0X00000a", "0000123", "000000",
                "10", "0", "2", "22", "01", "15", "9L", "9ll", "9LL", "9l", "0x0001u",
                "0XBBBU"};
            for (const auto &MatchingString : MatchingStrings) {
                assert(std::regex_match(MatchingString, Match, Regex) == 1);
            }
            std::cout << "\n";
            std::vector<std::string> NonMatchingStrings = {
                "0X", "0x", "000001238", "09", "0xz", "x", "x1234",
                "0x1234g1", "9lll", "0xauu", "0XAAAUU"};
            for (const auto &NonMatchingString : NonMatchingStrings) {
                assert(std::regex_match(NonMatchingString, Match, Regex) == 0);
            }
        }
        {
            std::regex Regex("/(\\*)((\\*(?!/))|([^\\*]))*(\\*)/");
            std::smatch Match;
            std::vector<std::string> MatchingStrings = {
                "/*a*/", "/* This is a comment */", "/**/", "/* */",
                "/* comment /* comment */", "/* **** */", "/* //// */"};
            for (const auto &MatchingString : MatchingStrings) {
                std::cout << "Test case (matching): " << MatchingString << "\n";
                assert(std::regex_match(MatchingString, Match, Regex) == 1);
            }
            std::cout << "\n";
            std::vector<std::string> NonMatchingStrings = {
                "/*", "/* not comment */ not comment */"};
            for (const auto &NonMatchingString : NonMatchingStrings) {
                std::cout << "Test case (not matching): " << NonMatchingString << "\n";
                assert(std::regex_match(NonMatchingString, Match, Regex) == 0);
            }
        }
        std::cout << "\ntestRegex: OK\n";
    }
};

class IsPalindrome
{
public:
    static bool isPalindrome(int x) {
        std::string NumberString = std::to_string(x);
        int N = NumberString.length();
        std::string LastHalf;
        for (int I = N - 1; I >= (N + 1) / 2; --I) {
            LastHalf.push_back(NumberString[I]);
        }
        for (int I = 0; I < LastHalf.length(); ++I) {
            if (LastHalf[I] != NumberString[I]) {
                return false;
            }
        }
        return true;
    }

    static void test() {
        std::cout << "Testing IsPalindrome: ";
        assert(IsPalindrome::isPalindrome(12321) == true);
        assert(IsPalindrome::isPalindrome(1232) == false);
        assert(IsPalindrome::isPalindrome(4334) == true);
        assert(IsPalindrome::isPalindrome(5) == true);
        std::cout << "PASSED";
    }
};

class MySqrt {
    static int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int Subtractor = 1;
        int SquareRootCounter = -1;
        while (x >= 0) {
            x -= Subtractor;
            Subtractor += 2;
            SquareRootCounter++;
        }
        return SquareRootCounter;
    }

public:
    static void test() {
        std::cout << "Testing MySqrt: ";
        assert(MySqrt::mySqrt(26) == 5);
        assert(MySqrt::mySqrt(24) == 4);
        assert(MySqrt::mySqrt(25) == 5);
        std::cout << "PASSED";
    }
};

class ClimbStairs {
    static int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        else if (n == 2) {
            return 2;
        }
        int First = 1;
        int Second = 2;
        int Third = Second + First;
        int NIterations = n - 2;
        for (int I = 0; I < NIterations - 1; ++I) {
            First = Second;
            Second = Third;
            Third = Second + First;
        }
        return Third;
    }

public:
    static void test() {
        std::cout << "Testing ClimbStairs: ";
        assert(ClimbStairs::climbStairs(5) == 8);
        std::cout << "PASSED";
    }
};

class DeleteDuplicates {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    static DeleteDuplicates::ListNode *deleteDuplicates(
        DeleteDuplicates::ListNode *head) {
        if (head == 0 || head->next == 0) {
            return head;
        }
        auto LeftNodePointer = head;
        auto RightNodePointer = head->next;
        while (RightNodePointer) {
            while (RightNodePointer->val ==
                   LeftNodePointer->val) {
                LeftNodePointer->next =
                    RightNodePointer->next;
                if (RightNodePointer->next) {
                    RightNodePointer = RightNodePointer->next;
                }
                else {
                    return head;
                }
            }
            LeftNodePointer = RightNodePointer;
            RightNodePointer = RightNodePointer->next;
        }
        return head;
    }

public:
    static void test() {
        std::cout << "Testing ClimbStairs: ";
        auto InputHead = new DeleteDuplicates::ListNode(1,
            new DeleteDuplicates::ListNode(1,
            new DeleteDuplicates::ListNode(2)));
        auto ExpectedOutput = new DeleteDuplicates::ListNode(1,
            new DeleteDuplicates::ListNode(2));
        auto ActualNode = DeleteDuplicates::deleteDuplicates(InputHead);
        auto OutputNode = ExpectedOutput;
        while (ActualNode && OutputNode) {
            assert(ActualNode->val == OutputNode->val);
            ActualNode = ActualNode->next;
            OutputNode = OutputNode->next;
        }
        std::cout << "PASSED";
    }
};

class MergeSortedArray {
    static void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2,
        int n) {
        if (!n) {
            return;
        }
        int RightIndex = n - 1;
        int LeftIndex = m - 1;
        int TotalIndex = n + m - 1;
        while ((RightIndex >= 0) && (LeftIndex >= 0)) {
            if (nums2[RightIndex] > nums1[LeftIndex]) {
                nums1[TotalIndex] = nums2[RightIndex];
                --RightIndex;
            }
            else {
                nums1[TotalIndex] = nums1[LeftIndex];
                --LeftIndex;
            }
            --TotalIndex;
        }
        int LongerIndex;
        std::vector<int> LongerVector;
        if (LeftIndex < 0) {
            LongerIndex = RightIndex;
            LongerVector = nums2;
        }
        else {
            LongerIndex = LeftIndex;
            LongerVector = nums1;
        }
        while (LongerIndex >= 0) {
            nums1[TotalIndex] = LongerVector[LongerIndex];
            --LongerIndex;
            --TotalIndex;
        }
    }

public:
    static void test() {
        std::cout << "Testing MergeSortedArray: ";
        std::vector<int> Numbers1 = {1, 2, 3, 0, 0, 0};
        std::vector<int> Numbers2 = {2, 5, 6};
        MergeSortedArray::merge(Numbers1, 3, Numbers2, 3);
        std::vector<int> Expected = {1, 2, 2, 3, 5, 6};
        for (int I = 0; I < Expected.size(); ++I) {
            assert(Numbers1[I] == Expected[I]);
        }
        std::cout << "PASSED";
    }
};

class FindMedianSortedArrays {
    static double findMedianSortedArrays(std::vector<int> &nums1,
        std::vector<int> &nums2) {
        int N = nums1.size();
        int M = nums2.size();
        int LeftIndex = 0;
        int RightIndex = 0;
        int MedianCounter = 0;
        int MedianIndex = (N + M) / 2;
        bool IsEvenLength = (N + M) % 2 == 0;
        MedianIndex += !IsEvenLength;
        int Median;
        while (MedianCounter < MedianIndex &&
               LeftIndex < N && RightIndex < M) {
            if (nums1[LeftIndex] < nums2[RightIndex]) {
                Median = nums1[LeftIndex];
                ++LeftIndex;
            }
            else {
                Median = nums2[RightIndex];
                ++RightIndex;
            }
            ++MedianCounter;
        }
        int *LongerIndex;
        std::vector<int> Longer;
        int LongerLength;
        if (N > M) {
            LongerIndex = &LeftIndex;
            Longer = nums1;
            LongerLength = N;
        }
        else {
            LongerIndex = &RightIndex;
            Longer = nums2;
            LongerLength = M;
        }
        while (*LongerIndex < LongerLength &&
               MedianCounter < MedianIndex) {
            Median = Longer[*LongerIndex];
            *LongerIndex += 1;
            ++MedianCounter;
        }
        if (IsEvenLength == true) {
            if (LeftIndex < N && RightIndex < M) {
                if (nums1[LeftIndex] < nums2[RightIndex]) {
                    return (Median + nums1[LeftIndex]) / 2.0;
                }
                else {
                    return (Median + nums2[RightIndex]) / 2.0;
                }
            }
            else if (LeftIndex < N) {
                return (Median + nums1[LeftIndex]) / 2.0;
            }
            else if (RightIndex < M) {
                return (Median + nums2[RightIndex]) / 2.0;
            }
        }
        return Median;
    }

public:
    static void test() {
        std::cout << "Testing FindMedianSortedArrays: ";
        std::vector<int> Input1{1, 2};
        std::vector<int> Input2{3, 4};
        assert(FindMedianSortedArrays::findMedianSortedArrays(
            Input1, Input2) == 2.5);
        std::cout << "PASSED";
    }
};

class PageRank {
    static std::vector<double> pageRank(
        std::vector<std::vector<double>> Graph,
        int IterationCount, double DampingFactor) {
        int NodeCount = Graph.size();
        double DampingTerm = (1.0 - DampingFactor) / NodeCount;
        double InitialValue = 1.0 / NodeCount;
        std::vector<double> PageRankValues(NodeCount, InitialValue);
        std::vector<int> OutgoingWeights = computeOutgoingWeights(
            Graph, NodeCount);
        for (int IterationCounter = 0;
            IterationCounter < IterationCount; ++IterationCounter) {
            std::vector<double> OldValues = PageRankValues;
            for (int NodeIndex = 0; NodeIndex < NodeCount; ++NodeIndex) {
                PageRankValues[NodeIndex] = updatePageRankValue(PageRankValues,
                NodeIndex, Graph, NodeCount,
                OldValues, DampingTerm, OutgoingWeights, DampingFactor);
            }
            PageRank::assertClose(sumVector(PageRankValues), 1.0000000);
        }
        return PageRankValues;
    }

    static double sumVector(std::vector<double> Vector) {
        double Sum = 0.0;
        for (const auto &Value : Vector) {
            Sum += Value;
        }
        return Sum;
    }

    static std::vector<int> computeOutgoingWeights(
        std::vector<std::vector<double>> Graph, int NodeCount) {
        std::vector<int> OutgoingWeights(NodeCount, 0);
        for (int ColumnNodeIndex = 0; ColumnNodeIndex < NodeCount;
             ++ColumnNodeIndex) {
            int OutgoingWeight = 0;
            for (int RowNodeIndex = 0; RowNodeIndex < NodeCount;
                 ++RowNodeIndex) {
                OutgoingWeight += static_cast<int>(
                    std::ceil(Graph[RowNodeIndex][ColumnNodeIndex]));
            }
            OutgoingWeights[ColumnNodeIndex] = OutgoingWeight;
        }
        return OutgoingWeights;
    }

    static inline double updatePageRankValue(std::vector<double> UpdatedValues,
        int NodeIndex, std::vector<std::vector<double>> Graph,
        int NodeCount, std::vector<double> OldValues, double DampingTerm,
        std::vector<int> OutgoingWeights, double DampingFactor) {
        double UpdateValue = DampingTerm;
        double PageRankSum = 0;
        for (int OtherNodeIndex = 0; OtherNodeIndex < NodeCount;
             ++OtherNodeIndex) {
            if (OtherNodeIndex == NodeIndex) {
                continue;
            }
            if (std::ceil(Graph[NodeIndex][OtherNodeIndex]) == 1) {
                PageRankSum +=
                    OldValues[OtherNodeIndex] / OutgoingWeights[OtherNodeIndex];
            }
        }
        return UpdateValue + DampingFactor * PageRankSum;
    }

    static void assertCloseVector(std::vector<double> Vector1,
        std::vector<double> Vector2, int Length) {
        double Threshold = 0.000001;
        for (int I = 0; I < Length; ++I) {
            assert(std::fabs(Vector1[I] - Vector2[I]) <= Threshold);
        }
    }

    static void assertClose(double Value1, double Value2) {
        double Threshold = 0.000001;
        assert(std::fabs(Value1 - Value2) <= Threshold);
    }

    template <typename T>
    static void printVector(std::vector<T> Vector) {
        for (const auto &Value : Vector) {
            std::cout << Value << " ";
        }
        std::cout << "\n";
    }

public:
    static void test() {
        std::cout << "Testing PageRank: ";
        std::vector<std::vector<double>> Graph = {
            {0, 0, 0, 0, 1},
            {0.5, 0, 0, 0, 0},
            {0.5, 0, 0, 0, 0},
            {0, 1, 0.5, 0, 0},
            {0, 0, 0.5, 1, 0}};
        int IterationCount = 100;
        double DampingFactor = 0.85;
        std::vector<double> Output = PageRank::pageRank(Graph,
            IterationCount, DampingFactor);
        std::vector<double> Expected = {0.25419178, 0.13803151,
            0.13803151, 0.20599017, 0.26375504};
        int ExpectedLength = Expected.size();
        int OutputLength = Output.size();
        assert(OutputLength == ExpectedLength);
        PageRank::assertCloseVector(Output, Expected, ExpectedLength);
        std::cout << "PASSED";
    }
};

class LongestPalindrome {
public:
    static std::string longestPalindrome(std::string s) {
        int StringLength = s.size();
        int MaximumPalindromeLength = 0;
        int StartIndex = -1;
        for (int I = 0; I < StringLength; ++I) {
            int LeftIndex = I - 1, RightIndex = I + 1;
            for (;LeftIndex >= 0 && RightIndex < StringLength &&
                s[LeftIndex] == s[RightIndex];
                --LeftIndex, ++RightIndex);
            int NewLength = RightIndex - LeftIndex - 1;
            if (NewLength > MaximumPalindromeLength) {
                MaximumPalindromeLength = NewLength;
                StartIndex = LeftIndex + 1;
            }
            LeftIndex = I, RightIndex = I + 1;
            for (;LeftIndex >= 0 && RightIndex < StringLength &&
                s[LeftIndex] == s[RightIndex];
                --LeftIndex, ++RightIndex);
            NewLength = RightIndex - LeftIndex - 1;
            if (NewLength > MaximumPalindromeLength) {
                MaximumPalindromeLength = NewLength;
                StartIndex = LeftIndex + 1;
            }
        }
        return s.substr(StartIndex, MaximumPalindromeLength);
    }

    static void test() {
        std::cout << "Testing LongestPalindrome: ";
        assert(LongestPalindrome::longestPalindrome("babad") == "bab" ||
               LongestPalindrome::longestPalindrome("babad") == "aba");
        assert(LongestPalindrome::longestPalindrome("cbbd") == "bb");
        assert(LongestPalindrome::longestPalindrome("e") == "e");
        assert(LongestPalindrome::longestPalindrome("abcdbbfcba") == "bb");
        assert(LongestPalindrome::longestPalindrome("ccc") == "ccc");
        std::cout << "PASSED";
    }
};

class ZigzagConversion {
    static std::string zigzag_conv(std::string s,
        int row_count) {
        if (s.size() < 2 || row_count == 1) {
            return s;
        }
        std::string result;
        for (int i = 0; i < s.size(); i += 2 * row_count - 2) {
            result.push_back(s[i]);
        }
        for (int i = 1; i < row_count - 1; ++i) {
            bool mode = false;
            for (int j = i; j < s.size();) {
                result.push_back(s[j]);
                if (mode == false) {
                    j += (row_count - i - 1) * 2;
                    mode = true;
                } else {
                    j += i * 2;
                    mode = false;
                }
            }
        }
        for (int i = row_count - 1; i < s.size(); i += 2 * row_count - 2) {
            result.push_back(s[i]);
        }
        return result;
    }

public:
    static void test() {
        std::cout << "\nZigzagConversion::test: ";
        assert(zigzag_conv("PAYPALISHIRING", 3) ==
            "PAHNAPLSIIGYIR");
        assert(zigzag_conv("PAYPALISHIRING", 4) ==
            "PINALSIGYAHRPI");
        assert(zigzag_conv("A", 1) == "A");   
        std::cout << "PASSED\n";
    }
};

class ReverseInteger {
    static int reverse(int x) {
        if (x <= 9 && x >= -9) {
            return x;
        }
        bool is_negative = false;
        if (x < 0) {
            is_negative = true;
        }
        x = std::abs(x);
        std::string x_str;
        int val = x;
        for (; val > 0;) {
            x_str.push_back(val % 10 + 48);
            val /= 10;
        }
        int first_nonzero = 0;
        for (; first_nonzero < x_str.size() && x_str[first_nonzero] == '0';) {
            ++first_nonzero;
        }
        std::string x_str_stripped;
        for (int i = first_nonzero; i < x_str.size(); ++i) {
            x_str_stripped.push_back(x_str[i]);
        }
        x_str = x_str_stripped;
        int as_int = string_to_int(x_str);
        if (as_int == -1) {
            return 0;
        } else if (is_negative) {
            return as_int * -1;
        } else {
            return as_int;
        }
    }

    static int string_to_int(std::string s) {
        int val = 0;
        int multiplier = 1;
        for (int i = s.size() - 1; i >= 0; --i) {
            if ((2147483648 - val) / (double)multiplier <= (s[i] - 48)) {
                return -1;
            }
            val += (s[i] - 48) * multiplier;
            if (2147483648 / 10.0 > multiplier) multiplier *= 10;
        }
        return val;
    }

public: 
    static void test() {
        std::cout << "\nReverseInteger::test: ";
        assert(reverse(123) == 321);
        assert(reverse(120) == 21);
        assert(reverse(-123) == -321);
        assert(reverse(1534236469) == 0);
        std::cout << "PASSED\n";
    }
};

int main() {
    std::cout << "\n";
    ReverseInteger::test();
    std::cout << "\n";
    return 0;
}
