class Solution {
public:
    int arrayNesting(vector<int>& nums) {

        int ans = 0;

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] == -1)
                continue;

            int count = 0;
            int curr = i;

            while (nums[curr] != -1) {

                int next = nums[curr];
                nums[curr] = -1;
                curr = next;
                count++;
            }

            ans = max(ans, count);
        }

        return ans;
    }
};