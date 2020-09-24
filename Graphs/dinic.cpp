#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename T, typename F>
struct Dinic
{
    struct Edge
    {
        int from, to;
        T cap, flow = 0;
        T free() { return cap - flow; }
        Edge(int u, int v, T cap) : from(u), to(v), cap(cap) {}
    };
    vector<Edge> edges;
    const T inf = numeric_limits<T>::max();
    const int n, s, t;
    vector<vector<int>> E;
    vector<int> level, ptr;
    void clear() { edges.clear(), E.assign(n, vector(0, 0)); }
    Dinic(int n, int s, int t) : n(n), s(s), t(t)
    {
        E.resize(n), level.resize(n), ptr.resize(n);
    }
    void add_edge(int u, int v, T cap)
    {
        int m = sz(edges);
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        E[u].push_back(m++);
        E[v].push_back(m++);
    }
    bool bfs()
    {
        fill(all(level), -1); level[s] = 0;
        static queue<int> q; q.push(s);
        while (not q.empty())
        {
            int u = q.front(); q.pop();
            for (auto idx : E[u])
            {
                int v = edges[idx].to;
                if (level[v] != -1 || edges[idx].free() <= 0) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }
    T push(int u, T pushed)
    {
        if (u == t || pushed == 0) return pushed;
        for (int& idx = ptr[u]; idx < sz(E[u]); ++idx)
        {
            auto &edge = edges[E[u][idx]], &back = edges[E[u][idx] ^ 1];
            if (level[edge.to] != level[u] + 1 || edge.free() <= 0) continue;
            T pushing = push(edge.to, min(pushed, edge.free()));
            if (pushing == 0) continue;
            edge.flow += pushing, back.flow -= pushing;
            return pushing;
        }
        return 0;
    }
    F flow()
    {
        F f = 0;
        while (bfs())
        {
            fill(all(ptr), 0);
            while (T pushed = push(s, inf)) f += pushed;
        }
        return f;
    }
};

int main()
{ _
    exit(0);
}

