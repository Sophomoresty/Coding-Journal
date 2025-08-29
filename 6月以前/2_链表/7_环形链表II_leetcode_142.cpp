struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *node) : val(x), next(node) {}
};
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // 处理边界 0个和1个
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }

        ListNode *slow, *fast;
        slow = fast = head;
        // 有环的情况下, fast和 slow相遇
        // 无环的情况下, fast和 slow不相遇

        // 退出循环即代表无环
        // 退出循环条件没考虑到如果是无环奇数个
        // 无环奇数个的情况下, fast会走到倒数第1个, fast->next= null,
        // 再访问属性,就报错了
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            // 二者相遇
            // 要返回入口
            if (slow == fast) {
                ListNode *index1 = head; // 从头出发的点
                ListNode *index2 = fast; // 相遇的点
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2;
            }
        }
        // 无环
        return nullptr;
    }
};
