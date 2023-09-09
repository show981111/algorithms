/**
 * KEY IDEA: Longest Path in Tree = Diameter
 * Diameter = 1 + sum of top 2 children's depth
 * No need to do dfs from all nodes, just do it from the ROOT,
 * Calculate Diameter from all nodes, get MAX!
 *
 * Visited check in Tree
 * 1) If parent and child are mutually connected
 * : Just check parent != curNode's child, since parent is in curNode's child.
 * 2) If parent -> child but parent is not in child's children vector(one way connected)
 * : No need to check anything. It will just go downwards.
 *
 *
 * Another Idea using BFS with TopSort
 * https://leetcode.com/problems/longest-path-with-different-adjacent-characters/solutions/3045253/bfs-solution-c-with-explanation-beats-99/
 */

class Solution
{
public:
    int getLongestPathFromCur(int &ans, vector<vector<int>> &graph, int curNode, string &idToChar)
    {
        int maxLengthStartingFromCur = 0;
        int maxChild = -1;

        int secondCandidate = -1;
        int secondMaxChild = -1;

        for (int child : graph[curNode])
        {
            int l = getLongestPathFromCur(ans, graph, child, idToChar);
            if (idToChar[curNode] != idToChar[child])
            {
                if (maxLengthStartingFromCur < l)
                {
                    secondCandidate = maxLengthStartingFromCur;
                    secondMaxChild = maxChild;
                    maxLengthStartingFromCur = l;
                    maxChild = child;
                }
                if (secondCandidate < l && child != maxChild)
                {
                    secondCandidate = l;
                    secondMaxChild = child;
                }
            }
        }
        if (secondCandidate != -1)
        {
            ans = max(ans, secondCandidate + maxLengthStartingFromCur + 1); // adding itself
        }
        else
            ans = max(ans, maxLengthStartingFromCur + 1);
        return maxLengthStartingFromCur + 1;
    }
    int longestPath(vector<int> &parent, string s)
    {
        vector<vector<int>> graph(parent.size());
        for (int i = 1; i < parent.size(); i++)
        {
            graph[parent[i]].push_back(i);
        }
        int ans = 0;
        getLongestPathFromCur(ans, graph, 0, s);
        return ans;
    }
};