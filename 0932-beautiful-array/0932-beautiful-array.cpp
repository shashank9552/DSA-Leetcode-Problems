class Solution {
public:
    vector<int> beautifulArray(int n) {

        vector<int> ans = {1};

        while (ans.size() < n) {

            vector<int> temp;

            // Generate odd numbers
            for (int x : ans) {
                if (2 * x - 1 <= n)
                    temp.push_back(2 * x - 1);
            }

            // Generate even numbers
            for (int x : ans) {
                if (2 * x <= n)
                    temp.push_back(2 * x);
            }

            ans = temp;
        }

        return ans;
    }
};