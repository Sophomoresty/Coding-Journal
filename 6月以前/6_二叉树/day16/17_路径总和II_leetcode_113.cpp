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
    void pre_traversal(TreeNode *root, vector<int> &path, int targetSum,
                       vector<vector<int>> &result_paths) {
        // 终止条件1
        if (root == nullptr) {
            return;
        }
        path.push_back(root->val);
        // 终止条件2
        if (root->left == nullptr && root->right == nullptr &&
            targetSum == root->val) {
            result_paths.push_back(path);
        }
        pre_traversal(root->left, path, targetSum - root->val, result_paths);
        pre_traversal(root->right, path, targetSum - root->val, result_paths);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        vector<vector<int>> result_paths;
        if (root == nullptr) {
            return result_paths;
        }

        vector<int> current_path;
        pre_traversal(root, current_path, targetSum,result_paths);
        return result_paths;
    }
};