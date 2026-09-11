class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        // Count available copies of each digit
        vector<int> freq(10, 0);

        for (int d : digits) {
            freq[d]++;
        }

        int ans = 0;

        // Check every 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Must be even
            if (num % 2 != 0) {
                continue;
            }

            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            // Check whether required digits are available
            vector<int> need(10, 0);

            need[a]++;
            need[b]++;
            need[c]++;

            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                ans++;
            }
        }

        return ans;
    }
};