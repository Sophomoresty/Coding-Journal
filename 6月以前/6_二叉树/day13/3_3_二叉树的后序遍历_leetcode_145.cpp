#include <algorithm>
#include <stack>
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
public:
    void postorder_traversal(TreeNode *root, vector<int> &vec_res) {
        if (root == nullptr) {
            return;
        }
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode *cur = st.top();
            st.pop();
            vec_res.push_back(cur->val);
            if (cur->left != nullptr) {
                st.push(cur->left);
            }
            if (cur->right != nullptr) {
                st.push(cur->right);
            }
        }
        reverse(vec_res.begin(), vec_res.end());
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> vec_res;
        postorder_traversal(root, vec_res);
        return vec_res;
    }
};