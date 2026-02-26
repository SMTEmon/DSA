#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int MAXLOG = 18;
int st[MAXN][MAXLOG];
int logs[MAXN];

//precompute logs for O(1) queries
void precomputeLogs() {
    logs[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        logs[i] = logs[i / 2] + 1;
    }
}

void solve(int caseNum) {
    int n, q;
    if (!(cin >> n >> q)) return;
    
    //read array into sparse table base
    for (int i = 1; i <= n; i++) {
        cin >> st[i][0];
    }
    
    //build sparse table
    for (int j = 1; j < MAXLOG; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    
    cout << "Case " << caseNum << ":\n";
    while (q--) {
        int l, r;
        cin >> l >> r;
        int k = logs[r - l + 1];
        int ans = min(st[l][k], st[r - (1 << k) + 1][k]);
        cout << ans << "\n";
    }
}

int main() {
    //standard fast io
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    precomputeLogs();
    
    int t;
    if (!(cin >> t)) return 0;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    
    return 0;
}
