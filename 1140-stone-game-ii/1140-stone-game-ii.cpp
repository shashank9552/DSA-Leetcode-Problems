class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = sum of piles from i to n-1
        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][M] = maximum stones current player can get
        // starting at i with M
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int M = n; M >= 1; --M) {

                // Can take everything remaining
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                int best = 0;

                for (int x = 1; x <= 2 * M && i + x <= n; ++x) {
                    int nextM = max(M, x);

                    int opponent = dp[i + x][nextM];

                    int current = suffix[i] - opponent;

                    best = max(best, current);
                }

                dp[i][M] = best;
            }
        }

        return dp[0][1];
    }
};