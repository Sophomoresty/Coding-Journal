struct ListNode {
    int val;
    struct ListNode *next;
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

    int get(int index) {
        // index: 0-_size-1
        if (index < 0 || index > _size - 1) {
            return -1;
        }
        ListNode *cur = dummy_head;
        for (int i = 0; i < index + 1; i++) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        ListNode *temp = new ListNode(val);
        temp->next = dummy_head->next;
        dummy_head->next = temp;
        _size++;
    }

    void addAtTail(int val) {
        ListNode *temp = new ListNode(val);
        ListNode *cur = dummy_head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = temp;
        _size++;
    }

    void addAtIndex(int index, int val) {
        // index<0 插入到头
        // index>_size 返回
        // index==size 插入到尾
        // index:0-_size-1 找到index前一个节点插入
        if (index > _size) {
            return;
        }

        if (index < 0) {
            addAtHead(val);
            return;
        }
        if (index == _size) {
            addAtTail(val);
            return;
        }

        ListNode *temp = new ListNode(val);
        ListNode *cur = dummy_head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        temp->next = cur->next;
        cur->next = temp;
        _size++;
    }

    void deleteAtIndex(int index) {
        // index:0-_size-1
        if (index < 0 || index > _size - 1) {
            return;
        }
        ListNode *cur = dummy_head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        ListNode *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        _size--;
    }
    ~MyLinkedList() {
        ListNode *cur = dummy_head;
        while (cur != nullptr) {
            ListNode *temp = cur;
            cur = cur->next;
            delete temp;
        }
        _size = 0;
    }
};