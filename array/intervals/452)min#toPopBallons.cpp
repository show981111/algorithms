class Solution
{
public:
    /**
    1,6 2,8 7,12 10,16
    1,6 7,12
    Balloons are represented as an interval.
    Multiple ballons can be popped if they overlap.
    Observation:
        If two intervals overlap, arrow should be thrown to smaller interval.
        EX) [1,5], [3,8] => overlaps at [3,5]. So arrow should be thrown at
            [max(start points), min(end points)]
        So we can merge intervals, but should shorten the interval to the overlaping interval.

    Now the goal is to create shortest array after merging all intervals.
    Merging Intervvals => Sorting
    */
    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });

        int idx = 0;
        int dot = 0;
        for (int i = 1; i < points.size(); i++)
        {
            if (points[idx][1] >= points[i][0])
            {
                // overlaps! can burst with one dot
                points[idx][1] = min(points[idx][1], points[i][1]);
                // should set it to min since points[i] will not burst if we go over points[i][1]
            }
            else
            {
                // not overlap!
                idx++;
                swap(points[idx], points[i]);
                // Now i_th is at the top of idx
            }
        }
        return idx + 1;
    }
};