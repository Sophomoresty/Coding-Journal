#include <iostream>
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

// 采用优化版本
// 哈希表存储inorder
// 不用剪切, 而采用序号表示分割后的数组
class Solution {
private:
    // 值: 索引
    unordered_map<int, int> inorder_map;

    // 返回值: 由前序和后序数组构建的树的根节点
    // 3.确定中序数组的分割点
    // 4.分割中序数组
    // 5.分割前序数组
    // 6.单层递归
    // 区间规则: 左闭右开
    TreeNode *buildTree_help(const vector<int> &preorder, int p_start,
                             int p_end, const vector<int> &inorder, int i_start,
                             int i_end) {
        // 1.终止条件
        if (!(p_start < p_end && i_start < i_end)) {
            return nullptr;
        }

        // 2.创建根节点
        int val = preorder[p_start];
        TreeNode *node = new TreeNode(val);

        // 3.获取中序数组的分割索引
        int i_index = inorder_map[val];

        // 4.分割中序数组 -> 左子树的中序数组 右子树的中序数组
        // 左中右

        // 1) 左子树
        int i_start_left = i_start;
        int i_end_left = i_index;

        // 2) 右子树
        int i_start_right = i_index + 1;
        int i_end_right = i_end;

        // 5.分割前序数组 -> 左子树的前序数组 右子树的前序数组
        // 中左右

        // 1) 左子树
        int p_start_left = p_start + 1;
        int p_end_left = p_start_left + i_end_left - i_start_left;

        // 2) 右子树
        int p_start_right = p_end_left;
        int p_end_right = p_end;

        // 6.单层递归逻辑
        node->left = buildTree_help(preorder, p_start_left, p_end_left, inorder,
                                    i_start_left, i_end_left);

        node->right = buildTree_help(preorder, p_start_right, p_end_right,
                                     inorder, i_start_right, i_end_right);

        return node;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            inorder_map[inorder[i]] = i;
        }

        return buildTree_help(preorder, 0, preorder.size(), inorder, 0,
                              inorder.size());
    }
};

void print_by_preorder(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    cout << root->val << " ";
    print_by_preorder(root->left);
    print_by_preorder(root->right);
}

int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    Solution sol;
    cout << "由前序和中序数组构建的树的前序遍历结果\n";
    print_by_preorder(sol.buildTree(preorder, inorder));
    cout << '\n';

    cout << "原前序数组\n";
    for (auto i : preorder) {
        cout << i << " ";
    }
    cout << '\n';
}
