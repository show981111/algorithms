/**
 * In-place merging.
 *
 * Keep a "cur" pointer, which represents that 0 ~ cur elements are non-overlapping intervals
 * If we see something that does not overlap with intervals[cur], than we increase cur pointer and
 * swap that interval into 0 ~ cur.
 * Otherwise, we just expanding the endpoint of the last interval of 0 ~ cur
 */

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });

        int cur = 0;

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[cur][1] < intervals[i][0])
            {
                cur++;
                swap(intervals[i], intervals[cur]);
            }
            else
            {
                intervals[cur][1] = max(intervals[cur][1], intervals[i][1]);
            }
        }

        intervals.erase(intervals.begin() + cur + 1, intervals.end());
        return intervals;
    }
};