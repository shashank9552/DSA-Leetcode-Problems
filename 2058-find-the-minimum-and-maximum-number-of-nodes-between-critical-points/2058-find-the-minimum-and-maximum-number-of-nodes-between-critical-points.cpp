class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (head == nullptr || head->next == nullptr ||
            head->next->next == nullptr) {
            return ans;
        }

        int first = -1;
        int prevCritical = -1;
        int minDist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next = curr->next;

        int pos = 1;

        while (next != nullptr) {

            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (isCritical) {

                if (first == -1) {
                    // First critical point
                    first = pos;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - prevCritical);
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = next;
            next = next->next;

            pos++;
        }

        // Need at least two critical points.
        if (first == -1 || first == prevCritical) {
            return ans;
        }

        // Maximum distance is between first and last critical point.
        int maxDist = prevCritical - first;

        return {minDist, maxDist};
    }
};