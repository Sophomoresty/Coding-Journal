#include <string>

using namespace std;

class Solution {
public:
    void swapString(string &s, int left, int right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
    }
    // 反转left到right的字符串, 是闭区间
    void reverseString(string &s, int left, int right) {
        for (; left < right; left++, right--) {
            swapString(s, left, right);
        }
    }

    string reverseStr(string s, int k) {

        for (int i = 0; i < s.size(); i += 2 * k) {
            // 反转前k个, 条件是i+k不超出s.size()

            if (i + k < s.size()) {
                this->reverseString(s, i, i + k - 1);
            }
            // 如果剩下的没有k个, 反转剩下的
            else {
                this->reverseString(s, i, s.size() - 1);
            }
        }
        return s;
    }
};