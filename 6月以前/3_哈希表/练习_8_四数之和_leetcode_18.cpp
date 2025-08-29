#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> res_vec;
        sort(nums.begin(), nums.end());
        if (nums.size() < 4) {
            return {};
        }
        for (int i = 0; i < nums.size() - 1 - 2; i++) {
            if (target > 0 && nums[i] >= target ||
                target == 0 && nums[i] > target) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            for (int j = i + 1; j < nums.size() - 1 - 1; j++) {
                if (target > 0 && nums[i] + nums[j] >= target ||
                    target == 0 && nums[i] + nums[j] > target) {
                    break;
                }
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;

                while (left < right) {
                    long long temp =
                        (long long)nums[i] + nums[j] + nums[right] + nums[left];
                    if (temp > target) {
                        right--;
                    } else if (temp < target) {
                        left++;
                    } else {
                        res_vec.push_back(
                            {nums[i], nums[j], nums[right], nums[left]});

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