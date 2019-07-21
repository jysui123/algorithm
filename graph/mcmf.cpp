#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class MCMF {
    const int INF = 1e8;
    using P = pair<int, int>;

    class Edge {
    public:
        int to, cap, cost, rev, flow;
        Edge(int to_, int cap_, int cost_, int rev_): to(to_), cap(cap_), cost(cost_), rev(rev_), flow(0) {}
    };

    int V;
    vector<vector<Edge>> graph;
    vector<int> potential, dist, prev_vertex, prev_edge;

public:
    MCMF(int V_):
        V(V_), graph(V_), potential(V_), dist(V_), prev_vertex(V_), prev_edge(V_) {}

    void addEdge(int from, int to, int cap, int cost) {
        graph[from].emplace_back(to, cap, cost, graph[to].size());
        graph[to].emplace_back(from, 0, -cost, graph[from].size() - 1);
    }

    void minCostFlow(int s, int t, int& flow, int& cost) {
        flow = cost = 0;
        fill(potential.begin(), potential.end(), 0);
        while (true) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<P, vector<P>, greater<P>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto p = pq.top();
                pq.pop();
                int v = p.second;
                if (dist[v] < p.first) continue;
                for (int i = 0; i < graph[v].size(); ++i) {
                    auto& e = graph[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + potential[v] - potential[e.to]) {
                        dist[e.to] = dist[v] + e.cost + potential[v] - potential[e.to];
                        prev_vertex[e.to] = v;
                        prev_edge[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int i = 0; i < V; ++i) potential[i] += dist[i];
            int d = INF;
            for (int x = t; x != s; x = prev_vertex[x])
			    d = min(d, graph[prev_vertex[x]][prev_edge[x]].cap);
            flow += d;
            cost += d * potential[t];
            for (int x = t; x != s; x = prev_vertex[x]) {
                auto& e = graph[prev_vertex[x]][prev_edge[x]];
                e.cap -= d;
                e.flow += d;
                graph[x][e.rev].cap += d;
            }
        }
    }
};