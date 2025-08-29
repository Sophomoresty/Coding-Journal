struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/*
双指针法2

设A独有的长度为a, 和B相同的部分为c
设B独有长度为b, 和A相同的部分为c
让A,B链表拼接在一起
1. A,B有相同的部分
curA从A端出发, curB从B端出发,
curA 第一次到达相同部分, 移动的距离是a-1
curA 第二次到达相同部分, 移动的距离是a+c-1+b
curB 第一次到达相同的部分, 移动的距离是b-1
curB 第二次到达相同的部分, 移动的距离是b+c-1+a
即A,B有相同的部分, 它们一定会移动相同的距离 a+b+c-1, 遇到第一个相等的对象
2. A, 没有相同的部分
A,B会走完全程, 遇到1个相等的对象 nullptr

总结:
通过让两个指针走的总路程相等(LA+LB)，它们一定会在某个时刻相遇。
而这个相遇点，必然是它们第一次同时到达的、在两条“加长”路径上具有相同相对位置的那个点，也就是
相交点（如果存在的话），或者最终的 nullptr（如果不相交的话）。
*/

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB)
            return nullptr;

        ListNode *curA, *curB;
        curA = headA;
        curB = headB;
        // 循环退出条件, curA,curB
        while (curA != curB) {

            curA = curA == nullptr ? headB : curA->next;
            curB = curB == nullptr ? headA : curB->next;
        }

        return curA;
    }
};