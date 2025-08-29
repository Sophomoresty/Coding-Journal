#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // 定义二维数组 n行m列
    int sum = 0;
    vector<vector<int>> vec(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> vec[i][j];
            sum += vec[i][j];
        }
    }
    // 行前缀和
    vector<int> horizontal(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            horizontal[i] += vec[i][j];
        }
    }
    // 列前缀和
    vector<int> vertical(n, 0);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            vertical[j] += vec[i][j];
        }
    }

    int result = INT_MAX;
    int horizontalCut = 0;
    for (int i = 0; i < n; i++) {
        horizontalCut += horizontal[i];
        result = min(result, abs(sum - horizontalCut - horizontalCut));
    }
    int verticalCut = 0;
    for (int j = 0; j < m; j++) {
        verticalCut += vertical[j];
        result = min(result, abs(sum - verticalCut - verticalCut));
    }
    cout << result << '\n';
}