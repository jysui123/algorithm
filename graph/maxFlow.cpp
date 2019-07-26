/*
 * https://blog.csdn.net/riba2534/article/details/79022209
 */

#include <vector>
#include <queue>

using namespace std;

class EdmondKarp {
    int n;
    vector<vector<int>> g, f;
    vector<int> pre;

    bool bfs(int s, int t) {
        fill(pre.begin(), pre.end(), -1);
        vector<bool> visited(n, false);
        queue<int> q;
        visited[s] = true;
        q.push(s);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (int j = 0; j < n; ++j)
                if (!visited[j] && g[i][j] > 0) {
                    visited[j] = true;
                    pre[j] = i;
                    if (j == t) return true;
                    q.push(j);
                }
        }
        return false;
    }

public:
    EdmondKarp(int n_): n(n_), g(n_, vector<int>(n_, 0)), f(n_, vector<int>(n_, 0)), pre(n_) {}
    void addEdge(int i, int j, int cap) {
        g[i][j] += cap;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            int d = INT_MAX;
            for (int v = t; v != s; v = pre[v])
                d = min(d, g[pre[v]][v]);
            flow += d;
            for (int v = t; v != s; v = pre[v]) {
                int w = pre[v];
                g[w][v] -= d;
                g[v][w] += d;
                if (f[v][w] > 0) f[v][w] -= d;
                else f[v][w] += d;
            }
        }
        return flow;
    }
};