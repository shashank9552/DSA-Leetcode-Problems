class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {

        int n = s.size();

        vector<int> prefixCnt(n + 1, 0);
        vector<long long> prefixSum(n + 1, 0);

        vector<int> digits;
        digits.reserve(n);

        for (int i = 0; i < n; i++) {
            prefixCnt[i + 1] = prefixCnt[i];
            prefixSum[i + 1] = prefixSum[i];

            if (s[i] != '0') {
                prefixCnt[i + 1]++;
                prefixSum[i + 1] += s[i] - '0';
                digits.push_back(s[i] - '0');
            }
        }

        int m = digits.size();

        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        // prefix hash of non-zero digits
        vector<long long> prefixValue(m + 1, 0);
        for (int i = 0; i < m; i++) {
            prefixValue[i + 1] = (prefixValue[i] * 10 + digits[i]) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {

            int l = q[0];
            int r = q[1];

            long long digitSum = prefixSum[r + 1] - prefixSum[l];

            int left = prefixCnt[l];
            int right = prefixCnt[r + 1];

            int len = right - left;

            if (len == 0) {
                ans.push_back(0);
                continue;
            }

            long long x =
                (prefixValue[right] -
                 prefixValue[left] * pow10[len] % MOD +
                 MOD) % MOD;

            ans.push_back((x * (digitSum % MOD)) % MOD);
        }

        return ans;
    }
};