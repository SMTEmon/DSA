#include <bits/stdc++.h>

using namespace std;

//segment tree for range sum and point update
class SegmentTree {
    int n;
    vector<int> tree;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void build(vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, 2 * v, tl, tm);
            build(arr, 2 * v + 1, tm + 1, tr);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, min(r, tm))
               + query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(2 * v, tl, tm, pos, new_val);
            else
                update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int pos, int new_val) {
        update(1, 0, n - 1, pos, new_val);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st(arr);

    cout << "Range sum [1, 3]: " << st.query(1, 3) << endl; //3+5+7 = 15
    st.update(1, 10); //update element at index 1 to 10
    cout << "Range sum [1, 3] after update: " << st.query(1, 3) << endl; //10+5+7 = 22

    return 0;
}
