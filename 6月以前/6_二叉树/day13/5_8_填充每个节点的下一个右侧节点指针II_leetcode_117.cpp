#include <queue>
using namespace std;
class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    void levelorder_traversal_v2(Node *root) {
        if (root == nullptr) {
            return;
        }
        queue<Node *> que;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();
            Node *cur;
            // i不是该层的最后一个, 都指向下一个节点
            // i是该层的最后一个, 指向空节点, 默认值是空, 不需要额外指定

            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                if (i < size - 1) {
                    cur->next = que.front();
                }

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
    }
    Node *connect(Node *root) {
        levelorder_traversal_v2(root);
        return root;
    }
};