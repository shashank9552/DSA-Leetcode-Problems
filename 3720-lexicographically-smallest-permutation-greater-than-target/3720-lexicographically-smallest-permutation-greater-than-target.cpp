class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // Try to construct a permutation equal to target
        // for as long as possible.
        string prefix;

        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            if (cnt[x] == 0) {
                // We cannot match target anymore.
                // We must increase at some previous position,
                // or at the current position.
                break;
            }

            prefix += target[i];
            cnt[x]--;
        }

        // Case 1: We couldn't match the whole target.
        if ((int)prefix.size() < n) {
            int pos = prefix.size();

            // Try to put the smallest character > target[pos].
            int x = target[pos] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = prefix;
                    ans += char('a' + c);
                    cnt[c]--;

                    // Fill remaining characters in ascending order.
                    for (int d = 0; d < 26; d++) {
                        while (cnt[d] > 0) {
                            ans += char('a' + d);
                            cnt[d]--;
                        }
                    }

                    return ans;
                }
            }

            // No larger character at this position.
            // Need to backtrack.
        }

        // We either matched all of target, or got stuck.
        // Reconstruct counts corresponding to the matched prefix.
        fill(cnt.begin(), cnt.end(), 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // Match target again, but keep the matched prefix.
        int matched = 0;

        while (matched < n && cnt[target[matched] - 'a'] > 0) {
            cnt[target[matched] - 'a']--;
            matched++;
        }

        // Backtrack from the last matched position.
        for (int i = matched - 1; i >= 0; i--) {
            // Put target[i] back into available characters.
            cnt[target[i] - 'a']++;

            int current = target[i] - 'a';

            // Find smallest character greater than target[i].
            for (int c = current + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);
                    cnt[c]--;

                    // Fill suffix with smallest possible characters.
                    for (int d = 0; d < 26; d++) {
                        while (cnt[d] > 0) {
                            ans += char('a' + d);
                            cnt[d]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};