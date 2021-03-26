#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

/* This program finds the median of two sorted arrays in logarithmic time and O(1) space
 * complexity. More explanation on the blog post can be found at the link below:
 *
 * This solution passed all LeetCode tests as of 03/24/2021
 */

class Solution {
public:
  double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    if (nums1.empty()) {
        // If one of the inputs is empty, we compute the median of the non-empty array
      return medianOfSingleArray(nums2);
    } else if (nums2.empty()) {
        // If one of the inputs is empty, we compute the median of the non-empty array
      return medianOfSingleArray(nums1);
    } else {
        // Optimization to check if both arrays contain the same element
        // In that case, we need not do any search and we can just return the
        // number
      if (nums1[0] == nums1[nums1.size() - 1] &&
          nums1[nums1.size() - 1] == nums2[0] &&
          nums2[0] == nums2[nums2.size() - 1])
        return nums1[0];
        
      if (nums1.size() > nums2.size()) {
          // Pass the smaller array as the first input
        return searchForMedian(nums2, nums1);
      } else {
          // Pass the smaller array as the first input
        return searchForMedian(nums1, nums2);
      }
    }
  }

private:
  double medianOfSingleArray(const std::vector<int> &nums) {
    size_t len = nums.size();
    if (len % 2 == 0) {
      // even length
      size_t indx1 = floor(len / 2);
      return static_cast<double>(nums[indx1] + nums[indx1 - 1]) / 2;
    } else {
      // odd length
      return static_cast<double>(nums[floor(len / 2)]);
    }
  }

  double searchForMedian(const std::vector<int> &A, const std::vector<int> &B) {
    // A is the smaller array
    int stop = static_cast<int>(A.size());
    int sizeOfCombinedArray = static_cast<int>(A.size() + B.size());
    int sizeOfLeftSubArray = static_cast<int>(floor(sizeOfCombinedArray / 2));
    
    // aL, aR, bL and bR represent the indices of the elements on either sides of the split
    // ALeft, ARight, BLeft and BRight correspond to the actual elements on either sides of the split
    int aL = 0;
    int aR = 0;
    int bL = 0;
    int bR = 0;
    int ALeft = 0;
    int ARight = 0;
    int BLeft = 0;
    int BRight = 0;

    while (aL <= stop) {
      int contribution_of_A = aL + 1; // these many elements are contributed by A
      int contribution_of_B =
          sizeOfLeftSubArray - contribution_of_A; // these many elements are contributed by B
      bL = contribution_of_B - 1;
      aR = aL + 1;
      bR = bL + 1;

      if (aL < 0) {
        // ALeft is empty. So, we compare with int min
        ALeft = std::numeric_limits<int>::min();
      } else {
        ALeft = A[aL];
      }

      if (bL < 0) {
          // BLeft is empty. So, we compare with int min
        BLeft = std::numeric_limits<int>::min();
      } else {
        BLeft = B[bL];
      }

      if (aR >= A.size()) {
          // ARight is empty. So, we compare with int max
        ARight = std::numeric_limits<int>::max();
      } else {
        ARight = A[aR];
      }

      if (bR >= B.size()) {
          // BRight is empty. So, we compare with int max
        BRight = std::numeric_limits<int>::max();
      } else {
        BRight = B[bR];
      }

      if (ALeft <= BRight && BLeft <= ARight) { // Check for target/median split
        if (sizeOfCombinedArray % 2 == 0) {
            // Even length of A+B
          return static_cast<double>(std::max(ALeft, BLeft) + std::min(ARight, BRight)) / 2;
        } else {
            // Odd length of A+B
          return std::min(ARight, BRight);
        }
      } else {
        if (ALeft > BRight) {
            // Include less of A and more of B
          aL = aL - 1;
        } else {
            // Include more of A and less of B
          aL = aL + 1;
        }
      }
    }

    return std::numeric_limits<int>::min(); // We should never get here
  }
};

int main() {
  std::vector<int> num1{1, 3};
  std::vector<int> num2{2};
   
  Solution obj;
  double result = obj.findMedianSortedArrays(num1, num2);
  std::cout << result << std::endl;
}
