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

// 层序遍历
class Solution {
public:
    int levelorder_traversal(TreeNode *root) {
        // root非空
        queue<TreeNode *> que;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();
            // 优化点：每次进入新的一层，当前层的第一个元素就是最左节点
            int res_val = que.front()->val; // 初始化
            for (int i = 0; i < size; i++) {
                TreeNode *cur = que.front();
                que.pop();
                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
        // 返回最后一层的第1个元素
    }

    int findBottomLeftValue_none_recursion(TreeNode *root) {
        return levelorder_traversal(root);
    }
    // 树的最大深度
    int max_depth_all;
    // 最后的结果
    int bottom_left_value;
    void preorder_traversal(TreeNode *root, int cur_path_depth) {
        // 终止条件1: 空节点
        if (root == nullptr) {
            return;
        }
        // 终止条件2: 叶子节点
        if (root->left == nullptr && root->right == nullptr) {
            // 如果当前深度大于max_depeht_all的话, 就要更新值
            if (cur_path_depth > max_depth_all) {
                max_depth_all = cur_path_depth;
                bottom_left_value = root->val;
            }
        }
        preorder_traversal(root->left, cur_path_depth + 1);
        preorder_traversal(root->right, cur_path_depth + 1);
    }
    int findBottomLeftValue_recursion(TreeNode *root) {
        max_depth_all = 0;
        preorder_traversal(root, 1);
        return bottom_left_value;
    }
};