#include <stdio.h>
#include <unordered_map>
#include <vector>
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
private:
    // 创建一个inorder 值:索引 的哈希表
    unordered_map<int, int> inorder_vec_map;

    // 采取左闭右开的原则
    TreeNode *buildeTree_help(vector<int> &inorder, int i_start, int i_end,
                              vector<int> &postorder, int p_start, int p_end) {

        // 1.终止条件
        if (!(i_start < i_end && p_start < p_end)) {
            return nullptr;
        }

        // 2.创建根节点
        TreeNode *node = new TreeNode(postorder[p_end - 1]);

        // 3.确定中序分割点
        int node_inorder_index = inorder_vec_map[postorder[p_end - 1]];

        // 4.分割中序数组 左中右
        int i_start_left = i_start;
        int i_end_left = node_inorder_index;

        int i_start_right = node_inorder_index + 1;
        int i_end_right = i_end;
        ;

        // 5.分割后序数组 左右中

        int p_start_left = p_start;
        int p_end_left = p_start_left + i_end_left -
                         i_start_left; // 左闭右开的长度即是 左 - 右

        int p_start_right = p_end_left;
        int p_end_right = p_start_right + i_end_right - i_start_right;
        // 左子树
        node->left = buildeTree_help(inorder, i_start_left, i_end_left,
                                     postorder, p_start_left, p_end_left);
        // 右子树
        node->right = buildeTree_help(inorder, i_start_right, i_end_right,
                                      postorder, p_start_right, p_end_right);
        return node;
    }

public:
    // 参数 前序数组 和 后序数组
    // 返回 对应的树的根节点
    // 1.后序数组为0, 返回空节点
    // 2.后序数组最后一个元素为根节点元素, 创建根节点
    // 3.用根节点元素寻找中序数组的位置, 作为切割点 (这里可以用哈希表优化)
    // 4.切割中序数组
    // 5.切割后序数组
    // 6.递归处理做区间和右区间
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // 1.创建索引
        for (int i = 0; i < inorder.size(); i++) {
            inorder_vec_map[inorder[i]] = i;
        }

        return buildeTree_help(inorder, 0, inorder.size(), postorder, 0,
                               postorder.size());
    }
};

void inorder_traversal(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    inorder_traversal(root->left);
    printf("%d ", root->val);
    inorder_traversal(root->right);
}

int main() {
    Solution sol;
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode *root = sol.buildTree(inorder, postorder);
    printf("中序遍历结果\n");
    inorder_traversal(root);
    printf("\n中序遍历结果\n");
    return 0;
}