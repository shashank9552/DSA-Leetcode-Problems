class Solution {
public:
    bool isMonotonic(vector<int>& nums) {

        int direction = 0; // 0 = unknown, 1 = increasing, -1 = decreasing

        for (int i = 1; i < nums.size(); i++) {

            if (nums[i] > nums[i - 1]) {

                if (direction == -1)
                    return false;

                direction = 1;
            }
            else if (nums[i] < nums[i - 1]) {

                if (direction == 1)
                    return false;

                direction = -1;
            }
        }

        return true;
    }
};