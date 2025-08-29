#include <vector>
using namespace std;

class Solution {
public:
    // 首先要知道螺旋矩阵边的元素个数和圈的关系
    // 设圈数为c
    // 由题最外圈的边元素个数为n
    // 边元素为偶数的情况下, n=2c, 边元素为奇数的情况下n=2c-1
    // 思路由外圈向内圈进行赋值,
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int loop = n / 2; //圈数
        int count = 1;
        int offset = 0; // x,y相对于(0,0)的偏移量

        while (loop) {
            int x = offset;
            int y = offset;
            for (; y < n - 1 - offset; y++) {
                res[x][y] = count++;
            }
            for (; x < n - 1 - offset; x++) {
                res[x][y] = count++;
            }
            for (; y > offset; y--) {
                res[x][y] = count++;
            }
            for (; x > offset; x--) {
                res[x][y] = count++;
            }
            offset++;
            loop--;
        }

        if (n % 2 == 1) {
            res[offset][offset] = count;
        }

        return res;
    }
};