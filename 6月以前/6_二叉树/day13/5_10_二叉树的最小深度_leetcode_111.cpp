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
    // 最优解法是去掉for和while的break,for原来的break用return depth+1代替即可
    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        queue<TreeNode *> que;
        que.push(root);
        int depth = 0;
        while (!que.empty()) {
            int size = que.size();
            TreeNode *cur;
            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                if (cur->left == nullptr && cur->right == nullptr) {
                    break;
                }

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
            depth++;
            if (cur->left == nullptr && cur->right == nullptr) {
                break;
            }
        }
        return depth;
    }
};