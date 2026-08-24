class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        vector<long long> prefix(n);

        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        // If Alice takes the first n-1 stones,
        // the game ends after Bob's move.
        long long best = prefix[n - 1];

        // i represents the end of the prefix Alice can take.
        for (int i = n - 2; i >= 1; i--) {
            best = max(best, prefix[i] - best);
        }

        return (int)best;
    }
};