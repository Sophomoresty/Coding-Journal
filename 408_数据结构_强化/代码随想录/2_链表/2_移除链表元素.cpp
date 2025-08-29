// leetcode_203_移除链表的元素

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// 采用虚拟头结点

class Solution {
public:
    ListNode *removeElements(ListNode *head, int val) {
        // C创建结构体
        // struct ListNode *dummmy_head;
        // dummmy_head = (ListNode *)malloc(sizeof(ListNode));
        // c++创建结构体
        ListNode *dummy_head = new ListNode();
        dummy_head->next = head;
        ListNode *cur = dummy_head;
        // 找到目标节点, 并删除, 可能有多个, 故是循环
        while (cur->next != nullptr) {
            //找到目标节点
            if (cur->next->val == val) {
                // 1.保存被删除节点
                ListNode *temp;

                temp = cur->next;
                // 2.改指针
                cur->next = cur->next->next;
                // 释放该节点
                delete temp;
            }
            // 未找到
            else {
                cur = cur->next;
            }
        }
        ListNode *result = dummy_head->next;

        delete dummy_head;
        return result;
    }
};