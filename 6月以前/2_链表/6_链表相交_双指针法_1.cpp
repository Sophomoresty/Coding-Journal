struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
// 双指针法1
// 把链表想象为一根绳子, 让绳子右端点对齐
// 1.分别遍历A,B两个链表, 得出A,B的长度
// 2.让长链表的初始指针移动到, 和短链表初始指针对齐

// 本次题暴露了自己循环体理解的问题, while和for是等价的
// 理解循环体, 一般是建立对应关系
// 对应关系的建立: 本次循环体刚进来的判别的对象 和 对应的变化值

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 处理长度为0的情况
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }

        // 1. 计算链表长度
        // 链表的索引从0开始
        ListNode *curA, *curB;
        curA = headA;
        int len_A, len_B;
        len_A = 0;
        len_B = 0;
        // curA是判别对象
        while (curA != nullptr) {
            curA = curA->next;
            len_A++;
            // 索引 0 -> 长度 1, 正确
        }

        curB = headB;
        while (curB != nullptr) {
            curB = curB->next;
            len_B++;
        }

        // 2. 重置指针
        curA = headA;
        curB = headB;
        // 3. 将长链表的指针向前移动长度差的步数进行对齐
        if (len_A > len_B) {
            // 从0移动到LA-LB,步数为LA-LB
            for (int i = 1; i <= (len_A - len_B); i++) {
                curA = curA->next;
            }
        }
        if (len_A < len_B) {
            for (int i = 1; i <= (len_B - len_A); i++) {
                curB = curB->next;
            }
        }
        // 现在curA和curB在同一起点, 同时出发

        while (curA != nullptr && curB != nullptr) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }
};
