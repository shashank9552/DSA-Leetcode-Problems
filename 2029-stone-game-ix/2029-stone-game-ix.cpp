class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // If there are no remainder-1 or remainder-2 stones,
        // Alice cannot make a winning move.
        if (cnt[1] == 0 && cnt[2] == 0)
            return false;

        // If cnt[0] is even, Alice can win whenever both
        // types 1 and 2 exist.
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // cnt[0] is odd.
        // Alice wins if one side has at least 3 more stones
        // than the other.
        return abs(cnt[1] - cnt[2]) > 2;
    }
};