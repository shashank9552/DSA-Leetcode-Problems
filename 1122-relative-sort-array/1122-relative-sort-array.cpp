class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {

        vector<int> freq(1001, 0);

        for (int num : arr1)
            freq[num]++;

        vector<int> ans;

        for (int num : arr2) {
            while (freq[num] > 0) {
                ans.push_back(num);
                freq[num]--;
            }
        }

        for (int num = 0; num <= 1000; num++) {
            while (freq[num] > 0) {
                ans.push_back(num);
                freq[num]--;
            }
        }

        return ans;
    }
};