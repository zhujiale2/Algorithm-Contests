#include <bits/stdc++.h>

using namespace std;

//#define DEBUG

const int MAXN = 200009;

int n, s[MAXN], g[MAXN], a[MAXN], ans[MAXN];

void add (int x, int k) {
    for (int i = x; i <= n; i += i&-i) s[i] += k;
}

int gets (int x) {
    int sum = 0;
    for (int i = x; i > 0; i -= i&-i) sum += s[i];
    return sum;
}

int main() {
    cin >> n;
    for (int k = 0; k < 2; k++) {
        for (int i = 1; i <= n; i++) cin >> g[i];
        for (int i = n; i > 0; i--) {
            a[n - i + 1] += gets (g[i] + 1);
            add (g[i] + 1, 1);
        }
        memset (s, 0, sizeof s);
    }
    for (int i = 1, k = 0; i <= n; i++) {
        a[i] += k;
        k = a[i] / i, a[i] %= i;
        add (i, 1);
    }
    for (int i = 1; i <= n; i++) {
        int l = 1, r = n, last = -1, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (gets (mid - 1) <= a[n - i + 1]) last = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << last-1 << ' ';
        add (last, -1);
    }
}