class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int v : nums) {
            auto ndp = dp;

            for (int cnt = 0; cnt <= 3; cnt++) {
                for (int x = 0; x < MAXX; x++) {
                    if (!dp[cnt][x]) continue;

                    for (int take = 1; take + cnt <= 3; take++) {
                        int nx = x;
                        if (take % 2 == 1)
                            nx ^= v;

                        ndp[cnt + take][nx] = true;
                    }
                }
            }

            dp.swap(ndp);
        }

        int ans = 0;
        for (bool ok : dp[3])
            if (ok) ans++;

        return ans;
    }
};