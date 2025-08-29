#include <queue>
using namespace std;

class MyStack {
queue<int> queue_stack;
public:
    MyStack() {
    }
    
    void push(int x) {
        queue_stack.push(x);
    }
    // 弹出栈的元素, 用queue实现
    // 1.弹出queue的size-1个元素, 再push进去
    // 2.弹出元素
    int pop() {
        int size = queue_stack.size();
        size--;
        while(size--){
            int temp = queue_stack.front();
            queue_stack.pop();
            queue_stack.push(temp);
        }
        int res = queue_stack.front();
        queue_stack.pop();
        return res;
    }
    
    int top() {
        return queue_stack.back();
    }
    
    bool empty() {
        return queue_stack.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */