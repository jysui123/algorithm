/*
 * Binary Index Tree, 1D and 2D version
 * Support range update and range query in O(logn) time
 */

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class BIT {
    int n;
    vector<int> d, id;

    inline int lowbit(int i) {
        return i & -i;
    }

public:
    BIT (int n_): n(n_), d(n_+1, 0), id(n_+1, 0) {}
    BIT (const vector<int>& arr_): n(arr_.size()), d(arr_.size()+1, 0), id(arr_.size()+1, 0) {
        for (int i = 0; i < n; ++i) add(i, i, arr_[i]);
    }

    void add(int pos, int val) {
        for (int i = pos + 1; i <= n; i += lowbit(i))
            d[i] += val, id[i] += pos * val;
    }
    void add(int left, int right, int val) {
        add(left, val), add(right + 1, -val);
    }

    int query(int pos) {
        int sum = 0;
        for (int i = ++pos; i > 0; i -= lowbit(i))
            sum += pos * d[i] - id[i];
        return sum;
    }
    int query(int left, int right) {
        return query(right) - query(left - 1);
    }
};

class BIT2D {
    int n, m;
    vector<vector<int>> d1, d2, d3, d4;

    inline int lowbit(int i) {
        return i & -i;
    }

public:
    BIT2D(int n_, int m_): n(n_), m(m_), d1(n_+1, vector<int>(m_+1, 0)),
      d2(n_+1, vector<int>(m_+1, 0)), d3(n_+1, vector<int>(m_+1, 0)), d4(n_+1, vector<int>(m_+1, 0)) {}
    BIT2D(const vector<vector<int>>& arr_): n(arr_.size()), m(arr_[0].size()), d1(n+1, vector<int>(m+1, 0)),
      d2(n+1, vector<int>(m+1, 0)), d3(n+1, vector<int>(m+1, 0)), d4(n+1, vector<int>(m+1, 0)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                add(i, i, j, j, arr_[i][j]);
    }

    void add(int posx, int posy, int val) {
        for (int i = posx + 1; i <= n; i += lowbit(i))
            for (int j = posy + 1; j <= m; j += lowbit(j)) {
                d1[i][j] += val;
                d2[i][j] += posx * val;
                d3[i][j] += posy * val;
                d4[i][j] += posx * posy * val;
            }
    }
    void add(int xleft, int xright, int yleft, int yright, int val) {
        add(xleft, yleft, val);
        add(xleft, yright + 1, -val);
        add(xright + 1, yleft, -val);
        add(xright + 1, yright + 1, val);
    }
    int query(int posx, int posy) {
        int sum = 0;
        posx++, posy++;
        for (int i = posx; i > 0; i -= lowbit(i))
            for (int j = posy; j > 0; j -= lowbit(j)) {
                sum += posx * posy * d1[i][j] + d4[i][j];
                sum -= posy * d2[i][j] + posx * d3[i][j];
            }
        return sum;
    }
    int query(int xleft, int xright, int yleft, int yright) {
        return query(xright, yright) - query(xleft - 1, yright)
             - query(xright, yleft - 1) + query(xleft - 1, yleft - 1);
    }
};

int main() {
    vector<int> arr{3, 5, 7, 2, 4, 9, 0, 11};
    BIT bit(arr);
    for (int i = 0; i < 6; ++i)
        cout << bit.query(i) << " ";
    cout << endl;
    for (int i = 0; i < 6; ++i)
        cout << bit.query(i, i) << " ";
    cout << endl;
    for (int i = 0; i < 6; ++i)
        cout << bit.query(i, i + 2) << " ";
    cout << endl;
    cout << "=====" << endl;
    vector<vector<int>> arr2{{1, 2, 3},
                             {4, 3, 2},
                             {9, 0, 1},
                             {3, 3, 3}};
    BIT2D bit2(arr2);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            cout << bit2.query(i, i+1, j, j+1) << endl;
    bit2.add(1, 3, 1, 2, 2);
    cout << "=====" << endl;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            cout << bit2.query(i, i+1, j, j+1) << endl;
}