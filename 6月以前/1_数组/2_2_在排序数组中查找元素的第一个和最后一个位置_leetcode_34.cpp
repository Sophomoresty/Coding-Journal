#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int left_border = LeftBorder(nums, target);

        if (left_border == int(nums.size()) || nums[left_border] != target)
        {
            return {-1, -1};
        }
        int right_border = RightBoreder(nums, target) - 1;
        return {left_border, right_border};
    }

private:
    int RightBoreder(vector<int> &nums, int target)
    {
        // 缩小区间找第一个大于target的值
        int left, right, mid;
        right = int(nums.size());
        left = 0;
        while (left < right)
        // [right,n-1)的值严格大于targt
        // [0, left)的值严格小于等于target
        // 最后left==right
        {
            mid = left + ((right - left) / 2);

            if (nums[mid] > target)
            {
                right = mid;
            }
            // nums[mid] <= target
            // 因为left处于开的位置, 已知mid<=target, 故left = mid+1
            else
            {
                left = mid + 1; //
            }
        }
        return left;
    }
    int LeftBorder(vector<int> &nums, int target)
    {
        int left, right, mid;
        left = 0;
        right = int(nums.size());
        while (left < right)
        {

            mid = left + (right - left) / 2;
            if (nums[mid] >= target)
            {
                right = mid;
            }

            // nums[mid] < target
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main()
{
    vector<int> nums = {5,7,7,8,8,10};
    int target = 8;
    Solution s;
    vector<int>result = s.searchRange(nums,target);
    cout <<"Result for "<< target << ": [" << result[0] << ", " << result[1] << "]" << endl; 
    return 0;
}
