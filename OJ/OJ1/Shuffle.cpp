#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        bool ok = true;
        // reverse process: for k = n..1 find a length-k segment with all >=1 and decrement it
        for (int k = n; k >= 1; --k) {
            bool found = false;
            for (int L = 0; L + k - 1 < n; ++L) {
                bool good = true;
                for (int j = L; j < L + k; ++j) {
                    if (p[j] <= 0) { good = false; break; }
                }
                if (good) {
                    // decrement this segment
                    for (int j = L; j < L + k; ++j) p[j]--;
                    found = true;
                    break;
                }
            }
            if (!found) { ok = false; break; }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
