#include <vector>
#include <queue>

using namespace std;

class Kruskal {
public:
    class Edge {
    public:
        int u, v, w;
        Edge(int u_, int v_, int w_): u(u_), v(v_), w(w_) {}
        bool operator<(const Edge& rhs) const {
            return w > rhs.w;
        }
    };

    Kruskal(int n_): n(n_), uf(n_) {
        for (int i = 0; i < n; ++i) uf[i] = i;
    }
    void addEdge(int u, int v, int w) {
        pq.emplace(u, v, w);
    }
    vector<Edge> mst() {
        vector<Edge> res;
        while (!pq.empty() && res.size() < n-1) {
            auto e = pq.top();
            pq.pop();
            if (find(e.u) == find(e.v)) continue;
            uni(e.u, e.v);
            res.push_back(e);
        }
        return res;
    }

private:
    vector<int> uf;
    priority_queue<Edge> pq;
    int n;

    int find(int i) {
        while (i != uf[i]) i = uf[i] = uf[uf[i]];
        return i;
    }
    void uni(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        uf[j] = i;
    }
};