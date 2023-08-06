#include <bits/stdc++.h>
 
using namespace std;
 
int n, q;
 
using ll = long long;
 
struct Node {
    ll sum, pre;
    
    Node() {
        sum = 0;
        pre = 0;
    }
};
 
const int MAXN = 2e5 + 1;
Node tree[MAXN*4];
 
void update(int node, int left, int right, int index, ll value) {
    if (index < left or right < index) {
        return;
    }
    if (left == right) {
        tree[node].sum = value;
        tree[node].pre = value;
        return;
    }
    int mid = (left + right) / 2;
    update(node*2, left, mid, index, value);
    update(node*2 + 1, mid + 1, right, index, value);
    tree[node].sum = tree[node*2].sum + tree[node*2 + 1].sum;
    tree[node].pre = max({
        tree[node*2].pre, 
        tree[node*2].sum + tree[node*2 + 1].sum,
        tree[node*2].sum,
        tree[node*2].sum + tree[node*2 + 1].pre
    });
}
 
Node query(int node, int left, int right, int qLeft, int qRight) {
    if (left > qRight or right < qLeft) {
        return Node();
    }
    if (qLeft <= left and right <= qRight) {
        return tree[node];
    }
    int mid = (right + left) / 2;
    Node left_node = query(node*2, left, mid, qLeft, qRight);
    Node right_node = query(node*2 + 1, mid + 1, right, qLeft, qRight);
    Node root;
    
    root.sum = left_node.sum + right_node.sum;
    root.pre = max({
        left_node.pre, 
        left_node.sum,
        left_node.sum + right_node.sum,
        left_node.sum + right_node.pre
    });
    
    return root;
    
}
 
int main()
{
    int n, q;
    
    cin >> n >> q;
    
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        update(1, 1, n, i, x);
    }
    
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            ll u;
            cin >> k >> u;
            update(1, 1, n, k, u);
        }
        else {
            int a, b;
            cin >> a >> b;
            cout << max(query(1, 1, n, a, b).pre, 0LL) << '\n';
        }
    }
    
    return 0;
}