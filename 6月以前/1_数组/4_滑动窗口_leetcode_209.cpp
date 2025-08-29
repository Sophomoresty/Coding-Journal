#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int result = INT_MAX; // 最小区间, 初始值为最大值
        int i, j;
        i = j = 0;
        int sum = 0;
        for (; j < int(nums.size()); j++) {
            sum += nums[j];
            // 满足条件后, 更新长s度,
            // j静止, 移动i
            while (sum >= target) {
                int length = j - i + 1;
                result = result < length ? result : length; // 长度取最小值
                sum -= nums[i];
                i++;
            }
        }

        return result < __INT_MAX__ ? result : 0;
    }
};

int main() {
    vector<int> test = {1, 1, 1, 98};
    int target = 100;
    Solution s;
    int result = s.minSubArrayLen(target, test);

    cout << result << endl;
}