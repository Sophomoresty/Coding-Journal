// leetcode_707_设计链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class MyLinkedList {
private:
    // 定义基础变量
    ListNode *dummy_head;
    int _size;

public:
    // 初始化函数
    MyLinkedList() {
        dummy_head = new ListNode();
        _size = 0;
    }
    //
    int get(int index) {
        // 合法性判断
        if (index < 0 || index > _size - 1) {
            return -1;
        }
        // 遍历节点, 找到第n个节点
        // 从头节点开始
        // 先把之前错误的思路修正过来, 循环的判断变量和循环内部的变量的对应关系是, 循环变量的初始值对应当前循环执行后循环内部的变量值
        ListNode *cur = dummy_head->next;
        // cur和i的对应关系, 第一次进入循环, cur执行后执行第1个节点, 为了便于后面边界条件的确定, i和cur保持一致
        // 边界条件一般思考到最后一次执行时的i和cur, 和下一次不能执行的i即可
        // 最后一次执行: cur执行index个, i=index, 下一次不能执行i=index+1, 故可执行的i<index+1
        for (int i = 1; i < index + 1; i++) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        // 不需要边界检查
        // 建立新节点, 用指针指向
        ListNode *temp = new ListNode(val);
        temp->next = dummy_head->next;
        dummy_head->next = temp;
        _size++;
    }

    void addAtTail(int val) {
        // 不需要边界检查
        // 创建永久节点, malloc和new, 都是返回结构体指针
        ListNode *temp = new ListNode(val);
        // 找到最后一个节点
        ListNode *cur = dummy_head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = temp;
        _size++;
        return;
    }

    void addAtIndex(int index, int val) {
        // index的合法性
        // index的合法取值0-_size-1, 这里的操作是一样的
        // index=_size, 即插入尾部
        // index<0 || i>_size 不合法

        // 这里实际前面的if和else if都可以写出if, 用if的递进表达, 最后一个else去掉
        // 这里是为了逻辑的严密
        if (index < 0 || index > _size) {
            return;
        } else if (index == _size) {
            addAtTail(val);
        } else {
            ListNode *temp = new ListNode(val);
            // 1.找到index-1的结构体指针
            // 2.插入节点, 插入和删除都需要注意顺序
            // 定义遍历指针
            // 这里也是要抓出循环变量和循环体变量的对应关系, 前面是从头节点开始
            // 这里从虚拟头节点开始, 练习逻辑挂你先
            ListNode *cur = dummy_head;
            // 第一次执行, 执行后cur指向第0个节点, 所以循环变量i初值与其对应,为0
            // 最后一次执行, cur指向index-1个节点, i为index-1
            // 下一次不能指向i为i<index, 故i<index
            for (int i = 0; i < index; i++) {
                cur = cur->next;
            }
            temp->next = cur->next;
            cur->next = temp;
            _size++;
        }
    }

    void deleteAtIndex(int index) {
        // index有效值0-_size-1
        if (index < 0 || index > _size - 1) {
            return;
        }

        //  要考虑下面的删除的通用操作, 对边界节点有没有问题
        // 1.尾节点,和一般节点处理相同
        // 2.头节点, index为0, 不会进入循环体, cur为虚拟头节点, 没问题.

        // 前面cur可以取头节点, 但是在插入和删除的时候, 为了考虑操作的普适性,cur必须从虚拟头节点出发
        // 如果选择从头节点出发, 那处理头节点需要单独处理, 就丧失了虚拟头节点的优越性.

        // 找到index-1的指针
        // 2.删除index指针: 1)保存index指针 2)index-1指针指向index的下一个 3)释放堆上的index的结构体
        ListNode *cur = dummy_head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        ListNode *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        _size--;
    }
    // 类调用结束后的处理函数
    // 问题是什么时候叫类调用结束? 类好像没有delete吧?
    // 栈上的类调用结束后自动调用析构函数
    // 堆上的类delete时会调用析构函数
    ~MyLinkedList() {
        ListNode *cur = dummy_head;
        // 删除所有节点, cur作为删除节点的前一个节点的指针
        // cur实际不用动
        while (cur->next != nullptr) {
            ListNode *temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        }
        _size = 0;
    }
};
