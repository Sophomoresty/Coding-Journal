#include <algorithm>
#include <limits>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 采用前序遍历
    int min_depth_overall; //全局变量, 存储最小的深度
    // min_depth_path 表示当前路径下的最小深度
    void min_depth(TreeNode *node, int current_depth_path) {
        // 1.终止条件 处理空节点
        if (node == nullptr) {
            return;
        }

        // 2.终止条件 处理叶子节点, 更新最小深度
        if (node->left == nullptr && node->right == nullptr) {
            min_depth_overall = min_depth_overall < current_depth_path
                                    ? min_depth_overall
                                    : current_depth_path;
            // 找到叶子节点, 当前路径的深度已确定, 不需要向下
            return;
        }
        // 3.递归到左右子树
        min_depth(node->left, current_depth_path + 1);
        min_depth(node->right, current_depth_path + 1);
    }

    int minDepth_preorder(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        // 初始化为最大值
        min_depth_overall = numeric_limits<int>::max();
        min_depth(root, 1);
        return min_depth_overall;
    }

    // 采用后序遍历
    int minDepth_postorder(TreeNode *root) {
        // 1.递归终止条件 处理空节点
        if (root == nullptr) {
            return 0;
        }

        // 2.递归获取左右子树的最小深度
        int left_min_depth = minDepth_postorder(root->left);
        int right_min_depth = minDepth_postorder(root->right);

        // 3.处理当前节点
        if (root->left == nullptr) {
            return right_min_depth + 1;
        }
        if (root->right == nullptr) {
            return left_min_depth + 1;
        }
        return min(left_min_depth, right_min_depth) + 1;
    }
};
