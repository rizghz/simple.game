#pragma once

template <typename T>
struct Vector {
    T x;
    T y;
};

template <typename T>
std::ostream& operator << (std::ostream& out, const Vector<T>& vec) {
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}

template <typename T>
inline bool operator == (const Vector<T>& v, const Vector<T>& w) {
    if (v.x == w.x and v.y == w.y) {
        return true;
    }
    return false;
}

template <typename T>
inline bool operator != (const Vector<T>& v, const Vector<T>& w) {
    if (v.x != w.x or v.y != w.y) {
        return true;
    }
    return false;
}
