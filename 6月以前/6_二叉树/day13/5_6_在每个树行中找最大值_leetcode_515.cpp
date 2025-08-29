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
public:
    void levelorder_traversal(TreeNode *root, vector<int> &vec_res) {
        if (root == nullptr) {
            return;
        }
        queue<TreeNode *> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            TreeNode *cur;
            int max;
            // max 初始化为每一层的第一个元素的值
            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                if (i == 0) {
                    max = cur->val;
                }

                if (max < cur->val) {
                    max = cur->val;
                }

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }

                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
            vec_res.push_back(max);
        }
    }

    vector<int> largestValues(TreeNode *root) {
        vector<int> vec_res;
        levelorder_traversal(root, vec_res);
        return vec_res;
    }
};