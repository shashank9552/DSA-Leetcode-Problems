class Solution {
public:
    const long long LIM = 1000001;
    vector<long long> fact;

    long long countWays(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = fact[total];

        for (int x : cnt)
            ans /= fact[x];

        return min(ans, LIM);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);

        string mid = "";

        int halfLen = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            halfLen += half[i];

            if (freq[i] & 1)
                mid.push_back(char('a' + i));
        }

        fact.assign(halfLen + 1, 1);

        for (int i = 1; i <= halfLen; i++) {
            fact[i] = min(LIM, fact[i - 1] * i);
        }

        if (countWays(half) < k)
            return "";

        string left = "";

        for (int pos = 0; pos < halfLen; pos++) {

            for (int c = 0; c < 26; c++) {

                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};