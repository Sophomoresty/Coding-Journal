#include <algorithm>
using namespace std;

// 用递归法完成
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int max_depth_overall; // 全局变量, 表示最大深度
    // 前序: 根左右,是自顶向下的

    void get_max_height_preorder(TreeNode *root, int cur_path_depth) {
        // 1.终止条件
        if (root == nullptr) {
            return;
        }
        // 2.递归
        // 根
        max_depth_overall = max(max_depth_overall, cur_path_depth);

        // 遍历左子树, 更新最大深度
        get_max_height_preorder(root->left, cur_path_depth + 1);
        // 遍历右子树, 更新最大深度
        get_max_height_preorder(root->right, cur_path_depth + 1);
    }

    int maxDepth_preorder(TreeNode *root) {
        max_depth_overall = 0;
        if (root == nullptr) {
            return 0;
        }
        get_max_height_preorder(root, 1);
        return max_depth_overall;
    }

    int maxDepth_postorder(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int left_height = maxDepth_postorder(root->left);
        int right_height = maxDepth_postorder(root->right);

        return max(left_height, right_height) + 1;
    }
};
