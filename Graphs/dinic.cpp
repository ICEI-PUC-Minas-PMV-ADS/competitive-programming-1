template<typename T>
struct Dinic {
    inline static const T inf = std::numeric_limits<T>::max();
    struct Edge {
        int from, to;
        T cap, flow = 0;
        T free() const { return cap - flow; }
        Edge(int u, int v, T cap) : from(u), to(v), cap(cap) {}
    };
    std::vector<Edge> edges;
    int N, M = 0;
    std::vector<std::vector<int>> E;
    std::vector<int> level, ptr;
    Dinic(int N) : N(N), E(N), level(N), ptr(N) {}
    int add_edge(int u, int v, T cap) {
        assert(cap >= 0);
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        E[u].push_back(M++);
        E[v].push_back(M++);
        return M - 2;
    }
    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        static std::queue<int> q;
        q.push(s);
        while (not q.empty()) {
            int u = q.front();
            q.pop();
            for (auto j : E[u]) {
                int v = edges[j].to;
                if (level[v] != -1 || edges[j].free() <= 0) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }
    T push(int u, int t, T pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int& i = ptr[u]; i < E[u].size(); ++i) {
            auto &edge = edges[E[u][i]], &back = edges[E[u][i] ^ 1];
            if (level[edge.to] != level[u] + 1 || edge.free() <= 0) continue;
            T pushing = push(edge.to, t, std::min(pushed, edge.free()));
            if (pushing == 0) continue;
            edge.flow += pushing, back.flow -= pushing;
            return pushing;
        }
        return 0;
    }
    T flow(int s, int t) {
        for (auto& edge : edges) edge.flow = 0;
        T f = 0;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (T pushed = push(s, t, inf)) f += pushed;
        }
        return f;
    }
    bool cut(int j) const {
        return edges[j].free() == 0 && level[edges[j].from] != -1 && level[edges[j].to] == -1;
    }
};
