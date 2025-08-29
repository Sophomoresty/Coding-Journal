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
    ListNode *swapPairs(ListNode *head) {
        ListNode *pre_head = new ListNode();
        pre_head->next = head;
        ListNode *cur = pre_head;

        while (cur->next != nullptr && cur->next->next != nullptr) {
            ListNode *temp1 = cur->next->next;       // 2
            ListNode *temp2 = cur->next->next->next; // 3
            cur->next->next->next = cur->next;       // 2->1
            cur->next = temp1;                       // 头->2 => 头->2->1
            cur->next->next->next = temp2;           // 1->3 => 头->2->1->3;
            cur = cur->next->next;
        }
        head = pre_head->next;
        delete pre_head;
        return head;
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
    ListNode *head2 = sol.swapPairs(head1);
    cout << "Modified ListNode" << '\n';
    printList(head2);

    return 0;
}