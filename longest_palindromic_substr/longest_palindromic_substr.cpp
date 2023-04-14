class Solution {
public:
  static std::string longestPalindrome(std::string s) {
    int StringLength = s.size();
    int MaximumPalindromeLength = 0;
    int StartIndex = -1;
    for (int I = 0; I < StringLength; ++I) {
      int LeftIndex = I - 1, RightIndex = I + 1;
      for (; LeftIndex >= 0 && RightIndex < StringLength &&
             s[LeftIndex] == s[RightIndex];
           --LeftIndex, ++RightIndex)
        ;
      int NewLength = RightIndex - LeftIndex - 1;
      if (NewLength > MaximumPalindromeLength) {
        MaximumPalindromeLength = NewLength;
        StartIndex = LeftIndex + 1;
      }
      LeftIndex = I, RightIndex = I + 1;
      for (; LeftIndex >= 0 && RightIndex < StringLength &&
             s[LeftIndex] == s[RightIndex];
           --LeftIndex, ++RightIndex)
        ;
      NewLength = RightIndex - LeftIndex - 1;
      if (NewLength > MaximumPalindromeLength) {
        MaximumPalindromeLength = NewLength;
        StartIndex = LeftIndex + 1;
      }
    }
    return s.substr(StartIndex, MaximumPalindromeLength);
  }
};
