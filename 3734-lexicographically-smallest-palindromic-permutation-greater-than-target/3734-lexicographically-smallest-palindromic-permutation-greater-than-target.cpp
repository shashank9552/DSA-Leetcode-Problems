class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        // A palindrome can have at most one odd-frequency character.
        int mid = -1;

        for (int c = 0; c < 26; c++) {
            if (cnt[c] % 2) {
                if (mid != -1) {
                    return "";
                }
                mid = c;
            }
        }

        // Counts for the first half.
        vector<int> halfCnt(26);

        for (int c = 0; c < 26; c++) {
            halfCnt[c] = cnt[c] / 2;
        }

        string t = target.substr(0, m);

        /*
         * Try target's first half exactly.
         */
        vector<int> rem = halfCnt;
        bool exact = true;

        for (char c : t) {
            if (rem[c - 'a'] == 0) {
                exact = false;
                break;
            }

            rem[c - 'a']--;
        }

        if (exact) {
            string candidate = build(t, mid, n);

            // If the palindrome made from exactly t is already
            // greater than target, it is automatically the answer.
            if (candidate > target) {
                return candidate;
            }
        }

        /*
         * Find the smallest half strictly greater than t.
         *
         * We try to increase the rightmost possible position.
         */
        for (int pos = m - 1; pos >= 0; pos--) {
            vector<int> available = halfCnt;

            // The prefix before pos must exactly equal t.
            bool ok = true;

            for (int i = 0; i < pos; i++) {
                int c = t[i] - 'a';

                if (available[c] == 0) {
                    ok = false;
                    break;
                }

                available[c]--;
            }

            if (!ok) {
                continue;
            }

            int current = t[pos] - 'a';

            // Increase this position by the smallest possible amount.
            for (int c = current + 1; c < 26; c++) {
                if (available[c] == 0) {
                    continue;
                }

                string left = t.substr(0, pos);
                left += char('a' + c);

                available[c]--;

                // Complete the left half as small as possible.
                for (int d = 0; d < 26; d++) {
                    while (available[d] > 0) {
                        left += char('a' + d);
                        available[d]--;
                    }
                }

                return build(left, mid, n);
            }
        }

        return "";
    }

private:
    string build(const string& left, int mid, int n) {
        string ans = left;

        if (n % 2 == 1) {
            ans += char('a' + mid);
        }

        for (int i = (int)left.size() - 1; i >= 0; i--) {
            ans += left[i];
        }

        return ans;
    }
};