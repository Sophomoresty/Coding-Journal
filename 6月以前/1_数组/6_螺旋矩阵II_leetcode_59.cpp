#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        int count = 1;    // 计数器
        int loop = n / 2; // 循环次数
        int i, j, start_x, start_y;
        start_x = start_y = 0;                       // 初始横纵坐标
        int offset = 0;                              // 偏移量
        vector<vector<int>> nums(n, vector<int>(n)); // 初始化n行n列的二位属猪
        while (loop--)
        {
            i = start_x;
            j = start_y;
            // 第1条边, x坐标不动, y坐标动
            for (; j < n - 1 - offset; j++)
            {
                nums[i][j] = count++;
            }
            // 第2条边, x坐标移动, y不动
            for (; i < n - 1 - offset; i++)
            {
                nums[i][j] = count++;
            }
            // 第3条边
            for (; j > start_y; j--)
            {
                nums[i][j] = count++;
            }
            //
            for (; i > start_x; i--)
            {
                nums[i][j] = count++;
            }
            start_x++;
            start_y++;
            offset++;
        }
        if (n % 2 != 0)
        {
            nums[start_x][start_y] = count++;
        }
        return nums;
    }
};


int main()
{
    int n = 3;
    Solution s;
    vector<vector<int>> nums = s.generateMatrix(n);
    for (const auto &row : nums)
    {
        for (int element : row)
        {
            cout << element << '\t';
        }
        cout << endl;
    }
    return 0;
}