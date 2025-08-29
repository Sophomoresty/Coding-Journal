#include <cstddef>
#include <ratio>
#include <stack>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        if (nums.empty()) {
            return nullptr;
        }
        stack<TreeNode *> st;
        for (int i = 0; i < nums.size(); i++) {
            TreeNode *cur = new TreeNode(nums[i]);

            // 左孩子
            while (!st.empty() && st.top()->val < cur->val) {
                TreeNode *p = st.top();
                st.pop();
                cur->left = p;
            }
            // 右孩子
            if (!st.empty()) {
                TreeNode *t = st.top();
                t->right = cur;
            }
            st.push(cur);
        }

        TreeNode *root = nullptr;
        while (!st.empty()) {
            root = st.top();
            st.pop();
        }
        return root;
    }
};

int main() {
    vector<int> nums = {1, 3, 2, 6, 4, 5};
    //      6
    //   3      5
    // 1   2  4
    // 前序遍历结果: 6 3 1 2 5 4
    Solution sol;
    TreeNode *root = sol.constructMaximumBinaryTree(nums);
}