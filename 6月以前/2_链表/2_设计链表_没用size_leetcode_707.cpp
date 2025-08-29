// 定义链表
struct LinkNode {
    int val;
    struct LinkNode *next;
    // 构造函数体
    LinkNode() : val(0), next(nullptr) {}
    LinkNode(int x) : val(x), next(nullptr) {}
    LinkNode(int x, LinkNode *node) : val(x), next(node) {}
};

class MyLinkedList {
private:
    int _size;
    LinkNode *_dummyHead;
    LinkNode *_tail;

public:
    // 虚拟头结点的序号记为-1, 头结点记为0
    MyLinkedList() {
        _size = 0;
        _dummyHead = new LinkNode();
        _tail = new LinkNode();
        // tail节点, 一直指向最后1个节点
    }

    int get(int index) {
        // 判断是否有效 index
        if (index < 0 || index > _size - 1) {
            return -1;
        }
        LinkNode *cur = _dummyHead;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->val;
    }
    // tail节点不用动
    void addAtHead(int val) {
        LinkNode *new_node = new LinkNode(val);
        new_node->next = _dummyHead->next;
        _dummyHead->next = new_node;
        _size++;
    }

    void addAtTail(int val) {}

    void addAtIndex(int index, int val) {}

    void deleteAtIndex(int index) {}
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */