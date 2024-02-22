class Solution
{
public:
    using Pair = pair<int, int>; // trusting(outdegree), trustedBy(indegree)
    int findJudge(int n, vector<vector<int>> &trust)
    {
        vector<Pair> degrees(n + 1);

        for (vector<int> &v : trust)
        {
            degrees[v[0]].first++;  // trusting other person
            degrees[v[1]].second++; // trusted by other person
        }
        for (int i = 1; i <= n; i++)
        {
            if (degrees[i].first == 0 && degrees[i].second == n - 1)
            {
                return i;
            }
        }
        return -1;
    }
};