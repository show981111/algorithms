/**
 * Inserting an interval can be divided into two phase
 * 1. Insert
 *      Insert new interval into correct position that observes ordering
 * 2. Merge interval
 *      Merge intervals that overlaps with new interval
 *      => Using an aux container makes stuff a lot easier. No need to bookkeep complex states
 *      OR
 *      Use swap idiom just like we did in in-place remove
 *      Move useful items to before "cur" pointer then throw away all items after "cur"
 */

// Using aux space
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> res;
        bool pushed = false;
        for (int i = 0; i < intervals.size(); i++)
        {
            if (newInterval[0] <= intervals[i][0])
            {
                intervals.insert(intervals.begin() + i, newInterval);
                pushed = true;
                break;
            }
        }
        if (!pushed)
        {
            intervals.push_back(newInterval);
        }

        for (int i = 0; i < intervals.size(); i++)
        {
            if (res.empty())
                res.push_back(intervals[i]);
            else
            {
                if (res.back()[1] < intervals[i][0])
                    res.push_back(intervals[i]);
                else
                    res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
        }
        return res;
    }
};

/*
In-place merging
*/
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        bool pushed = false;
        for (int i = 0; i < intervals.size(); i++)
        {
            if (newInterval[0] <= intervals[i][0])
            {
                intervals.insert(intervals.begin() + i, newInterval);
                pushed = true;
                break;
            }
        }
        if (!pushed)
        {
            intervals.push_back(newInterval);
        }
        int cur = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[cur][1] < intervals[i][0])
            { // no overlap
                cur++;
                swap(intervals[cur], intervals[i]);
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