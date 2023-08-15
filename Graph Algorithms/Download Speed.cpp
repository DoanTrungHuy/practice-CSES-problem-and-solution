#include <bits/stdc++.h>

using namespace std;

int n, m;
const int MAXN = 502;
using ll = long long;
ll cont[MAXN][MAXN], flow[MAXN][MAXN];
int trace[MAXN];

bool bfs(int start, int end) {
    memset(trace, -1, sizeof(trace));

    queue<int> mq;
    mq.push(start);
    trace[start] = 0;

    while (!mq.empty()) {
        int u = mq.front();
        mq.pop();

        for (int v = 1; v <= n; ++v) {
            if (trace[v] == -1 and cont[u][v] > flow[u][v]) {
                mq.push(v);
                trace[v] = u;
            }
        }
    }

    return trace[end] != -1;
}

int main() {
    memset(cont, 0, sizeof(cont));
    memset(flow, 0, sizeof(flow));

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        cont[a][b] += c*1LL;
    }

    ll total = 0LL;

    while (bfs(1, n)) {
        ll diff = LLONG_MAX;

        int v = n;

        while (v != 1) {
            int u = trace[v];
            diff = min(diff, cont[u][v] - flow[u][v]);
            v = u;
        }

        v = n;
        while (v != 1) {
            int u = trace[v];
            flow[u][v] += diff;
            flow[v][u] -= diff;
            v = u;
        }

        total += diff;
    }

    cout << total;

    return 0;
}