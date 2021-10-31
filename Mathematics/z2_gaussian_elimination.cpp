template<int N>
struct Z2GaussianElimination {
    using V = std::bitset<N>;
    std::array<V, N> basis, alpha;
    int dim = 0;
    std::pair<int, V> reduce(V& x) const {
        V coef;
        for (int i = N - 1; i >= 0 && x.any(); --i) {
            if (x[i] == 0) continue;
            if (basis[i] == 0) return std::pair(i, coef);
            x ^= basis[i], coef ^= alpha[i];
        }
        return std::pair(-1, coef);
    }
    bool insert(V x) {
        auto [i, coef] = reduce(x);
        if (i == -1) return false;
        basis[i] = x, dim += 1;
        alpha[i] = coef;
        alpha[i][dim - 1] = 1;
        return true;
    }
    std::pair<bool, V> solve(V x) const {
        auto [i, coef] = reduce(x);
        return std::pair(i == -1, coef);
    }
};
