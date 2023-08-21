#include <vector>

// #define DEBUG

#ifdef DEBUG
#include <iostream>
#define debug(x) x
#else
#define debug(x) ;
#endif

class Solution {
 public:
  static std::vector<int> trim(std::vector<int> &nums, int startIdx, int len) {
    std::vector<int> trimmed;
    for (int i = startIdx; i < startIdx + len; ++i) {
      bool found = false;
      for (int j = startIdx; j < startIdx + len; ++j) {
        if (nums[j] == nums[i] && i != j) {
          found = true;
          break;
        }
      }
      if (found) {
        trimmed.push_back(nums[i]);
      }
    }
    return trimmed;
  }

  static int compVal(std::vector<int> &nums, int startIdx, int len, int k) {
    auto trimmed = trim(nums, startIdx, len);
    return k + trimmed.size();
  }

  static bool thereIs(int target, std::vector<int> array, int startIdx,
                      int len) {
    for (int i = startIdx; i < startIdx + len; ++i) {
      if (target == array[i]) {
        return true;
      }
    }
    return false;
  }

  static void mergeLens(std::vector<int> &lens, std::vector<int> &nums) {
    int curIdx = 0;
    for (int i = 0; i < lens.size() - 1; ++i) {
      bool hasDuplicate = false;
      for (int j = curIdx; j < curIdx + lens[i]; ++j) {
        if (thereIs(nums[j], nums, curIdx + lens[i], lens[i + 1])) {
          hasDuplicate = true;
          break;
        }
      }
      if (!hasDuplicate) {
        lens[i] += lens[i + 1];
        lens.erase(lens.begin() + i);
      }
      curIdx += lens[i];
    }
  }

  static int minCost(std::vector<int> &nums, int k) {
    std::vector<int> lens;
    for (int i = 0; i < nums.size(); i += k) {
      if (nums.size() - i >= k) {
        debug(std::cout << "pushing " << k << "\n");
        lens.push_back(k);
      } else {
        lens.push_back(nums.size() - i);
        break;
      }
    }
    debug(std::cout << "\n");
    debug(std::cout << "minCost: lens before mergeLens: ");
    for (int i = 0; i < lens.size(); ++i) {
      debug(std::cout << lens[i] << " ");
    }
    debug(std::cout << "\n");
    mergeLens(lens, nums);
    debug(std::cout << "\n");
    debug(std::cout << "minCost: lens after mergeLens: ");
    for (int i = 0; i < lens.size(); ++i) {
      debug(std::cout << lens[i] << " ");
    }
    debug(std::cout << "\n");
    int totalVal = 0;
    int curIdx = 0;
    for (int i = 0; i < lens.size(); ++i) {
      totalVal += compVal(nums, curIdx, lens[i], k);
      curIdx += lens[i];
    }
    return totalVal;
  }
};
