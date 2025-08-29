/*

**问题：** 判断一棵二叉树是否是镜像对称的。

### 1. 初始思路与分析

* **思路：** 使用层次遍历（BFS），将**每一层的所有节点值**都保存到一个 `vector<vector<int>>` 中。然后，遍历这个二维 `vector`，对每一层的 `vector<int>` 进行**双指针检查**，判断是否回文（对称）。
* **`isSymmetric` 函数中的问题点：**
    * **`nullptr` 信息丢失：** `temp` 向量只存储了非空节点的值。当一个节点是 `nullptr` 但其兄弟节点非 `nullptr` 时，这种不对称信息会丢失，导致错误判断（例如 `[null, 3]` 会被当成 `[3]` 对称）。
    * **双指针循环条件错误：** `for(left=0,right=temp.size()-1 ; left < temp.size(); ...)` 应该修正为 `left < right`。
    * **根节点为空处理：** `if (root == nullptr) { return false; }` 应为 `return true;` (空树对称)。

### 2. 优化的 BFS 策略：“同时入队对称节点”

针对 `nullptr` 信息丢失和提高效率的问题，我们探讨并实现了一种更优、更高级的 BFS 策略：

* **核心思想：** **同时入队两个应该镜像对称的节点**，并在循环中成对地比较它们。
* **实现步骤：**
    1.  **根节点剪枝：** `if (root == nullptr) { return true; }`
    2.  **初始入队：** 将 `root->left` 和 `root->right` 作为第一对镜像节点入队。
    3.  **循环：** `while (!que.empty())`。
    4.  **取出节点对：** 每次从队列中取出两个节点 `node1` 和 `node2`。
    5.  **核心对称性判断逻辑（精髓）：**
        * **情况 A：** `if (node1 == nullptr && node2 == nullptr)`：两个都为空，是对称的，`continue` 检查下一对。
        * **情况 B：** `else if (node1 == nullptr || node2 == nullptr)`：一个为空，另一个不为空，**不对称，`return false`**。
        * **情况 C：** `else if (node1->val != node2->val)`：两个都不为空，但值不相等，**不对称，`return false`**。
        * **情况 D：** `else` (两个都不为空且值相等)：将它们的**镜像孩子对**入队，准备下一轮检查。
            * `que.push(node1->left); que.push(node2->right);`
            * `que.push(node1->right); que.push(node2->left);`
    6.  **最终返回：** 如果循环结束未发现不对称，`return true;`。

### 3. 算法评估 (优化后的 BFS)

* **时间复杂度：** $O(N)$。每个节点都被访问一次，比较一次，入队出队一次。
* **空间复杂度：** $O(W)$。队列中存储的节点数取决于树的最大宽度。
* **结论：** 这种“同时入队对称节点”的 BFS 策略是解决对称二叉树问题的**最优解法**。它比分层存储再判断更高效、更简洁，并正确处理了 `nullptr` 节点的对称性。

### 总结体会

**对称二叉树：** 层次遍历通过**巧妙地组织入队元素（成对入队镜像节点）**，直接在遍历过程中验证对称性，将问题转换为一系列的“镜像对”检查。

*/

#include <limits>
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
    bool isSymmetric_v2(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }
        queue<TreeNode *> que;

        // 加入对称节点

        que.push(root->left);
        que.push(root->right);
        while (!que.empty()) {
            TreeNode *left = que.front();
            que.pop();
            TreeNode *right = que.front();
            que.pop();
            // 1.左右为空, 跳过
            // 2.左右其中一个为空, return
            // 3.左右均不为空, 左右的值相等
            // 4.左右均不为空, 左右的值不相等
            if (left == nullptr && right == nullptr) {
                continue;
            } else if (left == nullptr || right == nullptr) {
                return false;
            } else if (left->val != right->val) {
                return false;
            } else {
                que.push(left->left);
                que.push(right->right);
                que.push(left->right);
                que.push(right->left);
            }
        }
        return true;
    }

    bool isSymmetric_v1(TreeNode *root) {
        // 本题root非空
        queue<TreeNode *> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            vector<int> temp;
            // temp用于保存每一层的值
            for (int i = 0; i < size; i++) {
                TreeNode *cur = que.front();
                que.pop();
                if (cur == nullptr) {
                    // 如果cur为空
                    // 加入一个int中的最小值
                    temp.push_back(numeric_limits<int>::min());
                } else {
                    temp.push_back(cur->val);
                    que.push(cur->left);
                    que.push(cur->right);
                }
            }

            int left = 0;
            int right = temp.size() - 1;

            for (; left < right; left++, right--) {
                if (temp[left] != temp[right]) {
                    return false;
                }
            }
        }
        return true;
    }
};
