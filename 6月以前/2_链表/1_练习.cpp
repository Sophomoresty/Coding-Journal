#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode *removeElements(ListNode *head, int val) {
        ListNode *pre_head = new ListNode();
        pre_head->next = head;
        ListNode *cur = pre_head;
        while (cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode *temp =
                    cur->next; // 临时指针, 帮助删除空间,
                               // 栈结束后temp会自动销毁, 不需要设置指向空
                cur->next = cur->next->next; // 逻辑上删除
                delete temp;                 // 清除空间
                // 删除的情况下, cur不需要移动
            } else {
                cur = cur->next;
            }
        }
        // 遍历循环结束, 删除该删除的节点
        //  删除后的头结点
        head = pre_head->next;
        // 虚拟头结点记得释放空间感!!
        delete pre_head;
        return head;
    }
};

// 建立链表
// Type& (非 const 引用): 当你需要函数修改原始变量时使用（值传递做不到）。
// const Type& (常量引用):
// 当你只需要函数读取原始变量，并且想避免对象拷贝提高效率时使用（值传递会创建拷贝，指针则需要手动解引用）。
ListNode *creat_list_node(const vector<int> &nums) {
    if (nums.empty()) {
        return nullptr;
    }
    ListNode *head = new ListNode(nums[0]);
    ListNode *current = head;
    for (size_t i = 0; i < nums.size(); i++) {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}

// 打印链表

void printlist(ListNode *head) {
    ListNode *current = head;
    while (current != nullptr) {
        cout << current->val << " -> " ;
        current = current->next;
    }
    cout << "nullptr" << '\n';
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 3, 4, 6};
    int target = 3;
    Solution sol;
    ListNode *head = creat_list_node(nums);
    // orgin_list
    cout << "orgin_list" << '\n';
    printlist(head);
    ListNode *new_head = sol.removeElements(head, target);
    cout << "modified_list" << '\n';
    printlist(new_head);
    return 0;
}