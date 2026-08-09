class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = maximum number of characters from the
        // suffix word2 that can be matched using word1[i...]
        vector<int> suf(n + 1, 0);

        int j = m - 1;

        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                --j;
            }

            suf[i] = m - 1 - j;
        }

        vector<int> ans;

        int pos = 0;
        bool changed = false;

        for (int i = 0; i < n && pos < m; ++i) {

            // Exact match
            if (word1[i] == word2[pos]) {
                ans.push_back(i);
                ++pos;
            }

            // Use the one allowed modification
            else if (!changed) {
                int remaining = m - pos - 1;

                // After choosing i, can we match the rest?
                if (suf[i + 1] >= remaining) {
                    ans.push_back(i);
                    ++pos;
                    changed = true;
                }
            }
        }

        if (pos == m)
            return ans;

        return {};
    }
};