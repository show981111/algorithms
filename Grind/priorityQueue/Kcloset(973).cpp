class Solution
{
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        if (k >= points.size())
            return points;
        sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b)
             { return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]); });
        points.erase(points.begin() + k, points.end());
        return points;
        // we can do
        // return vector<vector<int>> (points.begin(), points.begin() + k);
    }
};

/**
 * @brief USING A Priority Queue
 *
 */

class Solution
{
public:
    class compare
    {
    public:
        bool operator()(const vector<int> &a, const vector<int> &b)
        {
            return (a[0] * a[0] + a[1] * a[1]) > (b[0] * b[0] + b[1] * b[1]);
        }
    };
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        if (k >= points.size())
            return points;
        priority_queue<vector<int>, vector<vector<int>>, compare> pq;

        for (auto &item : points)
        {
            pq.push(move(item)); // make item invalid after this move.
        }
        vector<vector<int>> ans;
        while (k != 0)
        {
            k--;
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};
