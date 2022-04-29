#include <vector>

using namespace std;

// O(V+E) -> BFS == O(V^2) --> Adj Mat

class Solution
{
public:
    int findCircleNum(vector<vector<int> > &isConnected)
    {
        int totalProvinces = 0;
        vector<bool> visited(isConnected.size(), false);
        queue<int> q;

        for (int i = 0; i < isConnected.size(); i++)
        {
            if (!visited[i])
            { // if not visited, start bfs
                totalProvinces++;
                q.push(i);
                visited[i] = true;
                while (!q.empty())
                {
                    int cur = q.front();
                    q.pop();

                    for (int j = 0; j < isConnected[cur].size(); j++)
                    {
                        if (!visited[j] && isConnected[cur][j])
                        {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }
            }
        }
        return totalProvinces;
    }
};