#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        // 0. 处理边界情况：如果元素数量不足3个，直接返回空
        if (nums.size() < 3) {
            return {};
        }

        // 最后返回的值是多个三元组, 三元组的内容设为[i,j,k], ijk的和为0,
        // 且ijk的序号不能相同, 三元组不能重复
        // 对数组进行排序
        sort(nums.begin(), nums.end());
        // 如果最小值大于0, 也就以为三元组不可能存在, 返回空;
        if (nums[0] > 0) {
            return {};
        }
        vector<vector<int>> res_vec;
        // 对数组进行遍历
        // 使用i, left, right就是为了避免序号相同
        // 对i, left, right去重, 是为了避免三元组重复
        for (int i = 0; i < nums.size() - 2; i++) {
            // 进入循环前需要去i的重, 重复的情况下结束本次循环
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            // 定义left和right指针
            int left = i + 1;
            int right = nums.size() - 1;
            // right指针永远指向末尾会不会重复? 不会, 因为i去重了
            // 因为序号不能相同, 也就是退出循环时, right =left
            while (right > left) {
                int temp = nums[i] + nums[left] + nums[right];
                if (temp > 0) {
                    right--;
                } else if (temp < 0) {
                    left++;
                }
                // temp = 0;
                else {
                    res_vec.push_back({nums[i], nums[left], nums[right]});
                    // 当i,left,right的值刚好为0时, 此时i是固定的,
                    // 如果只动right或则left, 是找不到值的 也就是这种情况下,
                    // 为了找继续可能存在的值, left和right都必须收缩
                    do {
                        left++;
                    }
                    // 对left和while去重, 必须用循环处理, 退出条件是前后不相等,
                    // 这有可能导致right和left错位
                    // 综上, 循环条件是前后相等 且 left < right
                    while (nums[left] == nums[left - 1] && left < right);

                    do {
                        right--;
                    } while (nums[right] == nums[right + 1] && left < right);
                }
            }
        }
        return res_vec;
    }
};