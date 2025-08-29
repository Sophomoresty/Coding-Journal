#include <vector>
using namespace std;

class Solution {
private:
    int searchLeft(vector<int> &nums, int target) {
        // 采用左闭右开
        int right, left, mid;
        // 初始化

        left = 0;
        right = nums.size();
        // 因为要找第一个>=target
        // 我们的思路是通过不断增大[0,left), [right,nums.size())两个区间,
        // 直到right和left相等, 这个值就我们要找的值,
        // 因为是要找第1个大于等于target的, 所以这里 [right,
        // nums.size())里面的值严格大于等于target
        // [0,left)的值严格小于target,
        // 以此去更新区间
        //

        while (left < right) {
            mid = left + (right - left) / 2;
            // 更新值的时候要注意区间和区间的含义
            // 比如right, nums[mid] >= target,
            // right所在的区间是找大于等于target的, 而right处是闭的,
            // 所以更新的时候取mid
            if (nums[mid] >= target) {
                right = mid;
            }
            // nums[mid] < target
            // left, nums[mid] < target, left所在的区间是找小于target的,
            // 而left处在开, 所以更新的时候取mid+1

            else {
                left = mid + 1;
            }
        }
        return left;
    }
    // 找第一个>target
    int searchRight(vector<int> &nums, int target) {
        int right, left, mid;
        left = 0;
        right = nums.size();

        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }

public:
    vector<int> searchRange(vector<int> &nums, int target) {
        int left, right;
        left = searchLeft(nums, target);
        right = searchRight(nums, target) - 1;
        if (left == nums.size() || nums[left] != target) {
            return {-1, -1};
        } else {
            return {left, right};
        }
    }
};