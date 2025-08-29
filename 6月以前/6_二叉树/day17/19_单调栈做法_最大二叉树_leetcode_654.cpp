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
    TreeNode *constructMaximumBinaryTree(std::vector<int> &nums) {

        /*单调递减栈能做最大二叉树的原因:
        单调栈擅长解决“寻找左右第一个更大/更小元素”问题高度

        而对于本题数组中的任意元素 X (nums[i])：
        X 的左孩子：是 X 左边子数组中作为根的那个元素. 准确说, 是 X 左侧、且在 X 左边第一个比 X 大的元素的右侧范围内的最大值. 
        X 的右孩子：是 X 右边子数组中作为根的那个元素. 准确说, 是 X 右侧、且在 X 右边第一个比 X 大的元素的左侧范围内的最大值. 
        X 的父节点：是 X 左边第一个比它大的元素 和 X 右边第一个比它大的元素 中值较小的那一个. 如果它两边都没有比它大的, 那它就是整个树的根. 
        
        恰好符合单调栈的解决问题的特征
        */

        std::stack<TreeNode *> st; // 存储 TreeNode* 的单调递减栈

        // 遍历输入数组中的每个数字
        for (int i = 0; i < nums.size(); i++) {

            // 1. 为当前数字创建一个 TreeNode 节点
            TreeNode *cur = new TreeNode(nums[i]);

            // 2. “收编”阶段 (构建树的左子树) ：处理栈内比 cur 小的元素
            // 最后一次循环中的栈顶节点 p 满足: 
            // 是 cur 右侧, 且在 cur 左边第一个比 cur 大的元素的右侧范围内的最大值.
            // 总结: 循环中最后一次的栈顶节点 p 是 cur 的 左孩子
            while (!st.empty() && st.top()->val < cur->val) {
                TreeNode *p = st.top(); // 获取栈顶节点 p
                st.pop();               // 将 p 弹出栈
                cur->left = p;
            }

            // 3. “被收编”阶段 (构建树的右子树) ： 如果栈非空, 意味着栈内有元素, 且大于cur

            // 此时的栈顶节点 t 即是 cur左边第一个比它大的元素, cur也是t临近的右侧子数组中的根节点
            // 总结: 栈顶是cur的爸爸, cur是栈顶的右孩子

            if (!st.empty()) {
                TreeNode *t = st.top(); // 获取栈顶节点 t
                t->right = cur;         // 将 cur 设置为 t 的右孩子
            }

            // 4. 入栈
            st.push(cur);
        }

        // 5. 获取根节点

        // 树构建完毕, 栈非空, 栈底即是我们的根节点
        
        // 为什么非空? 为什么栈底是我们的根节点?
        // 我们维护的栈是单调递减栈, 维护体现在while循环中的pop中.
        // 根节点一旦入栈后, 将不会再遇到比它更大的元素（因为它已经是最大),
        // 因此它将永远不会被弹出, 并最终留在栈中, 沉到栈底.
        // 所以栈一定非空 且 栈底元素即为树的根节点.
        TreeNode *root = nullptr; // 初始化 root 为 nullptr
        if (!st.empty()) {
            root =
                st.top(); // 初始时 root 指向栈顶（可能是根, 也可能是根的右子孙）
            while (st.size() > 1) { // 循环弹出, 直到栈中只剩一个元素（根节点）
                st.pop();
                root = st.top(); // 更新 root 为新的栈顶（向栈底移动）
            }
        }
        return root; // 返回最终的根节点
    }
};
