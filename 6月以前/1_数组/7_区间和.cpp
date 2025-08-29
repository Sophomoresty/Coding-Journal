#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // int n, a, b, temp, result;

    // int sum = 0;
    // cin >> n;
    // vector<int> nums(n);
    // for (int i = 0; i < n; i++) {
    //     cin >> temp;
    //     sum += temp;
    //     nums[i] = sum;
    // }

    // while (cin >> a >> b) {
    //     if (a < 0 && b > n - 1) {
    //         cout << "输入不合法" << '\n';
    //     } else if (a == 0) {
    //         result = nums[b];
    //         cout << result << '\n';
    //     } else {
    //         result = nums[b] - nums[a - 1];
    //         cout << result << '\n';
    //     }
    // }
    int n, a, b, presum, temp;
    scanf("%d", &n);
    vector<int> vec(n);
    presum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        presum += temp;
        vec[i] = presum;
    }
    int result = 0;
    while (~scanf("%d%d", &a, &b)) {
        if (a == 0) {
            result = vec[b];
        } else {
            result = vec[b] - vec[a - 1];
        }
        printf("%d\n", result);
    }

    return 0;
}