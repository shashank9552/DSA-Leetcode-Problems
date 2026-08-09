class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1 || head == nullptr)
            return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* groupPrev = &dummy;

        while (true) {
            // Find the kth node
            ListNode* kth = groupPrev;

            for (int i = 0; i < k && kth != nullptr; i++) {
                kth = kth->next;
            }

            // Fewer than k nodes remain
            if (kth == nullptr)
                break;

            ListNode* groupNext = kth->next;

            // Reverse the current group
            ListNode* prev = groupNext;
            ListNode* curr = groupPrev->next;

            while (curr != groupNext) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // Connect previous part to reversed group
            ListNode* oldGroupStart = groupPrev->next;
            groupPrev->next = kth;

            // Move groupPrev to the end of reversed group
            groupPrev = oldGroupStart;
        }

        return dummy.next;
    }
};