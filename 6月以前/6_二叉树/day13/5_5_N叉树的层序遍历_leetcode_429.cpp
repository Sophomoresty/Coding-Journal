#include <queue>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

    class Solution {
    public:
        void levelorder_traversal(Node *root, vector<vector<int>> &vec_res) {
            if (root == nullptr) {
                return;
            }
            queue<Node *> que;
            que.push(root);
            while (!que.empty()) {
                int size = que.size();
                Node *cur;
                vector<int> temp;

                // 遍历每一层
                for (int i = 0; i < size; i++) {
                    cur = que.front();
                    que.pop();
                    temp.push_back(cur->val);

                    // 加入它的孩子, 孩子是有顺序的, 从左到右,
                    int child_count = cur->children.size();

                    // 剪枝
                    if (child_count == 0) {
                        continue;
                    }

                    for(int j=0;j<child_count;j++){
                        if (cur->children[j] == nullptr) {
                            continue;
                        } else {
                            que.push(cur->children[j]);
                        }
                    }


                }
                vec_res.push_back(temp);
            }
        }

        vector<vector<int>> levelOrder(Node *root) {
            vector<vector<int>> vec_res;
            levelorder_traversal(root, vec_res);
            return vec_res;
        }
    };