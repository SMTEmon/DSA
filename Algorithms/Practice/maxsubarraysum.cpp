#include<bits/stdc++.h>

using namespace std;
using lli = long long int;

lli findCrossMax(vector<lli> &arr, lli l, lli mid, lli r){
    lli left_max = INT_MIN, sum = 0;

    for (lli i = mid; i >= l; i--){
        sum += arr[i];
        left_max = max(left_max, sum);
    }

    lli right_max = INT_MIN; sum = 0;

    for (lli i = mid + 1; i <= r; i++){
        sum += arr[i];
        right_max = max(right_max, sum);
    }

    return left_max + right_max;
}

lli solve(vector<lli> &arr, lli l, lli r){
    if (l == r) return arr[l];

    lli mid = l + (r - l) / 2;

    lli left_max_sum = solve(arr, l, mid);
    lli right_max_sum = solve(arr, mid + 1, r);
    lli cross_max_sum = findCrossMax(arr, l, mid, r);

    return max(left_max_sum, max(right_max_sum, cross_max_sum));
}

int main() {
    struct TestCase {
        string description;
        vector<lli> arr;
        lli expected;
    };

    vector<TestCase> tests = {
        {"Standard (Mixed Pos/Neg)", {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6},
        {"All Positive Numbers", {1, 2, 3, 4, 5}, 15},
        {"All Negative Numbers", {-5, -2, -8, -1, -4}, -1},
        {"Single Element (Positive)", {7}, 7},
        {"Single Element (Negative)", {-3}, -3},
        {"Single Element (Zero)", {0}, 0},
        {"Two Elements (Both Positive)", {3, 4}, 7},
        {"Two Elements (Mixed)", {-2, 5}, 5},
        {"Two Elements (Both Negative)", {-4, -1}, -1},
        {"Crossing Middle Subarray", {2, 3, -1, 4, -2}, 8},
        {"64-bit Large Values", {1000000000LL, 2000000000LL, -500000000LL}, 3000000000LL},
        {"Zeros and Negatives", {0, -2, 0, 3, -1, 4, 0, -5}, 6}
    };

    cout << "=== Running Maximum Subarray Sum Test Cases ===\n\n";
    int caseNum = 1;
    for (auto &t : tests) {
        lli n = t.arr.size();
        lli result = solve(t.arr, 0, n - 1);
        
        cout << "Test #" << caseNum++ << ": " << t.description << "\n";
        cout << "  Input:    [";
        for (size_t i = 0; i < t.arr.size(); i++) {
            cout << t.arr[i] << (i + 1 < t.arr.size() ? ", " : "");
        }
        cout << "]\n";
        cout << "  Output:   " << result << "\n";
        cout << "  Expected: " << t.expected << "\n";
        cout << "  Status:   " << (result == t.expected ? "PASSED" : "FAILED") << "\n\n";
    }

    return 0;
}
