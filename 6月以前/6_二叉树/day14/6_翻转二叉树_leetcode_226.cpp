

#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    void swap_child(TreeNode *node) {
        TreeNode *temp = node->left;
        node->left = node->right;
        node->right = temp;
    }

    TreeNode *invertTree(TreeNode *root) {
        // 思路很简单, 层序遍历, 对每一层的节点, 调换左右孩子
        // 剪枝
        if (root == nullptr) {
            return root;
        }

        queue<TreeNode *> que;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();
            TreeNode *cur;
            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                // 调换左右孩子, 左右孩子一定存在, 要么为空, 要么为TreeNode*
                swap_child(cur);

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
        return root;
    }
};
