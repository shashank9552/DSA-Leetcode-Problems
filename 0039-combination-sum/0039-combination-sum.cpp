class Solution {
public:
    vector<vector<int>> ans;
    vector<int> curr;

    void backtrack(vector<int>& candidates, int target, int index) {

        if (target == 0) {
            ans.push_back(curr);
            return;
        }

        if (index == candidates.size() || target < 0)
            return;

        // Take current candidate
        curr.push_back(candidates[index]);
        backtrack(candidates, target - candidates[index], index);
        curr.pop_back();

        // Skip current candidate
        backtrack(candidates, target, index + 1);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

        backtrack(candidates, target, 0);
        return ans;
    }
};