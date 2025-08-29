#include <stack>
#include <string>
using namespace std;

class Solution {
public:
        bool isValid_v2(string s) {
        stack<char> stack_char;

        // 1.剪枝
        if (s.size() % 2 != 0) {
            return false;
        }
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stack_char.push(')');
            } else if (s[i] == '{') {
                stack_char.push('}');
            } else if (s[i] == '[') {
                stack_char.push(']');
            }
            // 处理右括号
            else{
                // 栈为空
                if(stack_char.empty()){
                    return false;
                }
                // 栈非空
                else if (s[i] ==stack_char.top()){
                    stack_char.pop();
                }
                else if(s[i]!=stack_char.top()){
                    return false;
                }
            }
        }
        // 循环结束后, 如果栈非空, 返回false
        return stack_char.empty();
    }
    bool isValid(string s) {
        stack<char> stack_char;

        // 1.剪枝
        if (s.size() % 2 != 0) {
            return false;
        }
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stack_char.push(')');
            } else if (s[i] == '{') {
                stack_char.push('}');
            } else if (s[i] == '[') {
                stack_char.push(']');
            }

            // 右括号, 情况1 栈顶的符号相同
            else if (!stack_char.empty() && s[i] == stack_char.top()) {
                stack_char.pop();
            }
            // 右括号, 情况2 栈顶的符号不相同
            else if (!stack_char.empty() && s[i] != stack_char.top()) {
                return false;
            }
            // 栈为空
            else if(stack_char.empty()){
                return false;
            }
        }
        // 循环结束后, 如果栈非空, 返回false
        return stack_char.empty();
    }
};