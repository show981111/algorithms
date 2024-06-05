class Solution
{
public:
    /*
    Alice: Upper left, Bob: Lower right
    Select all pairs from the points that we can form this -> O(N^2)
    When we fix Alice to (a,b), Bob should be
    (x >=a, y <=b) -> Two standards for sorting... PQ? But we need to consider that
    the other point cannot be in the box! -> Just iterate
    */
    bool inside(vector<int> &a, vector<int> &b, vector<int> &in)
    {
        return a[0] <= in[0] && in[0] <= b[0] && a[1] >= in[1] && in[1] >= b[1];
    }
    int numberOfPairs(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b)
             {
            if(a[0] > b[0]) return true;
            else if(a[0] == b[0]) return a[1] < b[1];
            return false; });
        int pairs = 0;
        for (int i = 1; i < points.size(); i++)
        {
            // make i as an Alice
            vector<vector<int>> bobs;
            for (int j = i - 1; j >= 0; j--)
            {
                // iterate possible bobs
                // find if there is a point (a,b) such that
                // points[i][0] <= a <= points[j][0] && points[j][1] <= b <= points[i][1]

                // cannot be a bob since it is not in the Lower position
                if (points[j][1] > points[i][1])
                    continue;
                bool conflict = false;
                for (int k = 0; k < bobs.size(); k++)
                {
                    if (inside(points[i], points[j], bobs[k])) // only a possible bob can be a candidate for the insider.
                    {
                        conflict = true;
                        break; // reject j as bob
                    }
                }
                if (!conflict)
                {
                    bobs.push_back(points[j]);
                }
            }
            pairs += bobs.size();
        }
        return pairs;
    }
    /**
     * Alternative without using a inner for loop for finding out the insider
     */

    int numberOfPairs(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b)
             {
            if(a[0] > b[0]) return true;
            else if(a[0] == b[0]) return a[1] < b[1];
            return false; });
        int pairs = 0;
        for (int i = 1; i < points.size(); i++)
        {
            // make i as an Alice
            int minY = INT_MIN;
            for (int j = i - 1; j >= 0; j--)
            {
                // iterate possible bobs

                // If it is lower than Alice and
                // minY <= points[i][1] since minY is the accepted bob position
                // so if points[j][1] <= minY, points[j][1] <= minY <= points[i][1]
                // Also, the x-position of minY (preciously accepted bob position) is
                // points[i][0](Alice) <= minY-x-pos <= points[j][1] since it is ordered.
                // Thus, points[j][1] <= minY <= points[i][1] + points[i][0](Alice) <= minY-x-pos <= points[j][1] Gives us there is a point in the bos that points[j] and points[i] creates
                if (points[j][1] <= points[i][1] && points[j][1] > minY)
                {
                    pairs++;
                    minY = points[j][1];
                }
            }
        }
        return pairs;
    }
};
