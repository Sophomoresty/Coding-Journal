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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // 删除一定要注意, 删除头结点的情况, 空表的情况,
        // 题目回缩了sz>=1

        // n如果不合法怎么办

        // 建立虚拟头结点
        ListNode *pre_head = new ListNode();
        pre_head->next = head;

        ListNode *fast, *slow;
        fast = slow = pre_head;

        // fast先走n步
        for (int i = 1; i <= n; i++) {
            fast = fast->next;
        }

        while (fast->next != nullptr) {

            fast = fast->next;
            slow = slow->next;
        }
        ListNode *temp = slow->next;
        slow->next = slow->next->next;
        delete temp;
        // 交换头结点
        head = pre_head->next;
        delete pre_head;
        return head;
    }
};

// 辅助函数：创建链表
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

    vector<int> nums1 = {1,2};
    int val = 1;
    ListNode *head1 = createList(nums1);
    cout << "Orgigincal ListNode" << '\n';
    printList(head1);
    ListNode *head2 = sol.removeNthFromEnd(head1, val);
    cout << "Modified ListNode" << '\n';
    printList(head2);

    return 0;
}