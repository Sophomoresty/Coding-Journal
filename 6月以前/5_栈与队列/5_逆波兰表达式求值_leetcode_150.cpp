#include <stack>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> stack_eval;
        for (int i = 0; i < tokens.size(); i++) {
            // 符号, 栈中取出两个元素, 进行运算, 加入到stack_eval
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
                tokens[i] == "/") {
                int res;
                int num2 = stack_eval.top();
                stack_eval.pop();
                int num1 = stack_eval.top();
                stack_eval.pop();
                if (tokens[i] == "+") {
                    res = num1 + num2;
                }
                if (tokens[i] == "-") {
                    res = num1 - num2;
                }
                if (tokens[i] == "*") {
                    res = num1 * num2;
                }
                if (tokens[i] == "/") {
                    res = num1 / num2;
                }
                stack_eval.push(res);
            }
            // 数字, 加入栈
            else {
                stack_eval.push(stoi(tokens[i]));
            }
        }
        return stack_eval.top();
    }
};