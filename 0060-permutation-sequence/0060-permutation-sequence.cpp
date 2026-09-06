class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums;

        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }

        // factorial[i] = i!
        vector<int> factorial(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        // Convert k to 0-based index
        k--;

        string ans;

        for (int i = n; i >= 1; i--) {
            int blockSize = factorial[i - 1];

            int index = k / blockSize;

            ans += to_string(nums[index]);

            nums.erase(nums.begin() + index);

            k %= blockSize;
        }

        return ans;
    }
};