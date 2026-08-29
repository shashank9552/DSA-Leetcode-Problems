class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store value and original index.
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value.
        sort(arr.begin(), arr.end());

        vector<int> ans(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Find the group where consecutive values differ
            // by at most limit.
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Collect original indices of this group.
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Values are already sorted because arr is sorted.
            // Put the smallest values at the smallest indices.
            sort(indices.begin(), indices.end());

            for (int i = start; i <= end; i++) {
                ans[indices[i - start]] = arr[i].first;
            }

            start = end + 1;
        }

        return ans;
    }
};