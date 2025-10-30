#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll eval(const vector<int>& v){
    ll s = 0;
    for (size_t i = 1; i < v.size(); ++i) s += ll(abs(v[i] - v[i-1]));
    return s;
}

// build alternating sequence by taking from ends: r, l, r-1, l+1, ...
vector<int> alt_from_ends(const vector<int>& b, bool start_with_right){
    int n = b.size();
    int l = 0, r = n-1;
    vector<int> res; res.reserve(n);
    bool right = start_with_right;
    while (l <= r){
        if (right){
            res.push_back(b[r--]);
        } else {
            res.push_back(b[l++]);
        }
        right = !right;
    }
    return res;
}

// build order list: indices order either r,l,r-1,l+1,... or l,r,l+1,r-1,...
vector<int> index_order(bool start_with_right, int n){
    int l = 0, r = n-1;
    vector<int> ord; ord.reserve(n);
    bool right = start_with_right;
    while (l <= r){
        if (right){ ord.push_back(r--); }
        else { ord.push_back(l++); }
        right = !right;
    }
    return ord;
}

// greedy place values (in given index order) into deque choosing side that maximizes incremental gain
vector<int> greedy_deque_place(const vector<int>& b, const vector<int>& ord){
    deque<int> dq;
    for (int idx : ord){
        int val = b[idx];
        if (dq.empty()){
            dq.push_back(val);
        } else {
            int left = dq.front();
            int right = dq.back();
            ll gainLeft = ll(abs(val - left));
            ll gainRight = ll(abs(val - right));
            if (gainLeft > gainRight) dq.push_front(val);
            else dq.push_back(val);
        }
    }
    vector<int> res;
    res.reserve(dq.size());
    for (int x : dq) res.push_back(x);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (n == 1){
        cout << 0 << '\n';
        return 0;
    }
    sort(a.begin(), a.end());
    ll best = 0;

    // candidate 1 & 2: alternating from ends starting with right (largest) or left (smallest)
    auto v1 = alt_from_ends(a, true);
    best = max(best, eval(v1));
    auto v2 = alt_from_ends(a, false);
    best = max(best, eval(v2));

    // candidate 3..6: greedy deque placement with two index orders (start with right / start with left),
    // and also try reversed order (reverse of deque) though eval same; but we compute both.
    for (int startRight = 0; startRight < 2; ++startRight){
        auto ord = index_order(startRight == 1, n);
        auto gv = greedy_deque_place(a, ord);
        best = max(best, eval(gv));
        reverse(gv.begin(), gv.end());
        best = max(best, eval(gv));
    }

    cout << best << '\n';
    return 0;
}
