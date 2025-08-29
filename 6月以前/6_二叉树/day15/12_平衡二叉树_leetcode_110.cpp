#include <algorithm>
#include <cstdlib>
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
    int get_height_postorder(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int left_height = get_height_postorder(root->left);
        if (left_height == -1) {
            return -1;
        }
        int right_height = get_height_postorder(root->right);
        if (right_height == -1) {
            return -1;
        }

        if (abs(left_height - right_height) > 1) {
            return -1;
        }
        return max(left_height, right_height) + 1;
    }

    bool isBalanced(TreeNode *root) { return get_height_postorder(root) != -1; }
};
