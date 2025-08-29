#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int low, fast;
        low = fast = 0;
        for (; fast < int(nums.size()); fast++)
        {
            if (nums[fast] != val)
            {
                nums[low++] = nums[fast];
            }
        }
        return low++;
    }
};

int main()
{
    Solution s;
    vector<int> test = {0,1,2,2,3,0,4,2};
    int val = 2;
    int k = s.removeElement(test,val);
    cout << k << '\n'; 
    return -1;
}