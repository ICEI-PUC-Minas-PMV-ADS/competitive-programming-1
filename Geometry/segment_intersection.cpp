template<typename T>
bool intersects(T a, T b, T c, T d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

template<typename T>
T sgn(T x) { return x > 0 ? +1 : x == 0 ? 0 : -1; }

template<typename T>
bool intersects(array<complex<T>, 2> U, array<complex<T>, 2> V) {
    auto [a, b] = U;
    auto [c, d] = V;

    // checks if segments are on the same line
    // return true if Ox and Oy projections intersect
    if (cross(a - c, d - c) == 0 && cross(b - c, d - c) == 0)
        return intersects(a.x(), b.x(), c.x(), d.x()) && intersects(a.y(), b.y(), c.y(), d.y());

    // checks if a and b don't lie on the same side of the segment c->d, and vice-versa
    return sgn(cross(b - a, c - a)) != sgn(cross(b - a, d - a)) &&
           sgn(cross(d - c, a - c)) != sgn(cross(d - c, b - c));
}
