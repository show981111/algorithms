class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        // BFS (2-coloring)
        vector<int> colors(graph.size(), -1); // not assigned any color = -1
        // -2: visited, -1 : not visited, 0: color , 1 : color

        for (int i = 0; i < graph.size(); i++)
        {
            if (colors[i] != -1)
                continue;

            queue<int> q;
            q.push(i);
            int curColor = 0;
            colors[i] = -2;
            while (!q.empty())
            {
                int qSize = q.size();

                for (int j = 0; j < qSize; j++)
                {
                    int f = q.front();
                    q.pop();
                    colors[f] = curColor;

                    for (int neighbor : graph[f])
                    {
                        if (colors[neighbor] == curColor)
                            return false;
                        else if (colors[neighbor] != -1)
                            continue;
                        colors[neighbor] = -2; // visited
                        q.push(neighbor);
                    }
                }

                curColor = (curColor + 1) % 2;
            }
        }

        return true;
    }
};