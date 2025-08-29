#include <iostream>
#include <unordered_set>
using namespace std;
class Solution {
public:
    int get_sum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n = n / 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> res_set;
        int sum;
        while (true) {
            sum = get_sum(n);
            cout << sum;
            if (sum == 1) {
                cout << '\n';
                return true;
            }
            if (res_set.find(sum) != res_set.end()) {
                cout << '\n';
                return false;
            } else {
                res_set.insert(sum);
            }
            cout << " -> ";
            n = sum;
        }
    }
    // 快慢指针法
    // 因为无解的情况下, 会陷入循环, 陷入循环的情况下,
    // 如果快指针和慢指针同时出发, 快指针一定会套圈, 追上慢指针 比如 2 -> 4 ->
    // 16 -> 37 -> 58 -> 89 -> 145 -> 42 -> 20 -> 4 有解的情况下, 没有循环 比如
    // 1 -> 1 -> 1
    // 19 -> 82 -> 68 -> 100 -> 1
    // 19    68
    // 19 82 100 1 1
    bool better_isHappy(int n) {

        int slow, fast;
        // 初始化

        slow = get_sum(n);
        fast = get_sum(n);
        fast = get_sum(fast);

        if (fast == 1) {
            return true;
        }

        // 也就是无解的情况下, 一定会退出循环, 有解的情况下, 快指针一定为1
        while (fast != slow) {

            if (fast == 1) {
                return true;
            }
            slow = get_sum(slow);
            fast = get_sum(fast);
            fast = get_sum(fast);
        }
        return false;
    }
    bool better_2_isHappy(int n) {
        int fast, slow;
        fast = slow = n;
        // // 初始化
        // slow = get_sum(slow);
        // fast = get_sum(fast);
        // fast = get_sum(fast);
        // 快指针和慢指针在哪种情况下都会相遇, 无解的情况下相遇的值不为1,
        // 有解的情况相遇的值为1
        do {
            slow = get_sum(slow);
            fast = get_sum(fast);
            fast = get_sum(fast);
        } while (fast != slow);

        return slow == 1;
    }
};

int main() {
    Solution sol;
    int n;
    cin >> n;
    cout << n << " -> ";
    sol.isHappy(n);
}