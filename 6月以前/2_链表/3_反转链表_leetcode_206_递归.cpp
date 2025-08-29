#include <iostream>
#include <vector>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *node) : val(x), next(node) {}
};

class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        return reverse(pre, cur);
    }

private:
    ListNode *reverse(ListNode *pre, ListNode *cur) {
        // 递归结束条件
        if (cur == nullptr) {
            return pre;
        }
        ListNode *temp = cur->next;
        // 完成反转
        cur->next = pre;
        // 递归
        return reverse(cur, temp);
    }
};
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

    vector<int> nums1 = {1, 2, 3, 4, 5, 6};

    ListNode *head1 = createList(nums1);
    cout << "Orgigincal ListNode" << '\n';
    printList(head1);
    ListNode *head2 = sol.reverseList(head1);
    cout << "Modified ListNode" << '\n';
    printList(head2);

    return 0;
}