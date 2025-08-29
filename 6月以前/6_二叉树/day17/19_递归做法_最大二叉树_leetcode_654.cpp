#include <iostream>
#include <queue>
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
    // 采取左闭右开
    TreeNode *constructMaximumBinaryTree_help(const vector<int> &nums,
                                              int start, int end) {
        // 1.终止条件, 数组为空
        if (start >= end) {
            return nullptr;
        }

        // 2.寻找最大值及其索引, 这里时间复杂度有点高, 特别是递归多次的话, 能否优化
        int max = nums[start];
        int max_index = start;
        for (int i = start; i < end; i++) {
            if (nums[i] > max) {
                max = nums[i];
                max_index = i;
            }
        }

        // 3.创建节点
        TreeNode *node = new TreeNode(max);
        // 4.分割数组
        // 1) 左子树
        int start_left = start;
        int end_left = max_index;

        // 2) 右子树
        int start_right = max_index + 1;
        int end_right = end;

        // 5.递归处理
        node->left =
            constructMaximumBinaryTree_help(nums, start_left, end_left);
        node->right =
            constructMaximumBinaryTree_help(nums, start_right, end_right);
        return node;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return constructMaximumBinaryTree_help(nums, 0, nums.size());
    }
};

vector<int> levorder_traversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    queue<TreeNode *> que;
    que.push(root);

    while (!que.empty()) {
        TreeNode *cur = que.front();
        que.pop();
        if (cur != nullptr) {
            res.push_back(cur->val);
            que.push(cur->left);
            que.push(cur->right);
        } else {
            res.push_back(-1);
        }
    }
    return res;
}

int main() {
    vector<int> nums = {3, 2, 1, 6, 0, 5};
    Solution sol;

    vector<int> res = levorder_traversal(sol.constructMaximumBinaryTree(nums));
    cout << "[";
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i != res.size() - 1) {
            cout << ',';
        }
    }

    cout << "]\n";
    return 0;
}