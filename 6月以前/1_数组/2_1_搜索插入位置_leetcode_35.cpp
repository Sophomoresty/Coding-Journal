#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        int left, right;
        left = 0;
        right = int(nums.size()) - 1;
        while (left <= right) {
            size_t mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 6};
    int target = 0;
    Solution s;
    int loc = s.searchInsert(nums, target);
    cout << loc << '\n';
    return 0;
}