#include <queue>
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
    int countNodes(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        queue<TreeNode *> que;
        que.push(root);
        int node_count = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode *cur = que.front();
                que.pop();
                node_count++;
                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
        return node_count;
    }
};