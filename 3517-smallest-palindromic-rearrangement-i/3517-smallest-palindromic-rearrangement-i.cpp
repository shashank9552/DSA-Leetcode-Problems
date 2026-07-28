class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string firstHalf = "";
        string middle = "";

        for (int i = 0; i < 26; i++) {
            firstHalf.append(freq[i] / 2, char('a' + i));

            if (freq[i] % 2 == 1)
                middle = char('a' + i);
        }

        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        return firstHalf + middle + secondHalf;
    }
};