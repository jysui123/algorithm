#include <vector>
#include <queue>

using namespace std;

class Dijkstra {
    int n;
    vector<vector<pair<int, int>>> g;
public:
    Dijkstra(int n_): n(n_), g(n_) {}
    void addEdge(int i, int j, int w) {
        g[i].push_back({j, w});
    }
    void shortestPath(int s, vector<int>& dist, vector<int>& pre) {
        dist.resize(n, INT_MAX);
        pre.resize(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            int i = pq.top().second, d = pq.top().first;
            pq.pop();
            if (dist[i] != d) continue;
            for (auto& e : g[i]) {
                int j = e.first, w = e.second;
                if (dist[j] < d + w) {
                    dist[j] = d + w;
                    pq.push({dist[j], j});
                    pre[j] = i;
                }
            }
        }
    }
};