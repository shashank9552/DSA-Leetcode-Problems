class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<long long> dp(n, 0);

        // Starting cell
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Obstacle blocks all paths
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                }
                else if (j > 0) {
                    // From above + from left
                    dp[j] += dp[j - 1];
                }
            }
        }

        return (int)dp[n - 1];
    }
};