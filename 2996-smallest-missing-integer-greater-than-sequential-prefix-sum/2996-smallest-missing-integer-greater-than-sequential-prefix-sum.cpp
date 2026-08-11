class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];

        // Find the longest sequential prefix
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }

        // Store all numbers in the array
        unordered_set<int> st(nums.begin(), nums.end());

        // Find the smallest missing number >= sum
        while (st.count(sum)) {
            sum++;
        }

        return sum;
    }
};