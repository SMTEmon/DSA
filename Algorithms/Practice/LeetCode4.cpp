#include<bits/stdc++.h>

using namespace std;
using lli = long long int;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Get to 1 Vector

        
        int size_of_vectors = nums1.size() + nums2.size();
        int size_of_nums1 = nums1.size();
        int size_of_nums2 = nums2.size();
        int idx_1 = 0, idx_2 = 0;
        vector<int> nums(size_of_vectors);

        for (int i = 0; i < size_of_vectors; i++){
            if (nums1[idx_1] < nums2[idx_2]){
                nums[i] = nums1[idx_1];
                idx_1++;
            }
            else {
                nums[i] = nums2[idx_2];
                idx_2++;
            }

            while (idx_1 < size_of )
            

        }

        for (int i = 0; i < size_of_vectors; i++){
            cout << nums[i] << " ";
        }
        cout << endl;
        return 0;
    }
};

int main(){
    Solution sol;
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    sol.findMedianSortedArrays(nums1, nums2);
}