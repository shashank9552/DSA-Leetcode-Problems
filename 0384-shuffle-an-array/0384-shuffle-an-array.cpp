class Solution {
private:
    vector<int> original;

public:
    Solution(vector<int>& nums) {
        original = nums;
    }

    vector<int> reset() {
        return original;
    }

    vector<int> shuffle() {

        vector<int> shuffled = original;
        int n = shuffled.size();

        for (int i = 0; i < n; i++) {
            int j = i + rand() % (n - i);
            swap(shuffled[i], shuffled[j]);
        }

        return shuffled;
    }
};