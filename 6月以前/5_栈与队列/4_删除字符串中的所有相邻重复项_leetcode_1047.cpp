#include <algorithm>
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    string removeDuplicates_v2(string s) {
        // 利用字符串作为栈
        string stack_char;

        // 通过字符栈可以达到删除的目的, 关键是如何顺序输出
        for (int i = 0; i < s.size(); i++) {
            // 字符栈为空
            if (stack_char.empty()) {
                stack_char.push_back(s[i]);
            }
            // 字符栈非空
            else {
                if (s[i] != stack_char.back()) {
                    stack_char.push_back(s[i]);
                } else {
                    stack_char.pop_back();
                }
            }
        }
        return stack_char;
        
    }

    string removeDuplicates_v1(string s) {
        stack<char> stack_char;

        // 通过字符栈可以达到删除的目的, 关键是如何顺序输出
        for (int i = 0; i < s.size(); i++) {
            // 字符栈为空
            if (stack_char.empty()) {
                stack_char.push(s[i]);
            }
            // 字符栈非空
            else {
                if (s[i] != stack_char.top()) {
                    stack_char.push(s[i]);
                } else {
                    stack_char.pop();
                }
            }
        }
        string result = "";
        while (!stack_char.empty()) {
            result += stack_char.top();
            stack_char.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};