#include <vector>
using namespace std;

class Solution {
public:
    // 平方后的数组最大值只能出现在两端
    // 比较得到最大值, 放在数组末尾
    vector<int> sortedSquares(vector<int> &nums) {
        int left = 0, right = nums.size() - 1;
        int k = nums.size() - 1;
        vector<int> result(nums.size());

        for (; left <= right;) {
            int nums_left = nums[left] * nums[left];
            int nums_right = nums[right] * nums[right];
            if (nums_left < nums_right) {
                result[k--] = nums_right;
                right--;
            }
            // nums_left >= nums_right
            else {
                result[k--] = nums_left;
                left++;
            }
        }
        return result;
    }
};