#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    while (cin >> s) {
        int old_len = s.size();
        int count = 0;
        //
        // 1.统计字符中数字出现的次数
        for (auto i : s) {
            if (i >= '0' && i <= '9') {
                count++;
            }
        }
        // 2.每个数字都要替换成number, 也就以为着数组增加5*count
        s.resize(old_len + 5 * count);
        int new_len = s.size();

        // 用双指针遍历
        int left, right;
        for (left = old_len - 1, right = new_len - 1; left > -1; left--) {
            // left的内容是数字
            if (s[left] >= '0' && s[left] <= '9') {
                s[right--] = 'r';
                s[right--] = 'e';
                s[right--] = 'b';
                s[right--] = 'm';
                s[right--] = 'u';
                s[right--] = 'n';
            }
            // left的内容是非数字

            else {
                s[right--] = s[left];
            }
        }
        cout << s << endl;
    }
}