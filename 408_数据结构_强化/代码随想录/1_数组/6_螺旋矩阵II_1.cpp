#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        // ⭐ 初始化写得很棒！
        vector<vector<int> > res(n, vector<int>(n, 0)); 
        
        int startX = 0, startY = 0; // 每一圈的起始位置
        int loop = n / 2; // 总共需要循环的圈数
        int mid = n / 2; // 矩阵的中心位置，n为奇数时需要单独处理
        int count = 1; // 用来填充的数字
        int offset = 1; // 每一圈循环，需要控制边界的偏移量
        int i, j;

        // 开始一圈一圈地循环
        while (loop--) {
            i = startX;
            j = startY;

            // 下面是四个 for 循环，模拟一圈的四条边，坚持“左闭右开”原则
            
            // 1. 从左到右填充上边
            // y 不变 (i)，x 变 (j)
            for (; j < startY + n - offset; ++j) {
                res[i][j] = count++;
            }
            
            // 2. 从上到下填充右边
            // x 不变 (j)，y 变 (i)
            for (; i < startX + n - offset; ++i) {
                res[i][j] = count++;
            }

            // 3. 从右到左填充下边
            // y 不变 (i)，x 变 (j)
            for (; j > startY; --j) {
                res[i][j] = count++;
            }

            // 4. 从下到上填充左边
            // x 不变 (j)，y 变 (i)
            for (; i > startX; --i) {
                res[i][j] = count++;
            }

            // 一圈结束后，更新下一圈的起始位置和边界偏移量
            startX++;
            startY++;
            offset += 2;
        }

        // 如果 n 是奇数，需要单独给最中间的位置赋值
        if (n % 2 == 1) {
            res[mid][mid] = count;
        }

        return res;
    }
};