class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // Empty list or single node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Find length and tail
        int n = 1;
        ListNode* tail = head;

        while (tail->next != nullptr) {
            tail = tail->next;
            n++;
        }

        // No need for full rotations
        k %= n;

        if (k == 0) {
            return head;
        }

        // Make the list circular
        tail->next = head;

        // Find the new tail
        int steps = n - k;
        ListNode* newTail = head;

        for (int i = 1; i < steps; i++) {
            newTail = newTail->next;
        }

        // New head is after the new tail
        ListNode* newHead = newTail->next;

        // Break the circle
        newTail->next = nullptr;

        return newHead;
    }
};