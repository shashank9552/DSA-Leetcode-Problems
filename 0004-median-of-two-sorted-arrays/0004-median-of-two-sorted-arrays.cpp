class Solution {
public:
    double getKth(vector<int>& A, int aStart,
                  vector<int>& B, int bStart, int k) {

        // If A is exhausted
        if (aStart >= A.size())
            return B[bStart + k - 1];

        // If B is exhausted
        if (bStart >= B.size())
            return A[aStart + k - 1];

        // Base case
        if (k == 1)
            return min(A[aStart], B[bStart]);

        int aMid = INT_MAX;
        int bMid = INT_MAX;

        if (aStart + k / 2 - 1 < A.size())
            aMid = A[aStart + k / 2 - 1];

        if (bStart + k / 2 - 1 < B.size())
            bMid = B[bStart + k / 2 - 1];

        if (aMid < bMid) {
            return getKth(A, aStart + k / 2, B, bStart, k - k / 2);
        } else {
            return getKth(A, aStart, B, bStart + k / 2, k - k / 2);
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        int left = (m + n + 1) / 2;
        int right = (m + n + 2) / 2;

        return (getKth(nums1, 0, nums2, 0, left) +
                getKth(nums1, 0, nums2, 0, right)) / 2.0;
    }
};