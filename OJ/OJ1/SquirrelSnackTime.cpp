#include <bits/stdc++.h>
using namespace std;

struct SegTree {
int n;
struct Node { int mn; int lazy; };
vector<Node> st;
SegTree(int _n=0): n(_n), st(4*_n+10){ }
void build(int p, int l, int r, const vector<int>& a){
st[p].lazy = 0;
if(l==r){ st[p].mn = a[l]; return; }
int m=(l+r)/2;
build(p<<1,l,m,a);
build(p<<1|1,m+1,r,a);
st[p].mn = min(st[p<<1].mn, st[p<<1|1].mn);
}
void init(const vector<int>& a){ n = (int)a.size(); st.assign(4*n+10, {0,0}); if(n) build(1,0,n-1,a); }
void apply(int p, int v){ st[p].mn += v; st[p].lazy += v; }
void push(int p){ if(st[p].lazy!=0){ apply(p<<1, st[p].lazy); apply(p<<1|1, st[p].lazy); st[p].lazy=0; }}
void add(int p, int l, int r, int ql, int qr, int v){
if(ql>r || qr<l) return;
if(ql<=l && r<=qr){ apply(p,v); return; }
push(p);
int m=(l+r)/2;
add(p<<1,l,m,ql,qr,v);
add(p<<1|1,m+1,r,ql,qr,v);
st[p].mn = min(st[p<<1].mn, st[p<<1|1].mn);
}
int range_min(int p, int l, int r, int ql, int qr){
if(ql>r || qr<l) return INT_MAX;
if(ql<=l && r<=qr) return st[p].mn;
push(p);
int m=(l+r)/2;
return min(range_min(p<<1,l,m,ql,qr), range_min(p<<1|1,m+1,r,ql,qr));
}
// wrappers
void range_add(int l, int r, int v){ if(l>r) return; add(1,0,n-1,l,r,v); }
int query_min(int l, int r){ if(l>r) return INT_MAX; return range_min(1,0,n-1,l,r); }
};

int main(){
ios::sync_with_stdio(false);
cin.tie(nullptr);
int n;
if(!(cin>>n)) return 0;
vector<int> p(n);
for(int i=0;i<n;i++) cin>>p[i];

SegTree seg;
seg.init(p);

vector<int> ans(n+1,-1); // ans[k] start position for length k (1-indexed)

for(int k=n;k>=1;k--){
    bool found=false;
    for(int L=1; L<=n-k+1; ++L){
        int l=L-1, r=L+k-2;
        if(seg.query_min(l,r) >= 1){
            seg.range_add(l,r,-1);
            ans[k]=L;
            found=true;
            break;
        }
    }
    if(!found){
        cout<<-1<<"\n";
        return 0;
    }
}

// print starts for k=1..n
for(int k=1;k<=n;k++){
    if(k>1) cout<<' ';
    cout<<ans[k];
}
cout<<"\n";
return 0;
}
