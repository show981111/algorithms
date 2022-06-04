class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        const int N = nums.size();

        int count = 0;
        unsigned long cur = 1;
        int start = 0;
        for (int end = 0; end < N; end++)
        {
            if (nums[end] >= k)
            {                    // 0 possibility of being an answer if it contains num[end]
                start = end + 1; // so the window should pass this element
                cur = 1;         // reset cur
                continue;
            }

            cur *= nums[end]; // add nums[end] to window
            while (start <= end && cur >= k)
            { // shrink the window until the window is smaller than k
                cur /= nums[start++];
            }
            count += end - start + 1; // all window inside this range is smaller than k
            // ex) 20 [2 3 4] 5, k = 30, 2*3*4, 3*4, 4 => so total 3 combinations
            // this does not overcount because it contains nums[end], which makes it unique
            // Window size is maintained to be a maxSize, because it stops shrinknig right after
            // when it goes under k
        }
        return count;
    }
};

// 1 2 3 4 5 , ws = 3, N - ws = 3
//