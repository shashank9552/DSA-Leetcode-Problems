class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        // last[c] = dp value before the previous occurrence of c
        vector<long long> last(26, 0);

        // dp includes the empty subsequence
        long long dp = 1;

        for (char c : s) {
            int x = c - 'a';

            long long newDp = (2 * dp % MOD - last[x] + MOD) % MOD;

            last[x] = dp;
            dp = newDp;
        }

        // Remove the empty subsequence
        return (dp - 1 + MOD) % MOD;
    }
};