/**
 * @brief Finding a Reverse Pair...
 * How many pairs are not in a sorted order?
 * We can utilized some sorting algo...
 * MERGE SORT!
 *
 * https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22
 */

class Solution
{
public:
    void merge(vector<int> &nums, int L, int M, int R, int &count)
    {
        vector<int> temp(R - L + 1);
        int index = 0;
        int i = L, j = M + 1;
        int curJ = M + 1, curI = L;
        // count
        while (curJ <= R && curI <= M)
        {
            if (nums[curI] > 2 * (long)nums[curJ])
            {
                // cout << nums[curI] << " " <<nums[curJ]  << endl;
                count += (M - curI + 1);
                curJ++;
            }
            else
                curI++;
        }
        // then sort
        while (i <= M || j <= R)
        {
            if (i >= M + 1)
            {
                temp[index++] = nums[j++];
            }
            else if (j >= R + 1)
            {
                temp[index++] = nums[i++];
            }
            else
            {
                if (nums[i] > nums[j])
                    temp[index++] = nums[j++];
                else
                {
                    temp[index++] = nums[i++];
                }
            }
        }
        copy(temp.begin(), temp.end(), nums.begin() + L);
    }
    void mergeSort(vector<int> &nums, int L, int R, int &count)
    {
        if (L >= R)
            return;
        int mid = L + (R - L) / 2;
        mergeSort(nums, L, mid, count);
        mergeSort(nums, mid + 1, R, count);
        merge(nums, L, mid, R, count);
    }
    int reversePairs(vector<int> &nums)
    {
        int c = 0;
        mergeSort(nums, 0, nums.size() - 1, c);
        // for(auto x : nums)
        //     cout << x << " ";
        return c;
    }
};