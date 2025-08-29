#include <vector>
using namespace std;

class Solution {
public:
    // 滑动窗口思路
    // 窗口初始化起点和终点为0
    // 先移动end, 直到窗口内的和>target
    // 开始移动起点, 直到和<taget
    int minSubArrayLen(int target, vector<int> &nums) {
        int result = 0x7FFFFFFF; // 4B
        // result保存最后的子序列最小值
        int start = 0, end = 0;
        int sum = 0;
        // sum记录窗口总和
        for (; end < nums.size(); end++) {
            sum += nums[end];
            // 开始缩减窗口
            while (sum >= target) {
                // 更新最小序列长度
                int sub_length = end - start + 1;
                result = result <= sub_length ? result : sub_length;
                // 缩减窗口, 开始移动起始点
                sum = sum - nums[start++];
            }
        }
        // 返回最小子序列长度
        // 这里要做一个合法性判断, 即最大窗口的值仍然小于target, 这种情况result为最大值
        return result == 0x7FFFFFFF ? 0 : result;
    }
};