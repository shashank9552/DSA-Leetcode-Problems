class Solution {
public:
    int longestWPI(vector<int>& hours) {

        unordered_map<int, int> firstIndex;

        int prefix = 0;
        int ans = 0;

        for (int i = 0; i < hours.size(); i++) {

            if (hours[i] > 8)
                prefix++;
            else
                prefix--;

            if (prefix > 0)
                ans = i + 1;
            else {
                if (firstIndex.count(prefix - 1))
                    ans = max(ans, i - firstIndex[prefix - 1]);
            }

            if (!firstIndex.count(prefix))
                firstIndex[prefix] = i;
        }

        return ans;
    }
};