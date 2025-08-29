struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 原始错误
// 循环嵌套需要初始化curB, 此前没有初始化curB
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 0个节点
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }

        // 暴力解法, 同时遍历A和B, 有个相等时即return
        ListNode *curA = headA;

        while (curA != nullptr) {
            ListNode *curB = headB; // 注意要初始化
            while (curB != nullptr) {
                if (curA == curB) {
                    return curA;
                }
                curB = curB->next;
            }
            curA = curA->next;
        }
        return nullptr;
    }
};
