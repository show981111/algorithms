class Solution
{
public:
    /**
     * Subsets.. here definition of subset is by index not the element.
     * Use map to look up any element that is +-k so that we can avoid putting the element.
     */
    void solve(vector<int> &nums, int k, unordered_map<int, int> &cur, int curIndex, int &ans)
    {
        if (curIndex == nums.size())
        {
            if (!cur.empty())
            {
                ans++;
            }
            return;
        }
        solve(nums, k, cur, curIndex + 1, ans);

        int num = nums[curIndex];
        if (cur.count(num - k) == 0 && cur.count(num + k) == 0)
        {
            cur[num]++;
            solve(nums, k, cur, curIndex + 1, ans);
            cur[num]--;
            if (cur[num] == 0)
                cur.erase(num);
        }
    }
    int beautifulSubsets(vector<int> &nums, int k)
    {
        int n = 0;
        unordered_map<int, int> cur;
        solve(nums, k, cur, 0, n);
        return n;
    }
};

class Solution
{
    /**
     * If the definition of the subset is by element,
     * we can use map to remove the duplicates!
     * Back track by how many elements we include.
     * EX) if there is x number of 3,
     * we iterate 0 ~ x number of 3.
     */
public:
    void solve(unordered_map<int, int>::iterator end, int k, unordered_map<int, int> &cur, unordered_map<int, int>::iterator curIter, int &ans)
    {
        if (curIter == end)
        {
            if (!cur.empty())
            {
                ans++;
            }
            return;
        }
        // cout << curIter->first << " " << curIter->second << endl;
        for (int i = 0; i <= curIter->second; i++)
        {
            if (i == 0)
                solve(end, k, cur, next(curIter), ans);
            else
            {
                int num = curIter->first;
                if (cur.count(num - k) == 0 && cur.count(num + k) == 0)
                {
                    cur[num] += i;
                    solve(end, k, cur, next(curIter), ans);
                    cur.erase(num);
                }
            }
        }
    }
    int beautifulSubsets(vector<int> &nums, int k)
    {
        int n = 0;
        unordered_map<int, int> cur;
        unordered_map<int, int> freq;
        for (int num : nums)
            freq[num]++;
        solve(freq.end(), k, cur, freq.begin(), n);
        return n;
    }
};

/*
6 3 5 6, k = 2
6
3
5
6 3
6 6
6 5
6 3 6
6 5 6
*/
