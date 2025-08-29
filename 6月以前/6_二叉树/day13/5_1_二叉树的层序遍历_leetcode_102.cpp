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
public:
    void levelorder_traversal(TreeNode *root, vector<vector<int>> &res) {
        if (root == nullptr) {
            return;
        }

        queue<TreeNode *> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> temp;
            for (int i = 0; i < size; i++) {
                TreeNode *cur = que.front();
                que.pop();
                temp.push_back(cur->val);

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }

                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
            res.push_back(temp);
        }
    }

    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        levelorder_traversal(root, res);
        return res;
    }
};