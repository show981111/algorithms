class Solution
{
public:
    int numberOfSubarrays(vector<int> &nums, int k)
    {
        int cnt = 0;
        int l = 0, r = 0;
        int oddCount = 0;
        int prevCnt = 0;
        // 2 2 2 1 2 1 2 1 1
        while (r < nums.size())
        {
            if (nums[r] % 2 == 1)
            {
                oddCount++;
            }
            else
            { // if curNumber is Even, it can make a subarray by extending previous subarrays.
                // So add previous Cnt
                cnt += prevCnt;
            }
            if (oddCount == k)
            {
                int tempCnt = cnt;
                while (l < nums.size())
                { // Shrink L as far as we can, and count
                    cnt++;
                    if (nums[l++] % 2 == 1)
                    {               // Now L is next to Odd
                        oddCount--; // decrease Odd -> now if r hits next Odd,
                        // it will not include this Odd, so no dup! This odd serves as a boundary.
                        //  cuz if the other subarray includes this one, it will go over K
                        break;
                    }
                }
                prevCnt = cnt - tempCnt;
            }
            r++;
        }
        return cnt;
    }
};