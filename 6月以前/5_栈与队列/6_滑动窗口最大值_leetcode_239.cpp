/*
滑动窗口主循环的终止条件错误：
原始条件： for (int i = 1; i + k < nums.size() - 1; i++)
问题： 这个条件导致循环提前结束。它未能处理到数组中的最后一个滑动窗口。
正确理解： 当 i 作为滑动窗口的起始索引时，它应该从
1（第二个窗口的起始）一直迭代到 nums.size() - k（最后一个窗口的起始）。
正确的条件： for (int i = 1; i <= nums.size() - k; i++)
*/
#include <deque>
#include <vector>
using namespace std;


// 构造一个单调队列,
class Solution {
private:
    deque<int> deque_k;

    // pop函数, 如果出口处的值和val相等, 则弹出
    void pop_k(int val) {
        if (!deque_k.empty() && val == deque_k.front()) {
            deque_k.pop_front();
        }
    }

    // push函数, 要弹出比val小的元素, 然后加入val
    void push_k(int val) {
        // 弹出比val小的元素
        while (!deque_k.empty() && deque_k.back() < val) {
            deque_k.pop_back();
        }
        deque_k.push_back(val);
    }

    // get_max_value
    int get_max_value() { return deque_k.front(); }

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> vec_res;
        // 剪枝
        if (nums.size() < k) {
            return vec_res;
        }
        // 循环最好先初始化
        for (int i = 0; i < k; i++) {
            push_k(nums[i]);
        }

        vec_res.push_back(get_max_value());

        for (int i = 1; i <= nums.size() - k; i++) {
            pop_k(nums[i - 1]);
            push_k(nums[i + k - 1]);
            vec_res.push_back(get_max_value());
        }

        return vec_res;
    }
};