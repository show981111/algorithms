/**
 * @brief Using map and set to count!
 * Encode multiple integers into a string to use it in map!
 *
 * O(N^3) to O(N^2)
 * If I calculate a line for two points, then if we iterate all points and count
 * how many points are in that line -> O(N^3)
 *
 * For point I, calculate slope for all other points J.
 * If slope is the same, add them to the map and increase the count.
 * Since all line contains point I, if the slope is the same, should be on the same line!
 */

class Solution
{
public:
    struct line
    {
        int a;
        int b;
        int c;
    };
    string encodeThreeNums(int a, int b, int c)
    {
        return to_string(a) + "_" + to_string(b) + "_" + to_string(c);
    }
    string encodeTwoNums(vector<int> &v)
    {
        return to_string(v[0]) + "_" + to_string(v[1]);
    }
    int maxPoints(vector<vector<int>> &points)
    {
        // O(N*N)
        unordered_map<int, int> rowCounter;
        unordered_map<int, int> colCounter;
        unordered_map<string, unordered_set<string>> lines;
        int maxPoints = 0;
        for (auto &v : points)
        {
            maxPoints = max(maxPoints, max(++colCounter[v[0]], ++rowCounter[v[1]]));
        }
        for (int i = 0; i < points.size(); i++)
        {
            for (int j = i + 1; j < points.size(); j++)
            {
                if (points[i][0] == points[j][0] || points[i][1] == points[j][1])
                    continue;
                int a = points[i][1] - points[j][1];
                int b = -points[i][0] + points[j][0];
                int c = (points[i][0] - points[j][0]) * points[i][1] - (points[i][1] - points[j][1]) * points[i][0];
                int g = gcd(gcd(a, b), c);
                string encoded_line = encodeThreeNums(a / g, b / g, c / g);
                lines[encoded_line].insert(encodeTwoNums(points[i]));
                lines[encoded_line].insert(encodeTwoNums(points[j]));
                maxPoints = max((unsigned long)maxPoints, lines[encoded_line].size());
            }
        }

        return maxPoints;
    }
};