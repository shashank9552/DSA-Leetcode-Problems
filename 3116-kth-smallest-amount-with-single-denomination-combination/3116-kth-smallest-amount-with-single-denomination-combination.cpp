class Solution {
public:
    long long gcd(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }

    long long countMultiples(long long x, vector<int>& coins) {
        int m = coins.size();
        long long total = 0;

        // Inclusion-exclusion over all subsets
        for (int mask = 1; mask < (1 << m); mask++) {
            long long mult = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    mult = lcm(mult, coins[i]);

                    if (mult > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            long long cnt = x / mult;

            if (bits % 2 == 1)
                total += cnt;
            else
                total -= cnt;
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countMultiples(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};