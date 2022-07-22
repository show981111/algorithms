class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });

        // this is O(N^2) because vector erase is O(N)
        // for(int i = 1; i < intervals.size(); i++){
        //     if(intervals[i-1][1] >= intervals[i][0]){
        //         intervals[i-1][1] = max(intervals[i-1][1], intervals[i][1]);
        //         intervals.erase(intervals.begin() + i);
        //         i--;
        //     }
        // }

        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++)
        {
            if (res.back()[1] >= intervals[i][0])
            {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
            else
            {
                res.push_back(intervals[i]);
            }
        }
        return res;

        /**
         * @brief other method
         * Saving more memory. But still worst case O(N^2) because
         */
        int mergeStart = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            mergeStart = i;
            while (i < intervals.size() && intervals[mergeStart - 1][1] >= intervals[i][0])
            {
                intervals[mergeStart - 1][1] = max(intervals[mergeStart - 1][1], intervals[i][1]);
                i++;
            }
            intervals.erase(intervals.begin() + mergeStart, intervals.begin() + i);
            i = mergeStart;
        }

        return intervals;
    }
};