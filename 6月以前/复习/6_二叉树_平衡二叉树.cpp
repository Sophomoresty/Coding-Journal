#include <algorithm>
#include <cmath>

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
    // 1.参数和承诺
    // 承诺:
    // 1)如果子树平衡, 则返回高度
    // 2)不平衡返回-1

    // 2.基本情况
    // root为根节点, 返回0

    // 3.假设子问题已经解决如何处理本层

    // 4.信息流向 自底向上

    int get_height_and_balance(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int left_info = get_height_and_balance(root->left);
        int right_info = get_height_and_balance(root->right);

        if (left_info == -1 || right_info == -1) {
            return -1;
        }

        if (std::abs(left_info - right_info) > 1) {
            return -1;
        }

        return std::max(left_info, right_info) + 1;
    }

    bool isBalanced(TreeNode *root) {
        return get_height_and_balance(root) != -1;
    }
};