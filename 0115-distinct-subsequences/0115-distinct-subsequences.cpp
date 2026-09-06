class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        vector<long long> dp(m + 1, 0);
        dp[0] = 1;

        const long long LIMIT = INT_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--) {

                if (s[i] == t[j]) {

                    if (dp[j + 1] > LIMIT - dp[j]) {
                        dp[j + 1] = LIMIT;
                    } else {
                        dp[j + 1] += dp[j];
                    }
                }
            }
        }

        return (int)dp[m];
    }
};