class Solution
{
public:
    /*
    Since 1 <= nums[i] <= 1000,
    If a*b*c*d <= 1000 then all combination of a,b,c,d <= 1000
    Thus, if we came accross a subarray that are bigger,
    ex) [a,|b,c,d,e|,f,g,h]
    add the window_size, and shrink.

    ** Do i need to pull back the left? No.
    a,b,c,d,e|,f,g
    1 + 2 = 3
    If a*b*c*d*e > k, then a*b*c*d*e*f > k. Since we only count subarray, should shrink.
    In order to inlcude "a" we need to include all from "b" ~ "e". Then, it will include a*b*c*d*e, which is larger thank "k"!
    */
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        int l = 0, r = 0;
        int cnt = 0;
        int prod = 1;
        // int prevCnt = 0;
        while (r < nums.size())
        {
            prod *= nums[r++];
            while (l < r && prod >= k)
            {
                prod /= nums[l++];
            }
            // if(prod < k){
            cnt += (r - l);
            // }
        }
        return cnt;
    }
};

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