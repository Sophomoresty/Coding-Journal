#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    string s;
    cin >> k;
    cin >> s;
    reverse(s.begin(), s.end());
    reverse(s.begin(), s.begin() + k);
    reverse(s.begin() + k, s.end());
    cout << s << '\n';
}
