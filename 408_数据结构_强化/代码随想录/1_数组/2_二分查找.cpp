#include <vector>
using namespace std;

class Solution {
public:
    // 最后返回目标值的序号
    int search(vector<int> &nums, int target) {
        // 采用左闭右开
        int left = 0, right = nums.size();
        int mid;
        // left<right即合法区间
        while (left < right) {
            mid = left + (right + left) / 2;
            if (target < nums[mid]) {
                right = mid;
            } else if (target > nums[mid]) {
                left = mid + 1;
            }

            // target == mid
            else {
                return mid;
            }
        }
        // 没搜索到
        return -1;
    }
};