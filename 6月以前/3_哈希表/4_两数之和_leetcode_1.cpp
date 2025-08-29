#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        // 遍历nums数组, 在map中找target-遍历值,
        // 找到了则输出它们的index
        // 找不到则在map中存储 遍历值:index
        unordered_map<int, int> nums_map;
        for (int i = 0; i < nums.size(); i++) {

            auto itter = nums_map.find(target - nums[i]);

            // 找到这个元素的情况下
            if (itter != nums_map.end()) {
                // 返回这对键值对
                return vector<int>{nums_map[target - nums[i]], i};
            }
            // 没找到这个元素的情况下
            else {
                nums_map.insert({nums[i], i});
            }
        }
        // 如果没有找到符合条件的两个数，返回空vector
        return {};
    }
    vector<int> baoli_twoSum(vector<int> &nums, int target) {
        // 暴力做法
        // 遍历嵌套两次
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return vector<int>{i, j};
                }
            }
        }
    }
};