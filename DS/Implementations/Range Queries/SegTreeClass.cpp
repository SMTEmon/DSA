#include <iostream>
#include <vector>
#include <numeric> // for std::gcd

using namespace std;

const int MAXN = 100005;
// From Page 1: Tree [4N]
int Arr[MAXN];
int Tree[4 * MAXN];

// Helper function based on Page 3: Tree[node] = GCD(Tree[left], Tree[right])
int getGCD(int a, int b)
{
    return std::gcd(a, b);
}

// ==========================================
// 1. BUILD TREE (From Pages 1 & 3)
// ==========================================
void buildTree(int node, int l, int r)
{
    if (l == r)
    {
        Tree[node] = Arr[l];
        return;
    }

    int leftNode = 2 * node;
    int rightNode = 2 * node + 1;
    int mid = (l + r) / 2;

    // Recursion
    buildTree(leftNode, l, mid);
    buildTree(rightNode, mid + 1, r);

    Tree[node] = getGCD(Tree[leftNode], Tree[rightNode]);
}

// ==========================================
// 2. QUERY (From Pages 3 & 4)
// ==========================================
int query(int node, int l, int r, int ql, int qr)
{
    // Exact match of query range
    if (l == ql && r == qr)
    {
        return Tree[node];
    }

    int leftNode = 2 * node;
    int rightNode = 2 * node + 1;

    // Ranges for left and right children
    int ll = l;
    int lr = (l + r) / 2;
    int rl = (l + r) / 2 + 1;
    int rr = r;

    // If the entire query lies in the right child
    if (lr < ql)
    {
        return query(rightNode, rl, rr, ql, qr);
    }
    // If the entire query lies in the left child
    if (qr < rl)
    {
        return query(leftNode, ll, lr, ql, qr);
    }

    // If the query overlaps both children (Page 4 logic)

    int lresult = query(leftNode, ll, lr, ql, lr);
    int rresult = query(rightNode, rl, rr, rl, qr);

    return getGCD(lresult, rresult);
}

// ==========================================
// 3. UPDATE (From Page 4)
// ==========================================
void update(int node, int l, int r, int key, int idx)
{
    if (l == idx && r == idx)
    {
        Tree[node] = key;
        return;
    }

    int leftNode = 2 * node;
    int rightNode = 2 * node + 1;
    int mid = (l + r) / 2;

    // Note logic: idx < ((l+r)/2 + 1) which is equivalent to idx <= mid
    if (idx <= mid)
    {
        update(leftNode, l, mid, key, idx);
    }
    else
    {
        update(rightNode, mid + 1, r, key, idx);
    }

    Tree[node] = getGCD(Tree[leftNode], Tree[rightNode]);
}

// ==========================================
// MAIN FUNCTION (Demonstrating Page 1 & 2 logic)
// ==========================================
int main()
{
    // Array from Page 2 (GCD Tree Example)
    // 1-based indexing: dummy 0 at start
    int sampleArr[] = {0, 1, 5, 7, 3, 2, 9, 8, 6};
    int N = 8;

    for (int i = 1; i <= N; i++)
    {
        Arr[i] = sampleArr[i];
    }

    // Calling convention from Page 1
    // buildTree(rootNode, startingIndex, endingIndex)
    buildTree(1, 1, N);

    cout << "GCD of range [1, 4]: " << query(1, 1, N, 1, 4) << endl;
    cout << "GCD of range [6, 8]: " << query(1, 1, N, 6, 8) << endl;

    // Update index 3 to a new value (e.g., 14)
    cout << "\nUpdating index 3 to 14..." << endl;
    update(1, 1, N, 14, 3);

    cout << "New GCD of range [3, 4]: " << query(1, 1, N, 3, 4) << endl;

    return 0;
}