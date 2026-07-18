class Solution {
public:
    int nextIndex(vector<int>& nums, bool forward, int cur) {
        bool dir = nums[cur] > 0;

        if (dir != forward)
            return -1;

        int n = nums.size();
        int next = ((cur + nums[cur]) % n + n) % n;

        if (next == cur)
            return -1;

        return next;
    }

    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {

            if (nums[i] == 0)
                continue;

            bool forward = nums[i] > 0;

            int slow = i;
            int fast = i;

            while (true) {

                slow = nextIndex(nums, forward, slow);
                if (slow == -1)
                    break;

                fast = nextIndex(nums, forward, fast);
                if (fast == -1)
                    break;

                fast = nextIndex(nums, forward, fast);
                if (fast == -1)
                    break;

                if (slow == fast)
                    return true;
            }

            int cur = i;

            while (true) {

                bool dir = nums[cur] > 0;

                if (dir != forward || nums[cur] == 0)
                    break;

                int nxt = ((cur + nums[cur]) % n + n) % n;

                nums[cur] = 0;

                if (nxt == cur)
                    break;

                cur = nxt;
            }
        }

        return false;
    }
};