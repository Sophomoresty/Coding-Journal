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
        ListNode *pre_head = new ListNode(); // 建立虚拟头指针
        pre_head->next = head;

        ListNode *current = pre_head;
        while (current->next != nullptr) {
            // 删除元素: 值存在相等 且 p->next不为空
            if (current->next->val == val) {
                ListNode *temp =
                    current->next; // 临时指向要被删除的指点, 要释放掉
                current->next = current->next->next; // 逻辑上删除指针
                delete temp;                         // 释放被删除的节点
            } else {
                current = current->next;
            }
        }
        // 修改后的头结点是虚拟节点的下一个节点
        ListNode *result = pre_head->next;

        // 释放虚拟节点内存
        delete pre_head;
        return result;
    }
};
// 辅助函数: 创建链表

ListNode *createList(const vector<int> &nums) {
    // 数组为空
    if (nums.empty()) {
        return nullptr;
    }
    ListNode *head = new ListNode(nums[0]);
    ListNode *current = head;
    for (size_t i = 1; i < nums.size(); ++i) {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}
// 辅助函数：打印链表
void printList(ListNode *head) {
    ListNode *current = head;
    while (current != nullptr) {
        cout << current->val << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}
int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 6, 3, 4, 5, 6};
    int val1 = 6;
    ListNode *head1 = createList(nums1);
    cout << "Original List 1: ";
    printList(head1);
    ListNode *modified_head1 = sol.removeElements(head1, val1);
    cout << "Modified List 1 (remove 6): ";
    printList(modified_head1);
    // deleteList(modified_head1); // 释放修改后链表的内存
    return 0;
}