#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> one_fourSum(vector<int> &nums, int target) {

        vector<vector<int>> res_vec; // vector初始化的数组为空
        sort(nums.begin(), nums.end());
        // 0.处理边界情况
        if (nums.size() < 4) {
            return {};
        }
        // i最多到nums.size()-4
        for (int i = 0; i < nums.size() - 3; i++) {

            // 1.1 i剪枝
            // target大于0的情况下, nums[i]如果大于target, 则无解,
            // 而且意味着后续的i也无解, 所以要结束循环, 而不是结束本次循环
            // target >= 0 , nums[i]可否等于target
            // target =0的情况下, num[i]=target=0,后续的值也可以找到四元组,
            // 比如{0,0,0,0}, 因为数组单调不减
            // 总结
            // target=0 , nums[i] > target
            // target >0的情况, nums[i] >=target

            if (target == 0 && nums[i] > target ||
                target > 0 && nums[i] >= target) {
                break;
            }
            // 1.2 i去重
            // i重复的情况下, 结束本次循环
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size() - 2; j++) {
                // 2.1 j 剪枝
                // 在有i的基础上, 如果targe >= 0, nums[i] + nums[j] >= target
                // >=0 ,也就意味着不可能是目标的四元组
                if (target == 0 && nums[i] + nums[j] > target ||
                    target > 0 && nums[i] + nums[j] >= target) {
                    break;
                }

                // 2.2 j去重
                // j > 1 && nums[j] == nums[j - 1])
                // 这个去重逻辑有问题,i和j的值可以相等
                // 实际上这里要避免的是i和j同时和上一轮的相同
                // 也就是结束循环的条件是j>1, i和上一轮的相同且j和上一轮相同
                // i的初始值是0, j的初始值是1, 也就是j要大于1
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    long long temp =
                        (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (temp > target)
                        right--;
                    else if (temp < target)
                        left++;
                    // temp=target
                    else {
                        // 添加四元组
                        res_vec.push_back(
                            {nums[i], nums[j], nums[left], nums[right]});
                        // 去重
                        do {
                            left++;
                        } while (nums[left] == nums[left - 1] && left < right);

                        do {
                            right--;
                        } while (nums[right] == nums[right + 1] &&
                                 left < right);
                    };
                }
            }
        }
        return res_vec;
    }
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> res_vec;
        if (nums.size() < 4)
            return res_vec;
        sort(nums.begin(), nums.end());
        size_t length = nums.size();
        for (int i = 0; i < length - 3; i++) {
            // 1.剪枝
            // 最小的组合都大于target ,无解, break
            if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] >
                target) {
                break;
            }
            // 初始值加最大的三个组合都小于target, 说明当前值肯定不行
            if ((long long)nums[i] + nums[length - 3] + nums[length - 2] +
                    nums[length - 1] <
                target) {
                continue;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            for (int j = i + 1; j < length - 2; j++) {
                if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] >
                    target) {
                    break;
                }

                if ((long long)nums[i] + nums[j] + nums[length - 2] +
                        nums[length - 1] <
                    target) {
                    continue;
                }

                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    long long sum =
                        (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum > target) {
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        res_vec.push_back(
                            {nums[i], nums[j], nums[left], nums[right]});
                        do {
                            left++;
                        } while (left < right && nums[left] == nums[left - 1]);
                        do {
                            right--;
                        } while (left < right &&
                                 nums[right] == nums[right + 1]);
                    }
                }
            }
        }
        return res_vec;
    }
};

int main() {
    vector<int> nums = {-2, -1, -1, 1, 2, 2};
    int target = 0;
    Solution sol;
    vector<vector<int>> res_vec = sol.fourSum(nums, target);
    for (auto i : res_vec) {
        cout << "[";
        for (auto j : i) {
            cout << j << ", ";
        }
        cout << "]" << '\n';
    }
}
